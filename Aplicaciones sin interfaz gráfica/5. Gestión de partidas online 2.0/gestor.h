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
#include "ListaAccesoPartidas.h"
using namespace std;

const string fPartida = "partidas.txt";
const string fUsuarios = "usuarios.txt";

typedef struct {
	tListaPartidas listaPartidas;
	tListaUsuarios listaUsuarios;
	tListaAccesoPartidas listaAccesoPartidas;
	int usuarioActivo;
	int partidaActiva;
}tGestor;

// Inicializa el gestor e intenta arrancarlo con la informaci�n del sistema.
bool arrancar(tGestor &gestor);
// puf, mejor mirar p�gina 8.
void generarAccesos(tGestor &gestor);
// Apagada el gestor abriendo los ficheros para guardar las listas de usuarios y de partidas del sistema.
void apagar(tGestor &gestor);
// Cierra las partidas con m�s de 30 d�as sin actividad.
void borrarCaducadas(tGestor &gestor);

// MEN� REGISTRO DEL MAIN
// Comprueba si el usuario existe y la contrase�a coincide.
bool iniciarSesion(tGestor &gestor, string const &idUsu, string const &clave);
// Crea la cuenta si el 'idUsu' no existe y si hay espacio en la lista.
bool crearCuenta(tGestor &gestor, string const &idUsu, string const &clave);
// Comprueba si el usuario de la sesi�n tiene avisos.
bool tieneAvisos(tGestor const &gestor, string &aviso);
// Actualiza los avisos del usuario a la cadena vac�a.
void limpiarAvisos(tGestor &gestor);
// Devuelve un string con los datos de la actividad del usuario de la sesi�n.
string resumenActividad(tGestor const &gestor);

// MEN� USUARIO DEL MAIN
// Ordena por fecha de la �ltima actualizaci�n la lista de partidas en curso del usuario de la sesi�n.
void ordenar_Fecha(tGestor &gestor);
// Ordena igual pero por turno (primero aquellas en las que le toca jugar al usuario de la sesi�n).
void ordenar_Turno(tGestor &gestor);
// Devuelve el n�mero de partidas en curso del usuario de la sesi�n.
int partidasUsuario(tGestor &gestor);
// Puf, p�gina 8.
string cabecera(tGestor &gestor, int posEnCurso);
// Puf, p�gina 8.
bool nuevaPartida(tGestor &gestor);
// Dada una posici�n de la lista de partidas en curso del usuario en sesi�n, guarda el �ndice de la partida.
void apuntaPartida(tGestor &gestor, int posParEnCurso);

// MEN� PARTIDA DEL MAIN
// Muestra el estado de la partida en curso.
void mostrarPartida(tGestor const &gestor);
// Comprueba si es el turno del usuario de la sesi�n en la partida seleccionada.
bool esSuTurno(tGestor const &gestor);
// Puf, p�gina 9.
void jugarPartida(tGestor &gestor, int col);
// Abandona la partida seleccionada por el usuario y actualiza a sus adversarios.
void abandonarPartida(tGestor &gestor);

#endif  // GESTOR_H
