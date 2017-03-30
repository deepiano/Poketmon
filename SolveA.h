
#include "GraphType.h"
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

#define MAX_NODE 100
#define MAX_CANDIDATES 10
#define NUM_POKETMON 10

struct Route
{
	vector<NodeType> route;
	int time;
	int poketmon_counter[NUM_POKETMON];
};

class SolveA
{
public:
	void setGraph(GraphType graph);
	vector<Route> getSolutionA();
	void setProblemA(int specificTime, int specific_poketmon_id);

	bool promising(vector<NodeType>& sol);
	void construct_candidates(vector<NodeType>& sol, bool visited[], vector<int>& cand);
	void process_solution(vector<NodeType>& sol, int time, int poketmon_counter[]);
	void backtrack(vector<NodeType>& sol, bool visited[], 
		int time, int poketmon_counter[]);
	void make_all_route();

	void find_solution();

private:
	vector<Route> all_routes;
	GraphType graph;
	int poketmon_counter[NUM_POKETMON];

	int specificTime;
	int specific_poketmon_id;
};

