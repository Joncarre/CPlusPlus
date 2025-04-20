//
//  Created by Jonathan Carrero.
//  Copyright (c) Jonathan Carrero. All rights reserved.
//

#ifndef FECHA_H
#define FECHA_H

#include <string>
#include <iostream>
#include <ctime>
using namespace std;

typedef time_t tFecha;

// Consultar la fecha actual.
tFecha fechaActual();
// Mostrar la fecha en formato A�o/Mes/D�a.
string stringFecha(tFecha fecha, bool hora);

#endif  // FECHA_H
