#ifndef CONTROLELCD_H
#define CONTROLELCD_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class ControleLcd
{
public:
	ControleLcd();

	void pinosLcd(int tipo, int digito1, int digito2, int digito3, int digito4, int a, int b, int c, int d, int e, int f, int g, int pd);
	void imprimirLcd(String v);
    	void doisPontos();

private:
	void controleSegmentos(int a, int b, int c, int d, int e, int f, int g);
	void controleDigitos(int valor1, int valor2, int valor3, int valor4);
	void desligarLcd();
	void imprimirDigito(char caractere);

	String valor;
	int liga, desliga, A, B, C, D, E, F, G, H, PD, D1, D2, D3, D4, tempo = 2;
};

#endif // ControleLcd_H
