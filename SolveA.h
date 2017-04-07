#pragma once
#include "GraphType.h"
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

#define MAX_NODE 100
#define MAX_CANDIDATES 12
#define NUM_ID 12

#define START_ID 0
#define POKETSTOP_ID 11

struct Route
{
	vector<NodeType> route;
	int time;
	int num_catch_poketmon;
};

/*
	ProblemA : In specific time, we have to catch specific Poketmon as many as possible.
*/
class SolveA
{
public:
	void setGraph(GraphType graph);
	void setProblemA(int specific_time, int specific_poketmon_id);

	vector<Route> getSolutionA();
	
	/*
	sol : solution
	visited : if true - The place has visited
	time : time
	num_catch_poketmon : check number of catched poketmon
	*/
	void backtrack(vector<NodeType>& sol, bool visited[], int time, int num_catch_poketmon);
	bool promising(vector<NodeType>& sol, int time);
	void construct_candidates(vector<NodeType>& sol, bool visited[], vector<int>& cand, bool can_catch_poketmon);
	void process_solution(vector<NodeType>& sol, int time, int num_catch_poketmon);
	void make_all_route();

	void find_solution();

	void search_nodes_by_id(int id, vector<NodeType>& node_list);
	void find_shortest_path(NodeType destination, vector<NodeType>& route, int& time);
	void check_for_home(vector<NodeType>& route, int& time);
	bool can_catch_poketmon();

private:
	vector<Route> all_solution_routes;
	GraphType graph;
	vector<vector<NodeType>> map_of_id_to_node;

	int specific_time;
	int specific_poketmon_id;
	int num_poketball;
};

