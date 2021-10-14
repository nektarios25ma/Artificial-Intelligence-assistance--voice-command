//ΕΔΩ ΟΙ ΟΡΙΣΜΟΙ ΓΙΑ ΦΩΝΗΤΙΚΗ ΠΡΟΕΙΔΟΠΟΙΗΣΗ -ΠΑΙΖΕΙ ΑΠΟ DFPLAYER MINI MP3 ΚΑΙ SD CARD
#include "SoftwareSerial.h"
SoftwareSerial mySerial(2, 3);    //SoftwareSerial mySerial(10, 11);
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]

# define ACTIVATED LOW

void setup()
{
 
mySerial.begin (9600);
delay(1000);
  Serial.begin(9600);
 //playFirstb();
//  delay(1000);
//  playFirst();
 // delay(1000);
  playSecond();  //thanks
  delay(100);
   playThird();  //vamos is the best
   delay(100);
   playFourth();  //joke
   delay(100);
   playFifth();  // η ομαδα ρομποτικης του λυκειου βαμος
   delay(400);
   playFifthb(); //Το οναμά μου arduino
   delay(300);
}
void loop()
{
  playSecond();
  
  delay(500);
playFifth();
delay(5000);
playFourth();

  delay(5000);
 playThird();
}
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
void playFifth() ς
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
