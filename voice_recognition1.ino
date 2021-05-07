#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); //TX, RX respetively

String readdata;

void setup() {

BT.begin(9600);

Serial.begin(9600);

pinMode(3, OUTPUT);

pinMode(4, OUTPUT); //

pinMode(5, OUTPUT); //

// pinMode(6, OUTPUT); //

}

//-----------------------------------------------------------------------//

void loop() {

 while (BT.available()){  //Check if there is an available byte to read
  delay(10); //Delay added to make thing stable
  char c = BT.read(); //Conduct a serial read
  readdata += c; //build the string- "forward", "reverse", "left" and "right"
  } 
if (readdata.length() > 0) {

Serial.println(readdata); // print data to serial monitor

if((readdata == "light on")|| (readdata == "Light ON"))

{

digitalWrite(3, HIGH);

}

else if((readdata == "light off") || (readdata == "Light off"))
{
digitalWrite(3, LOW);

}

else if ((readdata == "fan on")||(readdata == "Fan on"))

{

digitalWrite (4,HIGH);

}

else if (( readdata == "fan off")||(readdata == "Fan off")||(readdata == "Σβήσε"))

{

digitalWrite (4, LOW);

}

else if ((readdata == "tv on") || (readdata == "TV On")||(readdata == "Ωχ"))

{

digitalWrite (5, HIGH);

}

else if (( readdata == "tv off") || (readdata == "TV off"))

{

digitalWrite (5, LOW);

}
readdata="";}
} //Reset the variable

