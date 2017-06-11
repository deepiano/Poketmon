#include "SolveA.h"

void SolveA::setProblem(int specific_time, int specific_poketmon_id)
{
	this->specific_time = specific_time;
	this->specific_poketmon_id = specific_poketmon_id;
	this->map_of_id_to_node_index_list = graph.getMap();
	this->pStop_node_index_list = this->map_of_id_to_node_index_list[POKETSTOP_ID];
}


bool SolveA::promising(vector<NodeType>& sol, bool visited[], int time, int num_catch_poketmon, int limit_of_catch)
{
	if (limit_of_catch == num_catch_poketmon)
	{
		vector<NodeType> test_sol = sol;
		check_for_home(test_sol, time);
		if (time <= specific_time)
			return true;
	}
	
	return false;
}


void SolveA::process_solution(vector<NodeType>& sol, int time, int num_catch_poketmon)
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
}


void SolveA::construct_candidates(vector<NodeType>& sol, bool visited[], vector<int>& cand, bool can_catch_poketmon, int limit_of_catch, int num_of_poketstop_must_go)
{
	vector<int> node_list;
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

		// Second Comment Solve : stay on current poketstop
		// if (sol.back().MonsterType == POKETSTOP_ID)
		// {
		// 	cand.push_back(sol.back().index);
		// }
	}
}


void SolveA::backtrack(vector<NodeType>& sol, bool visited[], int time, int num_poketball, int num_catch_poketmon, int limit_of_catch, int num_of_poketstop_must_go, int poketStop_time[])
{
	vector<int> cand;
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
			destination = graph.getNodeByIndex(cand[i]);

			vector<NodeType> next_sol = sol;
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

			// Second Comment Solve : stay on current poketstop
			// if (destination == sol.back())
			// {
			// 	next_sol.push_back(destination);
			// 	next_time += 15;
			// 	next_num_must_go_pStop -= 1;
			// 	next_num_poketball += 3;
			// 	for (int index = 0; index < pStop_node_index_list.size(); ++index)
			// 	{
			// 		next_poketStop_time[pStop_node_index_list[index]] = 0;
			// 		next_visited[pStop_node_index_list[index]] = false;
			// 	}
			// 	next_poketStop_time[destination.index] = 15;
			// 	next_visited[destination.index] = true;
			// }
			else
			{
				find_shortest_path(destination, next_sol, next_time);

				vector<NodeType> home_test_sol = next_sol;
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


				vector<NodeType>::iterator iter;
				iter = next_sol.end() - (next_sol.size() - sol.size());
				while (iter != next_sol.end())
				{
					int consuming_time = graph.WeightIs(*(iter - 1), *iter);

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

					visit_counter[iter->index] += 1;
					if (visit_counter[iter->index] >= 3)
					{
						finished = true;
						break;
					}
					iter += 1;
				}
				if (finished) continue;	// pruning condition 3
			}
			
			backtrack(next_sol, next_visited, next_time, next_num_poketball, next_num_catch_poketmon, next_limit_of_catch, next_num_must_go_pStop, next_poketStop_time);

		}
		delete next_visited;
		delete next_poketStop_time;
	}
}



void SolveA::make_all_route()
{
	best_route.num_catch_poketmon = 0;
	best_route.time = 9999;
	int limit_of_catch, num_of_poketstop_must_go;
	vector<int> poketmon_index_list = map_of_id_to_node_index_list[specific_poketmon_id];
	for(limit_of_catch = 1; limit_of_catch <= poketmon_index_list.size(); ++limit_of_catch)
	{
		//if (limit_of_catch != 2) continue;
		if (limit_of_catch < 4) num_of_poketstop_must_go = 0;
		else if (limit_of_catch < 7) num_of_poketstop_must_go = 1;
		else num_of_poketstop_must_go = 2;

		vector<NodeType> sol;
		sol.push_back(graph.getNodeByIndex(START_ID));
		bool visited[MAX_NODE];
		int poketStop_time[MAX_NODE];
		visited[START_ID] = true;
		poketStop_time[START_ID] = 0;
		for(int i = 1; i < MAX_NODE; ++i)
		{
			visited[i] = false;
			poketStop_time[i] = 0;
		}
		int num_poketball = 3;
		int time = 0;
		int num_catch_poketmon = 0;

		backtrack(sol, visited, time, num_poketball, num_catch_poketmon, limit_of_catch, num_of_poketstop_must_go, poketStop_time);
		
		if (best_route.num_catch_poketmon != limit_of_catch)
			break;
	}

	
}

void SolveA::find_solution()
{
	make_all_route();

	cout << endl << "Best Route : ";
	for(int i = 0; i < best_route.route.size(); ++i)
		cout << best_route.route[i].index << " ";
	cout << endl;
	cout << "Best Time : " << best_route.time << endl;
	cout << "Best Catch : " << best_route.num_catch_poketmon << endl;
}


void SolveA::check_for_home(vector<NodeType>& route, int& time)
{
	NodeType destination;
	destination.index = START_VERTEX;
	find_shortest_path(destination, route, time);
}


void SolveA::search_nodes_by_id(int id, vector<int>& node_list)
{
	node_list = this->map_of_id_to_node_index_list[id];
}


void SolveA::find_shortest_path(NodeType destination, vector<NodeType>& route, int& time)
{
	int num_vertex = this->graph.getNodeCount();
	int** adj = this->graph.getAdjMatrix();
	int start = route.back().index;
	int end = destination.index;
	Dijkstra(&graph, num_vertex, adj, start, end, route, time);
}

void SolveA::find_closest_poketstop(NodeType cur, NodeType& destination, bool visited[])
{
	vector<int> poketstop_node_index_list = map_of_id_to_node_index_list[POKETSTOP_ID];
	int min_time = 9999;
	for(int i = 0; i < poketstop_node_index_list.size(); ++i)
	{
		if(visited[poketstop_node_index_list[i]] == false)
		{
			NodeType stop_node = graph.getNodeByIndex(poketstop_node_index_list[i]);

			vector<NodeType> tmp_route;
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