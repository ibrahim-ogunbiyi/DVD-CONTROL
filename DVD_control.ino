/* 
 *  The IR transmitter code.
 *  This code is a modification and part of Arduino-IR remote 
 * ***********************************************************************  
 * MIT License
 * Copyright original code(c) 2021 Armin Joachismeyer
 * 
 * Copyright modified (c) 2021 Ibrahim Ogunbiyi @folksconnect
 * 
 */

#define DECODE_NEC          // Includes Apple and Onkyo
#define DECODE_DISTANCE

#include "PinDefinitionsAndMore.h"
#if FLASHEND <= 0x1FFF  // For 8k flash or less, like ATtiny85. Exclude exotic protocols.
#define EXCLUDE_UNIVERSAL_PROTOCOLS // Saves up to 1000 bytes program space.
#define EXCLUDE_EXOTIC_PROTOCOLS
#endif

#define INFO // To see valuable informations from universal decoder for pulse width or pulse distance protocols
#include <IRremote.hpp>

#define DELAY_AFTER_SEND 2000
#define DELAY_AFTER_LOOP 5000




int incomingByte; // Variable to read incoming Serial data

void setup() {
  #if defined(_IR_MEASURE_TIMING) && defined(_IR_TIMING_TEST_PIN)
    pinMode(_IR_TIMING_TEST_PIN, OUTPUT);
#endif

    Serial.begin(115200);
#if defined(__AVR_ATmega32U4__) || defined(SERIAL_USB) || defined(SERIAL_PORT_USBVIRTUAL)  || defined(ARDUINO_attiny3217)
    delay(4000); // To be able to connect Serial monitor after reset or power up and before first print out. Do not wait for an attached Serial Monitor!
#endif
    // Just to know which program is running on my Arduino
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

// Start the infrared sender pin

#if defined(IR_SEND_PIN)
    IrSender.begin(); // Start with IR_SEND_PIN as send pin and enable feedback LED at default feedback LED pin
#else
    IrSender.begin(IR_SEND_PIN, ENABLE_LED_FEEDBACK); // Specify send pin and enable feedback LED at default feedback LED pin
#endif

Serial.print(F("Ready to send IR signals at pin "));
#if defined(ARDUINO_ARCH_STM32) || defined(ESP8266)
    Serial.println(IR_SEND_PIN_STRING);
#else
    Serial.println(IR_SEND_PIN);
#endif


}

void loop() {
   
   if (Serial.available()){
   incomingByte = Serial.read();
   
   if (incomingByte == '0'){
      Serial.println("Sending..");
      IrSender.sendNEC(0xFE01FF00, 1, 32);
      delay((RECORD_GAP_MICROS / 1000) + 5);
     }
   
   
   if (incomingByte == '1'){
      Serial.println("Sending..");
      IrSender.sendNEC(0xFE01FF00, 1, 32);
      delay((RECORD_GAP_MICROS / 1000) + 5);
     }
   
   
   if (incomingByte == 'O'|| incomingByte == 'o'){    // O --> Open 
      Serial.println ("Sending..");
      IrSender.sendNEC(0xFA05FF00, 5, 32);
      delay((RECORD_GAP_MICROS / 1000) + 5);
   }
   if  (incomingByte == 'C' || incomingByte == 'c'){ // C --> Close
      Serial.println("Sending..");
      IrSender.sendNEC(0xFA05FF00, 5, 32);
      delay((RECORD_GAP_MICROS / 1000) + 5);
   }
   if  (incomingByte == 'P' || incomingByte == 'p'){ // Play
      Serial.println("Sending..");
      IrSender.sendNEC(0xE817FF00, 17, 32);
      delay((RECORD_GAP_MICROS / 1000) + 5);
   }
   if  (incomingByte == 'Q' || incomingByte == 'q'){ // Pause the video
      Serial.println("Sending..");
      IrSender.sendNEC(0xF609FF00, 9, 32);
      delay((RECORD_GAP_MICROS / 1000) + 5);
   }
   if  (incomingByte == 's' || incomingByte == 'S'){ // Skip Forward.
      Serial.println("Sending..");
      IrSender.sendNEC(0xF20DFF00, 0xD, 32);
      delay((RECORD_GAP_MICROS / 1000) + 5);
   }
   if  (incomingByte == 'f' || incomingByte == 'F'){ // Skip Forward.
      Serial.println("Sending..");
      IrSender.sendNEC(0xF10EFF00, 0xE, 32);
      delay((RECORD_GAP_MICROS / 1000) + 5);
   }
   if  (incomingByte == 'b' || incomingByte == 'B'){ // Skip backward
      Serial.println("Sending..");
      IrSender.sendNEC(0xF00FFF00, 0xF, 32);
      delay((RECORD_GAP_MICROS / 1000) + 5);
   }
   if  (incomingByte == 'V' || incomingByte == 'v'){ // Volume Up
      Serial.println("Sending..");
      IrSender.sendNEC(0xED12FF00, 12, 32);
      delay((RECORD_GAP_MICROS / 1000) + 5);
   }
   if  (incomingByte == 'X' || incomingByte == 'x'){ // Volume down
      Serial.println("Sending..");
      IrSender.sendNEC(0xAE51FF00, 51, 32);
      delay((RECORD_GAP_MICROS / 1000) + 5);
   }

 
   }

}
