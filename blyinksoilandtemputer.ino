
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
int sense_Pin = 0;
float m=0;
// You should get Auth Token in the Blynk App.'jjp
// Go to the Project Settings (nut icon).
char auth[] = "845ffc43ba664658844ff20fa6196270";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "LOL";//"UIT-Student";
char pass[] = "wunnahtun";//"UIT5tudent$";

#define DHTPIN 2          // What digital pin we're connected to
#define motor1 0
#define motor2 2
int ENA = 5;
// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.

BLYNK_WRITE(V8) // V5 is the number of Virtual Pin  
{
  int pinValue = param.asInt();
  Serial.println("button");
  
  Serial.println(pinValue);
  if(pinValue==1){
    digitalWrite(ENA, HIGH);  
    digitalWrite(motor1, HIGH);  
    digitalWrite(motor2, LOW);  
    delay(1000);
  }
  else if(pinValue==0){

    digitalWrite(ENA, LOW);  
    digitalWrite(motor1, LOW);  
    digitalWrite(motor2, LOW); 
  }
  
}

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

     m= analogRead(sense_Pin);
     m= m/10;
  
   Serial.println(m);
  if (isnan(h) || isnan(t) ||isnan(m) ) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  Blynk.virtualWrite(V7, m);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(motor1,OUTPUT);
  pinMode(motor2,OUTPUT);
  pinMode(ENA,OUTPUT);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}

