#include <Arduino.h>
#include "ExtendedStepper.hpp"
#include "SM_42BYG011_25.hpp"
#include "HC_SR04.hpp"
#include "HC06.hpp"
#include "Timer.hpp"
#include "custom_packets.h"

#define pwmA 3
#define pwmB 11
#define brakeA 9
#define brakeB 8
#define dirA 12
#define dirB 13

SM_42BYG011_25 stepMotor(dirA, dirB, brakeA, brakeB, pwmA, pwmB);

HC_SR04 sonicSensor[2] = { HC_SR04(A2, A3), HC_SR04(A4, A5) };

#define HC06_RX 4
#define HC06_TX 5
HC06 bluetooth(HC06_RX, HC06_TX);

Timer transmitTimer(10UL, true);

//const float ROTATION_MAX = 360.0;
//const float ROTATION_MAX = 270.0;
const float ROTATION_MAX = 180.0;
//const float ROTATION_MAX = 90.0f;

void transmitData(void)
{
    float distance[2];
    float angle;

    distance[0] = sonicSensor[0].GetDistance();
    distance[1] = sonicSensor[1].GetDistance();
    angle = stepMotor.GetAngle();

    Serial.print("distance1="); Serial.print(distance[0]); Serial.print(", "); Serial.print("angle1="); Serial.print(angle); Serial.print(", ");
    Serial.print("distance2="); Serial.print(distance[1]); Serial.print(", "); Serial.print("angle2="); Serial.print(angle + 180.0f);
    Serial.println("");

    packet_proximitydata_t pkt[2];
    packet_mkproximitydata(&pkt[0], 0, distance[0], angle);
    packet_mkproximitydata(&pkt[1], 1, distance[1], angle + 180.0f);

    bluetooth.Write((const uint8_t* const)&pkt, sizeof(pkt));
}

void restartRotation(ExtendedStepper& instance)
{
    Serial.println("Max. rotation reached. Reversing...");
    Serial.flush();

    instance.Rotate(ROTATION_MAX * -instance.GetStepDirection());
}

void setupBluetooth(void)
{
    Serial.println("Initializing Bluetooth device...");
    bluetooth.Begin(HC06::BR_9600);

    Serial.println("Verifying device");
    while(!bluetooth.Ping())
    {
        Serial.println("Failed");
        delay(500UL);
    }

    delay(500UL);
    Serial.print("Version: ");
    const char* version = bluetooth.GetVersion();
    if(version != nullptr)
    {
        Serial.println(version);
    }
    else
    {
        Serial.println("N/A");
    }

    delay(500UL);
    Serial.println("Setting baud rate");

    while(!bluetooth.SetBaudRate(HC06::BR_9600))
    {
        Serial.println("Failed");
        delay(500UL);
    }

    delay(500UL);
    Serial.println("Setting PIN");
    while(!bluetooth.SetPIN("1357"))
    {
        Serial.println("Failed");
        delay(500UL);
    }

    delay(500UL);
    Serial.println("Setting name");
    while(!bluetooth.SetName("Marvin42-Sonar"))
    {
        Serial.println("Failed");
        delay(500UL);
    }

    Serial.println("");
}

void setup(void)
{
    delay(2500);
    Serial.begin(9600, SERIAL_8N1);
    Serial.println("Initializing...");
    Serial.flush();
    delay(2500);

    setupBluetooth();
    //bluetooth.begin(9600);

    Serial.println("Initializing stepper motor...");
    stepMotor.Begin();
    stepMotor.setSpeed(10);
    stepMotor.SetOnEndRotationEvent(restartRotation);
    stepMotor.Rotate(ROTATION_MAX / 2.0);

    transmitTimer.SetTriggerCallback(transmitData);

    Serial.println("Done");
    Serial.flush();

    transmitTimer.Start();
}

void loop(void)
{
    stepMotor.UpdateRotation();
    transmitTimer.Poll();
}
