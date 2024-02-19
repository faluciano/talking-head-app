#define IR_SMALLD_NEC

#define PIN_SD_MOSI A3
#define PIN_SD_MISO A2
#define PIN_SD_SCK  A4
#define PIN_SD_CS   A5

#include <IRsmallDecoder.h>
#include <SPI.h>
#include <SD.h>
//#include <AudioZero.h>

File myFile;

IRsmallDecoder irDecoder(D11);
irSmallD_t irData;

int melody[] = {
  262, 196, 196, 220, 196, 0, 247, 262
};

int noteDurations[] = {

  4, 8, 8, 4, 4, 4, 4, 4
};


void setup() {

  Serial.begin(19200);
  while (!Serial);
  delay(1000);
  Serial.println("Waiting for a NEC remote control IR signal...");
  Serial.println("held \t addr \t cmd");
  Serial.print("Initializing SD card with SS = ");  Serial.println(PIN_SD_CS);
  Serial.print("SCK = ");   Serial.println(PIN_SD_SCK);
  Serial.print("MOSI = ");  Serial.println(PIN_SD_MOSI);
  Serial.print("MISO = ");  Serial.println(PIN_SD_MISO);

  if (!SD.begin(PIN_SD_CS)) 
  {
    Serial.println("Initialization failed!");
    return;
  }
  
  Serial.println("Initialization done.");
}

void loop() {
  if(irDecoder.dataAvailable(irData)) {      
    Serial.print(irData.keyHeld,HEX);
    Serial.print("\t ");
    Serial.print(irData.addr,HEX); 
    Serial.print("\t ");
    Serial.println(irData.cmd,HEX);
    if(irData.cmd == 0x45){
      Serial.println("First action");
      tone(D13,1000,5000);
    }
    if(irData.cmd == 0x46){
      Serial.println("Second action"); 
      myFile = SD.open("santi.wav", FILE_WRITE);
      if (myFile) 
      {
        Serial.print("Reading from "); Serial.println("santi.wav");
        Serial.println("===============");
        //AudioZero.begin(2*44100);
        //AudioZero.play(myFile);
        //AudioZero.end();
        // close the file:
        myFile.close();

        Serial.println("===============");
      } 
      else 
      {
        // if the file didn't open, print an error:
        Serial.print("Error opening "); 
        Serial.println("santi.wav");
      }
    }
    if(irData.cmd == 0x47){
      for (int thisNote = 0; thisNote < 8; thisNote++) {

        // to calculate the note duration, take one second divided by the note type.

        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

        int noteDuration = 1000 / noteDurations[thisNote];

        tone(D13, melody[thisNote], noteDuration);

        // to distinguish the notes, set a minimum time between them.

        // the note's duration + 30% seems to work well:

        int pauseBetweenNotes = noteDuration * 1.30;

        delay(pauseBetweenNotes);

        // stop the tone playing:

        noTone(D13);

      }
    }


  }
}