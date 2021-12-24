#define DECODE_NEC          // Includes Apple and Onkyo
#define DECODE_DISTANCE

/*
 * Define macros for input and output pin etc.
 */
#include "PinDefinitionsAndMore.h"

#if FLASHEND <= 0x1FFF  // For 8k flash or less, like ATtiny85. Exclude exotic protocols.
#define EXCLUDE_UNIVERSAL_PROTOCOLS // Saves up to 1000 bytes program space.
#define EXCLUDE_EXOTIC_PROTOCOLS
#endif

#define INFO // To see valuable informations from universal decoder for pulse width or pulse distance protocols

#include <IRremote.hpp>

#define DELAY_AFTER_SEND 2000
#define DELAY_AFTER_LOOP 5000

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

    /*
     * Start the receiver, enable feedback LED and take LED feedback pin from the internal boards definition
     */
    IrReceiver.begin(IR_RECEIVE_PIN);
    Serial.print(F("Ready to receive IR signals of protocols: "));
    printActiveIRProtocols(&Serial);
    Serial.print(F("at pin "));
#if defined(ARDUINO_ARCH_STM32) || defined(ESP8266)
    Serial.println(IR_RECEIVE_PIN_STRING);
#else
    Serial.println(IR_RECEIVE_PIN);
#endif
    Serial.print(F("Ready to send IR signals at pin "));

#if FLASHEND >= 0x3FFF  // For 16k flash or more, like ATtiny1604
// For esp32 we use PWM generation by ledcWrite() for each pin.
#  if !defined(SEND_PWM_BY_TIMER) && !defined(USE_NO_SEND_PWM) && !defined(ESP32)
    /*
     * Print internal software PWM generation info
     */
    IrSender.enableIROut(38); // Call it with 38 kHz to initialize the values printed below
    Serial.print(F("Send signal mark duration is "));
    Serial.print(IrSender.periodOnTimeMicros);
    Serial.print(F(" us, pulse correction is "));
    Serial.print(IrSender.getPulseCorrectionNanos());
    Serial.print(F(" ns, total period is "));
    Serial.print(IrSender.periodTimeMicros);
    Serial.println(F(" us"));
#  endif

    // infos for receive
    Serial.print(RECORD_GAP_MICROS);
    Serial.println(F(" us is the (minimum) gap, after which the start of a new IR packet is assumed"));
    Serial.print(MARK_EXCESS_MICROS);
    Serial.println(F(" us are subtracted from all marks and added to all spaces for decoding"));
#endif
}
void receive_ir_data() {
    if (IrReceiver.decode()) {
        Serial.print(F("Decoded protocol: "));
        Serial.print(getProtocolString(IrReceiver.decodedIRData.protocol));
        Serial.print(F("Decoded raw data: "));
        Serial.print(IrReceiver.decodedIRData.decodedRawData, HEX);
        Serial.print(F(", decoded address: "));
        Serial.print(IrReceiver.decodedIRData.address, HEX);
        Serial.print(F(", decoded command: "));
        Serial.println(IrReceiver.decodedIRData.command, HEX);
        IrReceiver.resume();
    }
}


void loop(){
  delay((RECORD_GAP_MICROS / 1000) + 5);
      
    
   receive_ir_data();

   delay(100);
}
