#include <NewPing.h>

// Definición de pines físicos de los motores

#define motorIzqA 2
#define motorIzqB 3
#define motorDerA 4
#define motorDerB 5
#define ENA 11
#define ENB 6

int vel = 200;
int velsuave = 180;


//Definición de pines físicos de los sensores de ultrasonido

#define TriggerF 12
#define EchoF    13
#define TriggerL 8
#define EchoL    7
#define max_distance 500


int dmaxF = 30;
int dmaxL = 20;
NewPing sonarF(TriggerF, EchoF, max_distance);
NewPing sonarL(TriggerL, EchoL, max_distance);

// Funciones de dirección de movimiento y velocidad

void derechaa(){
  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
  digitalWrite(motorIzqA, LOW);
  digitalWrite(motorIzqB, HIGH);
  digitalWrite(motorDerA, LOW);
  digitalWrite(motorDerB, HIGH);
}

void izquierdaa(){
  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
  digitalWrite(motorIzqA, HIGH);
  digitalWrite(motorIzqB, LOW);
  digitalWrite(motorDerA, HIGH);
  digitalWrite(motorDerB, LOW);
}

void izquierda(){
  digitalWrite(motorIzqA, LOW);
  digitalWrite(motorIzqB, LOW);
  digitalWrite(motorDerA, HIGH);
  digitalWrite(motorDerB, LOW);
  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
}

void derecha(){
  digitalWrite(motorIzqA, LOW);
  digitalWrite(motorIzqB, HIGH);
  digitalWrite(motorDerA, LOW);
  digitalWrite(motorDerB, LOW);
  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
}

void go(){
  digitalWrite(motorIzqA, LOW);
  digitalWrite(motorIzqB, HIGH);
  digitalWrite(motorDerA, HIGH);
  digitalWrite(motorDerB, LOW);
  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
}

void derechasuave(){
  digitalWrite(motorIzqA, LOW);
  digitalWrite(motorIzqB, HIGH);
  digitalWrite(motorDerA, HIGH);
  digitalWrite(motorDerB, LOW);
  analogWrite(ENA, vel);
  analogWrite(ENB, velsuave);
}

void izquierdasuave(){
  digitalWrite(motorIzqA, LOW);
  digitalWrite(motorIzqB, HIGH);
  digitalWrite(motorDerA, HIGH);
  digitalWrite(motorDerB, LOW);
  analogWrite(ENA, velsuave);
  analogWrite(ENB, vel);
}

void back(){
  digitalWrite(motorIzqA, HIGH);
  digitalWrite(motorIzqB, LOW);
  digitalWrite(motorDerA, LOW);
  digitalWrite(motorDerB, HIGH);
  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
}

void stop(){
  digitalWrite(motorIzqA, LOW);
  digitalWrite(motorIzqB, LOW);
  digitalWrite(motorDerA, LOW);
  digitalWrite(motorDerB, LOW);
}


void setup() {
  Serial.begin(9600);
 // Configuración de pines de motores como salida
  pinMode(motorIzqA, OUTPUT);
  pinMode(motorIzqB, OUTPUT);
  pinMode(motorDerA, OUTPUT);
  pinMode(motorDerB, OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
}

// Lógica de movimiento para esquivar obstáculos

void loop() {
  float dL = 0;
  float dF = 0;
  dL = sonarL.ping_cm();
  dF = sonarF.ping_cm();
  // dL = (0.0344 *sonarL.ping_median(5)*1/2);
  // dF =(0.0344 *sonarF.ping_median(5)*1/2);
  // Serial.print(dL);
  // Serial.print( "\t" );
  // Serial.print(dF);
  // Serial.print( "\t" );
  if(dF > dmaxF or dF == 0) {
    if(dL == 0 or dL > 40){
      izquierdaa();
      // Serial.println("anti_clock");
    }else{
      if(dL<10){
        derechasuave();
        // Serial.println("derechasuave");

      }else{
        if(10<=dL and dL<=15){
          go();
          // Serial.println("go");
        }else{
          izquierdasuave();
          // Serial.println("anti_slow");
        }    
      }
    }
  }else{
    derechaa();
    // Serial.println("clock");
    delay(350);
    go();
    delay(350);
  }
}