/*
Problem B : In specific time, we have to catch 'Any' Poketmon as many as possible.
*/
#pragma once

#include "GraphType.h"
#include "ShortestPath.h"
#include <iostream>
#include <vector>

using namespace std;

#define MAX_NODE 100
#define MAX_CANDIDATES 12
#define NUM_ID 12

#define START_VERTEX 0
#define START_ID 0
#define POKETSTOP_ID 11

class SolveB
{
public:
	//void setGraph(GraphType graph);
	void setProblem(int specific_time);

	void backtrack(vector<NodeType>& sol, bool visited[], int time, int num_catch_poketmon, int num_poketball, int poketStop_time[]);
	bool promising(vector<NodeType>& sol, bool visited[], int time, int num_catch_poketmon);
	void process_solution(vector<NodeType>& sol, int time, int num_catch_poketmon);
	void construct_candidates(vector<NodeType>& sol, bool visited[], vector<int>& cand);
	void update_poketStop_state(bool visited[], int poketStop_time[], int consuming_time, int mode);

	void find_solution();

	//void check_for_home(vector<NodeType>& route, int& time);
	//void search_nodes_by_id(int id, vector<int>& node_list);
	//void find_shortest_path(NodeType destination, vector<NodeType>& route, int& time);

	//void find_closest_poketstop(NodeType cur, NodeType& destination, bool visited[]);

private:
	vector<Route> all_solution_routes;
	GraphType graph;

	vector<vector<int> > map_of_id_to_node_index_list;	// map(Poketmon_id -> node_index_list)
	int specific_time;
	vector<int> poketStop_node_index_list;
};

