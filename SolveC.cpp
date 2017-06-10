#include "SolveC.h"

void SolveC::setProblem()
{
	this->map_of_id_to_node_index_list = graph.getMap();
	this->pStop_node_index_list = map_of_id_to_node_index_list[POKETSTOP_ID];
	this->best_route.time = 9999;
}


void SolveC::backtrack(vector<NodeType>& sol, bool visited[], int time, bool poketmon_type_checkList[], int num_poketball, int num_catch_poketmon, int num_must_go_pStop, int poketStop_time[], vector<int> &catch_order)
{
	vector<int> cand;

	if (promising(num_catch_poketmon))
		process_solution(sol, time, catch_order);
	else
	{
		construct_candidates(sol, visited, cand, num_poketball, poketmon_type_checkList, num_must_go_pStop);
		bool* next_visited = new bool[MAX_NODE];
		int* next_poketStop_time = new int[MAX_NODE];
		bool* next_ptype_checkList = new bool[MAX_CANDIDATES];
		for (int i = 0; i < cand.size(); ++i)
		{
			NodeType destination;
			destination = graph.getNodeByIndex(cand[i]);
			vector<NodeType> next_sol = sol;
			int next_time = time;
			int next_num_poketball = num_poketball;
			int next_num_must_go_pStop = num_must_go_pStop;
			int next_num_catch_poketmon = num_catch_poketmon;


			for (int j = 0; j < MAX_NODE; ++j)
			{
				next_visited[j] = visited[j];
				next_poketStop_time[j] = poketStop_time[j];
			}
			for (int k = 0; k < MAX_CANDIDATES; ++k)
			{
				next_ptype_checkList[k] = poketmon_type_checkList[k];
			}

			find_shortest_path(destination, next_sol, next_time);
			if (next_time > best_route.time) continue;	// pruning condition 1

			int visit_counter[MAX_NODE];
			for (int j = 0; j < MAX_NODE; ++j)
				visit_counter[j] = 0;
			bool finished = false;

			if (next_num_poketball > 2 && (next_sol.size() - sol.size()) > 2)
			{
				finished = true;
			}
			if (finished) continue;		// pruning condition 2

			vector<NodeType>::iterator iter;
			iter = next_sol.end() - (next_sol.size() - sol.size());
			while (iter != next_sol.end())
			{
				int consuming_time = graph.WeightIs(*(iter-1), *iter);
				
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
					if (next_num_poketball > 0)
					{
						next_ptype_checkList[(*iter).MonsterType] = true;
						next_num_catch_poketmon += 1;
						next_visited[(*iter).index] = true;
						catch_order.push_back((*iter).MonsterType);
						next_num_poketball -= 1;
					}
					
				}

				visit_counter[iter->index] += 1;
				if (visit_counter[iter->index] >= 3)
				{
					finished = true;
					break;
				}
				iter += 1;
			}
			if (finished) continue;		// pruning condition 3

			backtrack(next_sol, next_visited, next_time, next_ptype_checkList, next_num_poketball, next_num_catch_poketmon, next_num_must_go_pStop, next_poketStop_time, catch_order);
			
			if (destination.MonsterType != POKETSTOP_ID)
			{
				catch_order.pop_back();
			}
		}
		delete next_visited;
		delete next_poketStop_time;
		delete next_ptype_checkList;
	}
}


bool SolveC::promising(int num_catch_poketmon)
{
	if (num_catch_poketmon == (MAX_CANDIDATES - 2))
		return true;
	return false;
}


void SolveC::process_solution(vector<NodeType>& sol, int time, vector<int> &catch_order)
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


void SolveC::construct_candidates(vector<NodeType>& sol, bool visited[], vector<int>& cand, int num_poketball, bool poketmon_type_checkList[], int num_must_go_pStop)
{
	if (num_must_go_pStop > 0)
	{
		NodeType destination;
		find_closest_poketstop(sol.back(), destination, visited);
		cand.push_back(destination.index);
	}

	if (num_poketball > 0)
	{
		vector<int> index_list;
		find_closest_poketmons(sol.back(), index_list, visited, poketmon_type_checkList);

		for (int i = 0; i < index_list.size(); ++i)
		{
			cand.push_back(index_list[i]);
		}
	}
}


void SolveC::find_solution()
{
	make_all_route();
	
	cout << "<Best Route>" << endl;
	for (int i = 0; i < best_route.route.size(); ++i)
		cout << best_route.route[i].index << " ";
	cout << endl;
	cout << "Best Time : " << best_route.time << endl;
} 


void SolveC::make_all_route()
{
	vector<NodeType> sol;
	vector<int> catch_order;
	sol.push_back(graph.getNodeByIndex(START_ID));
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
		poketmon_type_checkList[i] = false;
	int num_poketball = 3;
	int num_catch_poketmon = 0;
	int num_must_go_pStop = 3;
	backtrack(sol, visited, time, poketmon_type_checkList, num_poketball, num_catch_poketmon, num_must_go_pStop, poketStop_time, catch_order);
}


void SolveC::check_for_home(vector<NodeType>& route, int& time)
{
	NodeType destination;
	destination.index = START_VERTEX;
	find_shortest_path(destination, route, time);
}


void SolveC::search_nodes_by_id(int id, vector<int>& node_list)
{
	node_list = this->map_of_id_to_node_index_list[id];
}


void SolveC::find_shortest_path(NodeType destination, vector<NodeType>& route, int& time)
{
	int num_vertex = this->graph.getNodeCount();
	int** adj = this->graph.getAdjMatrix();
	int start = route.back().index;
	int end = destination.index;
	Dijkstra(&graph, num_vertex, adj, start, end, route, time);
}


void SolveC::find_closest_poketstop(NodeType cur, NodeType& destination, bool visited[])
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


void SolveC::find_closest_poketmons(NodeType cur, vector<int>& closest_poketmon_node_index_list, bool visited[], bool poketmon_type_checkList[])
{
	for (int p_id = 1; p_id < 11; ++p_id)
	{
		NodeType dest;
		if (poketmon_type_checkList[p_id] == false)
		{
			vector<int> poketmon_node_index_List = map_of_id_to_node_index_list[p_id];
			int min_distance = 9999;

			for (int i = 0; i < poketmon_node_index_List.size(); ++i)
			{
					NodeType poke_node = graph.getNodeByIndex(poketmon_node_index_List[i]);
					
					vector<NodeType> tmp_route;
					tmp_route.push_back(cur);
					int dist = 0;
					find_shortest_path(poke_node, tmp_route, dist);
					if (dist < min_distance)
					{
						min_distance = dist;
						dest = poke_node;
					}
			}
			closest_poketmon_node_index_list.push_back(dest.index);
		}
	}
}