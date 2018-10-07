/*
 * consumidor.cpp
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
	SharedMemory<cola_t> bufferpesa("/bufferpesa");
	SharedMemory<int> pesa1("/pesa1");
	SharedMemory<int> pesa2("/pesa2");

	cola_t &c = bufferpesa();
	int &p1 = pesa1();
	int &p2 = pesa2();

	int pid = getpid();
	int dato = -1;
	for (int cont = 0; cont < 5; cont ++) {
		cout << "Camión " << pid << ": Esperando que haya pesas disponibles" << endl;
		semPeCa.Wait();
		dato = c[0];
		cout << "Camión " << pid << ": Siendo pesado..." << endl;
		sleep(2);
		if(dato == 1) {
			semBufferPesa1.Wait();
			p1 = 0;
			semBufferPesa1.Signal();
		semBufferPesaDisponible.Signal();
		}
		if(dato == 2) {
			semBufferPesa2.Wait();
			p2 = 0;
			semBufferPesa2.Signal();
		semBufferPesaDisponible.Signal();
		}
		 semCaPe.Signal();
		cout << "Camión " << pid << ": Fue pesado en la pesa " << dato << endl;
	}
	return 0;
}



