#include <HCSR04.h>
#include <Wire.h> 
#include <LiquidCrystal.h>

//******* CONFIGURACAO DO PROJETO *********
#define pinTrig  D6
#define pinEcho  D7

#define pinBotao D8
#define tempoDebounce 50 //tempo em milisegundos para filtro do efeito bouncing

#define distMin 300  //em milimetros
#define distMax 4000 //em milimetros

#define pin_pwm 03
#define TEMPO_DE_ESPERA 025
//*****************************************

UltraSonicDistanceSensor hc(pinTrig, pinEcho);  //(trig, echo);
LiquidCrystal lcd(D0,D1,D2,D3,D4,D5);

bool estadoBotao = false;
bool estadoBotaoAnt = false;
unsigned long delayBotao;
int modo = 1;

int distanciaSens;
int distanciaInt;
float distanciaFlt;

void setup() { 
  pinMode(pin_pwm, OUTPUT);
  pinMode(pinBotao, INPUT_PULLUP);
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight(); 
  lcd.clear();
  lcd.print("Dist: ");
}

void loop() {
  estadoBotao = !digitalRead(pinBotao);
  if ((millis() - delayBotao) > tempoDebounce) {
     if (estadoBotao && !estadoBotaoAnt) {
        modo++;
        if (modo > 3) modo = 1;
        
        delayBotao = millis();
     } else if (!estadoBotao && estadoBotaoAnt) {
        delayBotao = millis();
     }
  }
  estadoBotaoAnt = estadoBotao;

  switch (modo) {
    case 1: 
     lcd.display();
     lcd.backlight();
     loop_modo1();
     break;
     
    case 2: 
     lcd.display();
     lcd.backlight();
     loop_modo2();
     break;
     
    case 3: 
     lcd.noDisplay();
     lcd.noBacklight();
     break;

  int valor_pwm = 0
  if hc.dist(>10000)
  else valor_pwm(150) 
  if hc.dist(10000<<25000)     
  }
}

//******************************************************************
void loop_modo1() { 
  distanciaSens  = hc.dist() * 100;
  distanciaInt   = constrain(distanciaSens, distMin, distMax);
  distanciaFlt   = float(distanciaInt) / 100;
  
  lcd.clear();
  
  lcd.print("Dist: ");
  if ((distanciaSens >= distMin) && (distanciaSens <= distMax)) {
     lcd.print( distanciaFlt ); 
     lcd.print("cm");
  } else {
     lcd.print("*****");
  }
  
  lcd.setCursor(15, 0);
  lcd.print(modo); 

  lcd.setCursor(0, 1);
  for (int nL=0; nL < map(distanciaInt,distMin,distMax,0,16); nL++) lcd.print(char(255));

  delay(20);
}

//********************************************************************
void loop_modo2() {
  distanciaSens  = hc.dist() * 100;
  distanciaInt   = constrain(distanciaSens, distMin, distMax);
  distanciaFlt   = float(distanciaInt) / 100;
  
  //lcd.clear();
  
  lcd.setCursor(6, 0);
  if ((distanciaSens >= distMin) && (distanciaSens <= distMax)) {
     lcd.print( distanciaFlt ); 
     lcd.print("cm  ");
  } else {
     lcd.print("*****    ");
  }
  
  lcd.setCursor(15, 0);
  lcd.print(modo); 

  lcd.setCursor(0, 1);
  int grafico = map(distanciaInt,distMin,distMax,0,16);
  for (int nL=0; nL < grafico; nL++)  lcd.print(char(255));
  for (int nL=grafico; nL < 16; nL++) lcd.print(" ");

  delay(20);
}

void loop_modo3() {
  
}