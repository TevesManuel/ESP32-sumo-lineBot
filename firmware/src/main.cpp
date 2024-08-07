#include <Arduino.h>

#include <HC_SR04/HC_SR04.hpp>
#include <LM298/LM298.hpp>
#include <Logger/Logger.hpp>

Logger logger(2, 10);
HC_SR04 hc01(19, 18);
LM298 lm298(13, 12, 14, 27, 26, 25);

void setup()
{
    Serial.begin(9600);

    hc01.setup();
    lm298.setup();
    lm298.setMotorDirection(AllMotors, Forward);
    logger.setup();
}

void loop()
{
    hc01.update();
    Serial.print("[");
    Serial.print(millis());
    Serial.print("ms] ");
    Serial.println(hc01.distance);
    if(hc01.distance < 50)
    {
        lm298.setMotorState(AllMotors, LOW);
    }
    else
    {
        lm298.setMotorState(AllMotors, HIGH);
    }
    logger.update();
}