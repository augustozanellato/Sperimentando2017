/*
 * V0-V7 pianeti
 * V29 tara
 * V30 LCD1
 * V31 LCD2
 */

#define BLYNK_MSG_LIMIT 5000
#define BLYNK_FANCY_LOGO_3D
#define BLYNK_EXPERIMENTAL
#define debug
#define BLYNK_PRINT Serial
//#define verb

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include "HX711mod.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

String nome = "Terra";
double g = 9.81;
String massa;
String peso;
bool isTerra = true;
double ultimoPeso = 0;

SimpleTimer timer;
HX711 scale;
LiquidCrystal_I2C lcd(0x27,16,2);

char auth[] = "04bfe36ef96b482c94a87bdd348ac069";

char ssid[] = "SperimentandoSeveri2017";
char pass[] = "itiseveripadova";


float rilevaPeso(){
  float mRilevata = scale.get_units();
  #ifdef verb
  Serial.println("mRilevata: " + (String) mRilevata);
  #endif
  if (ultimoPeso - mRilevata > -0.8 && ultimoPeso - mRilevata < 0.8) mRilevata = ultimoPeso;
  ultimoPeso = mRilevata;
  if (mRilevata == ultimoPeso && mRilevata < 1) {
    mRilevata = 0;
    ultimoPeso = 0;
  }
  const int arLenght = 24;
  const double masseGiuste[arLenght]    = {0, 2, 5, 7, 10, 12, 15, 17, 20, 22, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70.6, 75.6, 80.6, 85.6, 90.6};
  const double masseRilevate[arLenght]  = {0, 1.32, 4.03, 5.96, 8.83, 10.72, 13.63, 15.65, 18.75, 20.67, 23.43, 28.19, 32.98, 37.68, 42.6, 47.3, 52.32, 57.05, 61.87, 67.09, 71.93, 76.8, 81.83, 86.59};
  double distanzaP;
  for (int i = 1; i < arLenght; i++){
    if (mRilevata >= masseRilevate[i - 1] && mRilevata <= masseRilevate[i]){
      #ifdef verb
      Serial.println("masseRilevate[i]: " + (String) masseRilevate[i]);
      Serial.println("masseGiuste[i]: " + (String) masseGiuste[i]);
      Serial.println("i: " + (String) i);
      #endif
      distanzaP = (mRilevata - masseRilevate[i - 1]) / (masseRilevate[i] - masseRilevate[i -1]);
      return (masseGiuste[i - 1] + (masseGiuste[i] - masseGiuste[i - 1]) * distanzaP); 
    }
  }
  if (mRilevata > 86) return (mRilevata + 0.6282) / 0.9611;
  else return 0;
}

BLYNK_CONNECTED() {
  Blynk.syncAll();
  #ifdef debug
  BLYNK_LOG("Reconnected");
  #endif
}

BLYNK_WRITE(V0){
  if (param.asInt() == 1){
    isTerra = false;
    nome = "Mercurio";
    g = 3.701;
    //Blynk.virtualWrite(V0, HIGH);
    Blynk.virtualWrite(V1, LOW);
    Blynk.virtualWrite(V2, LOW);
    Blynk.virtualWrite(V3, LOW);
    Blynk.virtualWrite(V4, LOW);
    Blynk.virtualWrite(V5, LOW);
    Blynk.virtualWrite(V6, LOW);
    Blynk.virtualWrite(V7, LOW);
    Blynk.virtualWrite(V8, LOW);
    Blynk.virtualWrite(V9, LOW);
    Blynk.virtualWrite(V10, LOW);
    #ifdef debug
    BLYNK_LOG("Got Mercurio", param.asInt());
    #endif
  }
}

BLYNK_WRITE(V1){
  if (param.asInt() == 1){
    isTerra = false;
    nome = "Venere";
    g = 8.87;
    Blynk.virtualWrite(V0, LOW);
    //Blynk.virtualWrite(V1, HIGH);
    Blynk.virtualWrite(V2, LOW);
    Blynk.virtualWrite(V3, LOW);
    Blynk.virtualWrite(V4, LOW);
    Blynk.virtualWrite(V5, LOW);
    Blynk.virtualWrite(V6, LOW);
    Blynk.virtualWrite(V7, LOW);
    Blynk.virtualWrite(V8, LOW);
    Blynk.virtualWrite(V9, LOW);
    Blynk.virtualWrite(V10, LOW);
    #ifdef debug
    BLYNK_LOG("Got Venere", param.asInt());
    #endif
  }
}
BLYNK_WRITE(V2){
  if (param.asInt() == 1){
    nome = "Terra";
    g = 9.80665;
    isTerra = true;
    Blynk.virtualWrite(V0, LOW);
    Blynk.virtualWrite(V1, LOW);
    //Blynk.virtualWrite(V2, HIGH);
    Blynk.virtualWrite(V3, LOW);
    Blynk.virtualWrite(V4, LOW);
    Blynk.virtualWrite(V5, LOW);
    Blynk.virtualWrite(V6, LOW);
    Blynk.virtualWrite(V7, LOW);
    Blynk.virtualWrite(V8, LOW);
    Blynk.virtualWrite(V9, LOW);
    Blynk.virtualWrite(V10, LOW);
    #ifdef debug
    BLYNK_LOG("Got Terra", param.asInt());
    #endif
  }
}
BLYNK_WRITE(V3){
  if (param.asInt() == 1){
    isTerra = false;
    nome = "Marte";
    g = 3.69;
    Blynk.virtualWrite(V0, LOW);
    Blynk.virtualWrite(V1, LOW);
    Blynk.virtualWrite(V2, LOW);
    //Blynk.virtualWrite(V3, HIGH);
    Blynk.virtualWrite(V4, LOW);
    Blynk.virtualWrite(V5, LOW);
    Blynk.virtualWrite(V6, LOW);
    Blynk.virtualWrite(V7, LOW);
    Blynk.virtualWrite(V8, LOW);
    Blynk.virtualWrite(V9, LOW);
    Blynk.virtualWrite(V10, LOW);
    #ifdef debug
    BLYNK_LOG("Got Marte", param.asInt());
    #endif
  }
}
BLYNK_WRITE(V4){
  if (param.asInt() == 1){
    isTerra = false;
    nome = "Giove";
    g = 23.12;
    Blynk.virtualWrite(V0, LOW);
    Blynk.virtualWrite(V1, LOW);
    Blynk.virtualWrite(V2, LOW);
    Blynk.virtualWrite(V3, LOW);
    //Blynk.virtualWrite(V4, HIGH);
    Blynk.virtualWrite(V5, LOW);
    Blynk.virtualWrite(V6, LOW);
    Blynk.virtualWrite(V7, LOW);
    Blynk.virtualWrite(V8, LOW);
    Blynk.virtualWrite(V9, LOW);
    Blynk.virtualWrite(V10, LOW);
    #ifdef debug
    BLYNK_LOG("Got Giove", param.asInt());
    #endif
  }
}
BLYNK_WRITE(V5){
  if (param.asInt() == 1){
    isTerra = false;
    nome = "Saturno";
    g = 8.96;
    Blynk.virtualWrite(V0, LOW);
    Blynk.virtualWrite(V1, LOW);
    Blynk.virtualWrite(V2, LOW);
    Blynk.virtualWrite(V3, LOW);
    Blynk.virtualWrite(V4, LOW);
    //Blynk.virtualWrite(V5, HIGH);
    Blynk.virtualWrite(V6, LOW);
    Blynk.virtualWrite(V7, LOW);
    Blynk.virtualWrite(V8, LOW);
    Blynk.virtualWrite(V9, LOW);
    Blynk.virtualWrite(V10, LOW);
    #ifdef debug
    BLYNK_LOG("Got Saturno", param.asInt());
    #endif
  }
}
BLYNK_WRITE(V6){
  if (param.asInt() == 1){
    isTerra = false;
    nome = "Urano";
    g = 8.69;
    Blynk.virtualWrite(V0, LOW);
    Blynk.virtualWrite(V1, LOW);
    Blynk.virtualWrite(V2, LOW);
    Blynk.virtualWrite(V3, LOW);
    Blynk.virtualWrite(V4, LOW);
    Blynk.virtualWrite(V5, LOW);
    //Blynk.virtualWrite(V6, HIGH);
    Blynk.virtualWrite(V7, LOW);
    Blynk.virtualWrite(V8, LOW);
    Blynk.virtualWrite(V9, LOW);
    Blynk.virtualWrite(V10, LOW);
    #ifdef debug
    BLYNK_LOG("Got Urano", param.asInt());
    #endif
  }
}
BLYNK_WRITE(V7){
  if (param.asInt() == 1){
    isTerra = false;
    nome = "Nettuno";
    g = 11.15;
    Blynk.virtualWrite(V0, LOW);
    Blynk.virtualWrite(V1, LOW);
    Blynk.virtualWrite(V2, LOW);
    Blynk.virtualWrite(V3, LOW);
    Blynk.virtualWrite(V4, LOW);
    Blynk.virtualWrite(V5, LOW);
    Blynk.virtualWrite(V6, LOW);
    //Blynk.virtualWrite(V7, HIGH);
    Blynk.virtualWrite(V8, LOW);
    Blynk.virtualWrite(V9, LOW);
    Blynk.virtualWrite(V10, LOW);
    #ifdef debug
    BLYNK_LOG("Got Nettuno", param.asInt());
    #endif
  }
}
BLYNK_WRITE(V8){
  if (param.asInt() == 1){
    isTerra = false;
    nome = "Luna";
    g = 1.622;
    Blynk.virtualWrite(V0, LOW);
    Blynk.virtualWrite(V1, LOW);
    Blynk.virtualWrite(V2, LOW);
    Blynk.virtualWrite(V3, LOW);
    Blynk.virtualWrite(V4, LOW);
    Blynk.virtualWrite(V5, LOW);
    Blynk.virtualWrite(V6, LOW);
    Blynk.virtualWrite(V7, LOW);
    //Blynk.virtualWrite(V8, HIGH);
    Blynk.virtualWrite(V9, LOW);
    Blynk.virtualWrite(V10, LOW);
    #ifdef debug
    BLYNK_LOG("Got Luna", param.asInt());
    #endif
  }
}
BLYNK_WRITE(V9){
  if (param.asInt() == 1){
    isTerra = false;
    nome = "ISS";
    g = 0;
    Blynk.virtualWrite(V0, LOW);
    Blynk.virtualWrite(V1, LOW);
    Blynk.virtualWrite(V2, LOW);
    Blynk.virtualWrite(V3, LOW);
    Blynk.virtualWrite(V4, LOW);
    Blynk.virtualWrite(V5, LOW);
    Blynk.virtualWrite(V6, LOW);
    Blynk.virtualWrite(V7, LOW);
    Blynk.virtualWrite(V8, LOW);
    //Blynk.virtualWrite(V9, HIGH);
    Blynk.virtualWrite(V10, LOW);
    #ifdef debug
    BLYNK_LOG("Got ISS", param.asInt());
    #endif
  }
}
BLYNK_WRITE(V10){
  if (param.asInt() == 1){
    isTerra = false;
    nome = "Sole";
    g = 274.0;
    Blynk.virtualWrite(V0, LOW);
    Blynk.virtualWrite(V1, LOW);
    Blynk.virtualWrite(V2, LOW);
    Blynk.virtualWrite(V3, LOW);
    Blynk.virtualWrite(V4, LOW);
    Blynk.virtualWrite(V5, LOW);
    Blynk.virtualWrite(V6, LOW);
    Blynk.virtualWrite(V7, LOW);
    Blynk.virtualWrite(V8, LOW);
    Blynk.virtualWrite(V9, LOW);
    //Blynk.virtualWrite(V10, HIGH);
    #ifdef debug
    BLYNK_LOG("Got Sole", param.asInt());
    #endif
  }
}


BLYNK_WRITE(V29){
  if (param.asInt() == 1){
    scale.tare();
    #ifdef debug
    BLYNK_LOG("Got Tara", param.asInt());
    #endif
  }
}

void lcdUpdate(){
  String spaces1 = "";
  for (int i = 0; i < (16 - ((String) "Massa:" + massa + " Kg").length()); i++){
    spaces1 += " ";
  }
  String line1 = "Massa:" + spaces1 + ((String)massa + " Kg");

  
  String spaces2 = "";
  for (int i = 0; i < (16 - ((String) nome + ":" + peso).length()); i++){
    spaces2 += " ";
  }
  String line2 = nome + ":" + spaces2 + peso;
  Blynk.virtualWrite(V30, line2);
  Blynk.virtualWrite(V31, line1);
}

void i2cUpdate(){
  String spaces1 = "";
  for (int i = 0; i < (16 - ((String) "Massa:" + massa + " Kg").length()); i++){
    spaces1 += " ";
  }
  String line1 = "Massa:" + spaces1 + ((String)massa + " Kg");
  String spaces2 = "";
  for (int i = 0; i < (16 - ((String) nome + ":" + peso).length()); i++){
    spaces2 += " ";
  }
  String line2 = nome + ":" + spaces2 + peso;
  
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

void getForce(){
  massa = rilevaPeso();
  if (massa.toFloat() < 0) massa = (String) 0;
  peso = (float) massa.toFloat() / 9.80665 * g;
  peso.remove(peso.length() - 1); 
  peso += " N";
  massa.remove(massa.length() - 1);
}

void autoTare(){
  float massaTest = scale.get_units(1);
  if (massaTest < 0.8) scale.tare();
}

void setup(){
  lcd.init();
  lcd.backlight();
  ESP.wdtDisable();
  ESP.wdtEnable(2000);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass, IPAddress(172, 24, 1, 1));
  yield();
  ESP.wdtFeed();
  scale.begin(D3, D4);
  timer.setInterval(150L, getForce);
  timer.setInterval(150L, lcdUpdate);
  timer.setInterval(600L, i2cUpdate);
  timer.setInterval(6000L, autoTare);
  scale.tare();
  yield();
  ESP.wdtFeed();
  scale.set_scale(34856.f);
  Blynk.virtualWrite(V0, LOW);
  Blynk.virtualWrite(V1, LOW);
  Blynk.virtualWrite(V2, HIGH);
  Blynk.virtualWrite(V3, LOW);
  Blynk.virtualWrite(V4, LOW);
  Blynk.virtualWrite(V5, LOW);
  Blynk.virtualWrite(V6, LOW);
  Blynk.virtualWrite(V7, LOW);
  Blynk.virtualWrite(V8, LOW);
  Blynk.virtualWrite(V9, LOW);
  Blynk.virtualWrite(V10, LOW);
}

void loop(){
  Blynk.run();
  timer.run();
}

