#include "manymonscatch.h"

ManyMonsCatch::ManyMonsCatch()
{
    algNum=1;
}

QVector<QString> ManyMonsCatch::FindRoute()
{
    // try backtrack
    // try backtrack
    QVector<QString> toRet;
    QString temp,q,r,s;
    QVector<NodeType> sol;
    sol.push_back(g->getNodeByIndex(0));
    bool visited[MAX_NODE];
    for (int i = 0; i < MAX_NODE; ++i)
        visited[i] = false;
    int time = 0;
    int num_catch_poketmon = 0;
    int num_poketball = 3;
    int poketStop_time[MAX_NODE];
    best_route.time = 9999;
    best_route.num_catch_poketmon = 0;
    for (int i = 0; i < poketStop_node_index_list.size(); ++i)
        poketStop_time[poketStop_node_index_list[i]] = 0;
    backtrack(sol, visited, time, num_catch_poketmon, num_poketball, poketStop_time);

    // print solution
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

void ManyMonsCatch::SetProblem(QVector<int> data)
{
    this->specific_time = data[0];
    map_of_id_to_node_index_list = g->getMap();
    poketStop_node_index_list = map_of_id_to_node_index_list[POKETSTOP_ID];
    this->limit_time_for_poketStop = 50;
}

void ManyMonsCatch::setGraph(GraphType *gr)
{
    g=gr;
}



void ManyMonsCatch::backtrack(QVector<NodeType>& sol, bool visited[], int time, int num_catch_poketmon, int num_poketball, int poketStop_time[])
{
    QVector<int> cand;

    if (promising(sol, visited, time, num_catch_poketmon))
    {
        process_solution(sol, time, num_catch_poketmon);
    }
    else
    {
        // Test
        cout << "Route: ";
        for(int i = 0; i < sol.size(); ++i)
        {
            cout << sol[i].index << " ";
        }
        cout << endl;
        // cout << "poketball : " << num_poketball << endl;

        construct_candidates(sol, visited, time, cand, num_poketball);

        bool* next_visited = new bool[MAX_NODE];
        int* next_poketStop_time = new int[MAX_NODE];
        for (int i = 0; i < cand.size(); ++i)
        {
            NodeType next_node = g->getNodeByIndex(cand[i]);

            QVector<NodeType> next_sol = sol;
            int next_time = time;
            int next_num_poketball = num_poketball;
            int next_num_catch_poketmon = num_catch_poketmon;
            for (int i = 0; i < MAX_NODE; ++i)
            {
                next_visited[i] = visited[i];
                next_poketStop_time[i] = poketStop_time[i];
            }

            if (g->IsAdjacent(sol.back().index, next_node.index))    // To adjacent
            {
                int consuming_time = g->WeightIs(sol.back().index, next_node.index);

                if (specific_time < time + consuming_time)	continue;

                next_sol.push_back(next_node);	// Go to the next_node

                next_visited[cand[i]] = true;
                next_time += consuming_time;

                update_poketStop_state(next_visited, next_poketStop_time, consuming_time, 0);

                if (next_node.MonsterType == POKETSTOP_ID)
                {
                    next_num_poketball += 3;
                    next_poketStop_time[next_node.index] = 15;
                }
                else if (next_node.MonsterType != START_ID)
                {
                    if (next_num_poketball != 0)
                    {
                        next_num_poketball -= 1;
                        next_num_catch_poketmon += 1;
                    }
                }
            }
            else  // jump to poketStop by Dijkstra
            {
                find_shortest_path(next_node, next_sol, next_time);
                QVector<NodeType>::iterator iter;
                iter = next_sol.end() - (next_sol.size() - sol.size());
                while (iter != next_sol.end())
                {
                    int consuming_time = g->WeightIs((iter - 1)->index, iter->index);

                    // update p_stop state
                    // After time passes 15 min from last visit of poketstop, this can activate.
                    for (int index = 0; index < poketStop_node_index_list.size(); ++index)
                    {
                        int& cur_pStop_time = next_poketStop_time[poketStop_node_index_list[index]];
                        if (cur_pStop_time > 0)
                        {
                            cur_pStop_time -= consuming_time;
                            if (cur_pStop_time < 0)
                            {
                                cur_pStop_time = 0;
                                next_visited[poketStop_node_index_list[index]] = false;
                            }
                        }
                    }

                    if (next_visited[(*iter).index] == false && (*iter).MonsterType == POKETSTOP_ID)
                    {
                        next_num_poketball += 3;
                        next_poketStop_time[(*iter).index] = 15;
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
            }

            backtrack(next_sol, next_visited, next_time, next_num_catch_poketmon, next_num_poketball, next_poketStop_time);
        }
        delete next_visited;
        delete next_poketStop_time;
    }

}


bool ManyMonsCatch::promising(QVector<NodeType>& sol, bool visited[], int time, int num_catch_poketmon)
{
    if (time <= specific_time && sol.size() != 1)
        if (sol.back().MonsterType == START_ID)
            return true;
    return false;
}


void ManyMonsCatch::process_solution(QVector<NodeType>& sol, int time, int num_catch_poketmon)
{
    if (best_route.num_catch_poketmon < num_catch_poketmon)
    {
        best_route.route = sol;
        best_route.time = time;
        best_route.num_catch_poketmon = num_catch_poketmon;
    }
    else if (best_route.num_catch_poketmon == num_catch_poketmon)
    {
        if (best_route.time > time)
        {
            best_route.route = sol;
            best_route.time = time;
            best_route.num_catch_poketmon = num_catch_poketmon;
        }
    }

    // Test
    cout << "Route: ";
    for(int i = 0; i < sol.size(); ++i)
    {
        cout << sol[i].index << " ";
    }
    cout << endl;
}


void ManyMonsCatch::construct_candidates(QVector<NodeType>& sol, bool visited[], int time, QVector<int>& cand, int num_poketball)
{
    int i;

    NodeType last_node = sol.back();
    QVector<int> adjList = g->getAdjacent(last_node.index);
    NodeType next_pStopNode;
    find_closest_poketstop(sol.back(), next_pStopNode, visited);

    // Choose first catch poketmon
    if (sol.size() == 1)
    {
        for (i = 0; i < adjList.size(); ++i)
        {
            if (!visited[adjList[i]])
            {
                cand.push_back(adjList[i]);
            }
        }
        return;
    }

    if (time < specific_time / 2)   // Greedy
    {
        int min_time = 9999;
        int next_index;
        if (num_poketball > 0)
        {
            for(i = 0; i < adjList.size(); ++i)
            {
                if (!visited[adjList[i]])
                {
                    NodeType nextNode = g->getNodeByIndex(adjList[i]);
                    if (nextNode.MonsterType == START_ID || nextNode.MonsterType == POKETSTOP_ID)  continue;
                    int tmp_time = g->WeightIs(sol.back().index, nextNode.index);
                    if (tmp_time < min_time)
                    {
                        min_time = tmp_time;
                        next_index = nextNode.index;
                    }
                }
            }
            cand.push_back(next_index);
        }
        else
        {
            cand.push_back(next_pStopNode.index);
        }
    }
    else    // Backtracking
    {
        for (i = 0; i < adjList.size(); ++i)
        {
            if (!visited[adjList[i]])
            {
                cand.push_back(adjList[i]);
            }
        }
    }
}

/*
if mode == 0, then poketStop_time decreases.
else if mode == 1, then poketStop_time return to origin.
*/
void ManyMonsCatch::update_poketStop_state(bool visited[], int poketStop_time[], int consuming_time, int mode)
{
    if (mode == 0)
    {
        for (int i = 0; i < poketStop_node_index_list.size(); ++i)
        {
            if (poketStop_time[poketStop_node_index_list[i]] > 0)
            {
                poketStop_time[poketStop_node_index_list[i]] -= consuming_time;
                if (poketStop_time[poketStop_node_index_list[i]] < 0)
                {
                    visited[poketStop_node_index_list[i]] = false;
                }
            }
        }
    }

    else if (mode == 1)
    {
        for (int i = 0; i < poketStop_node_index_list.size(); ++i)
        {
            if (poketStop_time[poketStop_node_index_list[i]] > 0)
            {
                if (poketStop_time[poketStop_node_index_list[i]] <= 0)
                {
                    visited[poketStop_node_index_list[i]] = true;
                }
                poketStop_time[poketStop_node_index_list[i]] += consuming_time;
            }
        }
    }
}


void ManyMonsCatch::find_shortest_path(NodeType destination, QVector<NodeType>& route, int& time)
{
    int num_vertex = this->g->getNodeCount();
    int** adj = this->g->getAdjmatrix();
    int start = route.back().index;
    int end = destination.index;
    Dijkstra(g, num_vertex, adj, start, end, route, time);
}


void ManyMonsCatch::find_closest_poketstop(NodeType cur, NodeType& destination, bool visited[])
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
