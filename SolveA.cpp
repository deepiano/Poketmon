#include "SolveA.h"

void SolveA::setGraph(GraphType graph)
{
	this->graph = graph;
}

void SolveA::setProblemA(int specificTime, int specific_poketmon_id)
{
	this->specificTime = specificTime;
	this->specific_poketmon_id = specific_poketmon_id;
}

vector<Route> SolveA::getSolutionA()
{
	return all_routes;
}


// sol : route
// 처음 노드와 마지막 노드가 같은지 확인( 처음 장소로 돌아왔는지)
bool SolveA::promising(vector<NodeType>& sol)
{
	if (sol.size() == 1) return false;
	if (sol.back().MonsterType == START_ID)
	{
		return true;
	}
	return false;
}


// 방문하지 않은 노드만 방문하도록 후보를 만든다.
void SolveA::construct_candidates(vector<NodeType>& sol, bool visited[], vector<int>& cand)
{
	vector<int> adj;

	// 현재 까지의 경로 중 마지막 노드의 인접 노드 vector
	adj = graph.getAdjacent(sol.back());	 // 인접노드 받기

	for(int i = 0; i < adj.size(); ++i)
	{
		NodeType cur_node = graph.getNodeByIndex(adj[i]);
		if (cur_node.MonsterType == START_ID) cand.push_back(cur_node.index);
		else if(!visited[adj[i]]) 
			cand.push_back(adj[i]);
	}
}

// 완성된 한 cur_route(회로)를 all_route에 추가한다.
void SolveA::process_solution(vector<NodeType>& sol, int time, int poketmon_counter[])
{
	Route cur_route;
	cur_route.route = sol;
	cur_route.time = time;
	for(int i = 0; i < NUM_ID; ++i)
		cur_route.poketmon_counter[i] = poketmon_counter[i];
	all_routes.push_back(cur_route);
}


void SolveA::backtrack(vector<NodeType>& sol, bool visited[], int time, int poketmon_counter[])
{
	vector<int> cand;

	if ( promising(sol) )
		process_solution(sol, time, poketmon_counter);
	else
	{
		construct_candidates(sol, visited, cand);
		for(int i = 0; i < cand.size(); ++i)
		{
			NodeType cur_node;
			cur_node = graph.getNodeByIndex(cand[i]);
			sol.push_back(cur_node);
			visited[cur_node.index] = true;
			time += graph.WeightIs(sol[sol.size()-2], sol[sol.size()-1]);
			if (cur_node.MonsterType != START_ID)
				poketmon_counter[cur_node.MonsterType]++;

			backtrack(sol, visited, time, poketmon_counter);

			time -= graph.WeightIs(sol[sol.size()-2], sol[sol.size()-1]);
			if (cur_node.MonsterType != START_ID)
				poketmon_counter[cur_node.MonsterType]--;
			sol.pop_back();
			visited[cur_node.index] = false;
		}
	}
}


// 모든 회로를 만든다.
void SolveA::make_all_route()
{
	vector<NodeType> sol;
	sol.push_back(graph.getNodeByIndex(0));
	bool visited[MAX_NODE];
	visited[0] = true;
	for(int i = 1; i < MAX_NODE; ++i)
		visited[i] = false;
	specificTime = 0;
	for(int i = 0; i < NUM_ID; ++i)
		poketmon_counter[i]  = 0;
	backtrack(sol, visited, specificTime, poketmon_counter);
}

void SolveA::find_solution()
{
	make_all_route();

	for(int i = 0; i < all_routes.size(); ++i)
	{
		cout << "Route " << i << " : ";
		for(int j = 0; j < all_routes[i].route.size(); ++j)
		{
			cout << all_routes[i].route[j].index << " ";
		}
		cout << endl;
		cout << "Poketmon counter of Route :" << endl;
		for(int j = 0; j < NUM_ID; ++j)
		{
			cout << "[" << j << "]" << all_routes[i].poketmon_counter[j] << " ";
		}
		cout << endl;
		cout << "Time of Route : " << all_routes[i].time;
		cout << endl;
		cout << endl;
	}

	/*int big = 0;
	int big_route_index = 0;
	for(int i = 0; i < all_routes.size(); ++i)
	{
		if(all_routes[i].poketmon_counter[specific_poketmon_id] > big
			&& all_routes[i].time <= specificTime)
		{	
			big = all_routes[i].poketmon_counter[specific_poketmon_id];
			big_route_index = i;
		}
	}

	for(int i = 0; i < all_routes[big_route_index].route.size(); ++i)
	{
		cout << all_routes[big_route_index].route[i].index << " ";
	}*/
}


