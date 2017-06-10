
#include "SolveA.h"
#include "SolveB.h"
#include "SolveC.h"
#include "GreedySolveA.h"
#include "GreedySolveB.h"
#include "GreedySolveC.h"

#include <iostream>
#include <time.h>
using namespace std;

int main()
{
	bool unit = 1;
	if (unit)
	{
		cout << "Unit Test" << endl;
		
		int spec_time = 300;
		// int spec_id = 1;

		// GreedySolveA ga;
		// ga.setProblem(spec_time, spec_id);
		// ga.find_solution();

		//GreedySolveB gb;
		//gb.setProblem(spec_time);
		//gb.find_solution();
    
    GreedySolveC c;
    	c.setGraph(g);
	c.setProblem();
	c.find_solution();
		return 0;
	}

	
	clock_t begin, end;
	begin = clock();

	int sel;
	cout << "*** Test ***" << endl << endl;
	sel = 1;
	//cout << "Choose the number of problem" << endl;
	//cin >> sel;
	if (sel == 1)
	{
		SolveA solveA;
		int spec_time, spec_poketmon_id;
		/*cout << "Enter specific time: ";
		cin >> spec_time;
		cout << "Enter specific poketmon_id: ";
		cin >> spec_poketmon_id;*/
		spec_time = 300;		
		spec_poketmon_id = 1;
		solveA.setProblem(spec_time, spec_poketmon_id);
		solveA.find_solution();
	}
	// else if (sel == 2)
	// {
	// 	SolveB solveB;
	// 	int spec_time;
	// 	//cout << "Enter specific time: ";
	// 	//cin >> spec_time;
	// 	spec_time = 200;
	// 	solveB.setProblem(spec_time);
	// 	solveB.find_solution();
	// }
	// else
	// {
	// 	SolveC solveC;
	// 	solveC.setProblem();
	// 	solveC.find_solution();
	// }

	end = clock();
	cout << endl << "Algorithm Search Time : " << ((end - begin) / CLOCKS_PER_SEC) << endl;

	return 0;
}

