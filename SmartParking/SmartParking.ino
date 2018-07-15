#include <LiquidCrystal_I2C.h>

#include "UbidotsMicroESP8266.h"

#include <Wire.h>



LiquidCrystal_I2C lcd(0x27, 16, 2);

#define TOKEN  "xxxxxxxxxxxxxxxxxxxxxxxxxx"  // Put here your Ubidots TOKEN 
#define WIFISSID "xxxxxxxxxxxxxxxxxxxxxxxx" // Put here your Wi-Fi SSID
#define PASSWORD "xxxxxxxxxxxxxxxxxxxxxxxx" // Put here your Wi-Fi password

Ubidots client(TOKEN);
int Status = 12;  // Digital pin D6
int no_of_car=0;
int sensor1 = 13;
int sensor2 = 4;


void setup() {

Serial.begin(115200);
Serial.println("Hello world!");
  no_of_car=0;
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  client.wifiConnection(WIFISSID, PASSWORD);
    Wire.begin(D2,D1);
//  lcd.begin();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight 
  lcd.home();
  lcd.print(" Hello Makers "); // Start Printing
      
delay(25);
}

// the loop function runs over and over again forever
void loop() {

   int state1 = digitalRead(sensor1);
  /* Serial.println(state1);
        delay(500);
   */
    if(state1 == 1) {
     digitalWrite(LED_BUILTIN, HIGH);   
      Serial.println("Motion detected! in sensor1 CAR IS ENTERING PARKING LOT ");
      no_of_car=no_of_car+1;
      Serial.println(no_of_car);
      
      
      delay(4000);
    }

      else {
      digitalWrite (LED_BUILTIN, LOW);
      Serial.println("Motion absent! in sensor 1");
      delay(2000);
      }

    long state2 = digitalRead(sensor2);

    if(state2 == HIGH) {
     digitalWrite(LED_BUILTIN, HIGH);   
      //Serial.println("Motion detected! in sensor2 CAR IS EXITING OUT OF PARKING LOT");
      Serial.println("Motion absent! in sensor 2");
      //no_of_car=no_of_car-1;
      Serial.println(no_of_car);
      
      
      delay(4000);
    }

      else {
      digitalWrite (LED_BUILTIN, LOW);
      Serial.println("Motion absent! in sensor 2");
      delay(2000);
      }


client.add("no_of_car", no_of_car);
    //client.add("switch", value2);
    client.sendAll(true);
    delay(5000);

}
