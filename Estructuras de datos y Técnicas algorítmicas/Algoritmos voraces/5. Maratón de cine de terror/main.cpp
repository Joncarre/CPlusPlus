//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef struct{
	int inicio;
	int final;
}tPeli;

void resuelve(int numPelis);
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(1)
bool operator <(tPeli a, tPeli b){
	return a.inicio < b.inicio;
}
// ------------------------------------------------------------------------------------------------------
// Complejidad: O(N), donde N es el n�mero de pel�culas (hay que recorrer todo el vector)
void resuelve(int numPelis){
	int hora, min, duracion, termina, maxVisualizadas = 1;
	char c;

	vector<tPeli> peliculas(numPelis);
	for (int i = 0; i < numPelis; i++){
		cin >> hora; cin >> c; cin >> min; cin >> duracion;
		peliculas[i].inicio = (hora * 60) + min; // Establecemos el inicio de la pel�cula i-�sima
		peliculas[i].final = (hora * 60) + min + duracion+ 10; // Establecemos el final de la pel�cula i-�sima
	}
	sort(peliculas.begin(), peliculas.end(), less<tPeli>()); // Ordenamos el vector de menor a mayor
	int j = 1;
	termina = peliculas[0].final;
	while (j < numPelis){
		if (peliculas[j].inicio >= termina){ // Si el inicio de la pel�cula n es mayor o igual a cuando termina la pel�cula n-1
			termina = peliculas[j].final;
			maxVisualizadas++;
		}
		else if (termina > peliculas[j].final){
			termina = peliculas[j].final; // Actualizamos cu�ndo termina la pel�cula n-1
		}
		j++;
	}
	cout << maxVisualizadas << endl;
}
// ------------------------------------------------------------------------------------------------------
int main(){
	int numPelis;
	cin >> numPelis;
	while (numPelis > 0){
		resuelve(numPelis);
		cin >> numPelis;
	}
	//system("PAUSE");
	return 0;
}
