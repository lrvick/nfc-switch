#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>
#include <authorized_ids.h>

#define RELAY (9)

#define PN532_SS   (10)
#define PN532_MOSI (11)
#define PN532_MISO (12)
#define PN532_SCK  (13)

Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);

void setup(void) {
  Serial.begin(9600);
  pinMode(RELAY, OUTPUT);
  nfc.begin();
  nfc.SAMConfig();
}

void loop(void) {
  uint8_t success = 0;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength;

  if (nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength)){
    uint32_t i;
    uint32_t b;
    int num_uids = sizeof(auth_uids)/sizeof(auth_uids[0]);
    Serial.println(num_uids);
    for (i=0; i < num_uids; i++){
        for (b=0; b < 7; b++){
            if (uid[b] == auth_uids[i][b]){
                if (b == 6){
                    if (digitalRead(RELAY) == HIGH) {
                        digitalWrite(RELAY, LOW);
                        Serial.println("Power Off");
                    } else {
                        digitalWrite(RELAY, HIGH);
                        Serial.println("Power On");
                    }
                    i=num_uids;
                    success=1;
                    delay(1000);
                    break;
                }
            } else {
                b=7;
            }
        }
    }
    if (!success){
        Serial.print("Failed auth for unknown UID: ");
        nfc.PrintHex(uid, uidLength);
    }
  }
}
