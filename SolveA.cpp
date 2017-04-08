#include "SolveA.h"

void SolveA::setGraph(GraphType graph)
{
	this->graph = graph;
	//this->map_of_id_to_node = graph.getMap();
}

void SolveA::setProblemA(int specific_time, int specific_poketmon_id)
{
	this->specific_time = specific_time;
	this->specific_poketmon_id = specific_poketmon_id;
}

vector<Route> SolveA::getSolutionA()
{
	return all_solution_routes;
}



// ó�� ������ ������ ���尡 ������ Ȯ��( ó�� ���ҷ� ���ƿԴ���)
bool SolveA::promising(vector<NodeType>& sol, bool visited[], int time)
{
	if (time >= specific_time) return false;
	vector<NodeType> test_sol = sol;
	check_for_home(test_sol, time);
	if (time > specific_time) return false;

	vector<NodeType> node_list;
	search_nodes_by_id(specific_poketmon_id, node_list);

	for(int i = 0; i < node_list.size(); ++i)
		if(visited[node_list[i].index] == false)
			return false;

	return true;
}


// �湮���� ���� ���常 �湮�ϵ��� �ĺ��� ������.
void SolveA::construct_candidates(vector<NodeType>& sol, bool visited[], vector<int>& cand, bool can_catch_poketmon)
{
	vector<NodeType> node_list;
	if (can_catch_poketmon)
	{
		node_list = map_of_id_to_node[specific_poketmon_id];
	}
	else
	{
		node_list = map_of_id_to_node[POKETSTOP_ID];
	}

	for(int i = 0; i < node_list.size(); ++i)
	{
		if (!visited[node_list[i].index])
			cand.push_back(node_list[i].index);
	}
}

// �ϼ��� �� cur_route(ȸ��)�� all_route�� �߰��Ѵ�.
void SolveA::process_solution(vector<NodeType>& sol, int time, int num_catch_poketmon)
{
	Route cur_route;
	cur_route.route = sol;
	cur_route.time = time;
	cur_route.num_catch_poketmon = num_catch_poketmon;
	all_solution_routes.push_back(cur_route);
}


void SolveA::backtrack(vector<NodeType>& sol, bool visited[], int time, int num_catch_poketmon)
{
	vector<int> cand;

	if ( promising(sol, visited, time) )
		process_solution(sol, time, num_catch_poketmon);
	else
	{
		bool can_catch_poketmon = false;
		if (num_poketball > 0)
			can_catch_poketmon = true;

		construct_candidates(sol, visited, cand, can_catch_poketmon);

		for(int i = 0; i < cand.size(); ++i)
		{
			NodeType destination;
			destination = graph.getNodeByIndex(cand[i]);
			vector<NodeType> test_sol = sol;
			int test_time = time;
			find_shortest_path(destination, test_sol, test_time);
			visited[destination.index] = true;
			if (can_catch_poketmon) num_catch_poketmon++;

			backtrack(test_sol, visited, test_time, num_catch_poketmon);

			visited[destination.index] = false;
			if (can_catch_poketmon) num_catch_poketmon--;
		}
	}
}


// ���� ȸ�θ� ������.
void SolveA::make_all_route()
{
	vector<NodeType> sol;
	sol.push_back(graph.getNodeByIndex(START_ID));
	bool visited[MAX_NODE];
	visited[START_ID] = true;
	for(int i = 1; i < MAX_NODE; ++i)
		visited[i] = false;
	num_poketball = 2;
	int time = 0;
	int num_catch_poketmon = 0;
	backtrack(sol, visited, time, num_catch_poketmon);
}

void SolveA::find_solution()
{
	make_all_route();

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
	}
}


void SolveA::check_for_home(vector<NodeType>& route, int& time)
{
	NodeType destination;
	destination.index = START_VERTEX;
	find_shortest_path(destination, route, time);
}


void SolveA::search_nodes_by_id(int id, vector<NodeType>& node_list)
{
	node_list = this->map_of_poketmon_id_to_node[id];
}


void SolveA::find_shortest_path(NodeType destination, vector<NodeType>& route, int& time)
{
	int num_vertex = this->graph.getNodeCount();
	int** adj = this->graph.getAdjMatrix();
	int start = route.back().index;
	int end = destination.index;
	Dijkstra(num_vertex, adj, start, end, route, time);
}