#include <Arduino.h>

#include <HC_SR04/HC_SR04.h>
#include <LM298/LM298.h>
#include <Logger/Logger.h>

Logger logger(2, 10);
HC_SR04 hc01(19, 18);
LM298 lm298(13, 12, 14, 27, 26, 25);

void setup()
{
    Serial.begin(9600);

    hc01.setup();
    lm298.setup();
    logger.setup();
}

void loop()
{
    hc01.update();
    Serial.println(hc01.distance);
    logger.update();
}