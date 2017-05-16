#include "SolveA.h"
#include "SolveB.h"
#include "SolveC.h"

#include <iostream>
#include <time.h>
using namespace std;

int main()
{
	clock_t begin, end;
	begin = clock();

	int sel;
	cout << "*** Test ***" << endl << endl;
	sel = 3;
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
		SolveC solveC;
		solveC.setProblem();
		solveC.find_solution();
	}

	end = clock();
	cout << endl << "Algorithm Search Time : " << ((end - begin) / CLOCKS_PER_SEC) << endl;

	return 0;
}

