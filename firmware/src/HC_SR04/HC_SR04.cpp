#include <Arduino.h>

#include <HC_SR04/HC_SR04.h>

HC_SR04* HC_SR04::instance = nullptr;

void HC_SR04::isrCbk()
{
    if (instance)
    {
        instance->handleInterrupt();
    }
}

void HC_SR04::handleInterrupt()
{
    long nowTime = micros();
    if(digitalRead(this->echoPin))
    {
        this->duration = nowTime;
        this->isReaded = false;
    }
    else
    {
        this->duration = nowTime - this->duration;
        this->isReaded = true;
    }
}
HC_SR04::HC_SR04(uint8_t echoPin, uint8_t triggerPin)
{
    this->echoPin = echoPin;
    this->triggerPin = triggerPin;
}
void HC_SR04::setup()
{
    pinMode(this->echoPin, INPUT);
    pinMode(this->triggerPin, OUTPUT);
    digitalWrite(this->triggerPin, LOW);
    this->instance = this;
    attachInterrupt(digitalPinToInterrupt(this->echoPin), isrCbk, CHANGE);
    
    digitalWrite(this->triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(this->triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->triggerPin, LOW);
    Serial.println("Setup ended");
}
void HC_SR04::update()
{
    if(this->isReaded)
    {
        this->distance = duration * 0.034 / 2;
        digitalWrite(this->triggerPin, LOW);
        delayMicroseconds(2);
        digitalWrite(this->triggerPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(this->triggerPin, LOW);
    }
}