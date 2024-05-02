//Project Week 4 Code
//Written by RB2521
//For any queries or further information, please visit the github repository at 
//or email me at rb2521@bath.ac.uk and I will reply as quickly as possible!

//The following code is for use in the University of Bath, Dept. EEE, Year 1 project week 4: Modular Display Project
//Please see the read.me file on the git hub repo for a full list of components needed to run this code
//This code is in mind for the Arduino Nano ESP32. Bigger boards will have more pins and the code will not work for any other board due to the nature of the speificially manufactured PCB


//including the libraries needed to make this project work
#include <WiFi.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <Arduino_JSON.h>

//infomration for the Arduino board to connect with the UoB-IoT. Make sure to change "PASSWORD HERE" to your unique password!!
const char* ssid = "UoB-IoT";
const char* pass = "PASSWORD HERE";

//URLs to the locations used
const char* locationBath = "https://api.openweathermap.org/data/2.5/weather?lat=51.37932&lon=-2.32716&appid=b4a34f9df227f68bce84bf8ce44daef1";
const char* locationPerth = "https://api.openweathermap.org/data/2.5/weather?lat=-31.9514&lon=115.8617&appid=b4a34f9df227f68bce84bf8ce44daef1";

//Setting up pre-determined variables
int buttonState = LOW;
int lastButtonState = LOW;
unsigned long lastDebounce = 0;
unsigned long debounceDelay = 150;
int clickCount = 0;


//Setup code with all setup function such as connecting to the WiFi and starting the Serial Monitor
void setup() {
  //Setting the PinModes to be Outputs and the Button pin to be an input pin
  pinMode(8, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(D13, INPUT_PULLUP);

  //Ensuring all LEDs are off on startup
  digitalWrite(8, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A0, LOW);

  //Beginning the Serial Monitor
  Serial.begin(115200);

  //Beginning the connection to the WiFi
  WiFi.begin(ssid, pass);
  
  //if the Board cannot connect to the WiFi continue to run this:
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.println("Failed Connection to WiFi");
  }

  //If the board is connected to WiFi, continue
  Serial.println("");
  Serial.println("Wifi Connected");

}

//JSON function used to get all information from the JSON files stored as HTTPS.
void getJSON(const char* url) {
  //Turning all of the LEDs off
  digitalWrite(8, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A0, LOW);

  //Double check that the board is connected to WiFi
  if (WiFi.status() == WL_CONNECTED) {
    //Gathering the infomration from the JSON files using the HTTPClient livrary
    HTTPClient http;
    //changes based on the switch state
    http.begin(url);
    int httpCode = http.GET();
    
    if (httpCode > 0) {
      //Saves the JSON file as a string that can be used to gather infomration from
      String payload = http.getString();
      JSONVar myObject = JSON.parse(payload);
      //Save only the relevant information that we can use to compare against
      const char* main = myObject["weather"] [0] ["main"];
      const char* description = myObject["weather"] [0] ["description"];
      Serial.println(main);

      //Comparitive statements used to control the LEDs based on the weather.
      if (strcmp (main, "Clear") == 0) {
        digitalWrite(D8, HIGH);
      }
      else if (strcmp (main, "Clouds") == 0) {
        if (strcmp (description, "few clouds") == 0) {
          digitalWrite(A2, HIGH);
          digitalWrite(8, HIGH);
        }
        else {
          digitalWrite(A2, HIGH);
        }
      }
      else if (strcmp (main, "Rain") == 0) {
        if (strcmp (description, "shower rain") == 0) {
          digitalWrite(8, HIGH);
          digitalWrite(A2, HIGH);
          digitalWrite(A0, HIGH);
        }
        else if(strcmp (description, "heavy intensity rain") == 0){
          digitalWrite(A2, HIGH);
          digitalWrite(A1, HIGH);
          digitalWrite(A0, HIGH);
        }
        else{
          digitalWrite(A2, HIGH);
          digitalWrite(A0, HIGH);
        }
      }
      else if(strcmp (main, "Mist") == 0){
        digitalWrite(A1, HIGH);
      }
      else if(strcmp (main, "Haze") == 0){
        digitalWrite(A1, HIGH);
        digitalWrite(8, HIGH);
      }

      else{
        digitalWrite(8, LOW);
        digitalWrite(A1, LOW);
        digitalWrite(A2, LOW);
        digitalWrite(A0, LOW);
      }
      //Close the connection to the HTTP
      http.end();
    }
    //If no connection can be found to the destination
    else{
      Serial.println("Error on HTTP request");
    }
  }
  //Error connecting to the WiFi
  else{
    Serial.println("WiFi connection issue");
  }
}

//Main code loop
void loop() {
  //Get the state of the Button
  int buttRead = digitalRead(D13);

  //If the button can be pressed
  if (buttRead != lastButtonState) {
    //time since last press
    lastDebounce = millis();
  }

  //If the button is not being spam pressed
  if ((millis() - lastDebounce) > debounceDelay) {
    if (buttRead != buttonState) {
      buttonState = buttRead;
      if (buttonState == LOW){
        clickCount++;
        //Start a swtich/case function increasing the clickCount with each press
        switch (clickCount){
          //Cycles through all LEDs
          case 1:
            digitalWrite(8, HIGH);
            delay(100);
            digitalWrite(A2, HIGH);
            delay(100);
            digitalWrite(A1, HIGH);
            delay(100);
            digitalWrite(A0, HIGH);
            delay(100);

            digitalWrite(8, LOW);
            delay(100);
            digitalWrite(A2, LOW);
            delay(100);
            digitalWrite(A1, LOW);
            delay(100);
            digitalWrite(A0, LOW);
            delay(100);
            break;
          
          case 2:
          //calls the JSON function with the Bath location
            getJSON(locationBath);
            break;

          case 3:
          //calls the JSON function with the Perth location
            getJSON(locationPerth);
            break;
        }
        //Loop the click count to allow for cycling of all cases
        if (clickCount > 2) {
          clickCount = 0;
        }
        lastDebounce = millis();
      }
    }
  }
  //sets the button state to low or high
  lastButtonState = buttRead;
}
