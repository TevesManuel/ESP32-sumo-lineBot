#include <Arduino.h>

#include <HC_SR04/HC_SR04.hpp>
#include <LM298/LM298.hpp>
#include <TCRT5000/TCRT5000.hpp>
#include <Logger/Logger.hpp>

Logger logger(2, 10);
HC_SR04 hc01(4, 15);
LM298 lm298(13, 12, 14, 27, 26, 25);
TCRT5000 frontTCRT5000(23);

#define POWER 100

bool isBoxer = true;
bool movingForward = true;

void setup()
{
    setCpuFrequencyMhz(240);
    Serial.begin(9600);
    frontTCRT5000.setup();
    hc01.setup();
    lm298.setup();
    lm298.setMotorDirection(AllMotors, Forward);
    lm298.setMotorState(AllMotors, 0);
    logger.setup();
    //Select mode
    unsigned long initTime = millis();
    while((millis() - initTime) < 5000)
    {
        if(!frontTCRT5000.read())
        {
            isBoxer = false;
            break;
        }
    }
}

void loop()
{
    if(isBoxer)
    {
        hc01.update();

        if(hc01.distance < 20)
        {
            if(!movingForward)
            {
                lm298.setMotorState(AllMotors, 0);
                delay(100);
                lm298.setMotorDirection(AllMotors, Forward);
                lm298.setMotorState(AllMotors, 255);
                movingForward = true;
            }
        }
        else
        {
            if(movingForward)
            {
                lm298.setMotorState(AllMotors, 0);
                lm298.setMotorState(LeftMotor, 100);
                movingForward = false;
            }
        }
    }
    else
    {
        if(!frontTCRT5000.read())
        {
            if(movingForward)
            {
                lm298.setMotorState(RightMotor, 0);
                lm298.setMotorDirection(LeftMotor, Backward);
                movingForward = false;
            }
        }
        else
        {
            if(!movingForward)
            {
                lm298.setMotorState(AllMotors, POWER);
                lm298.setMotorDirection(LeftMotor, Forward);
                movingForward = true;
            }
        }   
    }
    logger.update();
}