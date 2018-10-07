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
	SimpleSemaphore semPeCa("/semPeCa", 0); //semáforo utilizado para Pesa Camión
	SimpleSemaphore semCaPe("/semCaPe", 1); //semáforo utilizado para Camión Pesa
	SimpleSemaphore semDeCa("/semDeCa", 0); //semáforo utilizado para Descargue Camión
	SimpleSemaphore semCaDe("/semCaDe", 1); //semáforo utilizado para Camión Descargue
	SimpleSemaphore semBufferPesaDisponible("/semBufferPesaDisponible");
	SimpleSemaphore semBufferCarrilDisponible("/semBufferCarrilDisponible");
	SimpleSemaphore semBufferPesa1("/semBufferPesa1");
	SimpleSemaphore semBufferPesa2("/semBufferPesa2");
	SimpleSemaphore semBufferPesa3("/semBufferPesa3");
	SimpleSemaphore semBufferCarril1("/semBufferCarril1");
	SimpleSemaphore semBufferCarril2("/semBufferCarril2");
	SimpleSemaphore semBufferCarril3("/semBufferCarril3");
	SimpleSemaphore semBufferCarril4("/semBufferCarril4");
	SharedMemory<cola_t> bufferpesa("/bufferpesa");
	SharedMemory<cola_t> buffercarril("/buffercarril");
	SharedMemory<int> pesa1("/pesa1");
	SharedMemory<int> pesa2("/pesa2");
	SharedMemory<int> pesa3("/pesa3");
	SharedMemory<int> carril1("/carril1");
	SharedMemory<int> carril2("/carril2");
	SharedMemory<int> carril3("/carril3");
	SharedMemory<int> carril4("/carril4");

	cola_t &c = bufferpesa();
	cola_t &ca = buffercarril();
	int &p1 = pesa1();
	int &p2 = pesa2();
	int &p3 = pesa3();
	int &c1 = carril1();
	int &c2 = carril2();
	int &c3 = carril3();
	int &c4 = carril4();

	int pid = getpid();
	int dato = -1;
	int datocarril = -1;
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
		if(dato == 3) {
			semBufferPesa3.Wait();
			p3 = 0;
			semBufferPesa3.Signal();
			semBufferPesaDisponible.Signal();
		}
		semCaPe.Signal();
		cout << "Camión " << pid << ": Fue pesado en la pesa " << dato << endl;
		// descargue
		cout << "Camión " << pid << ": Esperando carril para descargue " << endl;
		semDeCa.Wait();
		datocarril = ca[0];
		cout << "Camión " << pid << ": Siendo descargado..." << endl;
		sleep(5);
		if(datocarril == 1) {
			semBufferCarril1.Wait();
			c1 = 0;
			semBufferCarril1.Signal();
			semBufferCarril2.Wait();
			c2 = 0;
			semBufferCarril2.Signal();
			semBufferCarrilDisponible.Signal();
		}
		if(datocarril == 2) {
			semBufferCarril1.Wait();
			c1 = 0;
			semBufferCarril1.Signal();
			semBufferCarril2.Wait();
			c2 = 0;
			semBufferCarril2.Signal();
			semBufferCarril3.Wait();
			c3 = 0;
			semBufferCarril3.Signal();
			semBufferCarrilDisponible.Signal();
		}
		if(datocarril == 3) {
			semBufferCarril2.Wait();
			c2 = 0;
			semBufferCarril2.Signal();
			semBufferCarril3.Wait();
			c3 = 0;
			semBufferCarril3.Signal();
			semBufferCarril4.Wait();
			c4 = 0;
			semBufferCarril4.Signal();
			semBufferCarrilDisponible.Signal();
		}
		if(datocarril == 4) {
			semBufferCarril3.Wait();
			c3 = 0;
			semBufferCarril3.Signal();
			semBufferCarril4.Wait();
			c4 = 0;
			semBufferCarril4.Signal();
			semBufferCarrilDisponible.Signal();
		}
		semCaDe.Signal();
		cout << "Camión " << pid << ": Fue descargado en el carril " << datocarril << endl;
	}
	return 0;
}



