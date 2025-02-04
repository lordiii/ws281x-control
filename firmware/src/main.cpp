#include "main.h"

#include "globals.h"
#include "cli.h"
#include "led.h"
#include "gamepad.h"
#include "display.h"
#include "effects/_effects.h"

#include <Entropy.h>
#include <sensors.h>
#include <Wire.h>

// Scheduled Tasks
unsigned long taskReadSensorTemperature = 0;
unsigned long taskReadSensorCurrent = 0;
unsigned long taskReadControllerInput = 0;

unsigned long taskTimes[3] = {};

bool shouldRerenderDisplay = false;

void setup() {
    delay(1000);

    Entropy.Initialize();

    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);

    Serial.begin(115200);

    pinMode(PIN_PW_ON, OUTPUT);
    pinMode(PIN_PS_GOOD, INPUT);

    Wire.begin();

    initCLI();
    LED_init();
    FX_init();
    SENSOR_init();
    DSP_init();
}

void loop() {
    processCLI();

    if (LED_renderRequested()) {
        LED_render();
    }

    unsigned long time = millis();
    if ((time - taskReadControllerInput) > 10) {
        taskReadControllerInput = time;

        if (!GP_update()) {
            GP_clear();
            GP_enablePairing();
        } else {
            GP_disablePairing();
        }

        taskTimes[2] = millis() - taskReadControllerInput;
        return;
    }

    time = millis();
    if ((time - taskReadSensorCurrent) > 100) {
        taskReadSensorCurrent = time;

        SENSOR_update(false, true);
        taskTimes[1] = millis() - taskReadSensorCurrent;
        return;
    }

    time = millis();
    if ((time - taskReadSensorTemperature) > 1000) {
        taskReadSensorTemperature = time;

        SENSOR_update(true, false);
        taskTimes[0] = millis() - taskReadSensorTemperature;
        return;
    }


    if (shouldRerenderDisplay) {
        DSP_renderPage(nullptr);
        shouldRerenderDisplay = false;
    }

    if (Wire.getReadError()) {
        Wire.clearReadError();
    }

    if (Wire.getWriteError()) {
        Wire.clearWriteError();
    }

}
