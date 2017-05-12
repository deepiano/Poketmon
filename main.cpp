#include "SolveA.h"

#include <iostream>
#include <fstream>
using namespace std;

const int NUM_NODE_TEST = 5;
int** test;
//GraphType g;

void setTest()
{

	ifstream fileIn;
	fileIn.open("test2.txt");
	if(!fileIn)
	{
		cerr << "test2.txt error" << endl;
		exit(100);
	}

	test = new int*[NUM_NODE_TEST];
	for(int i = 0; i < NUM_NODE_TEST; ++i)
	{
		test[i] = new int[NUM_NODE_TEST];
	}

	cout << "adjMatrix : " << endl;
	for(int i = 0; i < NUM_NODE_TEST; ++i)
	{
		for(int j = 0; j < NUM_NODE_TEST; ++j)
		{
			fileIn >> test[i][j];
			cout << test[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	
	int node_index;
	int place_id;
	NodeType* node_list = new NodeType[NUM_NODE_TEST];
	for(int i = 0; i < NUM_NODE_TEST; ++i)
	{
		fileIn >> node_index >> place_id;
		node_list[i].index = node_index;
		node_list[i].MonsterType = place_id;
		// cout << node_index << ' ' << place_id << endl;
	}

	//g.setGraphType(test, node_list, NUM_NODE_TEST);
}

int main()
{
	cout << "*** Test ***" << endl << endl;
	SolveA solveA;
	//setTest();
	//solveA.setGraph(g);
	int spec_time, spec_poketmon_id;
	// cout << "Enter specific time: "; 
	// cin >> spec_time;
	// cout << "Enter specific poketmon_id: "; 
	// cin >> spec_poketmon_id;
	spec_time = 600;
	spec_poketmon_id = 1;
	solveA.setProblemA(spec_time, spec_poketmon_id);
	solveA.find_solution();
}

