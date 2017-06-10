#include "SolveB.h"

void SolveB::setProblem(int specific_time)
{
	this->specific_time = specific_time;
	map_of_id_to_node_index_list = graph.getMap();
	poketStop_node_index_list = map_of_id_to_node_index_list[POKETSTOP_ID];
}


void SolveB::backtrack(vector<NodeType>& sol, bool visited[], int time, int num_catch_poketmon, int num_poketball, int poketStop_time[])
{
	vector<int> cand;

	if (promising(sol, visited, time, num_catch_poketmon))
	{
		process_solution(sol, time, num_catch_poketmon);
	}
	else
	{
		construct_candidates(sol, visited, cand);

		for (int i = 0; i < cand.size(); ++i)
		{
			NodeType next_node = graph.getNodeByIndex(cand[i]);
			int next_num_poketball = num_poketball;
			int next_num_catch_poketmon = num_catch_poketmon;
			bool* next_visited = new bool[MAX_NODE];
			int* next_poketStop_time = new int[MAX_NODE];
			int consuming_time = graph.WeightIs(sol.back(), next_node);

			if (specific_time < time + consuming_time)	continue;

			for (int i = 0; i < MAX_NODE; ++i)
			{
				next_visited[i] = visited[i];
				next_poketStop_time[i] = poketStop_time[i];
			}

			sol.push_back(next_node);	// Go to the next_node
			
			next_visited[cand[i]] = true;
			time += consuming_time;
	
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

			backtrack(sol, next_visited, time, next_num_catch_poketmon, next_num_poketball, next_poketStop_time);

			/* return to origin state */
			sol.pop_back();
			time -= consuming_time;
		}
	}

}


bool SolveB::promising(vector<NodeType>& sol, bool visited[], int time, int num_catch_poketmon)
{
	if (time <= specific_time && sol.size() != 1)
		if (sol.back().MonsterType == START_ID)
			return true;
	return false;
}


void SolveB::process_solution(vector<NodeType>& sol, int time, int num_catch_poketmon)
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
}


void SolveB::construct_candidates(vector<NodeType>& sol, bool visited[], vector<int>& cand)
{
	NodeType last_node = sol.back();
	vector<int> adjList = graph.getAdjacent(last_node);

	for (int i = 0; i < adjList.size(); ++i)
	{
		if (!visited[adjList[i]])
		{
			cand.push_back(adjList[i]);
		}
	}
}
  
/* 
if mode == 0, then poketStop_time decreases.
else if mode == 1, then poketStop_time return to origin.
*/
void SolveB::update_poketStop_state(bool visited[], int poketStop_time[], int consuming_time, int mode)
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

void SolveB::find_solution()
{
	// try backtrack
	vector<NodeType> sol;
	sol.push_back(graph.getNodeByIndex(0));
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
}