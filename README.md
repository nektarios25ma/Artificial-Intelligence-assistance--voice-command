Αναλυτική περιγραφή ιδέας:	Αναγνώριση φωνής -βοηθός ατόμων με δυσκολία στην κίνηση
Artificial Intelligence assistance -voice command.
Εναλλακτικά ρομπότ με αναγνώριση φωνής 
και τεχνολογία AI το οποίο μπορεί να ανοίξει διάλογο μαζί μας και υπακούει εντολές.
VIDEO LINK:
https://www.youtube.com/watch?v=EHHKBFsGerw

ΚΑΙ
https://www.youtube.com/watch?v=t6V9hQNwK7s&t=1s



 Η τεχνολογία αναγνώρισης φωνής είναι πολύ χρήσιμη στον αυτοματισμό, 
η οποία όχι μόνο μας δίνει φωνητικό έλεγχο των συσκευών, 
αλλά και προσθέτει ασφάλεια στο σύστημα μας.
 Η αναγνώριση ομιλίας παρέχει επίσης σημαντική βοήθεια ,
σε άτομα που πάσχουν από διάφορες αναπηρίες. 


Λίστα προτεινόμενου εξοπλισμού:	
ΥΛΙΚΑ
 
2Χ BREADBOARD:
https://www.hellasdigital.gr/electronics/prototyping/pcb-breadboard/mini-universal-solderless-breadboard-400-tie-points/
2Χ€4,30
arduino uno :
https://www.hellasdigital.gr/go-create/arduino/uno-r3-atmega328p-ch340g-mini-usb-board-for-compatible-arduino-diy/
€6,78
Jumper Wires :
https://www.hellasdigital.gr/electronics/prototyping/cables-pins/40p-10cm-dupont-wire-male-to-male/
€2,99
Μπαταριοθήκη :
https://www.hellasdigital.gr/electronics/components/2-cells-18650-li-ion-lithium-battery-holder-w-5.52.1mm-dc-power-plug-connector/  
€1,24
 ΜΠΑΤΑΡΙΕΣ 18650:
 https://www.hellasdigital.gr/electronics/batteries/li-ion/panasonic-ncr18650b-battery-18650-3400mah/
2Χ€6,99
ΣΑΣΙ ΡΟΜΠΟΤ:
https://grobotronics.com/robot-smart-car-2wd.html                                   €12.90
MOTOR DRIVER:
https://grobotronics.com/dual-motor-driver-module-l298n.html  €4.20
MP3 Player:
https://grobotronics.com/dfplayer-a-mini-mp3-player.html €9.90
Κάρτα μνήμης microSD:
https://grobotronics.com/microsdhc-16gb-class-10-sandisk-ultra-sdsquar-sdsquar-016g-gn6ma.html €6.90
Αισθητήρας Υπερήχων:
https://grobotronics.com/ultrasonic-sensor-sr04.html €2.50
Βάση Στήριξης για Αισθητήρα Υπερήχων:
https://grobotronics.com/mounting-bracket-for-ultrasonic-sensor.html €0.60
Servo : 
https://grobotronics.com/servo-micro-2.2kg.cm-plastic-gears-waveshare-sg90.html €3.60

Σερβο βραχίονα στήριξης για servo SG90: 
https://grobotronics.com/servo-mounting-bracket-sg90.html €0.80
Μικρό ηχείο: 
https://www.hellasdigital.gr/electronics/components/8-0.5w-small-trumpet-36mm-diameter-loudspeaker/ €1,20 
Spacer Ποικιλία : 
https://www.hellasdigital.gr/electronics/prototyping/brass-buttons/120pcs-m3-male-female-brass-standoff-spacer-assortment-for-pcb/  €9,98
Bluetooth Module for Arduino:
https://grobotronics.com/bluetooth-module-for-arduino-hc05.html €6.80

ΣΥΝΟΛΟ:90,70€

ΛΟΓΙΣΜΙΚΟ: ARDUINO IDE 
ΚΑΙ MIT APP INVENTOR

1η προσέγγιση της αναγνώρισης φωνής
Στηρίζεται σε δύο κύρια στοιχεία :
α) arduino uno με σύνδεση σε κύκλωμα που ελέγχει 
είτε άνοιγμα και κλείσιμο συσκευών 
είτε την λειτουργία ενός μικρού ρομπότ
που υπακούει στις εντολές μας και ανοίγει διάλογο μαζί μας   
β)smartphone app- εφαρμογή αναγνώρισης φωνής που φτιάξαμε με τεχνολογία τεχνητής νοημοσύνης.

Η εφαρμογή mit app inventor του κινητού όπως και το πρόγραμμα του arduino 
(και η συνδεσμολογία του κυκλώματος)θα τα βρείτε ως εικόνες.png .

Η εφαρμογή του κινητού :
https://drive.google.com/file/d/1DAyleREWb_oeiSgXCcUE1LgrkpLdOXdx/view?usp=sharing

Α)Το πρόγραμμα του arduino για απλό έλεγχο συσκευών-led συμβολικά:

#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); //TX, RX respetively
String readdata;

void setup()
{
BT.begin(9600);
Serial.begin(9600);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT); //
pinMode(5, OUTPUT); //

}
//-----------------------------------------------------------------------//

void loop()
{
while (BT.available())
{  //Check if there is an available byte to read
delay(10); //Delay added to make thing stable
char c = BT.read(); //Conduct a serial read
readdata += c;  
}
if (readdata.length() > 0)
{
Serial.println(readdata); // print data to serial monitor
if((readdata == "light on")|| (readdata == "Light ON"))
{
digitalWrite(3, HIGH);
}
else if((readdata == "light off") || (readdata == "light off"))  
//δέχεται και ελληνικές φράσεις
{  
digitalWrite(3, LOW);
}
else if (readdata == "fan on")
{
digitalWrite (4,HIGH);
}
else if ( readdata == "fan off")
{
digitalWrite (4, LOW);
}
else if ((readdata == "tv on") || (readdata == "TV On"))
{
digitalWrite (5, HIGH);
}
else if (( readdata == "tv off") || (readdata == "TV off"))
{
digitalWrite (5, LOW);
}
readdata="";
}
} //Reset the variable

ΚΥΚΛΩΜΑ,link:

https://drive.google.com/file/d/1iMu3vorPIyGFPI8DEielNVL-gAWGKdJP/view?usp=sharing


B)Για το ρομπότ που υπακούει –αναγνωρίζει εντολές και
κάνει διάλογο αποφάσισα να δώσω τα κυκλώματα διαδοχικά και όχι σε’ένα όλα λόγω περιπλοκότητας 
(έτσι άλλωστε το φτιάξανε και τα παιδιά ): 

Α)κυρίως κύκλωμα:
ΔΕΣ
 CIRCUIT.PNG
 
 Β) Bluetooth: TX--> 8 , RX-->7 ,VCC-->5V ΤΟΥ MOTOR DRIVER,GND ΚΟΙΝΟ ΟΛΩΝ ΜΕ ARDUINO
 
 ΔΕΣ HC 05.PNG
 
MP3 –ΗΧΕΙΟ

DFPLAYER.PNG

ΣΕΡΒΟ : ΤΑ 5VOLT ΚΟΚΚΙΝΟ ΚΑΛΩΔΙΟ ΠΗΓΕ ΤΕΛΙΚΑ ΣΤΑ 5V ΤΟΥ MOTOR DRIVER

ΔΕΣ SERVO.PNG 

ULTRASONIC

ΔΕΣ ULTRASONIC1.PNG
 
CODE:

#include <SoftwareSerial.h> 
#include "Arduino.h"

SoftwareSerial mySerial(2, 3); // RX, TX
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]

# define ACTIVATED LOW

SoftwareSerial BT(7, 8); 
                               //TX, RX respetively

String readdata;


unsigned long start_time;
           // Δημιούργησε μια μεταβλητή τύπου unsigned long integer με όνομα start_time

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
pinMode(Lpwm_pin,OUTPUT);        // (PWM)
pinMode(Rpwm_pin,OUTPUT);         //  (PWM)
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

void loop()
{
  BT.listen();
  FrontDetection();
Set_Speed(Lpwm_val,Rpwm_val);
  
  
 while (BT.available())
 {
 //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable
  char c = BT.read(); //Conduct a serial read
  readdata += c;                                                        
  }
  
if (readdata.length() > 0)
{

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
void playsix() //ΠΡΟΣΟΧΗ ΥΨΗΛΗ ΘΕΡΜΟΚΡΑΣΙΑ
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

