//-- MOTEUR A --
int ENA=9; //Connecté à Arduino pin 9(sortie PWM)
int IN1=4; //Connecté à Arduino pin 4
int IN2=5; //Connecté à Arduino pin 5

//-- MOTEUR B --
int ENB=10; //Connecté à Arduino pin 10(Sortie PWM)
int IN3=6; //Connecté à Arduino pin 6
int IN4=7; //Connecté à Arduino pin

void setup() {
  // put your setup code here, to run once:
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  Serial.begin(9600);
  
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
}

void loop() {
  // moteur A = gauche (IN1,2)
  // moteur B = droite (IN3,4)
  
  Serial.print("2 : ");
  Serial.print(digitalRead(2));
  Serial.print("     3 : ");
  Serial.println(digitalRead(3));

  digitalWrite(ENA,200);// Moteur A - Ne pas tourner
  digitalWrite(ENB,200);
  
  if (digitalRead(2)==1){
    delay(50);
    digitalWrite(IN3,LOW); //on fait reculer la roue droite
    digitalWrite(IN4,HIGH);
    analogWrite(ENA,100);
    analogWrite(ENB,100);
    delay(2000); //temps de rotation
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
  }
}
