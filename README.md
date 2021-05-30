# Artificial-Intelligence-assistance--voice-command
Αναγνώριση φωνής -βοηθός ατόμων με δυσκολία στην κίνηση
Artificial Intelligence assistance -voice command
 
Η τεχνολογία αναγνώρισης φωνής είναι πολύ χρήσιμη στον αυτοματισμό, η οποία όχι μόνο μας δίνει φωνητικό έλεγχο των συσκευών, αλλά και προσθέτει ασφάλεια στο σύστημα μας. Η αναγνώριση ομιλίας παρέχει επίσης σημαντική βοήθεια σε άτομα που πάσχουν από διάφορες αναπηρίες. Σε αυτό το έργο θα χρησιμοποιήσουμε το nano 33 ble sense ως μια πλατφόρμα οριακά ικανή να “σηκώσει” το πρόγραμμά μας με σκοπό να μπορεί με φωνητικές εντολές να ελέγχει -απομακρυσμένα- το κλείδωμα ή το ξεκλείδωμα μιας πόρτας όπως και άλλων συσκευών.
ΥΛΙΚΑ
ΓΙΑ ΤΗΝ ΦΘΗΝΗ ΕΚΔΟΧΗ ΜΟΝΟ nano 33 ble sense ΚΑΙ LED,σύνολο=50 € 
https://grobotronics.com/arduino-nano-33-ble-sense-with-headers-abx00035.html
 
(τα led θα δείχνουν την επιτυχία αναγνώρισης φωνής και θα προσομοιάζουν το άνοιγμα και κλείσιμο της κλειδαριάς)

{{Για την πιο φθηνή:(όμως με δύσκολο λογισμικό ανάπτυξης)

 α)esp32 : https://grobotronics.com/esp32-development-board-devkit-v1.html
 €9.90

 β) BREADBOARD:https://www.hellasdigital.gr/electronics/prototyping/pcb-breadboard/mini-universal-solderless-breadboard-400-tie-points/
€4,30

γ) μικρόφωνο:

https://www.hellasdigital.gr/electronics/components/nmp441-mems-high-precision-low-power-ultra-small-volume-for-esp32/

€6,20

δ)ενισχυτής ήχου: https://grobotronics.com/adafruit-i2s-3w-class-d-amplifier-breakout-max98357a.html

€7.50

(ηχεία διαθέτουμε)

σύνολο =28€

}}

ΓΙΑ ΤΗΝ ακριβή: (ολοκληρωμένο έργο)
Α) ) nano 33 ble sense with headers :
https://grobotronics.com/arduino-nano-33-ble-sense-with-headers-abx00035.html
=46,8 € 
Β) arduino uno : https://www.hellasdigital.gr/go-create/arduino/uno-r3-atmega328p-ch340g-mini-usb-board-for-compatible-arduino-diy/
€6,78
Γ) Jumper Wires : https://www.hellasdigital.gr/electronics/prototyping/cables-pins/40p-10cm-dupont-wire-male-to-male/
€2,99
 
Δ)BREADBOARD:https://www.hellasdigital.gr/electronics/prototyping/pcb-breadboard/mini-universal-solderless-breadboard-400-tie-points/
€4,30
Ε)ρελέ : https://www.hellasdigital.gr/go-create/arduino-shields-and-accessories/5v-4-channel-relay-shield-module-for-arduino/
€8,68
Ζ)(2)x bluetooth hc-05 :https://www.hellasdigital.gr/electronics/43-membrane-switch-matrix-keypad/
2Χ€7,80 
Η)Μπαταριοθήκες : https://www.hellasdigital.gr/electronics/components/2-cells-18650-li-ion-lithium-battery-holder-w-5.52.1mm-dc-power-plug-connector/ και https://www.hellasdigital.gr/electronics/prototyping/cases/2-x-18650-battery-holder-with-dc2.1-power-jack-fit0538/
και https://www.hellasdigital.gr/electronics/components/3-x-18650-battery-holder-with-dc2.1-power-jack-fit0539/
3Χ€1,24
 
Θ)(5)Χ ΜΠΑΤΑΡΙΕΣ 18650: https://www.hellasdigital.gr/electronics/batteries/li-ion/panasonic-ncr18650b-battery-18650-3400mah/
5Χ€6,99
 
Ι)Κλειδαριά: https://www.hellasdigital.gr/smartliving/smartlocks/12v-solenoid-lock/
€7,44 
ΣΥΝΟΛΟ:130€
 
 
Software
Α)EDGE IMPULSE STUDIO :
https://studio.edgeimpulse.com/  ή
Tensorflow Lite( ή TinyML)
Β)ARDUINO IDE
 
1η προσέγγιση της αναγνώρισης φωνής

Στηρίζεται σε δύο κύρια στοιχεία : α) arduino uno με σύνδεση σε κύκλωμα που εμπεριέχει , άνοιγμα κλείσιμο: φωτός ,ανεμιστήρα,τηλεόρασης κ.τ.λ.   β)smartphone με την εφαρμογή αναγνώρισης φωνής που φτιάξαμε με τεχνολογία τεχνητής νοημοσύνης. Η εφαρμογή mit app inventor του κινητού όπως και το πρόγραμμα του arduino (και η συνδεσμολογία του κυκλώματος)θα κοινοποιηθεί σε σύνδεσμο κοινής χρήσης .

Η εφαρμογή του κινητού ΜΕ ΤΕΧΝΟΛΟΓΊΑ ΑΙ: https://drive.google.com/file/d/1DAyleREWb_oeiSgXCcUE1LgrkpLdOXdx/view?usp=sharing

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



