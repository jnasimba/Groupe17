all: tableau.o pion.o projet.cpp
	g++ tableau.o pion.o  projet.cpp -o projet
tableau.o: tableau.cpp
	g++ -c tableau.cpp
pion.o: pion.cpp
	g++ -c pion.cpp
clean:
	rm *.o
