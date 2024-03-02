#include <Servo.h>
#include <NewPing.h>
#define BUTTON_PIN 2
#define TRIGGER_PIN  9  
#define ECHO_PIN     10
#define MAX_DISTANCE 200
#define LED_PIN 13
#define PRESENCE_SENSOR 3

//definire obiecte
Servo servo;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
int numarIesiri=0;
int numarIntrari=0;
int StateUsa;
unsigned int Distance = 0;

//definire constante
int pozitieUsa = 150;
int presence_sensor = 0;
bool occupied = false;

void deschideUsa(){
  for(pozitieUsa; pozitieUsa > 10; pozitieUsa--)   
  {                                  
    servo.write(pozitieUsa);               
    delay(15);                   
  }
  delay(3000);
}

void inchideUsa(){
   for(pozitieUsa; pozitieUsa < 150; pozitieUsa++)  
  {                                  
    servo.write(pozitieUsa);               
    delay(15);                   
  }
}
void Print(int StateUsa,int Distance, int numarIesiri, int numarIntrari)
{
  if(StateUsa==1)
  {
    Serial.print("{\"StateUsa\":");
    Serial.print("Usa deschisa");  
  }
  else if(StateUsa==0)
  {
    Serial.print("{\"StateUsa\":");
    Serial.print("Usa inchisa");
  }
    Serial.print(",\"Distanta\":");
    Serial.print(Distance);
    Serial.print(",\"IesiriPersoane\":");
    Serial.print(numarIesiri);
    Serial.print(",\"IntrariPersoane\":");
    Serial.print(numarIntrari);
    Serial.println("}");
}

void setup() {
  pinMode(LED_PIN, OUTPUT);   
  pinMode(PRESENCE_SENSOR, INPUT);
  pinMode(BUTTON_PIN, INPUT);
  servo.attach(8);
  servo.write(pozitieUsa);
  Serial.begin(9600);
}

void loop() 
{ 
  presence_sensor = digitalRead(PRESENCE_SENSOR);
  int buttonState = digitalRead(BUTTON_PIN);    
  if(buttonState == HIGH && pozitieUsa == 150 && occupied==true){
    deschideUsa(); 
    occupied = false;
    delay(3000);
    inchideUsa();
    numarIesiri++;
    StateUsa=0;
    Print(StateUsa,Distance,numarIesiri,numarIntrari);
  }
  if(sonar.ping_cm()>10 && sonar.ping_cm()<20 && pozitieUsa == 150 && occupied==false ){
    deschideUsa();
    Distance = sonar.ping_cm();
    numarIntrari++;
    StateUsa = 1;
    Print(StateUsa,Distance,numarIesiri,numarIntrari);
  }
  if(presence_sensor==HIGH && pozitieUsa == 10 ){
    inchideUsa();
    occupied = true;
    StateUsa = 0;
    Print(StateUsa,Distance,numarIesiri,numarIntrari);
  }
}
