#include "ArduPID.h"

ArduPID myController;

double setpoint = 20; // Distanta dorita a mingii de ping-pong, in pratica din cauza aproximarilor, distanta reala= setpoint+7, deci aici e 27
double input;
double output;
double p = 1.21;//2.2; // Ajustarea parametrului P
double i = 0.39;//0.1; // Ajustarea parametrului I
double d = 0.05;//0.6; // Ajustarea parametrului D

const byte OC1A_PIN = 9; // Pinul pentru controlul ventilatorului
const byte OC1B_PIN = 10; // Alt pin pentru controlul ventilatorului

const int trigPin = 11; // Pinul pentru trimiterea semnalului ultrasunetelor
const int echoPin = 12; // Pinul pentru recepționarea semnalului ultrasunetelor

long duration;
int distance;

const word  PWM_FREQ_HZ = 25000;
const word TCNT1_TOP = 16000000/(2*PWM_FREQ_HZ);

void setup() {
  pinMode(OC1A_PIN, OUTPUT);
  pinMode(A0, INPUT);

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  TCCR1A |= (1 << COM1A1)  | (1 << WGM11);
  TCCR1B |= (1 << WGM13) | (1 << CS10);
  ICR1 = TCNT1_TOP;

  myController.begin(&input, &output, &setpoint, p, i, d);
  myController.setOutputLimits(20, 60);
  myController.setBias(40);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  //Serial.println(duration);
  distance = duration * 0.034 / 2;
  
  input = distance;
  Serial.println(input);
  myController.compute();
  setPwmDuty(output);
  
  //Serial.println(output);
}

void setPwmDuty(byte duty) {
  OCR1A = (word) (duty*TCNT1_TOP)/100;
}
