/*
Problem C : We have to catch at least one 'Every kind' of Poketmon as fast as possible.
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

class GreedySolveC
{
public:
	void setProblem();
	void setGraph(GraphType g);

	void greedy(vector<NodeType>& sol, bool visited[], int time, bool poketmon_type_checkList[], int num_poketboll, int num_catch_poketmon, int num_must_go_pStop, int poketStop_time[], vector<int> &catch_order);
	void determine_next_node(bool visited[],NodeType& node,vector<int> distList,vector<int> nodeList,int num_pBall,int mustGoPStop);
	bool promising(int num_catch_poketmon);
	void process_solution(vector<NodeType>& sol, int time, vector<int> &catch_order);
	void construct_candidates(vector<NodeType>& sol, bool visited[], vector<int>& cand,vector<int>& distList, int num_poketball, bool poketmon_type_checkList[], int num_must_go_pStop);

	void find_solution();
	void make_all_route();

	void check_for_home(vector<NodeType>& route, int& time);
	void search_nodes_by_id(int id, vector<int>& node_list);
	void find_shortest_path(NodeType destination, vector<NodeType>& route, int& time);

	void find_closest_poketstop(NodeType cur, NodeType& destination, bool visited[]);
	void find_closest_poketmons(NodeType cur,vector<int>& distList, vector<int>& closest_poketmon_node_index_list, bool visited[], bool poketmon_type_checkList[]);

private:
	Route best_route;
	GraphType graph;

	vector<vector<int> > map_of_id_to_node_index_list;	// map(Poketmon_id -> node_index_list)
	vector<int> pStop_node_index_list;
};