/*
	CODIGO PARA CONTROLAR UM LCD DE 7 SEGMENTOS COM 4 DIGITOS
	PARA ISSO USAMOS AS FUNÇOES:
	-pinosLcd(); 
	-doisPontos();
	-imprimirLcd();

	pinosLcd USADA PARA INICIAR E CONFIGURAR OS PINOS DO LCD

	doisPontos USADA PARA LIGAR OS DOIS PONTOS DO LCD, USADO ENTRE OS DIGITOS DE HORA E OS DE MINUTO EM UM RELOGIO POR EXEMPLO

	imprimirLcd USADA PARA IMPRIMIR ALGUM VALOR QUE O USUARIO QUISER NO LCD, SENDO QUE O VALOR DEVE TER ATE QUATRO DIGITOS, SENDO ELES NUMEROS
	E ALGUMAS LETRAS DO ALFABETO, CADA VEZ QUE UTILIZAR ESSA FUNCAO OS DOIS PONTOS SAO DESLIGADOS, PORTANTO CASO QUEIRA LIGALOS A OUTRA FUNÇAO
	DEVE SER CHAMADA NOVAMENTE

	AUTOR: JULIANO MARCELO SCHAURICH JUNIOR
	ANO: 2018
*/

#include "ControleLcd.h"

ControleLcd::ControleLcd()
{
    valor = "0000";
}

//INICIANDO E CONFIGURANDO OS PINOS DO LCD
void ControleLcd::pinosLcd(int tipo, int digito1, int digito2, int digito3, int digito4, int a, int b, int c, int d, int e, int f, int g, int pd)
{
    A = a, B = b, C = c, D = d, E = e, F = f, G = g, PD = pd, D1 = digito1, D2 = digito2, D3 = digito3, D4 = digito4;

    if (tipo == 0)
    {
        liga = 0;
        desliga = 1;
    }
    else if (tipo == 1)
    {
        liga = 1;
        desliga = 0;
    }

    pinMode(D1, OUTPUT);
    digitalWrite(D1, desliga);
    pinMode(D2, OUTPUT);
    digitalWrite(D2, desliga);
    pinMode(D3, OUTPUT);
    digitalWrite(D3, desliga);
    pinMode(D4, OUTPUT);
    digitalWrite(D4, desliga);

    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(C, OUTPUT);
    pinMode(D, OUTPUT);
    pinMode(E, OUTPUT);
    pinMode(F, OUTPUT);
    pinMode(G, OUTPUT);

    if (pd != 0)
    {
        pinMode(PD, OUTPUT);
    }

    desligarLcd();
}

//USADA PARA SIMPLIFICAR O PROCESSO DE ENVIAR SINAIS DIGITAIS AS PORTAS DO LCD
void ControleLcd::controleSegmentos(int a, int b, int c, int d, int e, int f, int g)
{
    digitalWrite(A, a);
    digitalWrite(B, b);
    digitalWrite(C, c);
    digitalWrite(D, d);
    digitalWrite(E, e);
    digitalWrite(F, f);
    digitalWrite(G, g);
}

//USADA PARA SIMPLIFICAR O PROCESSO DE ENVIAR SINAIS DIGITAIS AS PORTAS DO LCD
void ControleLcd::controleDigitos(int valor1, int valor2, int valor3, int valor4)
{
    digitalWrite(D1, valor1);
    digitalWrite(D2, valor2);
    digitalWrite(D3, valor3);
    digitalWrite(D4, valor4);
}

//USADA PARA IMPRIMIR DOIS PONTOS NO LCD
void ControleLcd::doisPontos()
{
    desligarLcd();
    controleDigitos(1, 0, 1, 1);
    digitalWrite(50, HIGH);
    delay(tempo);
}

////USADA PARA SIMPLIFICAR O PROCESSO DE ENVIAR SINAIS DIGITAIS AS PORTAS DO LCD, NESSE CASO SIMPLESMENTE DESLIGAR O LCD
void ControleLcd::desligarLcd()
{
    controleDigitos(desliga, desliga, desliga, desliga);
    controleSegmentos(0, 0, 0, 0, 0, 0, 0);
    digitalWrite(PD, LOW);
    delay(tempo);
}

//USADA PARA IMPRIMIR O VALOR EM UM DIGITO
void ControleLcd::imprimirDigito(char caractere)
{
    switch (caractere)
    {
    case '0':
        controleSegmentos(1, 1, 1, 1, 1, 1, 0);
        break;
    case '1':
        controleSegmentos(0, 1, 1, 0, 0, 0, 0);
        break;
    case '2':
        controleSegmentos(1, 1, 0, 1, 1, 0, 1);
        break;
    case '3':
        controleSegmentos(1, 1, 1, 1, 0, 0, 1);
        break;
    case '4':
        controleSegmentos(0, 1, 1, 0, 0, 1, 1);
        break;
    case '5':
        controleSegmentos(1, 0, 1, 1, 0, 1, 1);
        break;
    case '6':
        controleSegmentos(1, 0, 1, 1, 1, 1, 1);
        break;
    case '7':
        controleSegmentos(1, 1, 1, 0, 0, 0, 0);
        break;
    case '8':
        controleSegmentos(1, 1, 1, 1, 1, 1, 1);
        break;
    case '9':
        controleSegmentos(1, 1, 1, 1, 0, 1, 1);
        break;
    case 'a':
        controleSegmentos(1, 1, 1, 0, 1, 1, 1);
        break;
    case 'b':
        controleSegmentos(0, 0, 1, 1, 1, 1, 1);
        break;
    case 'c':
        controleSegmentos(1, 0, 0, 1, 1, 1, 0);
        break;
    case 'd':
        controleSegmentos(0, 1, 1, 1, 1, 0, 1);
        break;
    case 'e':
        controleSegmentos(1, 0, 0, 1, 1, 1, 1);
        break;
    case 'f':
        controleSegmentos(1, 0, 0, 0, 1, 1, 1);
        break;
    case 'h':
        controleSegmentos(0, 1, 1, 0, 1, 1, 1);
        break;
    case 'j':
        controleSegmentos(0, 1, 1, 1, 1, 0, 0);
        break;
    case 'l':
        controleSegmentos(0, 0, 0, 1, 1, 1, 0);
        break;
    case 'o':
        controleSegmentos(1, 1, 1, 1, 1, 1, 0);
        break;
    case 'p':
        controleSegmentos(1, 1, 0, 0, 1, 1, 1);
        break;
    case 'u':
        controleSegmentos(0, 1, 1, 1, 1, 1, 0);
        break;
    case 'X':
        controleSegmentos(1, 1, 0, 0, 0, 1, 1);
        break;
    case 'N':
        controleSegmentos(0, 0, 0, 0, 0, 0, 0);
        break;
    }
    delay(tempo);
}

//USADA PARA IMPRIMIR O VALOR TOTAL NO LCD, PASSANDO OS VALORES INDIVIDUAIS DE CADA DIGITO
void ControleLcd::imprimirLcd(String v)
{
    valor = v;
    int tamanho = valor.length();
    desligarLcd();

    if (tamanho  == 4)
    {
        controleDigitos(liga, desliga, desliga, desliga);
        imprimirDigito(v[0]);

        controleDigitos(desliga, liga, desliga, desliga);
        imprimirDigito(v[1]);

        controleDigitos(desliga, desliga, liga, desliga);
        imprimirDigito(v[2]);

        controleDigitos(desliga, desliga, desliga, liga);
        imprimirDigito(v[3]);
    }
    else if (tamanho == 3)
    {
        controleDigitos(desliga, liga, desliga, desliga);
        imprimirDigito(v[0]);

        controleDigitos(desliga, desliga, liga, desliga);
        imprimirDigito(v[1]);

        controleDigitos(desliga, desliga, desliga, liga);
        imprimirDigito(v[2]);
    }
    else if (tamanho == 2)
    {
        controleDigitos(desliga, desliga, liga, desliga);
        imprimirDigito(v[0]);

        controleDigitos(desliga, desliga, desliga, liga);
        imprimirDigito(v[1]);
    }
    else
    {
        controleDigitos(desliga, desliga, desliga, liga);
        imprimirDigito(v[0]);
    }
    delay(tempo);
}
