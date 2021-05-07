#include <LiquidCrystal_I2C.h> 
#include <IRremote.h>
// Include IR Remote Library by Ken Shirriff

#include <SoftwareSerial.h>

SoftwareSerial BT(7, 8); //TX, RX respetively
// Define sensor pin
const int RECV_PIN = 4;
//      0xFFA25D, // CH-
           /* 0xFF629D,   // CH  avoid
            0xFFE21D,  // CH+

            0xFF22DD, // |<<
            0xFF02FD, // >>|
            0xFFC23D, // >||          

            0xFFE01F, // -
            0xFFA857, // +
            0xFF906F, // EQ  big circle

            0xFF6897, // 0  medium cyrcle
            0xFF9867, // 100+
            0xFFB04F, // 200+

            0xFF30CF, // 1  +5 velocity right    
            0xFF18E7, // 2 forward
            0xFF7A85, // 3  -5 velocity both         

            0xFF10EF, // 4 left
            0xFF38C7, // 5  stop
            0xFF5AA5,  // 6 right

            0xFF42BD, // 7  +1 velocity left
            0xFF4AB5, // 8  backward
            0xFF52AD  // 9  +1 velocity right                             */  



   
// Define IR Receiver and Results Objects
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long start_time; // Δημιούργησε μια μεταβλητή τύπου unsigned long integer με όνομα start_time
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
  irrecv.enableIRIn();
LCD1602_init();
M_Control_IO_config();
Set_Speed(Lpwm_val,Rpwm_val);

lcd.setCursor(0, 0); //光标设置在第一行，第一列，也就是左上角
lcd.print(" Wait Signal ");
stopp();

}

//-----------------------------------------------------------------------//

void loop() {
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

if((readdata == "go")|| (readdata == "μπροστά")|| (readdata == "προχώρα"))

{

        advance();
       // Serial.print(" GO  "); Serial.print(Lpwm_val);  Serial.println(Rpwm_val);
       lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print(readdata);   //Serial.print("\n GO");
        lcd.print(Lpwm_val); lcd.print(" "); lcd.print(Rpwm_val);
        delay(7000);

}

else if((readdata == "stop") || (readdata == "σταμάτα")||(readdata == "σταμάτησε")||(readdata == "σεμνά"))
{
       stopp();
       // Serial.print(" stop  "); Serial.print(Lpwm_val);  Serial.println(Rpwm_val);
       lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print(readdata);  //Serial.print("\n Stop");
        lcd.print(Lpwm_val);lcd.print(" ");  lcd.print(Rpwm_val);

}

else if ((readdata == "πίσω")||(readdata == "back"))

{

       back();
       // Serial.print(" back "); Serial.print(Lpwm_val);  Serial.println(Rpwm_val);
       lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print(readdata);   //Serial.print("\n Back");
        lcd.print(Lpwm_val);lcd.print(" ");  lcd.print(Rpwm_val);
        delay(2000);

}

else if (( readdata == "right")||(readdata == "δεξιά"))

{

        turnR();
       // Serial.print(" turn right  "); Serial.print(Lpwm_val);  Serial.println(Rpwm_val);
       lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print(readdata);  //Serial.print("\n Right");
        lcd.print(Lpwm_val); lcd.print(" "); lcd.print(Rpwm_val);
        delay(3000);

}

else if ((readdata == "αρστερά") || (readdata == "left")||(readdata == "ζερβά"))

{

        turnL();
        lcd.clear();
       // Serial.print(" turn left  "); Serial.print(Lpwm_val);  Serial.println(Rpwm_val);
        lcd.setCursor(0, 1);
        lcd.print(readdata);  //Serial.print("\n Left");
        lcd.print(Lpwm_val); lcd.print(" "); lcd.print(Rpwm_val);
        delay(3000);

}

else if (( readdata == "κύκλος") || (readdata == "circle"))

{

       Set_Speed(75,255);
        advance();
       // Serial.print(" medium circle  "); Serial.print(Lpwm_val);  Serial.println(Rpwm_val);
       lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print(readdata);   //Serial.print("\n GO");
        lcd.print(Lpwm_val);lcd.print(" ");  lcd.print(Rpwm_val);
        delay(8000);

}

readdata="";}
} //Reset the variable

