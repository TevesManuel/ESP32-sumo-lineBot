#include <Arduino.h>
#include <LM298/LM298.hpp>

LM298::LM298(uint8_t enableA, uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4, uint8_t enableB)
{
    this->right.enablePin = enableA;
    this->right.in1 = in1;
    this->right.in2 = in2;
    this->left.enablePin = enableB;
    this->left.in1 = in3;
    this->left.in2 = in4;
}

void LM298::setup()
{
    pinMode(this->right.enablePin, OUTPUT);
    pinMode(this->right.in1, OUTPUT);
    pinMode(this->right.in2, OUTPUT);
    pinMode(this->left.enablePin, OUTPUT);
    pinMode(this->left.in1, OUTPUT);
    pinMode(this->left.in2, OUTPUT);

    digitalWrite(this->right.enablePin, LOW);
    digitalWrite(this->right.in1, HIGH);
    digitalWrite(this->right.in2, LOW);

    digitalWrite(this->left.enablePin, LOW);
    digitalWrite(this->left.in1, HIGH);
    digitalWrite(this->left.in2, LOW);
}

void LM298::setMotorDirection(MotorSpecific motor, MotorDirection direction)
{
    Motor * specifiedMotor = NULL;

    if(motor == LeftMotor)
    {
        specifiedMotor = &this->left;
    }
    else if(motor == RightMotor)
    {
        specifiedMotor = &this->right;
    }
    
    if(direction == Forward)
    {
        if(specifiedMotor)
        {
            digitalWrite(specifiedMotor->in1, LOW);
            digitalWrite(specifiedMotor->in2, HIGH);
        }
        else
        {
            digitalWrite(this->left.in1, LOW);
            digitalWrite(this->left.in2, HIGH);
            digitalWrite(this->right.in1, LOW);
            digitalWrite(this->right.in2, HIGH);
        }
    }
    else
    {
        if(specifiedMotor)
        {
            digitalWrite(specifiedMotor->in1, HIGH);
            digitalWrite(specifiedMotor->in2, LOW);
        }
        else
        {
            digitalWrite(this->left.in1, HIGH);
            digitalWrite(this->left.in2, LOW);
            digitalWrite(this->right.in1, HIGH);
            digitalWrite(this->right.in2, LOW);
        }
    }
}
void LM298::setMotorState(MotorSpecific motor, bool state)
{
    if(motor == LeftMotor)
    {
        digitalWrite(this->left.enablePin, state);
    }
    else if(motor == RightMotor)
    {
        digitalWrite(this->right.enablePin, state);
    }
    else
    {
        digitalWrite(this->left.enablePin, state);
        digitalWrite(this->right.enablePin, state);
    }
}