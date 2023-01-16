#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int trigPin = 9; 
const int echoPin = 10;
const int buzzer = 8;
const int led = 7;
const int button = 6;
int tombol = 0;

LiquidCrystal_I2C lcd(0x27,16,2);

long duration;
int distance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Kecepatan pengiriman data 9600 bit per detik 
  pinMode(trigPin, OUTPUT); //Setting Trigger sebagai output 
  pinMode(echoPin, INPUT); //Setting Echo sebagai input 
  pinMode(buzzer, OUTPUT); //Setting Buzzer sebagai output 
  pinMode(led, OUTPUT); //Setting led sebagai output 
  pinMode(button, INPUT); //Setting button sebagai input 
  lcd.init(); //LCD mulai menyala 
  lcd.backlight(); //Settingan agar lampu belakang LCD menyala
  lcd.setCursor(0,0); //Posisi karakter akan ditampilkan dalam LCD
  lcd.print("Jarak Parkir"); //Karakter yang akan ditampilkan dalam LCD 
  lcd.setCursor(0,1); //Posisi karakter akan ditampilkan dalam LCD
  delay(5000); //Durasi waktu karakter tampil dalam LCD yaitu 5 detik 
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear(); //Hapus karakter di layar LCD 
  digitalWrite(trigPin, LOW); //Trigger off mengirimkan sinyal 
  delayMicroseconds(2); //Selang waktu 0.002 detik 
  digitalWrite(trigPin, HIGH); //Trigger on mengirimkan sinyal 
  delayMicroseconds(10); // Selang waktu 0.01 detik 
  digitalWrite(trigPin, LOW); //Trigger off mengirimkan sinyal  
  
  duration = pulseIn(echoPin, HIGH); //Waktu tempuh sinyal dari dikirim Trigger, memantul, sampai diterima Echo  
  distance = duration * 0.0343/2; //Jarak = (Waktu x Kecepatan)/2 

  lcd.setCursor(0,0);
  lcd.print("Jarak: ");
  lcd.print(distance); //Menampilkan hasil pengukuran jarak
  lcd.print(" cm");
  delay(1000); //Karakter tampil selama 1 detik 

  if(distance <=30){ //Jika jarak benda <= 30 cm 
    tombol = digitalRead(button); //Membaca kondisi nilai pin digital 1/0
    if(tombol == HIGH){ //Jika tombol aktif atau dalam keadaan 1 
      digitalWrite(led, LOW); //Lampu off
      noTone(buzzer); //Buzzer off
      delay(500); //Lampu & buzzer off selama 0.5 detik 
      digitalWrite(led, HIGH); //lampu on 
      tone(buzzer, 700); //Buzzer on, f= 0.7 KHz  
      delay(200); //Lampu & buzzer on selama 0.2 detik
    }
    if(tombol == LOW){ //Jika tombol dalam keadaan 0 
      digitalWrite(led, HIGH); //Lampu on 
      tone(buzzer, 500); //Buzzer on, f = 0.5 KHz  
    }
    lcd.setCursor(0,1); //Menampilkan posisi karakter yang akan ditampilkan dalam LCD
    lcd.print("Terlalu Dekat");delay(1000); //Karakter akan tampil pada LCD selama 1 detik 
  }
  if(distance >30){ //Jika jarak benda > 30 cm 
    digitalWrite(led, LOW); //Lampu off 
    noTone(buzzer); //Buzzer off 
  }
}