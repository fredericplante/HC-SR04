#define broche_Trig 12
#define broche_Echo 3
#define broche_Piezo 8

unsigned long derniere_impulsion = 0; 
const long intervale = 1000;

bool en_attente = false;

unsigned long debut_ping = 0;

const double k_Mach = 29.4117647;
int ajustement_fin = 0;

byte distance;

void setup() {

  pinMode(broche_Trig, OUTPUT);
  pinMode(broche_Echo, INPUT);

  Serial.begin (115200);
  
}

void loop() {
  
  if((millis() - derniere_impulsion >= intervale) && (en_attente == false)) {
    
    envoyer_impulsion();
    derniere_impulsion = millis();
  
  }
    
}

void envoyer_impulsion(){
  
  digitalWrite(broche_Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(broche_Trig, LOW);
  attachInterrupt(1, echo_percue, RISING);
  en_attente = true;

}

void echo_percue(){
  
  debut_ping = micros();
  detachInterrupt(1);
  attachInterrupt(1, echo_terminee, FALLING);

}  

void echo_terminee(){
  
  distance = ((0.5 / k_Mach) * (micros() - debut_ping)) + ajustement_fin;
  
  if (!(distance >= 100 || distance <= 0)){
     
    Serial.println((String)distance + F(" cm"));
    tone(broche_Piezo, 10500 / distance, 5); 
    
  }
  
  detachInterrupt(1);
  en_attente = false;
  
}
