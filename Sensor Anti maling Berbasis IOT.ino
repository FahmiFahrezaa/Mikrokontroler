// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID           "TMPL0-XiF-ap"
#define BLYNK_DEVICE_NAME           "Sensor PIR"
#define BLYNK_AUTH_TOKEN            "MJpFvFLnxtcWBeJ2SEP_y0Gmkbf-Jg6C"

//include library CTBot
#include "CTBot.h";
//variable for bot telegram
CTBot myBot;
//konfiguration wifi connection


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
  char ssid[] = "Wokwi-GUEST";
  char pass[] = "";


const byte MOTION_SENSOR_PIN = 12  ; // pin ESP32 terkoneksi dengan pin D12 sebagai output dari pin sensor
const byte BUZZER_PIN        = 18  ; // pin ESP32 terkoneksi dengan pin Buzzer
const byte ECHO              = 25  ; // pin ESP32 terkoneksi dengan HC-SR04
const byte TRIG              = 26  ; // pin ESP32 terkoneksi dengan HC-SR04
const byte LED               = 19  ; // pin ESP43 terkoneksi dengan LED

//Buzzer
int freqB = 900;
int chan1B  = 0;
int resoB   = 8;
int dutyCycleB  = 128;

//Ultrasonic Sensor
float waktu, jarak; 

String token = "5933373005:AAG77Vd5EOZ1DYloS7GBOXA29k6-lvRE5_M";
const int id =  5977573249;


void setup(){
  
  myBot.setTelegramToken(token);

  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  while(WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.println(".");
  }
  Serial.println("WiFi.Connected!");
  Serial.println(WiFi.localIP());

 
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  pinMode(MOTION_SENSOR_PIN, INPUT); // masukkan PIR menjadi pin input
  pinMode(ECHO, INPUT); // masukkan pin HC-SR05 menjadi pin input
  pinMode(TRIG, OUTPUT); 
  pinMode(LED, OUTPUT) ;
  pinMode(BUZZER_PIN, OUTPUT) ; // masukan buzzer menjadi pin output

  ledcSetup(chan1B, freqB, resoB);
  ledcAttachPin(BUZZER_PIN, chan1B);

}

void loop(){
  TBMessage msg;
 if (myBot.getNewMessage(msg))
{

//variabel penampung isi pesan
String pesan = msg.text;
Serial.println("Pesan Masuk : " + pesan);
Serial.println("Kirim Balasan :" + pesan);
if (pesan == "Hello")
{
  //kirim pesan balasan
  myBot.sendMessage(msg.sender.id, "Hello, Aventura");
}
else {
  //kirim pesan balasan
  myBot.sendMessage(msg.sender.id, "Say Hello");
  }
}
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
   digitalWrite(MOTION_SENSOR_PIN, HIGH); // membaca sensor PIR
  delayMicroseconds(100); //waktu delay
  digitalWrite(MOTION_SENSOR_PIN, LOW);

  waktu = pulseIn(MOTION_SENSOR_PIN, HIGH);
  jarak = 0.017 * waktu;

  int pinSensor = digitalRead(MOTION_SENSOR_PIN);

 if(pinSensor == 1) {
     Serial.println("THE MOTION IS DETECTED");
     ledcWrite(chan1B, dutyCycleB);
     //kirim pesan balasan
  myBot.sendMessage(msg.sender.id, "DANGER!!!");
     digitalWrite(LED, HIGH);
     
     }
 

else {
  Serial.println(" NO MOTION ");
  //kirim pesan balasan
  myBot.sendMessage(msg.sender.id, "NO MOTION");
     ledcWrite(chan1B, 0);
    (jarak = 0 );
     digitalWrite(LED, LOW);
     
}
}

