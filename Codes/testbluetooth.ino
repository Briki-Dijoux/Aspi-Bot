#include<SoftwareSerial.h>

#define RX 2
#define TX 3

char data;

SoftwareSerial Bt(RX,TX);

void setup() {
  Serial.begin(9600);
  Serial.println("ouais ouais ouais");
  Bt.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Bt.available()) {
    Serial.print(char(Bt.read()));
    data = char(Bt.read());
    if (data=='C'){
      Serial.println("Start cleaning.");
    }
  }
  while (Serial.available()) {
    Bt.write(char(Serial.read()));
  }
}
