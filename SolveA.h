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

class SolveA
{
public:
	void setGraph(GraphType graph);
	void setProblemA(int specific_time, int specific_poketmon_id);

	vector<Route> getSolutionA();
	
	void backtrack(vector<NodeType>& sol, bool visited[], bool catched[], int time, int poketmon_counter[]);
	bool promising(vector<NodeType>& sol);
	void construct_candidates(vector<NodeType>& sol, bool visited[], bool catched[], vector<int>& cand);
	void process_solution(vector<NodeType>& sol, int time, int poketmon_counter[]);
	void make_all_route();




	void find_solution();

private:
	vector<Route> all_routes;
	GraphType graph;
	int poketmon_counter[NUM_ID];

	int specific_time;
	int specific_poketmon_id;
	int num_poketball;
};

