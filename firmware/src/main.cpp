#include <Arduino.h>

#include <HC_SR04/HC_SR04.h>
#include <LM298/LM298.h>

HC_SR04 hc01(19, 18);
LM298 lm298(13, 12, 14, 27, 26, 25);

void setup()
{
    hc01.setup();
    lm298.setup();
    Serial.begin(9600);

    pinMode(2, OUTPUT);
}

void loop()
{
    digitalWrite(2, !digitalRead(2));
    delay(100);
    hc01.update();
    Serial.println(hc01.distance);
}