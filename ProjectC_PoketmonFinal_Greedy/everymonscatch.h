#ifndef EVERYMONSCATCH_H
#define EVERYMONSCATCH_H
#define MAX_NODE 100
#define MAX_CANDIDATES 12
#define NUM_ID 12

#define START_VERTEX 0
#define START_ID 0
#define POKETSTOP_ID 11
#include "selectalgorithm.h"
class EveryMonsCatch : public SelectAlgorithm
{
private:
    Route best_route;
    QVector<QVector<int> > map_of_id_to_node_index_list;	// map(Poketmon_id -> node_index_list)
    QVector<int> pStop_node_index_list;
public:
    EveryMonsCatch();
    QVector<QString> FindRoute();
    void SetProblem(QVector<int> data);
    void SetGraph(GraphType* gr);
    void greedy(QVector<NodeType>& sol, bool visited[], int time, bool poketmon_type_checkList[], int num_poketboll, int num_catch_poketmon, int num_must_go_pStop, int poketStop_time[], QVector<int> &catch_order);
    void determine_next_node(bool visited[],NodeType& node,QVector<int> distList,QVector<int> nodeList,int num_pBall,int mustGoPStop);
    bool promising(int num_catch_poketmon);
    void process_solution(QVector<NodeType>& sol, int time, QVector<int> &catch_order);
    void construct_candidates(QVector<NodeType>& sol, bool visited[], QVector<int>& cand,QVector<int>& distList, int num_poketball, bool poketmon_type_checkList[], int num_must_go_pStop);

    void make_all_route(QVector<int>& catch_order);

    void check_for_home(QVector<NodeType>& route, int& time);
    void search_nodes_by_id(int id, QVector<int>& node_list);
    void find_shortest_path(NodeType destination, QVector<NodeType>& route, int& time);

    void find_closest_poketstop(NodeType cur, NodeType& destination, bool visited[]);
    void find_closest_poketmons(NodeType cur,QVector<int>& distList, QVector<int>& closest_poketmon_node_index_list, bool visited[], bool poketmon_type_checkList[]);
};

#endif // EVERYMONSCATCH_H
