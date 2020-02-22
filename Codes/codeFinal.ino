//constantes module HC-06
#include<SoftwareSerial.h>

#define RX 12
#define TX 13

char data;

SoftwareSerial Bt(RX,TX);

//-- MOTEUR A --
int ENA=9; //Connecté à Arduino pin 9(sortie PWM)
int IN1=4; //Connecté à Arduino pin 4
int IN2=5; //Connecté à Arduino pin 5

//-- MOTEUR B --
int ENB=10; //Connecté à Arduino pin 10(Sortie PWM)
int IN3=6; //Connecté à Arduino pin 6
int IN4=7; //Connecté à Arduino pin

//-- Capteur droite --
int CaptD = 2;

//-- Capteur gauche --
int CaptG = 3;

//variable pour l'activation du nettoyage
int cleaning;

void setup() {
  //module HC-06
  Serial.begin(9600);
  Serial.println("ouais ouais ouais");
  Bt.begin(9600);
  //capteurs
  pinMode(CaptD,INPUT);
  pinMode(CaptG,INPUT);
  // moteur
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  // Direction du Moteur A
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  // Direction du Moteur B
  // NB: en sens inverse du moteur A
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  digitalWrite(ENA,LOW);// Moteur A - Ne pas tourner
  digitalWrite(ENB,LOW);// Moteur B - Ne pas tourner
  
  cleaning = 0;
}

void loop() {
  if (cleaning==1) {
    analogWrite(ENA,255);
    analogWrite(ENB,255);
    while (!Bt.available()) { // tant que le module bluetooth n'est pas sollicité
      if ((digitalRead(CaptG)==0) || (digitalRead(CaptD)==0)) { //choc détecté
        delay(50);
        digitalWrite(IN1,HIGH); //on fait reculer la roue gauche
        digitalWrite(IN2,LOW);
        digitalWrite(IN3,LOW); //on fait reculer la roue droite
        digitalWrite(IN4,HIGH);
        analogWrite(ENB,100); //on fait tourner vers la gauche (moteur droit tourne moins vite)
        delay(1000); //temps de rotation
        digitalWrite(IN1,LOW); //on refait avancer tout droit jusqu'à un nouveau choc ou l'arrêt
        digitalWrite(IN2,HIGH);
        digitalWrite(IN3,HIGH); 
        digitalWrite(IN4,LOW);
        analogWrite(ENB,255);
      }
    }
    data = char(Bt.read());
    if (data=='S'){ // arrêt du nettoyage
      cleaning=0;
    }
  }

  if (cleaning==0){
    analogWrite(ENA,0);
    analogWrite(ENB,0);
  }
  
  while (Bt.available()) {
    Serial.print("OK");
    Serial.print(char(Bt.read()));
    data = char(Bt.read());
    if (data=='C'){ // lancement du nettoyage
      cleaning=1;
    }
  }
  
  while (Serial.available()) {
    Bt.write(char(Serial.read()));
  }
}
