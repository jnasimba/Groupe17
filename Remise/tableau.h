#include "pion.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <list>
using std::string;

using namespace std;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::string;
using std::getline;
class Tableau
{
private:
	string pion_noir ="X";
	string pion_blanc ="O";
	
	bool Xpossible=true;// verifier que le joueur peut jouer
	bool Opossible=true;
	

	list<Pion*> listX;		//On va creer une liste de ions noir
	list<Pion*> listO;		//On va creer une liste de ions blancs
	

	list<string> listchoixY;
	
	string tab[10][10];
	int compteur_pion_noir=2;
	int compteur_pion_blanc=2;	
	
	list<Pion> Pobjectifs;	//manger pions
	list<Pion> Penattente;
	
	
public:
	Tableau();//new Tableau dans le main
	Tableau(string chaine);
	
	
	int getCompteurNoir() const;			
	void incrementeCompteurNoir(int p);	
	int getCompteurBlanc() const;			
	void incrementeCompteurBlanc(int p);	
	
	void imprimeTableau() const;
	void cleanHashtag();

	void creerTab();
	bool getTourNoir();
	void setTourNoir(bool c);
	
	void placerPion(string type ,int c,int l);
	void placeslibres(string type);
	void choisirCase(string type);
	void finTour(string type);//passer tour
	void insereX(string y,string x);
	void insereO(string y,string x);
	void endGame();
	bool getXPossible();
	void setXPossible(bool c);
	bool getOPossible();
	void setOPossible(bool c);
	bool placementPossible();
	
	list<Pion> getPobjectifs();										//manger pions
	void viderListes(string type);
	void changePion(string l,string c,list<Pion*> L,string type);
};
