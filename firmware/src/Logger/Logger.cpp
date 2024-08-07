#include <Arduino.h>
#include <Logger/Logger.hpp>

Logger::Logger(uint8_t pin, uint8_t freq)
{
    this->pin = pin;
    this->freq = freq;
}
void Logger::setup()
{
    pinMode(this->pin, OUTPUT);
    this->time = millis();
    digitalWrite(this->pin, HIGH);
}
void Logger::update()
{
    if(millis() > this->time + ((1000/this->freq)/2))
    {
        digitalWrite(this->pin, !digitalRead(this->pin));
        time = millis();
    }
}