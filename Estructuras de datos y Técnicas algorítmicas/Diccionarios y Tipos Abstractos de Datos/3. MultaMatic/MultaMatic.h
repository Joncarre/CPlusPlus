//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//
#include <iostream>
#include "TreeMap.h"
#include "HashMap.h"
#include <ctime>
using namespace std;

typedef struct InfoTramo{
	TreeMap<string, int> camInicio;
	int tiempoMulta;
	HashMap<string, int> HashMultasTramo;
};

typedef class Aplicacion{
	public:
		//---------------------------------------------------------------------------------------------------------------------------------------------
		void actualizarMultasTotales(string matricula){
			if (HashMultasTotales.contains(matricula)){ // Si ya le hab�an puesto alguna otra multa (en este o en otro tramo)...
				HashMap<string, int>::Iterator it = HashMultasTotales.find(matricula);
				it.value()++; // Incrementamos su n�mero de multas
			}
			else{ // Si es la primera multa que le ponen...
				HashMultasTotales.insert(matricula, 1); // Lo insertamos con su primera multa
			}
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		// Complejidad: O(1) por tratarse de una tabla Hash
		void insertaTramo(string tramo){
			if (HashTramo.contains(tramo)){
				throw string("El tramo ya existe.");
			}
			else{
				InfoTramo nuevo;
				nuevo.tiempoMulta = 5;
				HashTramo.insert(tramo, nuevo);
			}
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		// Complejidad: O(1) + O(logn), luego O(logn) porque tiene que insertar en el TreeMap 'camInicio'
		void fotoEntrada(string tramo, string matricula, int instante){
			if (!HashTramo.contains(tramo)){
				throw string("Tramo no existente.");
			}
			else{
				HashMap<string, InfoTramo>::Iterator it = HashTramo.find(tramo); // Cogemos el tramo por el que entra el coche
				it.value().camInicio.insert(matricula, instante); // Y lo insertamos en la c�mara que capta los coches que entran en el tramo
			}
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		// Complejidad: O(logn) porque tiene que buscar el instante en el que entr� en el tramo, y esa b�squeda se hace en el TreeMap 'camInicio'
		void fotoSalida(string tramo, string matricula, int instante){
			if (!HashTramo.contains(tramo)){
				throw string("Tramo no existente.");
			}
			else{
				HashMap<string, InfoTramo>::Iterator itTramo = HashTramo.find(tramo); // Cogemos el tramo por el que sale el coche
				if (instante - itTramo.value().camInicio.at(matricula) < itTramo.value().tiempoMulta){ // Si el instante actual menos el instante en el que el coche atraves� el tunel es menor que 'tiempoMulta'...
					// Entonces es que debemos ponerle una multa. Y consultamos si esa matricula ya ten�a multas anteriormente
					if (itTramo.value().HashMultasTramo.contains(matricula)){ // Si ya ten�a multas...
						HashMap<string, int>::Iterator itMultas = itTramo.value().HashMultasTramo.find(matricula);
						itMultas.value()++; // Aumentamos su contador de multas en este tramo
					}
					else{ // Y si no ten�a multas... Es que no estaba en el HashMultasTramo y hay que insetarlo
						itTramo.value().HashMultasTramo.insert(matricula, 1); // Ahora esa matricula ya tiene 1 multa
					}
					actualizarMultasTotales(matricula);
				}
			}
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		// Complejidad: O(1) por realizar una b�squeda en una tabla Hash
		int multasPorMatricula(string matricula){
			if (!HashMultasTotales.contains(matricula)){
				throw string("La matricula no tiene multas.");
			}
			else{
				HashMap<string, int>::Iterator it = HashMultasTotales.find(matricula);
				return it.value();
			}
		}
		//---------------------------------------------------------------------------------------------------------------------------------------------
		// Complejidad: O(n) donde 'n' es el n�mero de matriculas multadas en el 'tramo'
		HashMap<string, int> multasPorTramos(string tramo){
			if (!HashTramo.contains(tramo)){
				throw string("Tramo no existente");
			}
			else{
				HashMap<string, InfoTramo>::Iterator it = HashTramo.find(tramo);
				return it.value().HashMultasTramo;
			}
		}

	private:
		HashMap<string, InfoTramo> HashTramo;
		HashMap<string, int> HashMultasTotales;
};

