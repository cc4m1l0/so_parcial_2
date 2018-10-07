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
	SimpleSemaphore semPeCa("/semPeCa", 0);
	SimpleSemaphore semCaPe("/semCaPe", 1);
	SimpleSemaphore semBufferPesaDisponible("/semBufferPesaDisponible");
	SimpleSemaphore semBufferPesa1("/semBufferPesa1");
	SimpleSemaphore semBufferPesa2("/semBufferPesa2");
	SimpleSemaphore semBufferPesa3("/semBufferPesa3");
	SharedMemory<cola_t> bufferpesa("/bufferpesa");
	SharedMemory<int> pesa1("/pesa1");
	SharedMemory<int> pesa2("/pesa2");
	SharedMemory<int> pesa3("/pesa3");

	cola_t &c = bufferpesa();
	int &p1 = pesa1();
	int &p2 = pesa2();
	int &p3 = pesa3();

	int pesa = -1;
	int estadopesa1 = -1; // 0 significa libre, 1 ocupado
	int estadopesa2 = -1; // 0 significa libre, 1 ocupado
	int estadopesa3 = -1; // 0 significa libre, 1 ocupado
	int pid = getpid();
	for (int cont = 0; cont < 5; cont ++) {
		semBufferPesa1.Wait();
		estadopesa1 = p1;
		semBufferPesa1.Signal();
		semBufferPesa2.Wait();
		estadopesa2 = p2;
		semBufferPesa2.Signal();
		semBufferPesa3.Wait();
		estadopesa3 = p3;
		semBufferPesa3.Signal();
		if(estadopesa1 == 0) {
			pesa = 1;
			semBufferPesa1.Wait();
			p1 = 1;
			semBufferPesa1.Signal();
			semBufferPesaDisponible.Wait();
			c[0] = pesa;
			cout << "Pesa " << pesa << ": Está disponible " << endl;
		} else if (estadopesa2 == 0) {
			pesa = 2;
			semBufferPesa2.Wait();
			p2 = 1;
			semBufferPesa2.Signal();
			semBufferPesaDisponible.Wait();
			c[0] = pesa;
			cout << "Pesa " << pesa << ": Está disponible " << endl;
		} else if (estadopesa3 == 0) {
			pesa = 3;
			semBufferPesa3.Wait();
			p3 = 1;
			semBufferPesa3.Signal();
			semBufferPesaDisponible.Wait();
			c[0] = pesa;
			cout << "Pesa " << pesa << ": Está disponible " << endl;
		} else {
			cout << "No hay pesas disponibles. Por favor esperar... " << endl;
			semCaPe.Wait();
		}
		semPeCa.Signal();
	}
	return 0;
}



