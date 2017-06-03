/*
ProblemA : In specific time, we have to catch 'specific' Poketmon as many as possible.
*/
#pragma once
#include "GraphType.h"
#include "ShortestPath.h"
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

#define MAX_NODE 100
#define MAX_CANDIDATES 12
#define NUM_ID 12

#define START_VERTEX 0
#define START_ID 0
#define POKETSTOP_ID 11

class GreedySolveA
{
public:

	void setProblem(int specific_time, int specific_poketmon_id);

	/*
	sol : solution
	visited : if true - The place has visited
	time : time
	num_catch_poketmon : check number of catched poketmon
	*/
	void backtrack(vector<NodeType>& sol, bool visited[], int time, int num_poketball, int num_catch_poketmon, int limit_of_catch, int num_of_poketstop_must_go, int poketStop_time[]);
	bool promising(vector<NodeType>& sol, bool visited[], int time, int num_catch_poketmon, int limit_of_catch);
	void process_solution(vector<NodeType>& sol, int time, int num_catch_poketmon);
	void construct_candidates(vector<NodeType>& sol, bool visited[], int time, vector<int>& cand, int num_poketball, int limit_of_catch, int num_of_poketstop_must_go);
	
	void make_all_route();

	void find_solution();

	void check_for_home(vector<NodeType>& route, int& time);
	void find_shortest_path(NodeType destination, vector<NodeType>& route, int& time);
	
	void find_closest_poketstop(NodeType cur, NodeType& destination, bool visited[]);

private:
	vector<Route> all_solution_routes;
	Route best_route;
	GraphType graph;
	vector<vector<int> > map_of_id_to_node_index_list;	// map(Poketmon_id -> node_index_list)
	vector<int> pStop_node_index_list;
	int specific_time;
	int specific_poketmon_id;

	int limit_time_for_poketStop;
	int first_catch_poketmon_index;
};

