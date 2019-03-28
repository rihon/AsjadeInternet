/*
 # Example code for the moisture sensor
 # Connect the sensor to the A0 (Analog 0) pin on the Arduino board
 # the sensor value description
 # 0 ~300 dry soil
 # 300~700 humid soil
 # 700~950 in water
*/ 
/*
PINTOUT: 
DHT22 1.juhe=Toide 2.juhe=D5 4.juhe=Ground
LUX andur VCC=Toide GND=Ground SCL=D1 SDA=D2
Moisture Sensor VCC=Toide A0 GND
Kaugus D6 = TRIGGER D7 = ECHO
Mootor D8
*/

/*
********************************************
14CORE ULTRASONIC DISTANCE SENSOR CODE TEST
********************************************
*/
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
#include "DHT.h"
#define DHTPIN 14
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);
ESP8266WiFiMulti WiFiMulti;
#define USE_SERIAL Serial
#define TRIGGER 12
#define ECHO    13





void setup(){
 Serial.begin(57600);
 //pinMode(8,OUTPUT);/*This is D8 on the NODEMCU*/
 /*PURPLE IS GROUND*/
 //pinMode(TRIGGER, OUTPUT);
 //pinMode(ECHO, INPUT);
 //pinMode(BUILTIN_LED, OUTPUT);
 dht.begin();
 /* Initialise the sensor */
 tsl.enableAutoRange(true);
 tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);
 WiFi.mode(WIFI_STA);
 WiFiMulti.addAP("TLU", "");
}

void loop(){
/*
  for(int i;i<20;i++){
  String payload;
  if((WiFiMulti.run() == WL_CONNECTED)) {
        HTTPClient http;
        USE_SERIAL.print("[HTTP] begin...\n");
        http.begin("http://internetofasjad.000webhostapp.com/mootor.txt"); //HTTP 
        USE_SERIAL.print("[HTTP] GET...\n");
        int httpCode = http.GET();
        if(httpCode > 0) {
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
            if(httpCode == HTTP_CODE_OK) {
                payload = http.getString();
                USE_SERIAL.println(payload);
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
        http.end();
    }
  delay(500);
  
  

  if(payload="true"){
    digitalWrite(14,HIGH);
    delay(2500);
    digitalWrite(14,LOW);
    if((WiFiMulti.run() == WL_CONNECTED)) {
        HTTPClient http;
        USE_SERIAL.print("[HTTP] begin...\n");
        http.begin("http://internetofasjad.000webhostapp.com/write_data.php?done=true"); //HTTP 
        USE_SERIAL.print("[HTTP] GET...\n");
        int httpCode = http.GET();
        if(httpCode > 0) {
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
        http.end();
    }
  }
  delay(5000);
  
  }
  */
//------------------------Ultrasonic-----------------------------------------------------------
 /*long duration, distance;
  
  digitalWrite(TRIGGER, LOW);  
  delayMicroseconds(2); 
  
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10); 

  
  digitalWrite(TRIGGER, LOW);
  duration = pulseIn(ECHO, HIGH);
  delay(500);
  distance = (duration/2) / 29.1;
  
  Serial.print(distance);
  Serial.println("Centimeter:");
*/
//------------------------Moisture and motor-----------------------------------------------------------  
 /*delay(500);//1800000
 Serial.print("Moisture Sensor Value:");
 Serial.println(analogRead(0));
 int Data = analogRead(0);
 Serial.println(Data);
 delay(500);
 if (analogRead(0)>800){
    Serial.println("Pump on");
    digitalWrite(14,HIGH);
    delay(3000);
 }else{
    Serial.println("Pump off");
    
 }
 delay(500);
 digitalWrite(14,LOW);
 */
//-----------------Light and DHT22------------------------
// Get a new sensor event 
  sensors_event_t event;
  tsl.getEvent(&event);
 
// Display the results (light is measured in lux)
float light_level = event.light;
  if (event.light)
  {
    
    Serial.print(event.light); 
    Serial.println(" lux");
  }
  else
  {
    Serial.println("Sensor overload");
  }
  // Wait a few seconds between measurements.
    delay(3000);
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();  
  delay(500); 

  //h,t,light_level,distance,Data
  /*
  float h = 500;//Humidity of air
  float t = 500; //Temperature
  float light_level = 500;
  */
  float Data=500;//Humidity of soil
  
  float distance=50;
  
if((WiFiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        //http.begin("https://192.168.1.12/test.html", "7a 9c f4 db 40 d3 62 5a 6e 21 bc 5c cc 66 c8 3e a1 45 59 38"); //HTTPS
        //String address = "http://sisekliima.000webhostapp.com/write_data.php?value=";
        //String result = address + boost::lexical_cast<std::string>(lux);
        http.begin("http://internetofasjad.000webhostapp.com/write_data.php?temperatuur="+String(t)+"&niiskus="+String(h)+"&valgus="+String(light_level)+"&pNiiskus="+String(Data)+"&taimeKorgus="+String(distance)); //HTTP 

        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        //http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }
    delay(500);
}
