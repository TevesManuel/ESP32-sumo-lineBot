#include <HC_SR04/HC_SR04.h>
#include <Arduino.h>

typedef struct Motor
{
    uint8_t in1;
    uint8_t in2;
    uint8_t enablePin;
}Motor;

class LM298
{
    private:
        Motor right;
        Motor left;
    public:
        LM298(uint8_t enableA, uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4, uint8_t enableB)
        {
            this->right.enablePin = enableA;
            this->right.in1 = in1;
            this->right.in2 = in2;
            this->left.enablePin = enableB;
            this->left.in1 = in3;
            this->left.in2 = in4;
        }
        void setup()
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
};

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