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
	int poketmon_counter[NUM_ID];
};

/*
	ProblemA : In specific time, we have to catch specific Poketmon as many as possible.
*/
class SolveA
{
public:
	void setGraph(GraphType graph);
	void setProblemA(int specificTime, int specific_poketmon_id);

	vector<Route> getSolutionA();
	
	/*
	sol : solution
	visited : if true - The place has visited
	catched : if true - Poketmon has catched
	time : time
	poketmon_counter : check counter
	*/
	void backtrack(vector<NodeType>& sol, bool visited[], bool catched[], int time, int poketmon_counter[]);
	bool promising(vector<NodeType>& sol);
	void construct_candidates(vector<NodeType>& sol, bool visited[], bool cahtched[], vector<int>& cand);
	void process_solution(vector<NodeType>& sol, int time, int poketmon_counter[]);
	void make_all_route();

	void find_solution();

private:
	vector<Route> all_routes;
	GraphType graph;
	int poketmon_counter[NUM_ID];

	int specificTime;
	int specific_poketmon_id;
	int num_poketball;
};

