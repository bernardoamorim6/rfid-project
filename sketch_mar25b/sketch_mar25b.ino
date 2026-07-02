 #include <SPI.h>
 #define SS_PIN 10
 #define BAUD_RATE 19200
 #define CHAR_BUF 128
 #include <MFRC522.h>
 #define RST_PIN         9           // Configurable, see typical pin layout above
 #define SS_PIN          10          // Configurable, see typical pin layout above


MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

//*****************************************************************************************//
void setup() {

  pinMode(SS_PIN, OUTPUT);
   Serial.begin(BAUD_RATE);
   SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
   SPI.begin();
   delay(1000); // Give the OpenMV Cam time to bootup.

  pinMode(SS_PIN, OUTPUT);
   Serial.begin(BAUD_RATE);
   SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
   SPI.begin();
   delay(1000); // Give the OpenMV Cam time to bootup.
                                            
  mfrc522.PCD_Init();                                              // Init MFRC522 card
  Serial.println(F("Read personal data on a MIFARE PICC:"));    //shows in serial that it is ready to read
}

//*****************************************************************************************//
void loop() {

   int32_t len1 = 0;
   char buff[CHAR_BUF] = {0};
   digitalWrite(SS_PIN, LOW);
   delay(1); // Give the OpenMV Cam some time to setup to send data.
 
   if(SPI.transfer(1) == 85) { // saw sync char?
     SPI.transfer(&len1, 4); // get length
     if (len1) {
       SPI.transfer(&buff, min(len1, CHAR_BUF));
       len1 -= min(len1, CHAR_BUF);
     }
     while (len1--) SPI.transfer(0); // eat any remaining bytes
   }
 
   digitalWrite(SS_PIN, HIGH);
   Serial.print(buff);
   Serial.println();
   delay(1000); // Don't loop to quickly.


  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;

  //-------------------------------------------

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.println(F("**TAG Detected:**"));

  //-------------------------------------------

  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card

  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex

  //-------------------------------------------

  Serial.print(F("Object: "));

  byte buffer1[18];

  block = 4;
  len = 18;

  //------------------------------------------- GET FIRST NAME
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  //PRINT FIRST NAME
  for (uint8_t i = 0; i < 16; i++)
  {
    if (buffer1[i] != 32)
    {
      Serial.write(buffer1[i]);
    }
  }
  Serial.print(" ");

  //---------------------------------------- GET LAST NAME

  byte buffer2[18];
  block = 1;

  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid)); //line 834
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer2, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  //PRINT LAST NAME
  for (uint8_t i = 0; i < 16; i++) {
    Serial.write(buffer2[i] );
  }


  //----------------------------------------

  Serial.println(F("\n**End Reading**\n"));

  delay(1000); //change value if you want to read cards faster

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
//*****************************************************************************************//
