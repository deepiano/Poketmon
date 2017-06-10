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
    this->limit_time_for_poketStop = 50;
}

QVector<QString> SpecificMonsCatch::FindRoute()
{
    QVector<QString> toRet;
    QString temp,q,r,s;
    make_all_route();
    cout << "Best Route : ";
    for (int i = 0; i < best_route.route.size(); ++i)
        cout << best_route.route[i].index << " ";
    cout << endl;
    cout << "Time : " << best_route.time << endl;
    cout << "Best catch : " << best_route.num_catch_poketmon << endl;
    for (int i = 0; i < best_route.route.size(); ++i)
    {
        temp=QString("%1").arg(best_route.route[i].index);
        q.append(temp);
        q.append(" ");
    }
    temp=QString("%1").arg(best_route.time);
    r=temp;
    temp=QString("%1").arg(best_route.num_catch_poketmon);
    s=temp;

    toRet.push_back(q);
    toRet.push_back(r);
    toRet.push_back(s);

    return toRet;
}

void SpecificMonsCatch::backtrack(QVector<NodeType>& sol, bool visited[], int time, int num_poketball, int num_catch_poketmon, int limit_of_catch, int num_of_poketstop_must_go, int poketStop_time[])
{
    QVector<int> cand;
    if ( promising(sol, visited, time, num_catch_poketmon, limit_of_catch) )
        process_solution(sol, time, num_catch_poketmon);
    else
    {
        construct_candidates(sol, visited, time, cand, num_poketball, limit_of_catch, num_of_poketstop_must_go);

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
            // if (best_route.num_catch_poketmon != 0 &&
            // 	best_route.num_catch_poketmon == limit_of_catch &&
            // 	best_route.time < home_test_time)	continue;	// pruning condition 2

            QVector<NodeType>::iterator iter;
            iter = next_sol.end() - (next_sol.size() - sol.size());
            while (iter != next_sol.end())
            {
                int consuming_time = g->WeightIs((iter - 1)->index,iter->index);

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
                    next_num_poketball -= 1;
                    next_num_catch_poketmon += 1;
                    next_visited[(*iter).index] = true;
                }

                iter += 1;
            }	// while

            backtrack(next_sol, next_visited, next_time, next_num_poketball, next_num_catch_poketmon, next_limit_of_catch, next_num_must_go_pStop, next_poketStop_time);

        }
        delete next_visited;
        delete next_poketStop_time;
    }
}


bool SpecificMonsCatch::promising(QVector<NodeType>& sol, bool visited[], int time, int num_catch_poketmon, int limit_of_catch)
{
    cout << "Route : ";
    for(int i = 0; i < sol.size(); ++i)
        cout << sol[i].index << " ";
    cout << endl;
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
    else if (best_route.num_catch_poketmon ==  num_catch_poketmon && best_route.time > time)
    {
        best_route.route = sol;
        best_route.time = time;
        best_route.num_catch_poketmon = num_catch_poketmon;
        cout << "I got it" << endl;
    }

    // Test
    // cout << "Route : ";
    // for(int i = 0; i < sol.size(); ++i)
    // 	cout << sol[i].index << " ";
    // cout << endl;
}


void SpecificMonsCatch::construct_candidates(QVector<NodeType>& sol, bool visited[], int time, QVector<int>& cand, int num_poketball, int limit_of_catch, int num_of_poketstop_must_go)
{
    int i;
    QVector<int> poketmon_index_list = map_of_id_to_node_index_list[specific_poketmon_id];

    if (sol.size() == 1)
    {
        cand.push_back(first_catch_poketmon_index);
        return;
    }

    if (time < specific_time / 2)	// Greedy : Find a next node taken shortest time .
    {
        int min_time = 9999;
        NodeType nextNode;
        if (num_poketball > 0)	// if you can catch poketmon
        {
            for (i = 0; i < poketmon_index_list.size(); ++i)
            {
                NodeType poketNode = g->getNodeByIndex(poketmon_index_list[i]);
                if (!visited[poketNode.index])
                {
                    int tmp_time = 0;
                    QVector<NodeType> tmp_route;
                    tmp_route.push_back(sol.back());
                    find_shortest_path(poketNode, tmp_route, tmp_time);
                    if (tmp_time < min_time)
                    {
                        min_time = tmp_time;
                        nextNode = poketNode;
                    }
                }
            }
        }

        // If you must go poketStop,
        // you have to find a poketStop taken shortest time.
        if (num_of_poketstop_must_go > 0)
        {
            for(i = 0; i < pStop_node_index_list.size(); ++i)
            {
                NodeType stopNode = g->getNodeByIndex(pStop_node_index_list[i]);
                if (!visited[stopNode.index])
                {
                    int tmp_time = 0;
                    QVector<NodeType> tmp_route;
                    tmp_route.push_back(sol.back());
                    find_shortest_path(stopNode, tmp_route, tmp_time);
                    if (tmp_time < min_time && tmp_time < limit_time_for_poketStop)
                    {
                        min_time = tmp_time;
                        nextNode = stopNode;
                    }
                }
            }
        }
        cand.push_back(nextNode.index);
    }	// if (time < specific_time / 2) : Greedy

    else // backtracking
    {
        if (num_poketball > 0)	// if you can catch poketmon
        {
            for(i = 0; i < poketmon_index_list.size(); ++i)
            {
                if (!visited[poketmon_index_list[i]])
                    cand.push_back(poketmon_index_list[i]);
            }
        }
        if (num_of_poketstop_must_go > 0)
        {
            NodeType dest;
            find_closest_poketstop(sol.back(), dest, visited);

            cand.push_back(dest.index);
        }
    }
}


void SpecificMonsCatch::make_all_route()
{
    best_route.num_catch_poketmon = 0;
    best_route.time = 9999;
    int i;
    int limit_of_catch, num_of_poketstop_must_go;
    QVector<int> poketmon_index_list = map_of_id_to_node_index_list[specific_poketmon_id];
    for(i = 0; i < poketmon_index_list.size(); ++i)
    {
        first_catch_poketmon_index = poketmon_index_list[i];
        for(limit_of_catch = 1; limit_of_catch <= poketmon_index_list.size(); ++limit_of_catch)
        {
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

            int time = 0;
            int num_poketball = 3;
            int num_catch_poketmon = 0;

            // // Choose first catch poketmon node
            // int tmp_time = 0;
            // vector<NodeType> tmp_route;
            // tmp_route.push_back(graph.getNodeByIndex(START_ID));
            // find_shortest_path(graph.getNodeByIndex(poketmon_index_list[i]), tmp_route, tmp_time);
            // if (tmp_time < specific_time)
            // {
            // 	sol = tmp_route;
            // 	time += tmp_time;
            // 	visited[poketmon_index_list[i]] = true;
            // 	num_poketball -= 1;
            // 	num_catch_poketmon += 1;
            // }
            // else continue;

            backtrack(sol, visited, time, num_poketball, num_catch_poketmon, limit_of_catch, num_of_poketstop_must_go, poketStop_time);

            if (best_route.num_catch_poketmon != limit_of_catch)
                break;
        }
    }

}


void SpecificMonsCatch::check_for_home(QVector<NodeType>& route, int& time)
{
    NodeType destination;
    destination.index = START_VERTEX;
    find_shortest_path(destination, route, time);
}


void SpecificMonsCatch::find_shortest_path(NodeType destination, QVector<NodeType>& route, int& time)
{
    int num_vertex = this->g->getNodeCount();
    int** adj = this->g->getAdjmatrix();
    int start = route.back().index;
    int end = destination.index;
    Dijkstra(g, num_vertex, adj, start, end, route, time);
}


void SpecificMonsCatch::find_closest_poketstop(NodeType cur, NodeType& destination, bool visited[])
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
