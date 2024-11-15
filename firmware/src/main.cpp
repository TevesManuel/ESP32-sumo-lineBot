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

void setup()
{
    Serial.begin(9600);
    frontTCRT5000.setup();
    hc01.setup();
    lm298.setup();
    lm298.setMotorDirection(AllMotors, Forward);
    lm298.setMotorState(AllMotors, HIGH, POWER);
    logger.setup();
}

void loop()
{
    hc01.update();
    Serial.print("[");
    Serial.print(millis());
    Serial.print("ms] ");
    Serial.println(hc01.distance);
    Serial.println(frontTCRT5000.read());
    if(hc01.distance < 20)
    {
        lm298.setMotorState(AllMotors, HIGH, 255);
    }
    if(frontTCRT5000.read())
    {
        lm298.setMotorState(AllMotors, LOW, POWER);
    }
    else
    {
        lm298.setMotorState(AllMotors, HIGH, POWER);
    }
    logger.update();
}