//Project Week 4 Code
//Written by RB2521
//For any queries or further information, please visit the github repository at 
//or email me at rb2521@bath.ac.uk and I will reply as quickly as possible!

//The following code is for use in the University of Bath, Dept. EEE, Year 1 project week 4: Modular Display Project
//Please see the read.me file on the git hub repo for a full list of components needed to run this code
//This code is in mind for the Arduino Nano ESP32. Bigger boards will have more pins and the code will not work for any other board due to the nature of the speificially manufactured PCB

void setup() {
  //Put your setup code here, to run once:
  //Configures all pins to be output since Analouge pins can also take inputs 
  pinMode(8, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A0, OUTPUT);
  //Begin the Serial Monitor to allow for outputs to be printed to it
  Serial.begin(9600);
}

void loop() {
  //Put your main code here, to run repeatedly:
  //Ensure all LEDs are "OFF" ie "LOW" before begining the cycle
  digitalWrite(8, LOW);
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  //begin a loop to ensure the cycle happens constantly
  while(true){
    //Prints to the console and sets the LED cycle ON and OFF. This is the case for all combinations listed
    //The delay is used to ensure that the LEDs do not cycle too quickly, rendering them impossible to see/read for the user
    Serial.println("Sunny");
    digitalWrite(8,HIGH);
    delay(2500);
    digitalWrite(8, LOW);
    delay(500);

    Serial.println("Cloudy");
    digitalWrite(A2, HIGH);
    delay(2500);
    digitalWrite(A2, LOW);
    delay(500);

    Serial.println("Windy");
    digitalWrite(A1, HIGH);
    delay(2500);
    digitalWrite(A1, LOW);
    delay(500);

    Serial.println("Rainy");
    digitalWrite(A2, HIGH);
    digitalWrite(A0, HIGH);
    delay(2500);
    digitalWrite(A2, LOW);
    digitalWrite(A0, LOW);
    delay(500);

    Serial.println("Cloudy with Sunny spells");
    digitalWrite(8, HIGH);
    digitalWrite(A2, HIGH);
    delay(2500);
    digitalWrite(8, LOW);
    digitalWrite(A2, LOW);
    delay(500);

    Serial.println("Rainy with Sunny spells");
    digitalWrite(8, HIGH);
    digitalWrite(A2, HIGH);
    digitalWrite(A0, HIGH);
    delay(2500);
    digitalWrite(8, LOW);
    digitalWrite(A2, LOW);
    digitalWrite(A0, LOW);
    delay(500);

    Serial.println("Sunny with Winds");
    digitalWrite(8, HIGH);
    digitalWrite(A1, HIGH);
    delay(2500);
    digitalWrite(8, LOW);
    digitalWrite(A1, LOW);
    delay(500);

    Serial.println("Raining with Winds");
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
    digitalWrite(A0, HIGH);
    delay(2500);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);
    digitalWrite(A0, LOW);
    delay(500);



  }
}
