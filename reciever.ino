#include <IRremote.h>

int const IRpin = 2;  
int const IRled = 3;  
IRrecv irrecv(IRpin);
IRsend irsend;  
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); 
  pinMode(IRled, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println("========== Zachycený IR signál ==========");

    Serial.print("Hodnota (DEC): ");
    Serial.println(results.value, DEC);

    Serial.print("Počet bitů: ");
    Serial.println(results.bits);

    Serial.print("Délka surových dat: ");
    Serial.println(results.rawlen);

    Serial.println("Surová data:");
    for (int i = 0; i < results.rawlen; i++) {
      Serial.print(results.rawbuf[i]);
      Serial.print(" ");
    }
    Serial.println();

    irsend.sendRaw(results.rawbuf, results.rawlen, 38); 
    Serial.println("Signál byl odeslán zpět!");

    Serial.println("=========================================");

    irrecv.resume(); 
    delay(1000);
  }
}
