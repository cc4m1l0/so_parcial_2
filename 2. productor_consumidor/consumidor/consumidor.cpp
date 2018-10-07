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
	SimpleSemaphore semPC("/semPC", 0);
	SimpleSemaphore semCP("/semCP", 1);
	SimpleSemaphore semBuffer("/semBuffer");
	SharedMemory<cola_t> buffer("/buffer");

	cola_t &c = buffer();

	int pid = getpid();
	int dato = -1;
	for (int cont = 0; cont < 5; cont ++) {
		cout << "Consumidor " << pid << ": Esperando que termine el productor" << endl;
		semPC.Wait();
		cout << "Consumidor " << pid << ": Recibiendo dato" << endl;
		semBuffer.Wait();
		dato = c[0];
		semBuffer.Signal();
		cout << "Consumidor " << pid << ": Consumiendo dato..." << endl;
		sleep(2);
		semCP.Signal();
		cout << "Consumidor " << pid << ": Consumió el valor " << dato << endl;
	}
	return 0;
}



