#include "SolveA.h"
#include "SolveB.h"

#include <iostream>
using namespace std;

int main()
{
	int sel;
	cout << "*** Test ***" << endl << endl;
	sel = 2;
	//cout << "Choose the number of problem" << endl;
	//cin >> sel;
	if (sel == 1)
	{
		SolveA solveA;
		int spec_time, spec_poketmon_id;
		cout << "Enter specific time: ";
		cin >> spec_time;
		cout << "Enter specific poketmon_id: ";
		cin >> spec_poketmon_id;
		//spec_time = 600;		// you can change this.
		//spec_poketmon_id = 1;	// you can change this.
		solveA.setProblemA(spec_time, spec_poketmon_id);
		solveA.find_solution();
	}
	else if (sel == 2)
	{
		SolveB solveB;
		int spec_time;
		//cout << "Enter specific time: ";
		//cin >> spec_time;
		spec_time = 200;
		solveB.setProblem(spec_time);
		solveB.find_solution();
	}
	else
	{

	}

	/*GraphType g;
	int index1 = 77, index2 = 75;
	NodeType node1 = g.getNodeByIndex(index1), node2 = g.getNodeByIndex(index2);
	cout << g.WeightIs(node1, node2) << endl;*/

	return 0;
}

