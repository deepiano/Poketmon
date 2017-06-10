#include "everymonscatch.h"

EveryMonsCatch::EveryMonsCatch()
{
    algNum=2;
}

QVector<QString> EveryMonsCatch::FindRoute()
{
    QVector<int> catch_order;
    make_all_route(catch_order);

    QVector<QString> toRet;
    cout << "<Best Route>" << endl;
    for (int i = 0; i < best_route.route.size(); ++i)
        cout << best_route.route[i].index << " ";
    cout << endl;
    cout<<"Caught pokemon: ";
    for(int i=0;i<catch_order.size();i++)
    {
        cout<<catch_order[i]<<" ";
    }
    cout<<endl;
    cout << "Best Time : " << best_route.time << endl;
    QString temp,q,r,s,t;
    for (int i = 0; i < best_route.route.size(); ++i)
    {
        temp=QString("%1").arg(best_route.route[i].index);
        q.append(temp);
        q.append(" ");
    }
    temp=QString("%1").arg(best_route.time);
    r=temp;
    best_route.num_catch_poketmon=catch_order.size();
    temp=QString("%1").arg(best_route.num_catch_poketmon);
    s=temp;
    for(int i=0;i<catch_order.size();i++)
    {
        temp=QString("%1").arg(catch_order[i]);
        t.append(temp);
        t.append(" ");
    }
    toRet.push_back(q);
    toRet.push_back(r);
    toRet.push_back(s);
    toRet.push_back(t);

    return toRet;
}

void EveryMonsCatch::SetGraph(GraphType *gr)
{
    g=gr;
}

void EveryMonsCatch::SetProblem(QVector<int> data)
{
    this->map_of_id_to_node_index_list = g->getMap();
    this->pStop_node_index_list = map_of_id_to_node_index_list[POKETSTOP_ID];
    this->best_route.time = 9999;
}


void EveryMonsCatch::determine_next_node(bool visited[],NodeType& node,QVector<int> distList,QVector<int> nodeList,int num_pBall,int mustGoPStop)
{
    QVector<int> tempList;
    NodeType pStopsInCandidate;
    search_nodes_by_id(POKETSTOP_ID,tempList);
    if(num_pBall<=0)//포켓스탑 가는 기준 주의!!포켓스탑으로 목적지를 정하는 함수와 포켓몬으로 정하는 함수 따로 만들기.
    {//포켓볼이 모자란 상황이므로 여기서는 무조건 포켓스탑으로 가게 한다.
        for(int i=0;i<nodeList.size();i++)
        {
            if(find(tempList.begin(),tempList.end(),nodeList[i])!=tempList.end())
            {
                pStopsInCandidate=g->getNodeByIndex(nodeList[i]);
            }

        }
        node=pStopsInCandidate;
    }
    else
    {
        int min=distList[0];
        for(int i=0;i<distList.size();i++)
        {
            if((distList[i]<min)&&(visited[i]==false))
            {
                min=distList[i];
                node=g->getNodeByIndex(i);
            }
        }
    }

}

void EveryMonsCatch::greedy(QVector<NodeType>& sol, bool visited[], int time, bool poketmon_type_checkList[], int num_poketball, int num_catch_poketmon, int num_must_go_pStop, int poketStop_time[], QVector<int> &catch_order)
{//모든 타입을 다 잡았을 때 집으로 돌아올수 있어야함
    QVector<int> cand;
    QVector<int> distList;
    int checkCount=0;//잡은 포켓몬의 종류 수를 카운트.

    for(int i=0;i<MAX_CANDIDATES;i++)
    {
        if(poketmon_type_checkList[i]==true)
            checkCount++;
    }
    if(checkCount>=10)
    {
        NodeType dest=g->getNodeByIndex(0);
        find_shortest_path(dest,sol,time);
        process_solution(sol,time,catch_order);
    }
    else
    {
        if(promising(num_catch_poketmon))
        {
            process_solution(sol,time,catch_order);
        }
        else
        {
            construct_candidates(sol, visited, cand,distList, num_poketball, poketmon_type_checkList, num_must_go_pStop);
            NodeType dest;
            determine_next_node(visited,dest,distList,cand,num_poketball,num_must_go_pStop);
            if(dest.MonsterType==POKETSTOP_ID)
            {
                //vector<NodeType>::iterator iter;
                //iter=sol.end();
                //int consuming_time = g->WeightIs(*(iter-1), *iter);

                //// update p_stop state
                //// After time passes 15 min from last visit of poketstop, this can activate.
                //for (int index = 0; index < pStop_node_index_list.size(); ++index)
                //{
                //	int& cur_pStop_time = poketStop_time[pStop_node_index_list[index]];
                //	if (cur_pStop_time > 0)
                //	{
                //		cur_pStop_time -= consuming_time;
                //		if (cur_pStop_time < 0)
                //		{
                //			cur_pStop_time = 0;
                //			visited[pStop_node_index_list[index]] = false;
                //		}
                //	}
                //}
                find_shortest_path(dest,sol,time);
                visited[dest.index]=true;
                num_poketball+=3;

            }
            else
            {
                QVector<NodeType> temp=sol;
                QVector<NodeType> temp2;
                find_shortest_path(dest,sol,time);
                QVector<NodeType>::iterator iter=find(sol.begin(),sol.end(),temp.back());
                while(iter!=sol.end())
                {
                    temp2.push_back(*iter);
                    iter=iter+1;
                }
                for(int i=0;i<temp2.size();i++)
                {
                    visited[temp2[i].index]=true;
                    if(num_poketball>0)
                    {
                        num_poketball-=1;
                    }
                    poketmon_type_checkList[temp2[i].MonsterType]=true;
                    catch_order.push_back(temp2[i].MonsterType);
                }
            }

            if(checkCount==10)
            {
                dest=g->getNodeByIndex(0);
                find_shortest_path(dest,sol,time);
                process_solution(sol,time,catch_order);
            }
            else
                greedy(sol,visited,time,poketmon_type_checkList,num_poketball,num_catch_poketmon,num_must_go_pStop, poketStop_time,catch_order);
        }

    }
}

bool EveryMonsCatch::promising(int num_catch_poketmon)
{
    if (num_catch_poketmon == (MAX_CANDIDATES - 2))
        return true;
    return false;
}


void EveryMonsCatch::process_solution(QVector<NodeType>& sol, int time, QVector<int> &catch_order)
{
    check_for_home(sol, time);
    if ((this->best_route).time > time)
    {
        best_route.route = sol;
        best_route.time = time;
        cout << "I got it" << endl;
        cout << "Route : ";
        for (int i = 0; i < best_route.route.size(); ++i)
        {
            cout << best_route.route[i].index << " - " <<  best_route.route[i].MonsterType << " -> " ;
        }
        cout << endl;
        cout << "Catch Order : ";
        for (int i = 0; i < catch_order.size(); ++i)
            cout << catch_order[i] << " ";
        cout << endl;
        cout << "Time : " << best_route.time << endl << endl;
    }
}


void EveryMonsCatch::construct_candidates(QVector<NodeType>& sol, bool visited[], QVector<int>& cand,QVector<int>& distList, int num_poketball, bool poketmon_type_checkList[], int num_must_go_pStop)
{
    if (num_must_go_pStop > 0)
    {
        NodeType destination;
        find_closest_poketstop(sol.back(), destination, visited);
        cand.push_back(destination.index);
    }

    if (num_poketball > 0)
    {
        QVector<int> index_list;
        find_closest_poketmons(sol.back(),distList, index_list, visited, poketmon_type_checkList);

        for (int i = 0; i < index_list.size(); ++i)
        {
            cand.push_back(index_list[i]);
        }
    }
}


void EveryMonsCatch::make_all_route(QVector<int>& catch_order)
{
    QVector<NodeType> sol;
    sol.push_back(g->getNodeByIndex(START_ID));
    bool visited[MAX_NODE];
    int poketStop_time[MAX_NODE];
    visited[START_ID] = true;
    poketStop_time[START_ID] = 0;
    for (int i = 1; i < MAX_NODE; ++i)
    {
        visited[i] = false;
        poketStop_time[i] = 0;
    }

    int time = 0;
    bool poketmon_type_checkList[MAX_CANDIDATES];
    for (int i = 0; i < MAX_CANDIDATES; ++i)
    {
        poketmon_type_checkList[i] = false;
    }
    int num_poketball = 3;
    int num_catch_poketmon = 0;
    int num_must_go_pStop = 3;
    greedy(sol, visited, time, poketmon_type_checkList, num_poketball, num_catch_poketmon, num_must_go_pStop, poketStop_time, catch_order);//이부분을 Greedy로 바꾸는 것이 필요
}


void EveryMonsCatch::check_for_home(QVector<NodeType>& route, int& time)
{
    NodeType destination;
    destination.index = START_VERTEX;
    find_shortest_path(destination, route, time);
}


void EveryMonsCatch::search_nodes_by_id(int id, QVector<int>& node_list)
{
    node_list = this->map_of_id_to_node_index_list[id];
}


void EveryMonsCatch::find_shortest_path(NodeType destination, QVector<NodeType>& route, int& time)
{
    int num_vertex = this->g->getNodeCount();
    int** adj = this->g->getAdjmatrix();
    int start = route.back().index;
    int end = destination.index;
    Dijkstra(g, num_vertex, adj, start, end, route, time);
}


void EveryMonsCatch::find_closest_poketstop(NodeType cur, NodeType& destination, bool visited[])
{
    QVector<int> poketstop_node_index_list = map_of_id_to_node_index_list[POKETSTOP_ID];
    int min_time = 9999;
    for(int i = 0; i < poketstop_node_index_list.size(); ++i)
    {
        if(visited[poketstop_node_index_list[i]] == false)
        {
            NodeType stop_node = g->getNodeByIndex(poketstop_node_index_list[i]);

            QVector<NodeType> tmp_route;
            tmp_route.push_back(cur);
            int time = 0;
            find_shortest_path(stop_node, tmp_route, time);
            if (min_time > time)
            {
                min_time = time;
                destination = stop_node;
            }
        }
    }
}


void EveryMonsCatch::find_closest_poketmons(NodeType cur,QVector<int>& distList, QVector<int>& closest_poketmon_node_index_list, bool visited[], bool poketmon_type_checkList[])
{//거리도 저장할 수 있게 수정!!
    for (int p_id = 1; p_id < 11; ++p_id)
    {
        NodeType dest;
        if (poketmon_type_checkList[p_id] == false)
        {
            QVector<int> poketmon_node_index_List = map_of_id_to_node_index_list[p_id];
            int min_distance = 9999;
            int dist=0;
            for (int i = 0; i < poketmon_node_index_List.size(); ++i)
            {
                    NodeType poke_node = g->getNodeByIndex(poketmon_node_index_List[i]);

                    QVector<NodeType> tmp_route;
                    tmp_route.push_back(cur);
                    dist = 0;
                    find_shortest_path(poke_node, tmp_route, dist);
                    if (dist < min_distance)
                    {
                        min_distance = dist;
                        dest = poke_node;
                    }
            }
            distList.push_back(dist);
            closest_poketmon_node_index_list.push_back(dest.index);
        }
    }
}
