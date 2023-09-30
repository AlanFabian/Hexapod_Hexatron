const int SensorPin = 9;

void setup(){
  Serial.begin(9600);
  pinMode(sensorPin,INPUT);
}
void loop(){
  int value = 0;
  value =  digitalRead(sensorPin);
  if(value==HIGH){
    Serial.println("Se ha detectado un obstaculo");
    
  }
  delay(1000);
}
