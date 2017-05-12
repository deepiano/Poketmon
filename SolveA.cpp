#include "SolveA.h"

void SolveA::setGraph(GraphType graph)
{
	this->graph = graph;
	this->map_of_id_to_node_index_list = graph.getMap();
}

void SolveA::setProblemA(int specific_time, int specific_poketmon_id)
{
	this->specific_time = specific_time;
	this->specific_poketmon_id = specific_poketmon_id;
	this->map_of_id_to_node_index_list = graph.getMap();
}

vector<Route> SolveA::getSolutionA()
{
	return all_solution_routes;
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
	Route cur_route;
	cur_route.route = sol;
	cur_route.time = time;
	cur_route.num_catch_poketmon = num_catch_poketmon;
	all_solution_routes.push_back(cur_route);
	cout << "I got it" << endl;
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
	}
}


void SolveA::backtrack(vector<NodeType>& sol, bool visited[], int time, int num_catch_poketmon, int limit_of_catch, int num_of_poketstop_must_go)
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

		for(int i = 0; i < cand.size(); ++i)
		{
			NodeType destination;
			destination = graph.getNodeByIndex(cand[i]);
			vector<NodeType> test_sol = sol;
			int test_time = time;

			find_shortest_path(destination, test_sol, test_time);
			vector<NodeType> home_test_sol = test_sol;
			
			int home_test_time = test_time;
			check_for_home(home_test_sol, home_test_time);
			if(home_test_time > specific_time) continue;

			if(test_time > 15)	// After 15 minutes from the last visit, we can visit again.
			{
				vector<int> node_list;
				node_list = map_of_id_to_node_index_list[POKETSTOP_ID];
				for(int i = 0; i < node_list.size(); ++i)
					visited[node_list[i]] = false;
			}

			if(destination.MonsterType == POKETSTOP_ID)
			{
				num_of_poketstop_must_go--;
				num_poketball += 3;
			}
			else
			{
				if (can_catch_poketmon) num_catch_poketmon++;
				num_poketball--;
			}
			visited[destination.index] = true;
			
			backtrack(test_sol, visited, test_time, num_catch_poketmon, limit_of_catch, num_of_poketstop_must_go);

			if(destination.MonsterType == POKETSTOP_ID)
			{
				num_of_poketstop_must_go++;
				num_poketball -= 3;
			}
			else
			{
				if (can_catch_poketmon) num_catch_poketmon--;
				num_poketball++;
			}
			visited[destination.index] = false;
		}
	}
}



void SolveA::make_all_route()
{

	int limit_of_catch, num_of_poketstop_must_go;
	vector<int> poketmon_index_list = map_of_id_to_node_index_list[specific_poketmon_id];
	cout << "poketmon size: " << poketmon_index_list.size() << endl;
	for(limit_of_catch = 1; limit_of_catch <= poketmon_index_list.size(); ++limit_of_catch)
	{
		if(limit_of_catch != 9) continue;
		cout << "limit_of_catch = 9" << endl;
		
		if (limit_of_catch < 4) num_of_poketstop_must_go = 0;
		else if (limit_of_catch < 7) num_of_poketstop_must_go = 1;
		else num_of_poketstop_must_go = 2;

		vector<NodeType> sol;
		sol.push_back(graph.getNodeByIndex(START_ID));
		bool visited[MAX_NODE];
		visited[START_ID] = true;
		for(int i = 1; i < MAX_NODE; ++i)
			visited[i] = false;
		num_poketball = 3;
		int time = 0;
		int num_catch_poketmon = 0;
		backtrack(sol, visited, time, num_catch_poketmon, limit_of_catch, num_of_poketstop_must_go);
	}
	
}

void SolveA::find_solution()
{
	make_all_route();

	Route min_time_route;
	int min_time = 9999;
	for(int i = 0; i < all_solution_routes.size(); ++i)
	{
		cout << "Route " << i << " : ";
		for(int j = 0; j < all_solution_routes[i].route.size(); ++j)
		{
			cout << all_solution_routes[i].route[j].index << " ";
		}
		cout << endl;
		cout << "Number of catched poketmon : " << all_solution_routes[i].num_catch_poketmon << endl;
		cout << "Time of Route : " << all_solution_routes[i].time << endl;
		cout << endl;
		if(all_solution_routes[i].time < min_time)
		{
			min_time = all_solution_routes[i].time;
			min_time_route = all_solution_routes[i];
		}
	}
	
	for(int i = 0; i < min_time_route.route.size(); ++i)
		cout << min_time_route.route[i].index << " ";
	cout << endl;
	cout << "Best Time : " << min_time << endl;
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
	vector<int> poketstop_node_index_List = map_of_id_to_node_index_list[POKETSTOP_ID];
	int min_distance = 9999;
	for(int i = 0; i < poketstop_node_index_List.size(); ++i)
	{
		if(visited[poketstop_node_index_List[i]] == false)
		{
			NodeType stop_node = graph.getNodeByIndex(poketstop_node_index_List[i]); 
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