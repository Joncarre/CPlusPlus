//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//

#ifndef GESTOR_H
#define GESTOR_H

#include <string>
#include <iostream>
#include "listaPartidas.h"
#include "listaUsuarios.h"
using namespace std;

const string fPartida = "partidas.txt";
const string fUsuarios = "usuarios.txt";

typedef struct {
	tListaPartidas listaPartidas;
	tListaUsuarios listaUsuarios;
	int usuarioActivo;
	int partidaActiva;
}tGestor;

//PROTOTIPOS
bool arrancar(tGestor &gestor); // Inicializa el gestor e intenta arrancarlo con la informaci�n del sistema.
void generarAccesos(tGestor &gestor); // puf, mejor mirar p�gina 8.
void apagar(tGestor &gestor); // Apagada el gestor abriendo los ficheros para guardar las listas de usuarios y de partidas del sistema.

// MEN� REGISTRO DEL MAIN
bool iniciarSesion(tGestor &gestor, string const &idUsu, string const &clave); // Comprueba si el usuario existe y la contrase�a coincide.
bool crearCuenta(tGestor &gestor, string const &idUsu, string const &clave); // Crea la cuenta si el 'idUsu' no existe y si hay espacio en la lista.
bool tieneAvisos(tGestor const &gestor, string &aviso); // Comprueba si el usuario de la sesi�n tiene avisos.
void limpiarAvisos(tGestor &gestor); // Actualiza los avisos del usuario a la cadena vac�a.
string resumenActividad(tGestor const &gestor); // Devuelve un string con los datos de la actividad del usuario de la sesi�n.

// MEN� USUARIO DEL MAIN
void ordenar_Fecha(tGestor &gestor); // Ordena por fecha de la �ltima actualizaci�n la lista de partidas en curso del usuario de la sesi�n.
void ordenar_Turno(tGestor &gestor); // Ordena igual pero por turno (primero aquellas en las que le toca jugar al usuario de la sesi�n).
int partidasUsuario(tGestor &gestor); // Devuelve el n�mero de partidas en curso del usuario de la sesi�n.
string cabecera(tGestor &gestor, int posEnCurso); // Puf, p�gina 8.
bool nuevaPartida(tGestor &gestor); // Puf, p�gina 8.
void apuntaPartida(tGestor &gestor, int posParEnCurso); // Dada una posici�n de la lista de partidas en curso del usuario en sesi�n, guarda el �ndice de la partida.

// MEN� PARTIDA DEL MAIN
void mostrarPartida(tGestor const &gestor); // Muestra el estado de la partida en curso.
bool esSuTurno(tGestor const &gestor); // Comprueba si es el turno del usuario de la sesi�n en la partida seleccionada.
void jugarPartida(tGestor &gestor, int col); // Puf, p�gina 9.
void abandonarPartida(tGestor &gestor); // Abandona la partida seleccionada por el usuario y actualiza a sus adversarios.


#endif  // GESTOR_H
