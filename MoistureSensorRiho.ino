/*
 # Example code for the moisture sensor
 # Connect the sensor to the A0 (Analog 0) pin on the Arduino board
 # the sensor value description
 # 0 ~300 dry soil
 # 300~700 humid soil
 # 700~950 in water
*/ 

/*
********************************************
14CORE ULTRASONIC DISTANCE SENSOR CODE TEST
********************************************
*/
#define TRIGGER 5
#define ECHO    4

// NodeMCU Pin D1 > TRIGGER | Pin D2 > ECHO

void setup(){
 Serial.begin(57600);
 pinMode(14,OUTPUT);/*This is D5 on the NODEMCU*/
 /*PURPLE IS GROUND*/
 pinMode(TRIGGER, OUTPUT);
 pinMode(ECHO, INPUT);
 pinMode(BUILTIN_LED, OUTPUT);
}

void loop(){
//------------------------Ultrasonic-----------------------------------------------------------
  long duration, distance;
  
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 

  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  delay(1000);
  distance = (duration/2) / 29.1;
  
  Serial.print(distance);
  Serial.println("Centimeter:");

//------------------------Moisture and motor-----------------------------------------------------------  
 delay(1800);//1800000
 Serial.print("Moisture Sensor Value:");
 Serial.println(analogRead(0));
 int Data = analogRead(0);
 Serial.println(Data);
 delay(300);
 if (analogRead(0)>800){
    Serial.println("Pump on");
    digitalWrite(14,HIGH);
 }else{
    Serial.println("Pump off");
    
 }
 delay(3000);
 digitalWrite(14,LOW);
 
 
}
