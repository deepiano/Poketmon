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
	bool unit = 0;
	if (unit)
	{
		cout << "Unit Test" << endl;
		
		//int spec_time = 300;
		// int spec_id = 1;

		// GreedySolveA ga;
		// ga.setProblem(spec_time, spec_id);
		// ga.find_solution();

		SolveC c;
		c.setProblem();
		c.find_solution();
		return 0;
	}

	
	clock_t begin, end;


	int sel;
	cout << "*** Test ***" << endl << endl;
	sel = 1;
	cout << "Choose the number of problem" << endl;
	cout << "1. SolveA" << endl;
	cout << "2. SolveB" << endl;
	cout << "3. SolveC" << endl;
	cout << "4. G SolveA" << endl;
	cout << "5. G SolveB" << endl;
	cout << "6. G SolveC" << endl;
	cin >> sel;

	begin = clock();
	if (sel == 1)
	{
		SolveA solveA;
		int spec_time, spec_poketmon_id;
		cout << "Enter specific time: ";
		cin >> spec_time;
		cout << "Enter specific poketmon_id: ";
		cin >> spec_poketmon_id;
		spec_time = 300;		
		spec_poketmon_id = 1;
		solveA.setProblem(spec_time, spec_poketmon_id);
		solveA.find_solution();
	}
	else if (sel == 2)
	{
		SolveB solveB;
		int spec_time;
		cout << "Enter specific time: ";
		cin >> spec_time;
		spec_time = 200;
		solveB.setProblem(spec_time);
		solveB.find_solution();
	}
	else if (sel == 3)
	{
		SolveC solveC;
		solveC.setProblem();
		solveC.find_solution();
	}
	else if (sel == 4)
	{
		GreedySolveA ga;
		int spec_time, spec_poketmon_id;
		cout << "Enter specific time: ";
		cin >> spec_time;
		cout << "Enter specific poketmon_id: ";
		cin >> spec_poketmon_id;
		ga.setProblem(spec_time, spec_poketmon_id);
		ga.find_solution();
	}
	else if (sel == 5)
	{
		GreedySolveB gb;
		int spec_time;
		cout << "Enter specific time: ";
		cin >> spec_time;
		gb.setProblem(spec_time);
		gb.find_solution();
	}
	else
	{
		cout << "gc" << endl;
		GreedySolveC gc;
		gc.setProblem();
		gc.find_solution();
	}

	end = clock();
	cout << endl << "Algorithm Search Time : " << ((end - begin) / CLOCKS_PER_SEC) << endl;

	return 0;
}

