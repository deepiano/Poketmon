#include "SolveA.h"

#include <iostream>
#include <fstream>
using namespace std;

int** test;
GraphType g;

void setTest()
{

	ifstream fileIn;
	fileIn.open("test.txt");
	if(!fileIn)
	{
		cerr << "test.txt error" << endl;
		exit(100);
	}

	test = new int*[5];
	for(int i = 0; i < 5; ++i)
	{
		test[i] = new int[5];
	}

	cout << "adjMatrix : " << endl;
	for(int i = 0; i < 5; ++i)
	{
		for(int j = 0; j < 5; ++j)
		{
			fileIn >> test[i][j];
			cout << test[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	
	int node_index;
	int place_id;
	NodeType* node_list = new NodeType[5];
	for(int i = 0; i < 5; ++i)
	{
		fileIn >> node_index >> place_id;
		node_list[i].index = node_index;
		node_list[i].MonsterType = place_id;
	}

	g.setGraphType(test, node_list, 5);
}

int main()
{
	cout << "***Test***" << endl << endl;
	SolveA solveA;
	setTest();
	solveA.setGraph(g);
	solveA.find_solution();
}

