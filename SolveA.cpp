#include "SolveA.h"

void SolveA::setGraph(GraphType graph)
{
	this->graph = graph;
}

void SolveA::setProblemA(int specific_time, int specific_poketmon_id)
{
	this->specific_time = specific_time;
	this->specific_poketmon_id = specific_poketmon_id;
	this->num_poketball = 2;
}

vector<Route> SolveA::getSolutionA()
{
	return all_routes;
}


// sol : route
// ó�� ������ ������ ���尡 ������ Ȯ��( ó�� ���ҷ� ���ƿԴ���)
bool SolveA::promising(vector<NodeType>& sol)
{
	if (sol.size() == 1) return false;
	if (sol.back().MonsterType == START_ID)
	{
		return true;
	}
	return false;
}


// �湮���� ���� ���常 �湮�ϵ��� �ĺ��� ������.
void SolveA::construct_candidates(vector<NodeType>& sol, bool visited[], bool catched[], vector<int>& cand)
{
	vector<int> adj;

	// ���� ������ ���� �� ������ ������ ���� ���� vector
	adj = graph.getAdjacent(sol.back());	 // �������� �ޱ�

	for(int i = 0; i < adj.size(); ++i)
	{
		NodeType cur_node = graph.getNodeByIndex(adj[i]);
		if (cur_node.MonsterType == START_ID) cand.push_back(cur_node.index);
		else if (num_poketball == 0 && !catched[adj[i]]) 
			cand.push_back(adj[i]);
		else if (num_poketball > 0 && !visited[adj[i]])
			cand.push_back(adj[i]);
	}
}

// �ϼ��� �� cur_route(ȸ��)�� all_route�� �߰��Ѵ�.
void SolveA::process_solution(vector<NodeType>& sol, int time, int poketmon_counter[])
{
	Route cur_route;
	cur_route.route = sol;
	cur_route.time = time;
	for(int i = 0; i < NUM_ID; ++i)
		cur_route.poketmon_counter[i] = poketmon_counter[i];
	all_routes.push_back(cur_route);
}


void SolveA::backtrack(vector<NodeType>& sol, bool visited[], bool catched[], int time, int poketmon_counter[])
{
	vector<int> cand;

	if ( promising(sol) )
		process_solution(sol, time, poketmon_counter);
	else
	{
		construct_candidates(sol, visited, catched, cand);
		for(int i = 0; i < cand.size(); ++i)
		{
			NodeType cur_node;
			cur_node = graph.getNodeByIndex(cand[i]);
			sol.push_back(cur_node);
			time += graph.WeightIs(sol[sol.size()-2], sol[sol.size()-1]);
			// cout << "cur_index : " << cur_node.index << endl;
			visited[cur_node.index] = true;
			if(num_poketball != 0 && cur_node.MonsterType != START_ID)
			{
				catched[cur_node.index] = true;
				poketmon_counter[cur_node.MonsterType]++;
				num_poketball--;
				// cout << "num_poketball : " << num_poketball << endl;
			}
			backtrack(sol, visited, catched, time, poketmon_counter);

			visited[cur_node.index] = false;
			if(num_poketball != 0 && cur_node.MonsterType != START_ID)
			{
				catched[cur_node.index] = false;
				poketmon_counter[cur_node.MonsterType]--;
				num_poketball++;
			}
			time -= graph.WeightIs(sol[sol.size()-2], sol[sol.size()-1]);
			sol.pop_back();
			
		}
	}
}


// ���� ȸ�θ� ������.
void SolveA::make_all_route()
{
	vector<NodeType> sol;
	sol.push_back(graph.getNodeByIndex(0));
	bool visited[MAX_NODE];
	bool catched[MAX_NODE];
	visited[0] = true;
	for(int i = 1; i < MAX_NODE; ++i)
		visited[i] = false;
	catched[0] = true;
	for(int i = 1; i < MAX_NODE; ++i)
		catched[i] = false;
	specific_time = 0;
	for(int i = 0; i < NUM_ID; ++i)
		poketmon_counter[i]  = 0;
	num_poketball = 2;
	backtrack(sol, visited, catched, specific_time, poketmon_counter);
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
			&& all_routes[i].time <= specific_time)
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


