//LCD
#include <ControleLcd.h>
ControleLcd lcd;
//FIM LCD

//DHT 11
#include <DHT.h>
#include <DHT_U.h>
DHT dht(13, DHT11);
//FIM DHT 11

//VARIAVEIS
int cont = 0, minuto = 0, hora = 00, aux = 0, aux2 = 0, op = 0, contt1 = 0, contt2 = 0, contu1 = 0, contu2 = 0;
float t = 0, h = 0;
unsigned long ms = 1000, mls = millis(), ms2 = 5 * ms * 60;
String valor;
//FIM VARIAVEIS

//LDR
#define ldrMinuto 5
#define ldrHora 6
#define ldrOpcao 7
//FIM LDR

void setup() {
  Serial.begin(9600);

  lcd.pinosLcd(0, 22, 25, 26, 53, 23, 27, 51, 49, 48, 24, 52, 50);

  dht.begin(); //INICIA O SENSOR DHT DE UMIDADE E TEMPERATURA

  //CONFIGURACAO PARA OS LDR'S USADOS COMO PINOS DE ENTRADA
  pinMode(ldrHora, INPUT);
  pinMode(ldrMinuto, INPUT);
  pinMode(ldrOpcao, INPUT);
  //FIM CONFIGURACAO PARA OS LDR'S USADOS COMO PINOS DE ENTRADA

  pinMode(12, OUTPUT); //CONFIGURACAO PARA A PORTA 12 DA PORTA COMO PINO DE SAIDA
  digitalWrite(12, HIGH); //PORTA 12 CONFIGURADA PARA ENVIAR ENERGIA, ASSIM ALIMENTANDO O VCC DO MODULO DO SENSOR DHT

  //RECEBENDO VALORES INICIAIS DA TEMPERATURA E UMIDADE DO AMBIENTE
  delay(100);
  t = dht.readTemperature();
  h = dht.readHumidity();
  //FIM RECEBENDO VALORES INICIAIS DA TEMPERATURA E UMIDADE DO AMBIENTE

  //LIGANDO LED PARA MANTER LUMINOSIDADE NOS LDR'S
  pinMode(4, OUTPUT);
  analogWrite(4, 100);
  //FIM LIGANDO LED PARA MANTER LUMINOSIDADE NOS LDR'S
}

void loop() {
  mls = millis(); //ATUALIZA O VALOR DA VARIAVEL REFERENTE AO TEMPO DECORRIDO DESDE A PLACA SER EXECUTADA
  lerOpcao(); //EXECUTA A LEITURA DA OPCAO A FIM DE EXECUTA-LA
  executarOpcao(); //EXECUTA A OPCAO NO LCD, OU SEJA, IMPRIMI NO LCD A TEMPERATURA, UMIDADE OU O HORARIO
  contagem(); //EXECUTA A AUTALIZACAO DO TEMPO DECORRIDO EM RELACAO A SEGUNDOS, AVANCANDO SUBSEQUENTEMENTE OS MINUTOS E HORAS
}

void contagem() //FUNCAO QUE EXECUTARA A CONTAGEM DE SEGUNDOS DO PROGRAMA, AFIM DE ATUALIZAR OS VALORES DO RELOGIO EM TEMPO REAL
{
  if (mls >= ms)
  {
    cont++;
    ms += 1000;

    if (cont >= 60)
    {
      minuto++;
      cont = 0;
    }
    if (minuto >= 60)
    {
      hora++;
      minuto = 0;
    }
    if (hora >= 24)
    {
      hora = 0;
    }
  }
  if (mls >= ms2)
  {
    ms2 += 1000 * 5 * 60;
    contt1++;
    contu1++;
  }
}

void relogio() //VERIFICA SE HA ALGUMA ATUALIZACAO MANUAL REALIZADA PELO USUARIO, E IMPRIMI NO LCD O VALOR DO RESPECTIVO HORARIO
{
  atualizarRelogio();

  //CONDICOES USADAS PARA IMPRIMIR O HORARIO DE FORMA QUE USE O MAXIMO DE DIGITOS DO LCD POSSIVEIS
  //PORTANDO O VALOR E TRANSFORMADO EM STRING PARA ADICIONAR O ZERO
  //QUANDO O VALOR FINAL DO HORARIO ESTA FORMADO, O MESMO E IMPRESSO NO LCD POR MEIO DE UMA CONVERSAO DE STRING PARA INT

  String h;

  if (hora == 0)
  {
    h = "00";
  }
  else if (hora > 0 && hora < 10)
  {
    h = "0" + String(hora);
  }
  else
  {
    h = String(hora);
  }


  if (minuto < 10)
  {
    valor = h + "0" + String(minuto);
  }
  else
  {
    valor = h + String(minuto);
  }

  lcd.doisPontos();
  lcd.imprimirLcd(valor);
}

void atualizarRelogio() //FUNCAO A FIM DE ATUALIZAR OS VALORES DO MINUTO OU HORA DE FORMA MANUAL
{
  if (mls >= ms)
  {
    if (digitalRead(ldrHora) == 1 && digitalRead(ldrMinuto) == 0 && digitalRead(ldrOpcao) == 0)
    {
      //APOS QUATRO ATUALIZACOES SEGUIDAS, O VALOR DA HORA ADICIONA MAIS 4 AO INVES DE 1 COMO FOI REALIZADO NOS 4 SEGUNDOS PASSADOS
      aux2++;
      aux = 0;

      if (aux2 > 4)
      {
        hora += 4;
      }
      else if (aux2 <= 4)
      {
        hora++;
      }

      if (hora >= 24)
      {
        hora = 0;
      }
    }
    else if (digitalRead(ldrHora) == 0 && digitalRead(ldrMinuto) == 1 && digitalRead(ldrOpcao) == 0)
    {
      //APOS CINCO ATUALIZACOES SEGUIDAS, O VALOR DO MINUTO ADICIONA MAIS 5 AO INVES DE 1 COMO FOI REALIZADO NOS 4 SEGUNDOS PASSADOS
      aux++;
      aux2 = 0;
      if (aux > 5)
      {
        minuto += 5;
      }
      else if (aux <= 5)
      {
        minuto++;
      }

      if (minuto >= 60)
      {
        minuto = 0;
      }
    }
    else
    {
      aux = 0;
      aux2 = 0;
    }
  }
}

void lerOpcao() //FUNCAO USADA PARA ATUALIZAR O VALOR DA OPCAO
{
  if (digitalRead(ldrHora) == 0 && digitalRead(ldrMinuto) == 0 && digitalRead(ldrOpcao) == 1 && mls >= ms)
  {
    op++;
    //COMO SO POSSUIMOS TRES OPCOES, O VALOR DE OP RETORNA A ZERO QUANDO ATINGIR UM VALOR IGUAL OU MAIOR A TRES
    if (op >= 3)
    {
      op = 0;
    }
  }
}

void executarOpcao() //FUNCAO USADA PARA EXECUTAR A OPCAO LIDA
{
  switch (op)
  {
    case 1:
      temperatura();
      break;

    case 2:
      umidade();
      break;

    case 0:
      relogio();
      break;
  }
}

int valorTemperatura() //RETORNA O VALOR DA TEMPERATURA
{
  //A CADA CINCO MINUTOS O VALOR E ATUALIZADO
  if (contt1 > contt2)
  {
    contt2 = contt1;
    t = dht.readTemperature();
    return t;
  }
  return t;
}

int valorUmidade() //RETORNA O VALOR DA UMIDADE
{
  //A CADA CINCO MINUTOS O VALOR E ATUALIZADO
  if (contu1 > contu2)
  {
    contu2 = contu1;
    h = dht.readHumidity();
    return h;
  }
  return h;
}

void temperatura() //USADA PARA IMPRIMIR O VALOR DA TEMPERATURA AMBIENTE
{
  String x = "Xc" + String(valorTemperatura());
  lcd.doisPontos();
  lcd.imprimirLcd(x);
}

void umidade() //USADA PARA IMPRIMIR O VALOR DA UMIDADE AMBIENTE
{
  String x = "u" + String(valorUmidade());
  lcd.doisPontos();
  lcd.imprimirLcd(x);
}
