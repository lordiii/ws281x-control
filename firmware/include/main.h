#ifndef FIRMWARE_MAIN_H
#define FIRMWARE_MAIN_H

#include <SD.h>
#include <QNEthernet.h>
#include <INA226.h>
#include <tft.h>

// Temperature Sensor Values
struct SensorValues {
    float temperatureTop;
    float temperatureCenter;
    float temperatureBottom;

    float currentLine1;
    float currentLine2;
    float currentLine3;

    float busVoltageLine1;
    float busVoltageLine2;
    float busVoltageLine3;
};

struct ControllerStatus
{
    bool buttonY;
    bool buttonB;
    bool buttonA;
    bool buttonX;
    bool dpadLeft;
    bool dpadRight;
    bool dpadUp;
    bool dpadDown;
    bool shoulderL1;
    bool shoulderL2;
    bool shoulderR1;
    bool shoulderR2;

    bool miscHome;
    bool miscStart; 
    bool miscSelect;
    bool miscSystem;
    bool miscBack;
    bool miscCapture;
    bool buttonTR;
    bool buttonTL; 

    uint16_t breakForce;
    uint16_t throttleForce;
};

extern SensorValues *sensorValues;
extern ControllerStatus *controller;
extern IntervalTimer *taskRenderLeds;

bool initializeCurrentSensor(INA226 *sensor);
File getFileContents(const String& fileName);
INA226 getCurrentSensor(int id);
void fetchBusVoltageValue(INA226 sensor, TUBE_SECTION section, float *oldvalue);
void fetchCurrentValue(INA226 sensor, TUBE_SECTION section, float *oldvalue);
void fetchTemperatureValue(const uint8_t * sensor, TUBE_SECTION section, float *oldvalue);
void processControllerInputs();

#endif