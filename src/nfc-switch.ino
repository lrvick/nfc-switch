#include <Wire.h>
#include <SPI.h>
#include <EEPROM.h>
#include <Adafruit_PN532.h>
#include <authorized_ids.h>

#define IRQ   (2)
#define RESET (3)  // Not connected by default on the NFC Shield
#define RELAY_RESET (11)
#define RELAY_SET (12)
#define STATUS_LED (13)
#define RELAY_MEM (0)

Adafruit_PN532 nfc(IRQ, RESET);

void setup(void) {
  Serial.begin(9600);
  pinMode(RELAY_SET, OUTPUT);
  pinMode(RELAY_RESET, OUTPUT);
  pinMode(STATUS_LED, OUTPUT);
  nfc.begin();
  nfc.SAMConfig();
}

void loop(void) {
  uint8_t success = 0;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength;
  int relay_state = 0;
  EEPROM.get(RELAY_MEM, relay_state);
  digitalWrite(STATUS_LED, relay_state);

  if (nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength)){
    uint32_t i;
    uint32_t b;
    int num_uids = sizeof(auth_uids)/sizeof(auth_uids[0]);
    Serial.println(num_uids);
    for (i=0; i < num_uids; i++){
        for (b=0; b < 7; b++){
            if (uid[b] == auth_uids[i][b]){
                if (b == 6){
                    if (relay_state == 0) {
                        digitalWrite(RELAY_SET, HIGH);
                        delay(200);
                        digitalWrite(RELAY_SET, LOW);
                        Serial.println("Power On");
                        EEPROM.put(RELAY_MEM, 1);
                    } else {
                        digitalWrite(RELAY_RESET, HIGH);
                        delay(200);
                        digitalWrite(RELAY_RESET, LOW);
                        Serial.println("Power Off");
                        EEPROM.put(RELAY_MEM, 0);
                    }
                    EEPROM.get(RELAY_MEM, relay_state);
                    digitalWrite(STATUS_LED, relay_state);
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
