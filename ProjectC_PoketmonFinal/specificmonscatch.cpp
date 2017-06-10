#include "specificmonscatch.h"

SpecificMonsCatch::SpecificMonsCatch()
{
    algNum=0;
}

void SpecificMonsCatch::SetGraph(GraphType *gr)
{
    g=gr;
}

void SpecificMonsCatch::SetProblem(QVector<int> data)
{
    this->specific_time = data[0];
    this->specific_poketmon_id = data[1];
    this->map_of_id_to_node_index_list = g->getMap();
    this->pStop_node_index_list = this->map_of_id_to_node_index_list[POKETSTOP_ID];
}

QVector<QString> SpecificMonsCatch::FindRoute()
{
    make_all_route();
    cout << "<Best Route>" << endl;
    for (int i = 0; i < best_route.route.size(); ++i)
        cout << best_route.route[i].index << " ";
    cout << endl;
    cout << "Best Time : " << best_route.time << endl;
    cout<<"Poketemon Caught: "<<best_route.num_catch_poketmon<<endl;
    QVector<QString> stringRet;
    QString r;
    QString t;
    QString c;
    QString temp;
    for(int i = 0; i < best_route.route.size(); ++i)
    {
        temp=QString("%1").arg(best_route.route[i].index);
        r.append(temp);
        r.append(" ");
    }
    cout << endl;
    temp=QString("%1").arg(best_route.time);
    t=temp;
    temp=QString("%1").arg(best_route.num_catch_poketmon);
    c=temp;
    stringRet.push_back(r);
    stringRet.push_back(t);
    stringRet.push_back(c);
    return stringRet;
}

QVector<Route> SpecificMonsCatch::getSolutionA()
{
    return all_solution_routes;
}


bool SpecificMonsCatch::promising(QVector<NodeType>& sol, bool visited[], int time, int num_catch_poketmon, int limit_of_catch)
{
    if (limit_of_catch == num_catch_poketmon)
    {
        QVector<NodeType> test_sol = sol;
        check_for_home(test_sol, time);
        if (time <= specific_time)
            return true;
    }

    return false;
}


void SpecificMonsCatch::process_solution(QVector<NodeType>& sol, int time, int num_catch_poketmon)
{
    check_for_home(sol, time);
    if (best_route.num_catch_poketmon < num_catch_poketmon)
    {
        best_route.route = sol;
        best_route.time = time;
        best_route.num_catch_poketmon = num_catch_poketmon;
        cout << "I got it" << endl;
    }
    else if (best_route.time > time)
    {
        best_route.route = sol;
        best_route.time = time;
        best_route.num_catch_poketmon = num_catch_poketmon;
        cout << "I got it" << endl;
    }

}


void SpecificMonsCatch::construct_candidates(QVector<NodeType>& sol, bool visited[], QVector<int>& cand, bool can_catch_poketmon, int limit_of_catch, int num_of_poketstop_must_go)
{
    QVector<int> node_list;
    if (can_catch_poketmon)
    {
        node_list = map_of_id_to_node_index_list[specific_poketmon_id];
    }

    for(int i = 0; i < node_list.size(); ++i)
    {
        if (!visited[node_list[i]])
            cand.push_back(node_list[i]);
    }

    if (num_of_poketstop_must_go > 0)
    {
        NodeType dest;
        find_closest_poketstop(sol.back(), dest, visited);

        cand.push_back(dest.index);
    }
}


void SpecificMonsCatch::backtrack(QVector<NodeType>& sol, bool visited[], int time, int num_catch_poketmon, int limit_of_catch, int num_of_poketstop_must_go, int poketStop_time[])
{
    QVector<int> cand;
    if ( promising(sol, visited, time, num_catch_poketmon, limit_of_catch) )
        process_solution(sol, time, num_catch_poketmon);
    else
    {
        bool can_catch_poketmon = false;
        if (num_poketball > 0)
            can_catch_poketmon = true;

        construct_candidates(sol, visited, cand, can_catch_poketmon, limit_of_catch, num_of_poketstop_must_go);

        bool* next_visited = new bool[MAX_NODE];
        int* next_poketStop_time = new int[MAX_NODE];
        for(int i = 0; i < cand.size(); ++i)
        {
            NodeType destination;
            destination = g->getNodeByIndex(cand[i]);
            QVector<NodeType> next_sol = sol;
            int next_time = time;
            int next_num_must_go_pStop = num_of_poketstop_must_go;
            int next_num_catch_poketmon = num_catch_poketmon;
            int next_num_poketball = num_poketball;
            int next_limit_of_catch = limit_of_catch;

            for (int i = 0; i < MAX_NODE; ++i)
            {
                next_visited[i] = visited[i];
                next_poketStop_time[i] = poketStop_time[i];
            }

            find_shortest_path(destination, next_sol, next_time);

            QVector<NodeType> home_test_sol = next_sol;
            int home_test_time = next_time;
            check_for_home(home_test_sol, home_test_time);
            if (home_test_time > specific_time) continue;	// pruning condition 1
            if (best_route.num_catch_poketmon != 0 &&
                best_route.num_catch_poketmon == limit_of_catch &&
                best_route.time < home_test_time)	continue;

            int visit_counter[MAX_NODE];
            for (int j = 0; j < MAX_NODE; ++j)
                visit_counter[j] = 0;
            bool finished = false;


            QVector<NodeType>::iterator iter;
            iter = next_sol.end() - (next_sol.size() - sol.size());
            while (iter != next_sol.end())
            {
                int consuming_time = g->WeightIs((iter - 1)->index, iter->index);

                // update p_stop state
                // After time passes 15 min from last visit of poketstop, this can activate.
                for (int index = 0; index < pStop_node_index_list.size(); ++index)
                {
                    int& cur_pStop_time = next_poketStop_time[pStop_node_index_list[index]];
                    if (cur_pStop_time > 0)
                    {
                        cur_pStop_time -= consuming_time;
                        if (cur_pStop_time < 0)
                        {
                            cur_pStop_time = 0;
                            next_visited[pStop_node_index_list[index]] = false;
                        }
                    }
                }

                if (next_visited[(*iter).index] == false && (*iter).MonsterType == POKETSTOP_ID)
                {
                    next_num_poketball += 3;
                    next_poketStop_time[(*iter).index] = 15;
                    next_num_must_go_pStop -= 1;
                    next_visited[(*iter).index] = true;
                }

                if ((*iter).MonsterType != POKETSTOP_ID && (iter == next_sol.end() - 1))
                {
                    next_num_catch_poketmon += 1;
                    next_visited[(*iter).index] = true;
                }

                visit_counter[iter->index] += 1;
                if (visit_counter[iter->index] >= 3)
                {
                    finished = true;
                    break;
                }
                iter += 1;
            }
            if (finished) continue;	// pruning condition 3


            backtrack(next_sol, next_visited, next_time, next_num_catch_poketmon, next_limit_of_catch, next_num_must_go_pStop, next_poketStop_time);

        }
        delete next_visited;
        delete next_poketStop_time;
    }
}



void SpecificMonsCatch::make_all_route()
{
    best_route.num_catch_poketmon = 0;
    best_route.time = 9999;
    int limit_of_catch, num_of_poketstop_must_go;
    QVector<int> poketmon_index_list = map_of_id_to_node_index_list[specific_poketmon_id];
    for(limit_of_catch = 1; limit_of_catch <= poketmon_index_list.size(); ++limit_of_catch)
    {
        //if (limit_of_catch != 2) continue;
        if (limit_of_catch < 4) num_of_poketstop_must_go = 0;
        else if (limit_of_catch < 7) num_of_poketstop_must_go = 1;
        else num_of_poketstop_must_go = 2;

        QVector<NodeType> sol;
        sol.push_back(g->getNodeByIndex(START_ID));
        bool visited[MAX_NODE];
        int poketStop_time[MAX_NODE];
        visited[START_ID] = true;
        poketStop_time[START_ID] = 0;
        for(int i = 1; i < MAX_NODE; ++i)
        {
            visited[i] = false;
            poketStop_time[i] = 0;
        }
        num_poketball = 3;
        int time = 0;
        int num_catch_poketmon = 0;

        backtrack(sol, visited, time, num_catch_poketmon, limit_of_catch, num_of_poketstop_must_go, poketStop_time);

        if (best_route.num_catch_poketmon != limit_of_catch)
            break;
    }


}


void SpecificMonsCatch::check_for_home(QVector<NodeType>& route, int& time)
{
    NodeType destination;
    destination.index = START_VERTEX;
    find_shortest_path(destination, route, time);
}


void SpecificMonsCatch::search_nodes_by_id(int id, QVector<int>& node_list)
{
    node_list = this->map_of_id_to_node_index_list[id];
}


void SpecificMonsCatch::find_shortest_path(NodeType destination, QVector<NodeType>& route, int& time)
{
    int num_vertex = g->getNodeCount();
    int** adj = g->getAdjmatrix();
    int start = route.back().index;
    int end = destination.index;
    Dijkstra(g, num_vertex, adj, start, end, route, time);
}

void SpecificMonsCatch::find_closest_poketstop(NodeType cur, NodeType& destination, bool visited[])
{
    QVector<int> poketstop_node_index_List = map_of_id_to_node_index_list[POKETSTOP_ID];
    int min_distance = 9999;
    for(int i = 0; i < poketstop_node_index_List.size(); ++i)
    {
        if(visited[poketstop_node_index_List[i]] == false)
        {
            NodeType stop_node = g->getNodeByIndex(poketstop_node_index_List[i]);
            double dist = (cur.x - stop_node.x) * (cur.x - stop_node.x);
            dist += (cur.y - stop_node.y) * (cur.y - stop_node.y);
            dist = sqrt(dist);

            if(dist < min_distance)
            {
                min_distance = dist;
                destination = stop_node;
            }
        }
    }
}

