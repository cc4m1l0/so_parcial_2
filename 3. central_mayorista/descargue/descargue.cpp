/*
 * productor.cpp
 *
 *  Created on: Sep 21, 2018
 *      Author: jlalinde
 */

#ifndef __SIMPLESEMAPHORE_H_
#include "include/SimpleSemaphore.h"
#define __SIMPLESEMAPHORE_H_
#endif

#ifndef __SHAREDMEMORY_H_
#include "include/SharedMemory.h"
#define __SHAREDMEMORY_H_
#endif

#ifndef __IOSTREAM__
#include <iostream>
#define __IOSTREAM__
#endif

#ifndef __CSTDLIB__
#include <cstdlib>
#define __CSTDLIB__
#endif

#ifndef __CTIME__
#include <ctime>
#define __CTIME__
#endif

using std::cout;
using std::cerr;
using std::endl;
using std::rand;
using std::time;
const int tamCola = 1;
typedef int cola_t[tamCola];


int main() {
	SimpleSemaphore semDeCa("/semDeCa", 0);
	SimpleSemaphore semCaDe("/semCaDe", 1);
	SimpleSemaphore semBufferCarrilDisponible("/semBufferCarrilDisponible");
	SimpleSemaphore semBufferCarril1("/semBufferCarril1");
	SimpleSemaphore semBufferCarril2("/semBufferCarril2");
	SharedMemory<cola_t> buffercarril("/buffercarril");
	SharedMemory<int> carril1("/carril1");
	SharedMemory<int> carril2("/carril2");

	cola_t &c = buffercarril();
	int &c1 = carril1();
	int &c2 = carril2();

	int carril = -1;
	int estadocarril1 = -1;
	int estadocarril2 = -1;
	int pid = getpid();
	for (int cont = 0; cont < 5; cont ++) {
		semCaDe.Wait();
		semBufferCarril1.Wait();
		estadocarril1 = c1;
		semBufferCarril1.Signal();
		semBufferCarril2.Wait();
		estadocarril2 = c2;
		semBufferCarril2.Signal();
		if(estadocarril1 == 0) {
			carril = 1;
			semBufferCarril1.Wait();
			c1 = 1;
			c2 = 1;
			semBufferCarril1.Signal();
			semBufferCarrilDisponible.Wait();
			c[0] = carril;
			cout << "Carril " << carril << ": Está disponible " << endl;
		} else if (estadocarril2 == 0) {
			carril = 2;
			semBufferCarril2.Wait();
			c1 = 1;
			c2 = 1;
			semBufferCarril2.Signal();
			semBufferCarrilDisponible.Wait();
			c[0] = carril;
			cout << "carril " << carril << ": Está disponible " << endl;
		} else {
			cout << "No hay carriles disponibles. Por favor esperar... " << endl;
			semCaDe.Wait();
		}
		semDeCa.Signal();
	}
	return 0;
}



