#include <Arduino.h>

#include <USB.h>
#include <USBHIDKeyboard.h>
#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

#include <secrets.h>


// #if ARDUINO_USB_MODE
// #warning This sketch should be used when USB is in OTG mode
// void setup(){}
// void loop(){}
// #else



WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
bool isAwake;
USBHIDKeyboard kb;


void onIsAwakeChange()  {
    if (isAwake) {
        Serial.println("Handle ON!");
    }
    else {
        Serial.println("Handle OFF!");
    }
}


void setup() {
    Serial.begin(115200);
    delay(1500);
    Serial.println("Hello, I'm DomiStick!");

    ArduinoCloud.setBoardId(DEVICE_ID);
    ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
    ArduinoCloud.addProperty(isAwake, READWRITE, ON_CHANGE, onIsAwakeChange);
    ArduinoCloud.begin(ArduinoIoTPreferredConnection);
    ArduinoCloud.printDebugInfo();

    kb.begin();
    USB.begin();
}


void loop() {
    ArduinoCloud.update();
}


// #endif /* ARDUINO_USB_MODE */