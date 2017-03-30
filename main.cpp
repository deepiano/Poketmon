#include "SolveA.h"

int test5[5][5] =
{
	{0, 1, 1, 1, 0},
	{1, 0, 1, 0, 0},
	{1, 1, 0, 1, 1},
	{1, 0, 1, 0, 1},
	{0, 0, 1, 1, 0}
};



int main()
{
	SolveA solveA;

	//cout<<"How many?: ";
	int n = 5;
	int **test = new int*[n];
	for(int i = 0; i < n; ++i)
	{
		test[i] = new int[n];
	}
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			test[i][j] = test5[i][j];
		}
	}

	GraphType g(test, n);

	solveA.setGraph(g);
	solveA.find_solution();
}

