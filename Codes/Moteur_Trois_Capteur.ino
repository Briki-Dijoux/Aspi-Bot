//-- MOTEUR A --
int ENA=9; //Connecté à Arduino pin 9(sortie PWM)
int IN1=4; //Connecté à Arduino pin 4
int IN2=5; //Connecté à Arduino pin 5

//-- MOTEUR B --
int ENB=10; //Connecté à Arduino pin 10(Sortie PWM)
int IN3=6; //Connecté à Arduino pin 6
int IN4=7; //Connecté à Arduino pin

// -- Capteur droite --
int CaptD = 11;

// -- Capteur central --
int CaptC = 12;

// -- Capteur gauche --
int CaptG = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(CaptD,INPUT);
  pinMode(CaptC,INPUT);
  pinMode(CaptG,INPUT);
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
  
  Serial.print("Capteur Gauche : ");
  Serial.print(digitalRead(CaptG));
    Serial.print("Capteur Central : ");
  Serial.print(digitalRead(CaptC));
    Serial.print("Capteur Droite : ");
  Serial.print(digitalRead(CaptD));

  digitalWrite(ENA,255);// Moteur A - Ne pas tourner
  digitalWrite(ENB,255);
  
  if ( (digitalRead(CaptG)==0) || (digitalRead(CaptC)==0) || (digitalRead(CaptD)==0) ){
    
    delay(50);
    
    digitalWrite(IN1,1); //on fait reculer la roue gauche
    digitalWrite(IN2,0);
    digitalWrite(IN3,0); //on fait reculer la roue droite
    digitalWrite(IN4,1);
    
    analogWrite(ENB,155); //on fait tourner vers la gauche (moteur droit tourne moins vite)

    delay(1000); //temps de rotation
    digitalWrite(IN3,1); //on refait avancer tout droit jusqu'à un nouveau choc
    digitalWrite(IN4,0);
    
  }
}
