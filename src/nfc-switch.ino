#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>
#include <authorized_ids.h>

#define IRQ   (2)
#define RESET (3)  // Not connected by default on the NFC Shield

Adafruit_PN532 nfc(IRQ, RESET);

void setup(void) {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
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
                    if (digitalRead(13) == HIGH) {
                        digitalWrite(13, LOW);
                        Serial.println("Power Off");
                    } else {
                        digitalWrite(13, HIGH);
                        Serial.println("Power On");
                    }
                    delay(1000);
                    i=num_uids;
                    success=1;
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
