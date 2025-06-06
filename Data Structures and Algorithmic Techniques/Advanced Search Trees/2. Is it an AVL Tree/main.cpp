//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include <algorithm>
#include "Arbin.h"
using namespace std;

void resuelve();
Arbin<int> leerArbol();
bool equilibrado(Arbin<int> arbol);
bool ordenado(Arbin<int> arbol);
bool esMayor(Arbin<int> arbol);
int altura(Arbin<int> arbol);
// ------------------------------------------------------------------------------------------------------
// Complexity: O(N), where N is the number of elements read from the input
Arbin<int> leerArbol(){
	int numero;
	cin >> numero;

	if (numero == -1)
		return Arbin<int>();
	else{
		const Arbin<int> &iz = leerArbol();
		const Arbin<int> &dr = leerArbol();
		return Arbin<int>(iz, numero, dr);
	}
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O(N), where N is the number of nodes (it must check that all nodes meet the property)
bool ordenado(Arbin<int> arbol){
	if (arbol.esVacio())
		return true;
	else{
		if (ordenado(arbol.hijoIz()) &&
			ordenado(arbol.hijoDr()) &&
			esMayor(arbol)
			)
			return true;
		else
			return false;
	}
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O(1), it simply has to access the two children to perform the check
bool esMayor(Arbin<int> arbol){
	/*
	if (arbol.hijoIz().esVacio() && (arbol.hijoDr().esVacio() && arbol.hijoDr().raiz() > arbol.raiz()))
		return true;
	else if (arbol.hijoDr().esVacio() && (!arbol.hijoIz().esVacio() && arbol.hijoIz().raiz() < arbol.raiz()))
		return true;
	else if ((!arbol.hijoIz().esVacio() && arbol.hijoIz().raiz() < arbol.raiz()) &&
		(!arbol.hijoDr().esVacio() && arbol.hijoDr().raiz() > arbol.raiz()))
		return true;
	else if (arbol.hijoIz().esVacio() && arbol.hijoDr().esVacio())
		return true;
	else
		return false;
	*/
	if ((!arbol.hijoIz().esVacio() && arbol.hijoIz().raiz() > arbol.raiz()) ||
		(!arbol.hijoDr().esVacio() && arbol.hijoDr().raiz() < arbol.raiz()))
		return false;
	else
		return true;
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O(N), where N is the number of nodes in the tree
int altura(Arbin<int> arbol){
	if (arbol.esVacio())
		return 0;
	else
		return 1 + max(altura(arbol.hijoIz()), altura(arbol.hijoDr()));
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O(N)
bool equilibrado(Arbin<int> arbol){
	if (arbol.esVacio())
		return true;
	else{
		if (equilibrado(arbol.hijoIz()) &&
			equilibrado(arbol.hijoDr()) &&
			(altura(arbol.hijoIz()) - altura(arbol.hijoDr()) <= 1 &&
			altura(arbol.hijoDr()) - altura(arbol.hijoIz()) <= 1))
			return true;
		else
			return false;
	}
}
// ------------------------------------------------------------------------------------------------------
// Complexity: O(N)
void resuelve(){
	Arbin<int> arbol;
	arbol = leerArbol();
	if (equilibrado(arbol) && ordenado(arbol))
		cout << "SI" << endl;
	else
		cout << "NO" << endl;
}
// ------------------------------------------------------------------------------------------------------
int main(){
	int numCasos;
	cin >> numCasos;

	for (int i = 0; i < numCasos; i++){
		resuelve();
	}
	//system("PAUSE");
	return 0;
}
