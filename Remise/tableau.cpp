#include "tableau.h"
#include <stdio.h>
#include <string.h>
using std::cout;
using std::endl;
Tableau::Tableau()
{
	
	creerTab();
	
	}
	
void Tableau::imprimeTableau() const
{
	for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j){
     cout << tab[i][j] << " ";
     }
    cout << endl;
	}
}
list<Pion> Tableau::getPobjectifs()
{
	return Pobjectifs;
	}	
	
void Tableau::viderListes(string type)
{
	Pobjectifs.clear();
	Penattente.clear();
	
}
void Tableau::creerTab()		
{
  string t[10][10];				//on met des points dans les cases
  string lettres[8] = {"a","b","c","d","e","f","g","h"};
  string num[8]={"1","2","3","4","5","6","7","8"};
	int k,j;
	
	for (k = 1; k < 9; k++){
		tab[k][0] = num[k-1];
		tab[k][9] = num[k-1];
	}
	tab[0][1] = " "+lettres[0];
	tab[9][1] = " "+lettres[0];
	for (j = 2; j < 9; j++){
		tab[0][j] = lettres[j-1];
		tab[9][j] = lettres[j-1];
	}

  for (int i = 1; i < 9; i++)
    for (int j = 1; j < 9; j++)
      t[i][j] = ".";
      
  
  t[4][5]=t[5][4]="X";  		//on met les pions dans les cases
  insereX("5","4");
  insereX("4","5");
  t[4][4]=t[5][5]="O"; 
  insereO("4","4");
  insereO("5","5");
  
  for (int i = 1; i < 9; i++)
    for (int j = 1; j < 9; j++)
      tab[i][j] =t[i][j];
  
  
  }
void Tableau::insereX(string y,string x) 
{
	
	listX.push_back(new Pion(y,x));
	
}
void Tableau::insereO(string y,string x)
{

	listO.push_back(new Pion(y,x));
}


bool Tableau::getXPossible()
{
	return Xpossible;
	}
void Tableau::setXPossible(bool c)
{
	Xpossible=c;
	}
bool Tableau::getOPossible()
{
	return Opossible;
	}
void Tableau::setOPossible(bool c)
{
	Opossible=c;
	}


void Tableau::choisirCase(string type)
{
	int colonne;		
	int ligne;
	{
		bool jeupossible;
		if(type=="noir")
		jeupossible=getXPossible();
				
				
		if(type=="blanc")
		jeupossible=getOPossible();
		
		
		cout<<"Joueur "<< type <<". Veuillez choisir une case # ex: c4. Si aucun # ne s'affiche faites 00.  Faites stop pour arreter."<<endl;     //fonction pour arreter le jeu
		cout<<endl;
		
		char c[2];								//On laisse l'utilisateur choisir la case
		scanf("%s",c);
		
		if(strcmp(c,"stop")==0 )				//On arrete le programme
			{
			endGame();	
			}
			
		else if(strlen(c)==2)
		{
			if(c[0]=='0' && c[1]=='0' )
			{
				
				if(!jeupossible)
				finTour(type);	
				
				else 
				{
				cout<<"\n \n Vous avez des places libres"<<endl;
				imprimeTableau();
				choisirCase(type);
				}
			}
			else if((c[0]>='a' && c[0]<='h' ) && (c[1]>='1' && c[1]<='8')){
				colonne=(int)(c[0]);			//On donne la valeur 0-7 pour les char a-h
				colonne-=96;					//Voir tableau ASCII						changer par 96
				
				ligne=(int)c[1];				//On donne la valeur 0-7 pour les char a-h
				ligne-=48;						//Voir tableau ASCII						changer par 48
				if(tab[ligne][colonne]=="#")	//On regarde si la place est libre
					{
					cout<<"Bon emplacement"<<endl;
					placerPion(type,colonne,ligne);
					}	
					
				else if(!jeupossible)
				{
					imprimeTableau();
					choisirCase(type);
				}
				else
				{
					cout<<"\n \n Veuillez choisir un emplacement libre"<<endl;
					
					imprimeTableau();
					choisirCase(type);
				}

			}
			
			else
			{
			cout << "\n \n Il faut un format ex: a2 de a->h et de 1->8"<< endl;
			imprimeTableau();
			choisirCase(type);
			}
			
		}	
		else
		{
			cout << "\n \n Il faut un format ex: a2 de a->h et de 1->8"<< endl;
			imprimeTableau();
			choisirCase(type);
		}
		
}
}


void Tableau::placerPion(string type,int c,int l)
{
	
	if(type=="noir")
	{
		tab[l][c]="X";
		insereX(to_string(l),to_string(c)); //On place le nouveau pion dans sa liste
	}
	else if (type=="blanc")
	{
		tab[l][c]="O";
		insereO(to_string(l),to_string(c));
	}
	
	for(Pion P :Pobjectifs)								
	{
		if(P.getx()==to_string(c) && P.gety()==to_string(l))
		{
			for(Pion s: P.getPenattente())
			{
				string ystring=s.gety();	//On accede aux coordonnees
				int y=stoi(ystring);
				string xstring=s.getx();
				int x=stoi(xstring);
					if(type=="noir")
					{
						changePion(ystring,xstring,listO,type);
						tab[y][x]="X"; //On place le nouveau pion dans sa liste
						insereX(to_string(y),to_string(x));
					}
					else if (type=="blanc")
					{
						
						changePion(ystring,xstring,listX,type);
						tab[y][x]="O";
						insereO(to_string(y),to_string(x));
					}
				
			
			}
		}	
	}
	viderListes(type);
	
	finTour(type);								//On passe de tour
}


void Tableau::changePion(string l,string c,list<Pion*> L,string type)
{
	list<Pion*> LL;
	for(Pion* P: L )
	{
		string ystring=P->gety();	//On accede aux coordonnees
		string xstring=P->getx();
		if(ystring==l && xstring==c)
		{
			
			LL.push_back(P);

			}
	}
	for(Pion* P: LL )
	{
		string ystring=P->gety();	//On accede aux coordonnees
		string xstring=P->getx();
		if(ystring==l && xstring==c)
		{
			if(type=="noir")
			listO.remove(P);
			else if(type=="blanc")
			listX.remove(P);

			}
	}
	
	
}

void Tableau::finTour(string type)
{
	cleanHashtag();		//On enleve les # pour pouvoir afficher les places libres pour le joueur suivant
	
	if (type=="noir"){
		
		placeslibres("blanc");		
		choisirCase("blanc");
	}
	else if(type=="blanc"){
		
		placeslibres("noir");
		choisirCase("noir");
		}
	
}


void Tableau::cleanHashtag()
	{
		
	for (int i = 1; i < 9; i++) 
    for (int j = 1; j < 9; j++)
	  if(tab[i][j]=="#")
	  tab[i][j]=".";
	  
	}
	

void Tableau::placeslibres(string type)
{

	
	list<Pion*> listePieces;
	string pionEnemi;
	string pionAllie;
	bool allieTrouve=false; 			
	if (type=="noir")
	{
		listePieces=listX;
		pionEnemi="O";
		pionAllie="X";
	}
	if (type=="blanc")
	{
		pionEnemi="X";
		pionAllie="O";
		listePieces=listO;
	}
	list<Pion*> objtot;
	
	for(Pion* pk : listePieces)
	{
		string ystring=pk->gety();	//On accede aux coordonnees
		int y=stoi(ystring);
		string xstring=pk->getx();
		int x=stoi(xstring);
		
												//   f g h
												// 1 . # . On cherche les O a proximite
			for(int i=y-1;i<y+2 ;i++)			// 2 # O X 
			for(int j=x-1;j<x+2;j++)			// 3 . X O 
			
			if(tab[i][j]==pionEnemi)
			{
				int dy=i-y;
				int dx=j-x;

				int num=2;
				
				
				list<Pion> obj;
				obj.push_back(Pion(to_string(y+dy),to_string(x+dx)));
			
				while(y+num*dy>0 && y+num*dy<9 && x+num*dx>0 && x+num*dx<9 && tab[y+num*dy][x+num*dx]!="." && !allieTrouve)  // . X O ->.<- . ou . X O ->X<- . 
					{
						
						obj.push_back(Pion(to_string(y+num*dy),to_string(x+num*dx))); 		
						if(tab[y+num*dy][x+num*dx]==pionAllie)
						{
						 allieTrouve=true;
							}
						num++;							// donc si on trouve . X O ->O<- . on va aller voir . X O O ->.<-
					}
					
					
					
					
				if(!allieTrouve && y+num*dy<9 && y+num*dy>0 && x+num*dx<9 && x+num*dx>0){

					Pion p=Pion(to_string(y+num*dy),to_string(x+num*dx),obj);
					Pobjectifs.push_back(p);

					if(type=="noir")
						setOPossible(true);
					else if(type=="blanc")
						setXPossible(true);
				}
				
				allieTrouve=false; 
			
				
			}
		}
		
		for(Pion ash:Pobjectifs)	
		{
			string ystring=ash.gety();	//On accede aux coordonnees
			int y=stoi(ystring);
			string xstring=ash.getx();
			int x=stoi(xstring);
			tab[y][x]="#";

		}
		
		if(type=="noir"&& !placementPossible())
		{
			
			setXPossible(false);
			if(!getXPossible() && !getOPossible())
			{
				cout << "FIN DE PARTIE"<< endl;
				endGame();
			}
		}
		else if(type=="blanc" && !placementPossible())
		{
			setOPossible(false);
			if(!getXPossible() && !getOPossible())
			{
				cout << "FIN DE PARTIE"<< endl;
				endGame();
			}
				
		}
	
	imprimeTableau();
}
bool Tableau::placementPossible()
	{
	
	for (int i = 1; i < 9; i++) 
    for (int j = 1; j < 9; j++)
	  if(tab[i][j]=="#")
	  {
		return true;	
		}
	return false;
	
  }	
void Tableau::endGame()
{
	int nombreX=0;
	int nombreO=0;
	imprimeTableau();
	for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j){
     if(tab[i][j]=="X")
     nombreX++;
     else if (tab[i][j]=="O")
     nombreO++;
     }
    
	}
	if(nombreX>nombreO) {
	cout << "\n Nombre noir:" << nombreX << "\n Nombre blanc:" <<nombreO << "\n Noir gagne" << endl;
	exit(0);}
	else if(nombreX<nombreO) {
	cout << "\n Nombre noir:" << nombreX << "\n Nombre blanc:" <<nombreO <<  "\n Blanc gagne" << endl;
	exit(0);}
	else if(nombreX==nombreO){
	cout << "\n Nombre noir:" << nombreX << "\n Nombre blanc:" <<nombreO <<  "\n Personne gagne" << endl;
	exit(0);}
	
	}
