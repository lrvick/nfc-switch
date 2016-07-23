#include <Wire.h> include <SPI.h> include <Adafruit_PN532.h> include 
#<authorized_ids.h>

Adafruit_PN532 nfc(10);

void setup(void) {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  nfc.begin();
  nfc.SAMConfig();
  Serial.println("did a config");
}

void loop(void) {
  uint8_t success = 0;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength;

  Serial.println("reading");
  if (nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength)){
    Serial.println("got thing");
    uint32_t i;
    uint32_t b;
    int num_uids = sizeof(auth_uids)/sizeof(auth_uids[0]);
    Serial.println(num_uids);
    for (i=0; i < num_uids; i++){
        for (b=0; b < 7; b++){
            if (uid[b] == auth_uids[i][b]){
                if (b == 6){
                    if (digitalRead(2) == HIGH) {
                      digitalWrite(2, LOW);
                      Serial.println("Power Off");
                    } else {
                      digitalWrite(2, HIGH);
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
  bool PN532::shutDown(){
		
		pn532_packetbuffer[0] = PN532_COMMAND_POWERDOWN;
		pn532_packetbuffer[1] = 0x8; // 8 for RF
		pn532_packetbuffer[2] = 0x00; // To eneable the IRQ, 0x00 if you dont want 
too use the IRQ
		DMSG("Shutting down RF module");

		if(HAL(writeCommand)(pn532_packetbuffer, 3))
		return pn532_packetbuffer[1];

		delay(2); //Delay to make sure the module is off.
		return (0 < HAL(readResponse)(pn532_packetbuffer, 
sizeof(pn532_packetbuffer)));
	}

}
