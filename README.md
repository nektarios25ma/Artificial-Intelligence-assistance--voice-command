# Artificial-Intelligence-assistance--voice-command
Αναγνώριση φωνής -βοηθός ατόμων με δυσκολία στην κίνηση
Artificial Intelligence assistance -voice command
 
Η τεχνολογία αναγνώρισης φωνής είναι πολύ χρήσιμη στον αυτοματισμό, η οποία όχι μόνο μας δίνει φωνητικό έλεγχο των συσκευών, αλλά και προσθέτει ασφάλεια στο σύστημα μας. Η αναγνώριση ομιλίας παρέχει επίσης σημαντική βοήθεια σε άτομα που πάσχουν από διάφορες αναπηρίες. 
 
1η προσέγγιση της αναγνώρισης φωνής

Στηρίζεται σε δύο κύρια στοιχεία : α) arduino uno με σύνδεση σε κύκλωμα που εμπεριέχει , άνοιγμα κλείσιμο: φωτός ,ανεμιστήρα,τηλεόρασης κ.τ.λ.   β)smartphone με την εφαρμογή αναγνώρισης φωνής που φτιάξαμε με τεχνολογία τεχνητής νοημοσύνης. Η εφαρμογή mit app inventor του κινητού όπως και το πρόγραμμα του arduino (και η συνδεσμολογία του κυκλώματος)θα κοινοποιηθεί σε σύνδεσμο κοινής χρήσης .

Η εφαρμογή του κινητού ΜΕ ΤΕΧΝΟΛΟΓΊΑ ΑΙ : https://drive.google.com/file/d/1DAyleREWb_oeiSgXCcUE1LgrkpLdOXdx/view?usp=sharing

Το πρόγραμμα του arduino :

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


ΚΥΚΛΩΜΑ,link:

https://drive.google.com/file/d/1iMu3vorPIyGFPI8DEielNVL-gAWGKdJP/view?usp=sharing
πηγές: 
MIT APP VOICE RECOGNITION

https://www.dropbox.com/s/e1wjkqsgoqu1s3o/electrical_devices.ino?dl=0

https://www.dropbox.com/s/174zp3s8d60w5o8/Voiceandbutton.aia?dl=0

https://www.dropbox.com/s/2d5ibwbws0fe9ai/Voiceandbutton.apk?dl=0


