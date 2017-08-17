#include <OneWire.h>

#include <DallasTemperature.h>

// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2
 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
 
 
const int buttonPlus = 8;
const int buttonMinus = 9;
const int ledRed = 10;
const int ledGreen = 11;


//Variables
float targetTemp = 0; 
float currentTemp = 0; 
float tempDiff = 0.5;
 
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Temperature Controller");

  // Start up the library
  sensors.begin();
  pinMode(buttonMinus,INPUT);
  pinMode(buttonPlus,INPUT);
  pinMode(ledRed,OUTPUT);
  pinMode(ledGreen,OUTPUT);
  
  digitalWrite(ledRed, HIGH);
  digitalWrite(ledGreen, HIGH);
  delay(1000);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledGreen, LOW);
}
 
 
void loop(void)
{
  
  if(digitalRead(buttonPlus)){
     targetTemp++;
   }
   
   if(digitalRead(buttonMinus)){
     if(targetTemp<1)
       targetTemp = 0;
       else
         targetTemp--;
   }
  
  sensors.requestTemperatures(); // Send the command to get temperatures
  currentTemp = sensors.getTempCByIndex(0); 
  
  
  
  if(currentTemp < targetTemp - tempDiff)
    digitalWrite(ledRed, HIGH);
    else
      digitalWrite(ledRed, LOW);
    
   if(currentTemp > targetTemp + tempDiff)
    digitalWrite(ledGreen, HIGH);
    else
      digitalWrite(ledGreen, LOW);
      
      
    Serial.print("Current Temp: ");Serial.println(currentTemp);
    Serial.print("Target Temp: ");Serial.println(targetTemp);
    
    Serial.print("Heat: ");Serial.println(ledRed);
    Serial.print("Cooling: ");Serial.println(ledGreen);
      
    

 
}


