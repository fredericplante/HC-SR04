#define broche_Trig 12
#define broche_Echo 3
#define broche_Piezo 8

unsigned long debut_ping = 0;

const double k_Mach = 29.4117647;

byte distance;
bool en_attente = false;

void setup() {

  
  pinMode(broche_Trig, OUTPUT);
  pinMode(broche_Echo, INPUT);

  Serial.begin (115200);
  
}

void loop() {
  
  
  if(en_attente == false) {
  
    delay(500);
    digitalWrite(broche_Trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(broche_Trig, LOW);
    attachInterrupt(1, echo_percue, RISING);
    en_attente = true;
    
  }
  
}

void echo_percue(){
  
  debut_ping = micros();
  detachInterrupt(1);
  attachInterrupt(1, echo_terminee, FALLING);

}  

void echo_terminee(){
  
  distance = ((0.5 / k_Mach) * (micros() - debut_ping));//f(x) = ax
  
  if (!(distance >= 150 || distance <= 0)){
     
    Serial.println((String)distance + F(" cm"));
    tone(broche_Piezo, 10500, 5); 
    
  }
  
  detachInterrupt(1);
  en_attente = false;
}
