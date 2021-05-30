#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h> 
#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"

//SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;



SoftwareSerial BT(7, 8); //TX, RX respetively



unsigned long start_time; // Δημιούργησε μια μεταβλητή τύπου unsigned long integer με όνομα start_time

//ultrasonicservo
#include "AlphaBot.h"

int ECHO = 12;
int TRIG = 11;
char inByte=0;
int FrontDistance = 0;
int LeftDistance = 0;
int RightDistance = 0;

int ServoPin = 9;                            //Set the SG90 servo drive pin to digital port 9  ()
int myangle;                                 //Defines the angle variable
int pulsewidth;                              //Defines the pulse width variable
int val;

AlphaBot Car1 = AlphaBot();

void UltrasonicConfig()
{
  pinMode(ECHO, INPUT);                      // Define the ultrasonic echo input pin
  pinMode(TRIG, OUTPUT);                     // Define the ultrasonic trigger input pin
}

void ServoConfig()
{
  pinMode(ServoPin,OUTPUT);                  //Set the servo output interface
}

float DistanceTest()                         // Measure the distance  
{
  digitalWrite(TRIG, LOW);                   // set trig pin low 2μs
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);                  // set trig pin 10μs , at last 10us 
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);                   // set trig pin low
  float Fdistance = pulseIn(ECHO, HIGH);     // Read echo pin high level time(us)
  Fdistance= Fdistance / 58;        
  //Y m=（X s*344）/2
  //X s=（ 2*Y m）/344 
  //X s=0.0058*Y m 
  //cm = us /58
  
  //Serial.print("Fdistance:");               //output distance (Unit: cm)
 // Serial.println(Fdistance);
  return Fdistance;
}  

void DistanceDisplay(int Distance)          //display distance
{
  if((2<Distance)&(Distance<400))           //Ultrasonic range ranging 2cm to 400cm
  {
   // Serial.print("Distance:");             //print distance
   // Serial.print(Distance);      
  //  Serial.print("cm\n\n");        
  }
  else
  {
    //Serial.print("!!! Out of range\n");      
  }
  delay(250);
}

void ServoPulse(int ServoPin,int myangle)    /*Defines an impulse function that is used to simulate PWM generation*/
{
  pulsewidth=(myangle*11)+500;              //The angle is converted to a pulse width value of 500-2480
  digitalWrite(ServoPin,HIGH);              //Set the servo Pin level high
  delayMicroseconds(pulsewidth);            //delay the pulse width value
  digitalWrite(ServoPin,LOW);               //Set the servo Pin level low
  delay(20-pulsewidth/1000);                //delay the remaining time of period
}

void FrontDetection()
{
  //Here the number of cycles decreased, in order to increase the speed of the car encounter obstacles
  for(int i=0;i<=5;i++)                     //The number of PWM,the equivalent delay to ensure that can go to the response angle
  {
    ServoPulse(ServoPin,90);                //analog out PWM
  }
  FrontDistance = DistanceTest();
  //Serial.print("FrontDistance:");     
  // Serial.println(FrontDistance);        
  //DistanceDisplay(FrontDistance);
}

void LeftDetection()
{
  for(int i=0;i<=15;i++)                   //The number of PWM,the equivalent delay to ensure that can go to the response angle
  {
    ServoPulse(ServoPin,140);              //analog out PWM
  }
  LeftDistance = DistanceTest();
  //Serial.print("LeftDistance:");      
  //Serial.println(LeftDistance);         
}

void RightDetection()
{
  for(int i=0;i<=15;i++) 
  {
    ServoPulse(ServoPin,40);
  }
  RightDistance = DistanceTest();
  //Serial.print("RightDistance:");      
  //Serial.println(RightDistance);         
}


LiquidCrystal_I2C lcd(0x27,16,2); //定义一个液晶
#define Lpwm_pin 6 //在這調速   //9
#define Rpwm_pin 5 //在這調速 //
int pinLB=A2; // 定義2腳位 左後
int pinLF=A3; // 定義4腳位 左前
int pinRB=A1; // 定義7腳位 右後
int pinRF=A0; // 定義8腳位 右前  //6
unsigned char Lpwm_val =155;
unsigned char Rpwm_val =195;
int L=0;
int R=0;
int Car_state=0;
int divtime;
void M_Control_IO_config(void)
{
pinMode(pinLB,OUTPUT); 
pinMode(pinLF,OUTPUT); 
pinMode(pinRB,OUTPUT); 
pinMode(pinRF,OUTPUT); 
pinMode(Lpwm_pin,OUTPUT); // (PWM)
pinMode(Rpwm_pin,OUTPUT); //  (PWM)
}
void Set_Speed(unsigned char Left,unsigned char Right)
{
analogWrite(Lpwm_pin,Left);
analogWrite(Rpwm_pin,Right);
}
void advance(void) // 前進
{

digitalWrite(pinLB,LOW); // 使馬達（左後）動作
digitalWrite(pinLF,HIGH);
digitalWrite(pinRB,LOW); // 使馬達（右後）動作
digitalWrite(pinRF,HIGH);
Car_state = 1;

}
void turnR(void) //右轉(雙輪)
{
digitalWrite(pinRB,LOW); //使馬達（右後）動作
digitalWrite(pinRF,HIGH);
digitalWrite(pinLB,HIGH);
digitalWrite(pinLF,HIGH); //使馬達（左前）動作
Car_state = 4;

}
void turnL(void) //左轉(雙輪)
{
digitalWrite(pinRB,HIGH);
digitalWrite(pinRF,HIGH); //使馬達（右前）動作
digitalWrite(pinLB,LOW); //使馬達（左後）動作
digitalWrite(pinLF,HIGH);
Car_state = 3;

}
void stopp(void) //停止
{
digitalWrite(pinRB,HIGH);
digitalWrite(pinRF,HIGH);
digitalWrite(pinLB,HIGH);
digitalWrite(pinLF,HIGH);
Car_state = 5;

}
void back(void) //後退
{

digitalWrite(pinLB,HIGH); //使馬達（左後）動作
digitalWrite(pinLF,LOW);
digitalWrite(pinRB,HIGH); //使馬達（右後）動作
digitalWrite(pinRF,LOW);
Car_state = 2;

}

void LCD1602_init(void) //液晶初始化用到的函数，包罗在这里
{
lcd.init(); //调用LiquidCrystal_I2C.h里的LCD初始化函数
delay(10); //延时10毫秒
lcd.backlight(); //开LCD1602的背光灯
lcd.clear(); //清除屏幕
}

String readdata;

void setup() {

BT.begin(9600);

Serial.begin(9600);

// Enable the IR Receiver

LCD1602_init();
M_Control_IO_config();
Set_Speed(Lpwm_val,Rpwm_val);

lcd.setCursor(0, 0); //光标设置在第一行，第一列，也就是左上角
lcd.print(" Wait Signal ");
stopp();

 UltrasonicConfig();
  ServoConfig();
  FrontDetection();
   myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms

  //----Set volume----
  myDFPlayer.volume(25);  //Set volume value (0~30).
   myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
   myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
   
}

//-----------------------------------------------------------------------//

void loop() {
  FrontDetection();
Set_Speed(Lpwm_val,Rpwm_val);
  lcd.setCursor(0, 1);
  lcd.print(" L: ");lcd.print(Lpwm_val); lcd.print(" , R: "); lcd.print(Rpwm_val);
 while (BT.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable
  char c = BT.read(); //Conduct a serial read
  readdata += c; //build the string- "forward", "reverse", "left" and "right"
  } 
if (readdata.length() > 0) {

Serial.println(readdata); // print data to serial monitor

if((readdata == "go")|| (readdata == "μπροστά")|| (readdata == "προχώρα")||(readdata == "A"))

{

        advance();
       // Serial.print(" GO  "); Serial.print(Lpwm_val);  Serial.println(Rpwm_val);
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print(readdata); 
        lcd.setCursor(0, 1);
          //Serial.print("\n GO");
        lcd.print(Lpwm_val); lcd.print(" "); lcd.print(Rpwm_val);
        delay(7000);

}

else if((readdata == "stop") || (readdata == "σταμάτα")||(readdata == "σταμάτησε")||(readdata == "σεμνά")||(readdata == "L"))
{
       stopp();
       // Serial.print(" stop  "); Serial.print(Lpwm_val);  Serial.println(Rpwm_val);
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print(readdata); 
        lcd.setCursor(0, 1);
         //Serial.print("\n Stop");
        lcd.print(Lpwm_val);lcd.print(" ");  lcd.print(Rpwm_val);

}

else if ((readdata == "πίσω")||(readdata == "back")||(readdata == "B"))

{

       back();
       // Serial.print(" back "); Serial.print(Lpwm_val);  Serial.println(Rpwm_val);
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print(readdata); 
        lcd.setCursor(0, 1);
         //Serial.print("\n Back");
        lcd.print(Lpwm_val);lcd.print(" ");  lcd.print(Rpwm_val);
        delay(2000);

}

else if (( readdata == "right")||(readdata == "δεξιά")||(readdata == "P"))

{

        turnR();
       // Serial.print(" turn right  "); Serial.print(Lpwm_val);  Serial.println(Rpwm_val);
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print(readdata); 
        lcd.setCursor(0, 1);
         //Serial.print("\n Right");
        lcd.print(Lpwm_val); lcd.print(" "); lcd.print(Rpwm_val);
        delay(3000);

}

else if ((readdata == "αριστερά") || (readdata == "left")||(readdata == "ζερβά")||(readdata == "N"))

{

        turnL();
        lcd.clear();
        lcd.setCursor(0, 0);
       lcd.print(readdata); 
       // Serial.print(" turn left  "); Serial.print(Lpwm_val);  Serial.println(Rpwm_val);
        lcd.setCursor(0, 1);
         //Serial.print("\n Left");
        lcd.print(Lpwm_val); lcd.print(" "); lcd.print(Rpwm_val);
        delay(3000);

}

else if ((readdata == "Πως σε λένε") || (readdata == "ποιο είναι το όνομά σου")||(readdata == "όνομα")||(readdata == "What is your name"))

{

      myDFPlayer.playMp3Folder(1); //play specific mp3 in SD:/MP3/0004.mp3; File Name(0~65535)
  

        lcd.clear();
        lcd.setCursor(0, 0);
       lcd.print(readdata); 
       // Serial.print(" turn left  "); Serial.print(Lpwm_val);  Serial.println(Rpwm_val);
        lcd.setCursor(0, 1);
         //Serial.print("\n Left");
        lcd.print(Lpwm_val); lcd.print(" "); lcd.print(Rpwm_val);lcd.print("ARDUINO ROBOT");
        delay(3000);

}

else if ((readdata == "Ποιος σε έφτιαξε") || (readdata == "ποιος είναι ο κατασκευαστής σου")||(readdata == "ο δημιουργό σου")||(readdata == "your Creator"))

{

         myDFPlayer.playMp3Folder(2); //play specific mp3 in SD:/MP3/0004.mp3; File Name(0~65535)
        lcd.clear();
        lcd.setCursor(0, 0);
       lcd.print(readdata); 
       // Serial.print(" turn left  "); Serial.print(Lpwm_val);  Serial.println(Rpwm_val);
        lcd.setCursor(0, 1);
         //Serial.print("\n Left");
        lcd.print(Lpwm_val); lcd.print(" "); lcd.print(Rpwm_val);lcd.print("GEL VAMOU");
        delay(3000);

}

else if ((readdata == "Πες ένα ανέκδοτο") || (readdata == "Πες ένα αστείο")||(readdata == "Tell me a joke")||(readdata == "πες κάτι"))

{

         myDFPlayer.playMp3Folder(3); //play specific mp3 in SD:/MP3/0004.mp3; File Name(0~65535)
        lcd.clear();
        lcd.setCursor(0, 0);
       lcd.print(readdata); 
       // Serial.print(" turn left  "); Serial.print(Lpwm_val);  Serial.println(Rpwm_val);
        lcd.setCursor(0, 1);
         //Serial.print("\n Left");
        lcd.print(Lpwm_val); lcd.print(" "); lcd.print(Rpwm_val);lcd.print("JOKE");
        delay(3000);

}

else if ((readdata == "ποιο είναι το καλύτερο σχολείο"))

{

         myDFPlayer.playMp3Folder(4); //play specific mp3 in SD:/MP3/0004.mp3; File Name(0~65535)
        lcd.clear();
        lcd.setCursor(0, 0);
       lcd.print(readdata); 
       // Serial.print(" turn left  "); Serial.print(Lpwm_val);  Serial.println(Rpwm_val);
        lcd.setCursor(0, 1);
         //Serial.print("\n Left");
        lcd.print(Lpwm_val); lcd.print(" "); lcd.print(Rpwm_val);lcd.print("VAMOS GEL");
        delay(3000);

}

else if ((readdata == "You are the best")|| (readdata=="μπράβο" ))

{

         myDFPlayer.playMp3Folder(5); //play specific mp3 in SD:/MP3/0004.mp3; File Name(0~65535)
        lcd.clear();
        lcd.setCursor(0, 0);
       lcd.print(readdata); 
       // Serial.print(" turn left  "); Serial.print(Lpwm_val);  Serial.println(Rpwm_val);
        lcd.setCursor(0, 1);
         //Serial.print("\n Left");
        lcd.print(Lpwm_val); lcd.print(" "); lcd.print(Rpwm_val);lcd.print("THANKS");
        delay(3000);

}

else if ((readdata == "είσαι ελεύθερο") || (readdata == "ελεύθερο")||(readdata == "απόφυγε εμπόδια")||(readdata == "free"))

{

        lcd.clear();    
              lcd.setCursor(0, 0);
        lcd.print("I AVOID OBSTACLE,");
        lcd.setCursor(0, 1);
        lcd.print("OK? PROBLEM?"); 
       FrontDetection();
        start_time=millis();
while ((millis() - start_time < 24000UL) && (FrontDistance > 4 )) { // Εφόσον δεν πέρασαν 24 δευτ και η απόσταση απο εμπόδιο είναι μεγαλύτερη απο 4cm κάνε:
       
      FrontDetection();   
       if(FrontDistance < 32)                              //there is an obstacle 
    {
      Car1.Backward();
      delay(200);
      
      Car1.Brake();                                     //stop 
      delay(200);
      
      LeftDetection();                                  //Measure the distance to the left obstacle
      DistanceDisplay(LeftDistance);                    //display distance
      RightDetection();                                 //Measure the distance to the right obstacle
      DistanceDisplay(RightDistance);                   //display distance
      if((LeftDistance < 35 ) &&( RightDistance < 35 )) //When the left and right sides are relatively close by the obstacles
      {
        Car1.LeftCircle();                              //Turn around
        delay(70);
      }
      else if(LeftDistance > RightDistance)             //The left is far more than the right
      {      
        Car1.Left();                                    //Turn left
        delay(300);
        Car1.Brake();                                   //stop
        delay(100);
      }
      else                                              //The right is far more than the left
      {
        Car1.Right();                                   //turn right
        delay(300);
        Car1.Brake();                                   //stop
        delay(100);
      }
    }
    else
    {
      Car1.Forward();                                   //there is no objtacle ,go straight    
    }
    }
}

else if (( readdata == "κύκλος") || (readdata == "circle")||(readdata == "C"))

{

       Set_Speed(75,255);
        advance();
       // Serial.print(" medium circle  "); Serial.print(Lpwm_val);  Serial.println(Rpwm_val);
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print(readdata); 
        lcd.setCursor(0, 1);
        //Serial.print("\n GO");
        lcd.print(Lpwm_val);lcd.print(" ");  lcd.print(Rpwm_val);
        delay(8000);

}

readdata="";}
} //Reset the variable
