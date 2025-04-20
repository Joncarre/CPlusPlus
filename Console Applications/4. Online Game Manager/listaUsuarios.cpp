//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "listaUsuarios.h"
using namespace std;

bool buscarUsuarioEsperando(tListaUsuarios const &usuarios, tNivel nivel, int &pos){
	bool encontrado = false;
	int i = 0;
	while (i < usuarios.cont && !encontrado){
		if (usuarios.lista[i].categoria == nivel && usuarios.lista[i].esperando == true){
			encontrado = true;
			pos = i;
		}
		i++;
	}
	return encontrado;
}

bool insertar(tListaUsuarios &usuarios, tUsuario const &usuario, int &pos){
	bool exito = true;

	if (usuarios.cont == DIM_usuario) // Si la lista est� llena...
		exito = false;
	else {
		pos = 0;
		if (!buscar(usuarios, usuario.nombre, pos)){ // Si no hay un usuario con el mismo ID...
			desplazarDerecha(usuarios, pos);
			usuarios.lista[pos] = usuario;
		}
		else
			exito = false;
	}
	return exito;
}

void desplazarDerecha(tListaUsuarios &usuarios, int pos){
	for (int i = usuarios.cont; i > pos; i--)
		usuarios.lista[i] = usuarios.lista[i - 1];
}

bool buscar(tListaUsuarios const &usuarios, string const &idUser, int &pos){
	// Complejidad: O(log2 N) Implementaci�n de la b�squeda binaria
	bool encontrado = false;
	int ini = 0, fin = usuarios.cont - 1, mitad;
	while ((ini <= fin) && !encontrado){
		mitad = (ini + fin) / 2;
		if (idUser < usuarios.lista[mitad].nombre)
			fin = mitad - 1;
		else if (idUser > usuarios.lista[mitad].nombre)
			ini = mitad + 1;
		else
			encontrado = true;
	}

	if (encontrado)
		pos = mitad;
	else
		pos = ini;

	return encontrado;
}

bool cargar(tListaUsuarios &usuarios, ifstream &archivo){
	usuarios.cont = 0; // Inicializamos el n�mero de usuarios
	bool exito = true;
	int numElementos;

	archivo >> numElementos; // Leemos el n�mero de elementos que tiene la lista (donde numElementos es el n�mero de usuarios)
	if (numElementos > DIM_usuario){  // Y si 'numElementos' es mayor que 'DIM_usuario', entonces devolvemos 'false'
		exito = false;
	}
	else {
		for (int i = 0; i < numElementos; i++){
			cargar(usuarios.lista[i], archivo); // Para cada posici�n de la lista, rellenamos los datos de un usuario
			usuarios.cont++; // E incrementamos el contador de usuarios
		}
	}
	return exito;
}

void guardar(tListaUsuarios const &usuarios, ofstream &archivo){
	archivo << usuarios.cont << endl; // Metemos el primer n�mero que �ndica el n�mero de usuarios que vamos a guardar
	for (int i = 0; i < usuarios.cont; i++){ // Obtenemos el n�mero de usuarios gracias a 'cont'
		guardar(usuarios.lista[i], archivo); // Y para cada usuario le�do guardamos sus datos
	}
}
