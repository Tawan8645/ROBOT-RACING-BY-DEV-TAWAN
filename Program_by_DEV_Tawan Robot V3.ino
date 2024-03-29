//###############################Program_by_DEV_Tawan ROBOT V3###################################//


#include <PS2X_lib.h>  //for v1.6
#include <Servo.h>
// create PS2 Controller Class
PS2X ps2x;
int error = 0;
byte type = 0;
byte vibrate = 0;

Servo myservo1;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;


int enA = 2;                                               // PWM A
int in1 = 3;                                               //motorA
int in2 = 4;                                               //motorA
int enB = 5;                                               // PWM B
int in3 = 6;                                               //motor B
int in4 = 7;                                               //motor B
int val1 = 255;                                            //สปีด1
int val2 = 60;                                             //สปีด2
int Relay = 8;                                             //รีเลปั้ม
int degree1, degree2, degree3, degree4, degree5, degree6;  //ตัวแปรองศา

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(Relay, OUTPUT);


  Serial.begin(9600);
  Serial.println("Connecting load");  // แสดงข้อความเพื่อแจ้งว่า กำลังเชื่อมต่อกับจอยสติ๊ก

  error = ps2x.config_gamepad(A0, A1, A2, A3, true, true);  //clock, command, attention, data,

  if (error == 0) {
    Serial.print("Found Controller,");
  } 
  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.print("Unknown Controller type");
      break;
    case 1:
      Serial.print("DualShock Controller Found");
      break;
    case 2:
      Serial.print("Controller Found");
      break;
  }
  myservo1.attach(9);   // กำหนด myservo ตัวยก-วาง ใช้ขา 13
  myservo2.attach(10);  // กำหนด myservo2 ตัวหนีบ-คลาย ใช้ขา 12
  myservo3.attach(11);
  myservo4.attach(12);
  myservo5.attach(13);
  myservo6.attach(14);

  myservo1.write(0);  // กำหนดตำแหน่งเริ่มต้น servo ตัวยก-วาง
  myservo2.write(0);  // กำหนดตำแหน่งเริ่มต้น servo ตัวหนีบ-คลาย
  myservo3.write(0);
  myservo4.write(0);
  myservo5.write(0);
  myservo6.write(0);
}
//***********************************************************************************

void foward1()  //หุ่นยนต์เดินหน้า
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, val2);  //ตั้งความเร็ว PWM ไว้ตามค่า val2
  analogWrite(enB, val2);  //ตั้งความเร็ว PWM ไว้ตามค่า val2
}
//***********************************************************************************

void back1() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, val2);  //ตั้งความเร็ว PWM ไว้ตามค่า val2
  analogWrite(enB, val2);  //ตั้งความเร็ว PWM ไว้ตามค่า val2
}
//***********************************************************************************

void turnLeft() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, val2);  //ตั้งความเร็ว PWM ไว้ตามค่า val2
  analogWrite(enB, val2);  //ตั้งความเร็ว PWM ไว้ตามค่า val2
}
//***********************************************************************************

void turnRight() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, val2);  //ตั้งความเร็ว PWM ไว้ตามค่า val2
  analogWrite(enB, val2);  //ตั้งความเร็ว PWM ไว้ตามค่า val2
}
//***********************************************************************************

void stopBot() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);  //ตั้งความเร็ว PWM ไว้ตามค่า val2
  analogWrite(enB, 0);  //ตั้งความเร็ว PWM ไว้ตามค่า val2
}
//***********************************************************************************

void motor() {
  delay(500);
  digitalWrite(Relay, LOW);
}
//***********************************************************************************

void motorstop() {
  delay(500);
  digitalWrite(Relay, HIGH);
}
//***********************************************************************************
void loop() {

  myservo1.write(degree1);  //ตามที่เราตั้ง
  myservo2.write(degree2);  //ตามที่เราตั้ง
  myservo3.write(degree3);  //ตามที่เราตั้ง
  myservo4.write(degree4);  //ตามที่เราตั้ง
  myservo5.write(degree5);  //ตามที่เราตั้ง
  myservo6.write(degree6);  //ตามที่เราตั้ง

  Serial.println("Connecting OK");
  ps2x.read_gamepad();

  if (ps2x.Analog(PSS_RY) < 30) {
    Serial.println("Start speed 100");
    val2 = 255;  // เปลี่ยนค่า val2 ให้เท่ากับ 255
  } else if (ps2x.Analog(PSS_RY) < 235) {
    Serial.println("Select speed 40");
    val2 = 160;  // เปลี่ยนค่า val2 ให้เท่ากับ 150
  }
  if (ps2x.Analog(PSS_LY) < 20) {
    Serial.println("Up");  // แสดงข้อความว่า Up
    foward1();             //กระโดดไปทำงานฟังก์ชั่น forward1()
  } else if (ps2x.Analog(PSS_LY) < 235) {
    Serial.println("Down");  // แสดงข้อความว่า Down
    back1();                 //กระโดดไปทำงานฟังก์ชั่น back1()
  } else if (ps2x.Analog(PSS_LX) < 20) {
    Serial.println("Left");  // แสดงข้อความว่า Left
    turnLeft();              //กระโดดไปทำงานฟังก์ชั่น turnLeft ()
  } else if (ps2x.Analog(PSS_LX) < 235) {
    Serial.println("Right");  // แสดงข้อความว่า Right
    turnRight();              //กระโดดไปทำงานฟังก์ชั่น turnRight ()
  }

  else if (ps2x.Button(PSB_L1)) {
    Serial.println("L1");  // แสดงข้อความว่า L1
    if (degree1 < 180) {
      degree1 += 2;
    }
  } else if (ps2x.Button(PSB_L2)) {
    Serial.println("L2");  // แสดงข้อความว่า L2
    if (degree1 > 0) {
      degree1 -= 2;
    }
  } else if (ps2x.Button(PSB_R1)) {
    Serial.println("R1");
    if (degree2 < 180) {
      degree2 += 2;
    }
  } else if (ps2x.Button(PSB_R2)) {
    Serial.println("R2");
    if (degree2 > 0) {
      degree2 -= 2;
    }
  } else if (ps2x.Button(PSB_L3)) {
    Serial.println("L3");
    motor();
  } else if (ps2x.Button(PSB_R3)) {
    Serial.println("R3");
    motorstop();
  } else if (ps2x.Button(PSB_GREEN)) {
    Serial.println("GREEN");  // แสดงข้อความว่า L1
    if (degree3 < 180) {
      degree3 += 2;
    }
  } else if (ps2x.Button(PSB_BLUE)) {
    Serial.println("BLUE");  // แสดงข้อความว่า L2
    if (degree3 > 0) {
      degree3 -= 2;
    }
  } else if (ps2x.Button(PSB_PINK)) {
    Serial.println("PINK");
    if (degree4 < 180) {
      degree4 += 2;
    }
  } else if (ps2x.Button(PSB_RED)) {
    Serial.println("RED");
    if (degree4 > 0) {
      degree4 -= 2;
    }
  } else if (ps2x.Button(PSB_PAD_UP)) {
    Serial.println("UP");
    if (degree5 < 180) {
      degree5 += 2;
    }
  } else if (ps2x.Button(PSB_PAD_DOWN)) {
    Serial.println("DOWN");
    if (degree5 > 0) {
      degree5 -= 2;
    }
  } else if (ps2x.Button(PSB_PAD_LEFT)) {
    Serial.println("LEFT");
    if (degree6 < 180) {
      degree6 += 2;
    }
  } else if (ps2x.Button(PSB_PAD_RIGHT)) {
    Serial.println("RIGHT");
    if (degree6 > 0) {
      degree6 -= 2;
    }
  } else {
    stopBot();  //กระโดดไปทำงานฟังก์ชั่น stopBot ()
  }
  delay(10);
}