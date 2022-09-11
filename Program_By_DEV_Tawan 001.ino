#include <PS2X_lib.h>  // เรียกใช้งานไลบรารีสำหรับจอยสติ๊ก PS2
#include <Servo.h>

#define PS2_DAT 8   // กำหนดขา Data เป็นขา 8
#define PS2_CMD 9   // กำหนดขา Command เป็นขา 9
#define PS2_SEL 10  // กำหนดขา Select เป็นขา 10
#define PS2_CLK 11  // กำหนดขา Clock เป็นขา 11

Servo myservo;  // create servo object to control a servo
Servo myservo2;
Servo myservo3;
// Servo myservo4;

int trig = 15;            //ประกาศขา trig
int echo = 16;            //ประกาศขา echo
long duration, distance;  //ประกาศตัวแปรเก็บค่าระยะ

int enA = 3;  // PWM A
int in1 = 2;  //motorA
int in2 = 4;  //motorA
int enB = 5;  // PWM B
int in3 = 6;  //motor B
int in4 = 7;  //motor B

int val1 = 255;  //สปีด1
int val2 = 225;  //สปีด2
int Relay = 16;  //รีเลปั้ม
int old_incom = 0;
byte valservo1 = 120;
byte valservo2 = 100;
byte valservo3 = 100;
// byte valservo4 = 100;

PS2X ps2x;  // ประกาศตัวแปรสำหรับจอยสติ๊ก PS2

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(Relay, OUTPUT);
  pinMode(echo, INPUT);   //สั่งให้ขา echo ใช้งานเป็น input
  pinMode(trig, OUTPUT);  //สั่งให้ขา trig ใช้งานเป็น output

  delay(1000);  // หน่วงเวลา 1 วินาทีเพื่อรอให้บอร์ดพร้อมทำงาน
  Serial.begin(9600);
  Serial.print("Connecting");  // แสดงข้อความเพื่อแจ้งว่า กำลังเชื่อมต่อกับจอยสติ๊ก
                               //  display.println("Connecting");
  while (true)                 // วนรอการเชื่อมต่อกับจอยสติ๊ก
  {
    int error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, false, false);

    if (error == 0)  // กรณีที่เชื่อมต่อได้ Error = 0
    {
      Serial.println("OK");  // แสดงข้อความว่า เชื่อมต่อกับจอยสติ๊กเรียบร้อยแล้ว
                             // display.println("OK");
      delay(100);           // หน่วงเวลา 1 วินาที
      break;                 // ออกจาก while(true)
    }
    delay(50);  // หน่วงเวลา 500 มิลลิวินาทีเพื่อรอการเชื่อมต่อครั้งต่อไปในกรณีที่เชื่อมต่อไม่สำเร็จ
  }
  myservo.attach(12);   // กำหนด myservo ตัวยก-วาง ใช้ขา 13
  myservo2.attach(13);  // กำหนด myservo2 ตัวหนีบ-คลาย ใช้ขา 12
  myservo3.attach(14);
  // myservo4.attach(15);
  delay(300);
  myservo.write(valservo1);   // กำหนดตำแหน่งเริ่มต้น servo ตัวยก-วาง
  myservo2.write(valservo2);  // กำหนดตำแหน่งเริ่มต้น servo ตัวหนีบ-คลาย
  myservo3.write(valservo3);
  // myservo4.write(valservo4);
  delay(1000);
}
void foward1()  //หุ่นยนต์เดินหน้า
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, val2);  //ตั้งความเร็ว PWM ไว้ตามค่า val2
  analogWrite(enB, val2);  //ตั้งความเร็ว PWM ไว้ตามค่า val2
}

void back1() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, val2);  //ตั้งความเร็ว PWM ไว้ตามค่า val2
  analogWrite(enB, val2);  //ตั้งความเร็ว PWM ไว้ตามค่า val2
}

void turnLeft() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, val2);  //ตั้งความเร็ว PWM ไว้ตามค่า val2
  analogWrite(enB, val2);  //ตั้งความเร็ว PWM ไว้ตามค่า val2
}

void turnRight() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, val2);  //ตั้งความเร็ว PWM ไว้ตามค่า val2
  analogWrite(enB, val2);  //ตั้งความเร็ว PWM ไว้ตามค่า val2
}

void stopBot() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);  //ตั้งความเร็ว PWM ไว้ตามค่า val2
  analogWrite(enB, 0);  //ตั้งความเร็ว PWM ไว้ตามค่า val2
}

void motor() {
  delay(500);
  digitalWrite(Relay, HIGH);
}

void motorstop() {
  delay(500);
  digitalWrite(Relay, LOW);
  ;
}

void stopBotback1() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, val2);  //ตั้งความเร็ว PWM ไว้ตามค่า val2
  analogWrite(enB, val2);  //ตั้งความเร็ว PWM ไว้ตามค่า val2
}

//*****************************************************************
void servo1_up()  //ควบคุมการยกแขนขึ้น
{
  if (valservo1 > 25) {
    valservo1 = valservo1 - 5;  //ลดค่าครั้งละ 5
    myservo.write(valservo1);
    delay(10);
  }
  Serial.println(valservo1);
}

void servo1_down()  //ควบคุมการวางแขนลง
{
  if (valservo1 < 190) {
    valservo1 = valservo1 + 5;  //เพิ่มค่าครั้งละ 5
    myservo.write(valservo1);
    delay(10);
  }
  Serial.println(valservo1);
}

//*****************************************************************
void servo2_out()  //ควบคุมการลายออก
{
  if (valservo2 < 190) {
    valservo2 = valservo2 + 5;
    myservo2.write(valservo2);
    delay(15);
  }
  Serial.println(valservo2);
}

void servo2_in()  //ควบคุมการหนีบเข้า
{
  if (valservo2 > 15) {
    valservo2 = valservo2 - 5;
    myservo2.write(valservo2);
    delay(15);
  }
  Serial.println(valservo2);
}

//*****************************************************************
void servo3_pull()  //ควบคุมการลายออก
{
  if (valservo3 < 45) {
    valservo3 = valservo3 + 5;
    myservo3.write(valservo3);
    delay(15);
  }
  Serial.println(valservo3);
}

void servo3_release()  //ควบคุมการหนีบเข้า
{
  if (valservo3 > 180) {
    valservo3 = valservo3 - 5;
    myservo3.write(valservo3);
    delay(15);
  }
  Serial.println(valservo3);
}

// //*****************************************************************
// void servo4_left () //ควบคุมการลายออก
// {
//   if(valservo4 < 25)
// {
//   valservo4 = valservo4+5;
//    myservo4.write(valservo4);
//     delay(15);
// }
//   Serial.println(valservo4);
// }

// void servo4_right () //ควบคุมการหนีบเข้า
// {
//   if(valservo4 > 190)
// {
//   valservo4 = valservo4-5;
//    myservo4.write(valservo4);
//     delay(15 );
// }
//   Serial.println(valservo4);
// }

//***********************************************************************************

void loop() {

  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);          //ใช้งานขา trig
  duration = pulseIn(echo, HIGH);   //อ่านค่าของ echo
  distance = duration * 0.034 / 2;  //คำนวณเป็น centimeters



  ps2x.read_gamepad(false, false);  // อ่านข้อมูลจาก PS2 Controller
  if (ps2x.Button(PSB_L1))          // ถ้าปุ่ม L1 ถูกกด
  {
    Serial.println("L1");  // แสดงข้อความว่า L1
    servo1_up();
    //  display.println("Servo1 up");
  } else if (ps2x.Button(PSB_L2))  // ถ้าปุ่ม L2 ถูกกด
  {
    Serial.println("L2");  // แสดงข้อความว่า L2
    servo1_down();
    //  display.println("Servo1 down");
  }
  //##################################################################
  else if (ps2x.Button(PSB_CIRCLE))  // ถ้าปุ่ม R1 ถูกกด
  {
    Serial.println("CIRCLE");
    servo2_in();
    //  display.println("Servo2 up");
  } else if (ps2x.Button(PSB_SQUARE))  // ถ้าปุ่ม R2 ถูกกด
  {
    Serial.println("SQUARE");
    servo2_out();
    //  display.println("Servo2 down");
  }
  //##################################################################
  else if (ps2x.Button(PSB_R1))  // ถ้าปุ่ม L3 ถูกกด
  {
    Serial.println("R1");
    servo3_pull();
    //  display.println("Servo3 up");
  } else if (ps2x.Button(PSB_R2))  // ถ้าปุ่ม R3 ถูกกด
  {
    Serial.println("R2");
    servo3_release();
    //  display.println("Servo3 down");
  }
  //##################################################################
  else if (ps2x.Button(PSB_TRIANGLE))  // ถ้าปุ่ม Start ถูกกด
  {
    Serial.println("TRIANGLE");
    motor();
    //  display.println("motor high");
  } else if (ps2x.Button(PSB_CROSS))  // ถ้าปุ่ม Start ถูกกด
  {
    Serial.println("CROSS");
    motorstop();
    //  display.println("motor stop");
  }
  //##################################################################
  else if (ps2x.Button(PSB_START))  // ถ้าปุ่ม Start ถูกกด
  {
    Serial.println("Start");
    val2 = 255;  // เปลี่ยนค่า val2 ให้เท่ากับ 255
    // display.println("speed 100");
  }
  //##################################################################
  else if (ps2x.Button(PSB_SELECT))  // ถ้าปุ่ม Select ถูกกด
  {
    Serial.println("Select");
    val2 = 60;  // เปลี่ยนค่า val2 ให้เท่ากับ 150
                // display.println("speed 20");
  }
  //##################################################################
  else if (ps2x.Button(PSB_PAD_UP))  // ถ้าปุ่ม Up ถูกกด
  {
    Serial.println("Up");  // แสดงข้อความว่า Up
    if (old_incom != 1) {
      foward1();  //กระโดดไปทำงานฟังก์ชั่น forward1()
      // display.println("foward");
    }
    old_incom = 1;

  }
  //##################################################################

  else if (ps2x.Button(PSB_PAD_DOWN))  // ถ้าปุ่ม Down ถูกกด
  {
    Serial.println("Down");  // แสดงข้อความว่า Up
    if (old_incom != 2) {
      back1();  //กระโดดไปทำงานฟังก์ชั่น back1()
                //  display.println("back1");
    }
    old_incom = 2;
  }
  //##################################################################

  else if (ps2x.Button(PSB_PAD_LEFT))  // ถ้าปุ่ม Left ถูกกด
  {
    Serial.println("Left");  // แสดงข้อความว่า Up
    if (old_incom != 3) {
      turnLeft();  //กระโดดไปทำงานฟังก์ชั่น turnLeft ()
                   //  display.println("Left");
    }
    old_incom = 3;
  }
  //##################################################################

  else if (ps2x.Button(PSB_PAD_RIGHT))  // ถ้าปุ่ม Right ถูกกด
  {
    Serial.println("Right");  // แสดงข้อความว่า Up
    if (old_incom != 4) {
      turnRight();  //กระโดดไปทำงานฟังก์ชั่น turnRight ()
                    //  display.println("Right");
    }
    old_incom = 4;
  }
  //##################################################################

  //    else if(ps2x.ButtonPressed(PSB_TRIANGLE)) // ถ้าปุ่ม Triangle ถูกกด
  //{
  //Serial.println("Triangle"); // แสดงข้อความว่า Triangle
  //        valservo1 = 100; //ให้ valservo1=100
  //        myservo.write(valservo1);
  //         delay(200);
  //}
  //##################################################################
  else if (distance <= 20) {  //ระยะการใช้งาน
    // display.println("Botback");
    stopBotback1();
    delay(500);
  }
  //##################################################################
  else  //ถ้าไม่ใช่ทุกกรณี
  {
    stopBot();  //กระโดดไปทำงานฟังก์ชั่น stopBot ()
    old_incom = 0;
    delay(10);  // หน่วงเวลา 50 มิลลิวินาที
  }

  delay(10);
}
//##################################################################