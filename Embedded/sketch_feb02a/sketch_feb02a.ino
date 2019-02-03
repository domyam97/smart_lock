#include <ESP8266WiFi.h>

//Set device ID
#define DEVICE_ID 0x01U

const char* lockSSID = "Caps Lock";
const char* ssid = "Pixel";
const char* password = "pixelpixel";

//tracks if lid is open
boolean isOpen;
//flag for button interrupt
boolean isButton = false;

//setup pins
#define BUTTON_PIN 12
#define LED_PIN 13 
#define MOTOR_PIN 14

const char* host; //Vlad's phone server





void setup() {
  // put your setup code here, to run once:
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  //setup button input
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onPress, CHANGE);
  
  //setup motor output
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

}

void onPress(){
  if(digitalRead(BUTTON_PIN))
  {
    isButton = true; 
    delay(20);
  }
}

void loop() {
  /*check if button was pressed
   * request unlock
   * if unlock approved drive motor + light LED
   */
   if(isButton)
   {
    analogWrite(LED_PIN, 150);
   }

}
