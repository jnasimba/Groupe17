#include <iostream>
#include <string>
#include <list>
using std::string;
using namespace std;
class Pion
{
private:
	string x;
	string y;
	list<string> Xobjectifs;
	list<Pion> Penattente;
	list<Pion> Pobjectifs;
	
public:
	Pion(string chainey,string chainex,list<Pion> listeEnemi);
	Pion(string chainey,string chainex);

	string getx() const;
	string gety() const;
	
	

	list<Pion> getPobjectifs();
	list<Pion> getPenattente();
};
