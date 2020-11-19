#include "pion.h"

Pion::Pion(string chainey,string chainex,list<Pion> listeEnemi)
{
	y=chainey;
	x=chainex;
	for(Pion i:listeEnemi)
	{
			Penattente.push_back(i);		
	}
	
}
	
Pion::Pion(string chainey,string chainex)
{
	y=chainey;
	x=chainex;
	

	}


string Pion::getx() const
{
	return x;
	}
string Pion::gety() const
{
	return y;
	}
list<Pion> Pion::getPenattente()
{
	return Penattente;
	}

	
list<Pion> Pion::getPobjectifs() 
{
	
	return Pobjectifs;
	}
