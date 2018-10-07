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
	SimpleSemaphore semBufferCarril3("/semBufferCarril3");
	SimpleSemaphore semBufferCarril4("/semBufferCarril4");
	SharedMemory<cola_t> buffercarril("/buffercarril");
	SharedMemory<int> carril1("/carril1");
	SharedMemory<int> carril2("/carril2");
	SharedMemory<int> carril3("/carril3");
	SharedMemory<int> carril4("/carril4");

	cola_t &c = buffercarril();
	int &c1 = carril1();
	int &c2 = carril2();
	int &c3 = carril3();
	int &c4 = carril4();

	int carril = -1;
	int estadocarril1 = -1; // 0 significa libre, 1 ocupado
	int estadocarril2 = -1; // 0 significa libre, 1 ocupado
	int estadocarril3 = -1; // 0 significa libre, 1 ocupado
	int estadocarril4 = -1; // 0 significa libre, 1 ocupado
	int pid = getpid();
	for (int cont = 0; cont < 5; cont ++) {
		semBufferCarril1.Wait();
		estadocarril1 = c1;
		semBufferCarril1.Signal();
		semBufferCarril2.Wait();
		estadocarril2 = c2;
		semBufferCarril2.Signal();
		semBufferCarril3.Wait();
		estadocarril3 = c3;
		semBufferCarril3.Signal();
		semBufferCarril4.Wait();
		estadocarril4 = c4;
		semBufferCarril4.Signal();
		if(estadocarril1 == 0) {
			carril = 1;
			semBufferCarril1.Wait();
			c1 = 1;
			semBufferCarril1.Signal();
			semBufferCarril2.Wait();
			c2 = 1;
			semBufferCarril2.Signal();
			semBufferCarrilDisponible.Wait();
			c[0] = carril;
			cout << "Carril " << carril << ": Está disponible " << endl;
		} else if (estadocarril2 == 0) {
			carril = 2;
			semBufferCarril1.Wait();
			c1 = 1;
			semBufferCarril1.Signal();
			semBufferCarril2.Wait();
			c2 = 1;
			semBufferCarril2.Signal();
			semBufferCarril3.Wait();
			c3 = 1;
			semBufferCarril3.Signal();
			semBufferCarrilDisponible.Wait();
			c[0] = carril;
			cout << "carril " << carril << ": Está disponible " << endl;
		}  else if (estadocarril3 == 0) {
			carril = 3;
			semBufferCarril2.Wait();
			c2 = 1;
			semBufferCarril2.Signal();
			semBufferCarril3.Wait();
			c3 = 1;
			semBufferCarril3.Signal();
			semBufferCarril4.Wait();
			c4 = 1;
			semBufferCarril4.Signal();
			semBufferCarrilDisponible.Wait();
			c[0] = carril;
			cout << "carril " << carril << ": Está disponible " << endl;
		}  else if (estadocarril4 == 0) {
			carril = 4;
			semBufferCarril3.Wait();
			c3 = 1;
			semBufferCarril3.Signal();
			semBufferCarril4.Wait();
			c4 = 1;
			semBufferCarril4.Signal();
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



