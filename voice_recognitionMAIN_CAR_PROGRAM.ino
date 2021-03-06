
#include <SoftwareSerial.h> 
#include "Arduino.h"

SoftwareSerial mySerial(2, 3); // RX, TX
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]

# define ACTIVATED LOW

SoftwareSerial BT(7, 8); //TX, RX respetively
String readdata;


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

#define Lpwm_pin 6 
#define Rpwm_pin 5
int pinLB=A2; 
int pinLF=A3; 
int pinRB=A1; 
int pinRF=A0; 
unsigned char Lpwm_val =115;
unsigned char Rpwm_val =115;
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
void advance(void) 
{

digitalWrite(pinLB,LOW); 
digitalWrite(pinLF,HIGH);
digitalWrite(pinRB,LOW); 
digitalWrite(pinRF,HIGH);
Car_state = 1;

}
void turnR(void) 
{
digitalWrite(pinRB,LOW); 
digitalWrite(pinRF,HIGH);
digitalWrite(pinLB,HIGH);
digitalWrite(pinLF,HIGH); 
Car_state = 4;

}
void turnL(void) 
{
digitalWrite(pinRB,HIGH);
digitalWrite(pinRF,HIGH); 
digitalWrite(pinLB,LOW); 
digitalWrite(pinLF,HIGH);
Car_state = 3;

}
void stopp(void) 
{
digitalWrite(pinRB,HIGH);
digitalWrite(pinRF,HIGH);
digitalWrite(pinLB,HIGH);
digitalWrite(pinLF,HIGH);
Car_state = 5;

}
void back(void) 
{

digitalWrite(pinLB,HIGH); 
digitalWrite(pinLF,LOW);
digitalWrite(pinRB,HIGH); 
digitalWrite(pinRF,LOW);
Car_state = 2;

}

void setup() {

BT.begin(9600);
 mySerial.begin(9600);
Serial.begin(9600);

M_Control_IO_config();
Set_Speed(Lpwm_val,Rpwm_val);


stopp();

 UltrasonicConfig();
  ServoConfig();
  FrontDetection();
   playSecond();
//   playFifthb(); //Το οναμά μου arduino
   delay(300);  
   
}

//-----------------------------------------------------------------------//

void loop() {
  BT.listen();
  FrontDetection();
Set_Speed(Lpwm_val,Rpwm_val);
  
  
 while (BT.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable
  char c = BT.read(); //Conduct a serial read
  readdata += c; //build the string- "forward", "reverse", "left" and "right"
  } 
if (readdata.length() > 0) {

Serial.println(readdata); // print data to serial monitor

if((readdata == "go")|| (readdata == "μπροστά")|| (readdata == "προχώρα")||(readdata == "A"))

{
        FrontDetection();
        advance();
       
        delay(7000);

}

else if((readdata == "stop") || (readdata == "σταμάτα")||(readdata == "σταμάτησε")||(readdata == "σεμνά")||(readdata == "L"))
{
       stopp();
       

}

else if ((readdata == "πίσω")||(readdata == "back")||(readdata == "B"))

{

       back();
       
        delay(2000);

}

else if (( readdata == "right")||(readdata == "δεξιά")||(readdata == "P"))

{

        turnR();
       
        delay(3000);

}

else if ((readdata == "αριστερά") || (readdata == "left")||(readdata == "ζερβά")||(readdata == "N"))

{

        turnL();
        
        delay(3000);

}



else if ((readdata == "είσαι ελεύθερο") || (readdata == "ελεύθερο")||(readdata == "απόφυγε εμπόδια")||(readdata == "free"))

{

        
       FrontDetection();
        start_time=millis();
while ((millis() - start_time < 14000UL) && (FrontDistance > 4 )) { // Εφόσον δεν πέρασαν 24 δευτ και η απόσταση απο εμπόδιο είναι μεγαλύτερη απο 4cm κάνε:
       
      FrontDetection();   
       if(FrontDistance < 32)                              //there is an obstacle 
    {
      back();
      delay(200);
      
      stopp();                                     //stop 
      delay(200);
      
      LeftDetection();                                  //Measure the distance to the left obstacle
      DistanceDisplay(LeftDistance);                    //display distance
      RightDetection();                                 //Measure the distance to the right obstacle
      DistanceDisplay(RightDistance);                   //display distance
      if((LeftDistance < 35 ) &&( RightDistance < 35 )) //When the left and right sides are relatively close by the obstacles
      {
        turnL();                              //Turn around
        delay(70);
      }
      else if(LeftDistance > RightDistance)             //The left is far more than the right
      {      
        turnL();                                    //Turn left
        delay(300);
        stopp();                                   //stop
        delay(100);
      }
      else                                              //The right is far more than the left
      {
        turnR();                                   //turn right
        delay(300);
        stopp();                                   //stop
        delay(100);
      }
    }
    else
    {
      advance();                                   //there is no objtacle ,go straight  
      playten();  
    }
    }
}

else if (( readdata == "κύκλος") || (readdata == "circle")||(readdata == "C"))

{

       Set_Speed(75,255);
        advance();
       
        delay(8000);

}


else if ((readdata == "Πώς σε λένε") || (readdata == "ποιο είναι το όνομά σου")||(readdata == "όνομα")||(readdata == "What is your name"))
//if ((readdata == "Πως σε λένε") || (readdata == "ποιο είναι το όνομά σου")||(readdata == "όνομα")||(readdata == "What is your name"))
{

     

       playSecond();
      
        delay(3000);

}

else if ((readdata == "Ποιος σε έφτιαξε") || (readdata == "ποιος είναι ο κατασκευαστής σου")||(readdata == "ο δημιουργός σου")||(readdata == "your Creator")||(readdata == "kreator"))

{       
         playThird();
       
        delay(3000);

}

else if ((readdata == "Πες ένα ανέκδοτο") || (readdata == "Πες ένα αστείο")||(readdata == "Tell me a joke")||(readdata == "πες κάτι"))

{

         playFourth();
       
        delay(3000);

}

else if ((readdata == "ποιο είναι το καλύτερο σχολείο"))

{
       
        playFifth();
        
        delay(3000);

}

else if ((readdata == "You are the best")|| (readdata=="μπράβο" ))

{

        playFifthb();
        
        delay(3000);

}
else if ((readdata == "Ποιοι είναι οι φίλοι σου")|| (readdata=="οι φίλοι σου" )|| (readdata=="η φίλη σου" ))

{

        playsix();
        
        delay(3000);

}
else if ((readdata == "τι είπε ο Αϊνστάιν")|| (readdata=="κάτι που είπε ο Αϊνστάιν" )|| (readdata=="Αϊνστάιν" ))

{

        playseven();
        
        delay(3000);

}
else if ((readdata == "ποια είναι η διακρίνουσα")|| (readdata=="Πες την διακρίνουσα" )|| (readdata=="διακρίνουσα" ))

{

        playeight();
        
        delay(3000);

}
else if ((readdata == "Πόσο κάνει 1+1")|| (readdata=="πόσο κάνει" )|| (readdata=="Πόσο κάνει" ))

{

        playnine();
       

        delay(3000);

}

FrontDetection();

readdata="";}
} //Reset the variable

//ΓΙΑ ΤΑ MP3 
void playFirst()
{
  execute_CMD(0x3F, 0, 0);
  delay(2500);
  setVolume(30);
  delay(500);
 
}
void playFirstb()
{
  execute_CMD(0x03, 0, 0);
  delay(2500);
  setVolume(30);
  delay(500);
 
}
void playFifthb()
{
  execute_CMD(0x03, 0, 5);
  delay(4500);
  setVolume(30);
  delay(500);
 
}
void playFifth() 
{
  execute_CMD(0x03, 0, 4);
  delay(6500);
  setVolume(30);
  delay(50);
 
}
void playSecond() 
{
  execute_CMD(0x03, 0, 1);
  delay(7000);
  setVolume(30);
  delay(50);
 
}
void playThird() 
{
  execute_CMD(0x03, 0, 2);
  delay(6500);
  setVolume(30);
  delay(50);
 
}
void playFourth() 
{
  execute_CMD(0x03, 0, 3);
  delay(8000);
  setVolume(30);
  delay(50);
 
}
void playsix() 
{
  execute_CMD(0x03, 0, 6);
  delay(13000);
  setVolume(30);
  delay(50);
 
}

void playseven() 
{
  execute_CMD(0x03, 0, 7);
  delay(14000);
  setVolume(30);
  delay(50);
 
}
void playeight() 
{
  execute_CMD(0x03, 0, 8);
  delay(14000);
  setVolume(30);
  delay(50);
 
}
void playnine() 
{
  execute_CMD(0x03, 0, 9);
  delay(14000);
  setVolume(30);
  delay(50);
 
}
void playten() 
{
  execute_CMD(0x03, 0, 10);
  delay(4000);
  setVolume(30);
  delay(50);
 
}
void pause()
{
  execute_CMD(0x0E,0,0);
  delay(500);
}

void play()
{
  execute_CMD(0x0D,0,1); 
  delay(500);
}



void setVolume(int volume)
{
  execute_CMD(0x25, 0, volume); // Set the volume (0x00~0x30)
  delay(1000);
}

void execute_CMD(byte CMD, byte Par1, byte Par2)
// Excecute the command and parameters
{
// Calculate the checksum (2 bytes)
word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);
// Build the command line
byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte};
//Send the command line to the module
for (byte k=0; k<10; k++)
{
mySerial.write( Command_line[k]);
}
}
