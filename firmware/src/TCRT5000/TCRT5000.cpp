#include <TCRT5000/TCRT5000.hpp>

TCRT5000::TCRT5000(uint8_t pin)
{
    this->pin = pin;
}

void TCRT5000::setup()
{
    pinMode(this->pin, INPUT);
}

bool TCRT5000::read()
{
    return digitalRead(this->pin);
}