#include <Arduino.h>
#include <LM298/LM298.h>

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

    digitalWrite(this->right.enablePin, HIGH);
    digitalWrite(this->right.in1, HIGH);
    digitalWrite(this->right.in2, LOW);

    digitalWrite(this->left.enablePin, LOW);
    digitalWrite(this->left.in1, HIGH);
    digitalWrite(this->left.in2, LOW);
}