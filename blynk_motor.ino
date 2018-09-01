
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define motor1 0
#define motor2 2
int ENA = 5;
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "845ffc43ba664658844ff20fa6196270";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "LOL";
char pass[] = "wunnahtun";




BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.

void setup()
{
  // Debug console
  Serial.begin(9600);
 pinMode(ENA, OUTPUT);
pinMode(motor1, OUTPUT);
pinMode(motor2, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);


}

BLYNK_WRITE(V8) // V5 is the number of Virtual Pin  
{
  int pinValue = param.asInt();
  Serial.println("button");
  
  Serial.println(pinValue);
  if(pinValue==1){
    Serial.println("on");
    digitalWrite(ENA, HIGH);  
    digitalWrite(motor1, LOW);  
    digitalWrite(motor2, HIGH);
    delay(1000);  
  }
  else if(pinValue==0){

    digitalWrite(ENA, LOW);  
    digitalWrite(motor1, LOW);  
    digitalWrite(motor2, LOW); 
  }
  
}

void loop()
{
  Blynk.run();
  timer.run();
}

