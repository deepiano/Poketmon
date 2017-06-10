#ifndef SPECIFICMONSCATCH_H
#define SPECIFICMONSCATCH_H
#include <QStack>
#include <string>
#include <iostream>
#include "graphtype.h"
#include "selectalgorithm.h"

using namespace std;
#define MAX_NODE 100
#define MAX_CANDIDATES 12
#define NUM_ID 12

#define START_VERTEX 0
#define START_ID 0
#define POKETSTOP_ID 11




class SpecificMonsCatch : public SelectAlgorithm
{
private:
    QVector<Route> all_solution_routes;
    Route best_route;
    QVector<QVector<int> > map_of_id_to_node_index_list;	// map(Poketmon_id -> node_index_list)
    QVector<int> pStop_node_index_list;
    int specific_time;
    int specific_poketmon_id;

    int limit_time_for_poketStop;
    int first_catch_poketmon_index;

public:
    SpecificMonsCatch();
    void SetGraph(GraphType* gr);
    void SetProblem(QVector<int> data);
    QVector<QString> FindRoute();

    void backtrack(QVector<NodeType>& sol, bool visited[], int time, int num_poketball, int num_catch_poketmon, int limit_of_catch, int num_of_poketstop_must_go, int poketStop_time[]);
    bool promising(QVector<NodeType>& sol, bool visited[], int time, int num_catch_poketmon, int limit_of_catch);
    void process_solution(QVector<NodeType>& sol, int time, int num_catch_poketmon);
    void construct_candidates(QVector<NodeType>& sol, bool visited[], int time, QVector<int>& cand, int num_poketball, int limit_of_catch, int num_of_poketstop_must_go);

    void make_all_route();

    void check_for_home(QVector<NodeType>& route, int& time);
    void find_shortest_path(NodeType destination, QVector<NodeType>& route, int& time);

    void find_closest_poketstop(NodeType cur, NodeType& destination, bool visited[]);

};

#endif // SPECIFICMONSCATCH_H
