#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#define S0 10
#define S1 11
#define S2 12
#define S3 13
#define sensorOut 6

const int motorPin1 = 2;
const int motorPin2 = 3;
const int motorPin3 = 4;
const int motorPin4 = 5;
int bekleme = 2;



Servo bottomServo;
LiquidCrystal_I2C lcd(0x3F, 20, 4);
int color = 0;
int frequency = 0;
int col[6] = {0, 0, 0, 0, 0, 0}; //0 mavi 1 kaverengi 2 sarı 3 yeşil 4turuncu 5 kırmızı

void adim1() {
digitalWrite(motorPin1, HIGH);
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin3, LOW);
digitalWrite(motorPin4, LOW);
delay(bekleme);
}

void adim2() {
digitalWrite(motorPin1, LOW);
digitalWrite(motorPin2, HIGH);
digitalWrite(motorPin3, LOW);
digitalWrite(motorPin4, LOW);
delay(bekleme);
}

void adim3() {
digitalWrite(motorPin1, LOW);
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin3, HIGH);
digitalWrite(motorPin4, LOW);
delay(bekleme);
}

void adim4() {
digitalWrite(motorPin1, LOW);
digitalWrite(motorPin2, LOW);
digitalWrite(motorPin3, LOW);
digitalWrite(motorPin4, HIGH);
delay(bekleme);
}


void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(motorPin1, OUTPUT);
pinMode(motorPin2, OUTPUT);
pinMode(motorPin3, OUTPUT);
pinMode(motorPin4, OUTPUT);
  
  bottomServo.attach(9);
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

}

void loop() {

for (int i = 0; i <64 ; i++)// step motorun adım sayısı < sağındaki sayıyı değiştirin
{
adim1();
adim2();
adim3();
adim4();
}


 
  
 
  


  
  delay(500);
  color = readColor();
  delay(20);
  


  switch (color) {
 /*   case 1: //RED
      bottomServo.write(50);
      col[5]++;
      break;*
    case 2: //orange
      bottomServo.write(75);
      col[4]++;
      break;*/
    case 3: //green
      bottomServo.write(45);
      col[3]++;
      break;
    case 4: //red
      bottomServo.write(90);
      col[2]++;
      break;
    case 5: //brown
      bottomServo.write(135);
      col[1]++;
      break;
    case 6:
      bottomServo.write(180);
      col[0]++;
      break;
    case 0:
      break;
  }
  delay(300);
 
  color = 0;
  lcd.clear();
  lcdPrint(col[0], col[1], col[2], col[3], col[4], col[5]);
  delay(1000);
 /* for (int i = 0; i < 412; i++)
{
adim1();
adim2();
adim3();
adim4();
}
*/

}

void lcdPrint(int a, int b, int c, int d, int e, int f) {
  lcd.setCursor(0, 0);
  lcd.print("M:");
  lcd.setCursor(2, 0);
  lcd.print(a);
  lcd.setCursor(5, 0);
  lcd.print("Ka:");
  lcd.setCursor(8, 0);
  lcd.print(b);
  lcd.setCursor(11, 0);
  lcd.print("K:");
  lcd.setCursor(13, 0);
  lcd.print(c);
  lcd.setCursor(0, 2);
  lcd.print("Y:");
  lcd.setCursor(2, 2);
  lcd.print(d);
  lcd.setCursor(5, 2);
  /*lcd.print("T:");
  lcd.setCursor(7, 2);
  lcd.print(e);
  lcd.setCursor(10, 2);*/
 /* lcd.print("P:");
  lcd.setCursor(12, 2);
  lcd.print(f);
*/
}
int readColor() {
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(50);
 /* if (R<80 & R>45 & G<120 & G>70) {
    color = 1; // PINK
  }*/
 /* if (G<135 & G>110 & B<165 & B>130) {
    color = 2; // Orange
  }*/
  if (R<60 & R>50 & G<60 & G>50) {
    color = 3; // Green 
  }
  if (R<55 & R>40 & G<86 & G>70 ) {
    color = 4; // Red 
  }
  if (R<70 & R>50 & G<90 & G>60  ) {
    color = 5; // Brown 
  }
  if (G<75 & G>60 & B<55 & B>40) {
    color = 6; // Blue 
  }
  return color;
}
