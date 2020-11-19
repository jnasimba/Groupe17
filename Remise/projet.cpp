#include "tableau.h"
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
int main()
{
	

	Tableau tableau;

	tableau.placeslibres("noir");
	tableau.choisirCase("noir");
	return 0;

	}
