//Carro desviando de obstáculos

#include <Servo.h>
#include "NewPing.h"


//Pinos no Sensor Shield v5.0
#define SONAR_SERVO_PIN 4
#define TRIGGER_PIN     A0
#define ECHO_PIN        A1

#define MAX_DISTANCE    200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Servo myServo;

//Motor A (Lado Direito)
const int enA = 10;
const int in1 = 9;
const int in2 = 8;

//Motor B (Lado Esquerdo)
const int enB = 5;
const int in3 = 7;
const int in4 = 6;

const int triggerDistance = 20;

//Variaveis
unsigned int time;   // Armazena o tempo da onda ultrassônica
int distance;        // Armazena a distância calculada a partir do sensor
int fDistance;      //  Armazena a distância na frente do robô
int eDistance;      //  Armazena a distância no lado esquerdo do robô
int dDistance;      //  Armazena a distância no lado direito do robô


char dist[3];
char rot[3];
int rotation = 0;
String output = "";


void setup() 
{ 
  pinMode (TRIGGER_PIN, OUTPUT);
  pinMode (ECHO_PIN, INPUT);
  myServo.attach(SONAR_SERVO_PIN);  // Anexa o Servo ao objeto Servo

  // Controle de saída do motor
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
} 

void loop(){
  scan();                                //Obter a distância recuperada
  fDistance = distance;
  if(fDistance < triggerDistance){
    paratras(255);
    delay(1000); 
    direita(255);
    delay(300);
    parar();
    scan();
    dDistance = distance;
    esquerda(255);
    delay(500);
    parar();
    scan();
    eDistance = distance;
    if(eDistance < dDistance){
      direita(255);
      delay(1000);
      parafrente(255);
    }
    else{
      parafrente(255);
    }
  }
  else{
    parafrente(255);
  }
}

void scan(){
  int deg = 90;
  myServo.write(deg);
  delay(10);

  time = sonar.ping();
  distance = time / US_ROUNDTRIP_CM; //ping
  delay(10);
  if(distance <= 0){
    distance = triggerDistance;
  }

  delay(30);
}

void parafrente(int speed)
{
  // turn on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

void paratras(int speed)
{
  // turn on motor A
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  // turn on motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

void direita(int speed)
{
  // on motor A
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  // off motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

void esquerda(int speed)
{
  // on motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  // off motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  analogWrite(enA, speed);
  analogWrite(enB, speed);
}

void parar()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  delay(200);
}









