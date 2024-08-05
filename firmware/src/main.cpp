#include <Arduino.h>

#include <HC_SR04/HC_SR04.h>
#include <LM298/LM298.h>

class Logger
{
    private:
        uint8_t pin;
        uint8_t freq;
        long time;
    public:
        Logger(uint8_t pin, uint8_t freq)
        {
            this->pin = pin;
            this->freq = freq;
        }
        void setup()
        {
            pinMode(this->pin, OUTPUT);
            this->time = millis();
            digitalWrite(this->pin, HIGH);
        }
        void update()
        {
            if(millis() > this->time + ((1000/this->freq)/2))
            {
                digitalWrite(this->pin, !digitalRead(this->pin));
                time = millis();
            }
        }
};

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