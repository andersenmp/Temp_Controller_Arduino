#include <OneWire.h>

#include <DallasTemperature.h>

#include <LiquidCrystal.h>

// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 6
 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
 
 
const int buttonPlus = 8;
const int buttonMinus = 9;
const int ledRed = 10;
const int ledGreen = 7;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


//Variables
float targetTemp = 0; 
float currentTemp = 0; 
float tempDiff = 0.5;
int heat = 0;
int cooling = 0;
 
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
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Catspaw!!!!");
  
  digitalWrite(ledRed, HIGH);
  digitalWrite(ledGreen, HIGH);
  delay(1000);
  digitalWrite(ledRed, LOW);
  digitalWrite(ledGreen, LOW);
  
  sensors.requestTemperatures(); // Send the command to get temperatures
  currentTemp = sensors.getTempCByIndex(0); 
  targetTemp = (int)currentTemp;
  
  lcd.clear();
  
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
  
  
  
    lcd.setCursor(15, 0);
    lcd.print("*");
  if(currentTemp < targetTemp - tempDiff){
    heat = 1;
    digitalWrite(ledRed, HIGH);
    lcd.setCursor(15, 0);
    lcd.print("H");
  }else{
    heat = 0;  
    digitalWrite(ledRed, LOW);
  }  
   if(currentTemp > targetTemp + tempDiff){
     cooling = 1;
     digitalWrite(ledGreen, HIGH);
     lcd.setCursor(15, 0);
     lcd.print("C");
   }else{
     cooling = 0;
     digitalWrite(ledGreen, LOW);
   }
      
    Serial.print("Current Temp: ");Serial.println(currentTemp);
    Serial.print("Target Temp: ");Serial.println(targetTemp);
    
    Serial.print("Heat: ");Serial.println(heat);
    Serial.print("Cooling: ");Serial.println(cooling);
     
     
   lcd.setCursor(0, 0);
   lcd.print("Target:");
   lcd.setCursor(8, 0);
   lcd.print(targetTemp);  
      
   lcd.setCursor(0, 1);
   lcd.print("Temp:");
   lcd.setCursor(8, 1);
   lcd.print(currentTemp);
   
   
    

 
}


