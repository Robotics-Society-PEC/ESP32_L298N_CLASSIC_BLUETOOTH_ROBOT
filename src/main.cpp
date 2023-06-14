/*
*Robotics Pec
*robotics@pec.edu.in
*
*                    GNU GENERAL PUBLIC LICENSE
*                       Version 3, 29 June 2007
*
*Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
*Everyone is permitted to copy and distribute verbatim copies
*of this license document, but changing it is not allowed.
*
*The GNU General Public License is a free, copyleft license for
*software and other kinds of works.
*
*THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY
*APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT
*HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY
*OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,
*THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
*PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM
*IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF
*ALL NECESSARY SERVICING, REPAIR OR CORRECTION.
*/

#include <Arduino.h>
#include <BluetoothSerial.h>
BluetoothSerial SerialBT;

const int freq = 20000;
#define motor1Channel 0
#define motor2Channel 1
const int resolution = 8;

#define motor1E 26
#define motor1A 33
#define motor1B 25
#define motor2A 32
#define motor2B 14 
#define motor2E 27

char temp;
byte speed = 255;
bool stop_mode = 0; // 0 is immediate stop



void setup() {
  //Serial.begin(115200);
  SerialBT.begin("Avalanche Acers 200"); //Bluetooth device name
  //Serial.println("The device started, now you can pair it with bluetooth!");

  pinMode(motor1A,OUTPUT);
  pinMode(motor1B,OUTPUT);
  pinMode(motor2A,OUTPUT);
  pinMode(motor2B,OUTPUT);


  temp = 'S';
  ledcSetup(motor1Channel, freq, resolution);
  ledcSetup(motor2Channel, freq, resolution);
  ledcAttachPin(motor1E, motor1Channel);
  ledcAttachPin(motor2E, motor2Channel);
  
}

void loop() {
if (!SerialBT.hasClient())
  {
      digitalWrite(motor1A,LOW);
      digitalWrite(motor1B,LOW);
      digitalWrite(motor2A,LOW);
      digitalWrite(motor2B,LOW);
  }

if (SerialBT.available()) {
    temp = SerialBT.read();

    switch(temp)
    {
      case 'F':
      ledcWrite(motor1Channel, speed);
      ledcWrite(motor2Channel, speed);
      digitalWrite(motor1A,HIGH);
      digitalWrite(motor1B,LOW);
      digitalWrite(motor2A,HIGH);
      digitalWrite(motor2B,LOW);
      break;

      case 'B':
      ledcWrite(motor1Channel, speed);
      ledcWrite(motor2Channel, speed);
      digitalWrite(motor1A,LOW);
      digitalWrite(motor1B,HIGH);
      digitalWrite(motor2A,LOW);
      digitalWrite(motor2B,HIGH);
      break;

      case 'L':
      ledcWrite(motor1Channel, speed);
      ledcWrite(motor2Channel, speed);
      digitalWrite(motor1A,LOW);
      digitalWrite(motor1B,HIGH);
      digitalWrite(motor2A,HIGH);
      digitalWrite(motor2B,LOW);
      break;

      case 'R':
      ledcWrite(motor1Channel, speed);
      ledcWrite(motor2Channel, speed);
      digitalWrite(motor1A,HIGH);
      digitalWrite(motor1B,LOW);
      digitalWrite(motor2A,LOW);
      digitalWrite(motor2B,HIGH);
      break;

      case 'G':
      if (stop_mode)
      {
        ledcWrite(motor1Channel, 0);
      }
      ledcWrite(motor2Channel, speed);
      digitalWrite(motor1A,LOW);
      digitalWrite(motor1B,LOW);
      digitalWrite(motor2A,HIGH);
      digitalWrite(motor2B,LOW);
      break;

      case 'I':
      ledcWrite(motor1Channel, speed);
      if (stop_mode)
      {
        ledcWrite(motor2Channel, 0);
      }
      digitalWrite(motor1A,HIGH);
      digitalWrite(motor1B,LOW);
      digitalWrite(motor2A,LOW);
      digitalWrite(motor2B,LOW);
      break;

      case 'H':
      if (stop_mode)
      {
        ledcWrite(motor1Channel, 0);
      }
      ledcWrite(motor2Channel, speed);
      digitalWrite(motor1A,LOW);
      digitalWrite(motor1B,LOW);
      digitalWrite(motor2A,LOW);
      digitalWrite(motor2B,HIGH);
      break;

      case 'J':
      if (stop_mode)
      {
        ledcWrite(motor2Channel, 0);
      }
      ledcWrite(motor1Channel, speed);
      digitalWrite(motor1A,LOW);
      digitalWrite(motor1B,HIGH);
      digitalWrite(motor2A,LOW);
      digitalWrite(motor2B,LOW);
      break;

      case 'S':
      if (stop_mode)
      {// non immediate stop mode
        ledcWrite(motor1Channel, 0);
        ledcWrite(motor2Channel, 0);
      }
      digitalWrite(motor1A,LOW);
      digitalWrite(motor1B,LOW);
      digitalWrite(motor2A,LOW);
      digitalWrite(motor2B,LOW);
      break;

      case '0':
      speed = (0.0/10)*255; 
      break;
      case '1':
      speed = (5.0/10)*255; 
      break;
      case '2':
      speed = (5.5/10)*255; 
      break;
      case '3':
      speed = (6.0/10)*255; 
      break;
      case '4':
      speed = (6.5/10)*255; 
      break;
      case '5':
      speed = (7.0/10)*255; 
      break;
      case '6':
      speed = (7.5/10)*255; 
      break;
      case '7':
      speed = (8.0/10)*255; 
      break;
      case '8':
      speed = (8.5/10)*255; 
      break;
      case '9':
      speed = (9.0/10)*255; 
      break;
      case 'q':
      speed = (10.0/10)*255; 
      break;

      case 'X':
      stop_mode = 1;
      break;
      case 'x':
      stop_mode = 0;
      break;
    }

    
    
  }
}
