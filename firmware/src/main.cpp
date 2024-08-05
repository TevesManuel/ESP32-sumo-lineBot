#include <Arduino.h>

class HC_SR04
{
    private:
        uint8_t echoPin;
        uint8_t triggerPin;
        static HC_SR04* instance;
        bool isReaded = false;
        volatile long duration;

        static void isrCbk()
        {
            if (instance)
            {
                instance->handleInterrupt();
            }
        }

        void handleInterrupt()
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
    public:
        uint16_t distance = 0;
        HC_SR04(uint8_t echoPin, uint8_t triggerPin)
        {
            this->echoPin = echoPin;
            this->triggerPin = triggerPin;
        }
        void setup()
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
        void update()
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
};

HC_SR04* HC_SR04::instance = nullptr;

volatile long duration;
volatile bool isReaded = false;

HC_SR04 hc01(19, 18);

void setup()
{
    hc01.setup();
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