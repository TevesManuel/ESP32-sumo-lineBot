#include <Arduino.h>

class Logger
{
    private:
        uint8_t pin;
        uint8_t freq;
        long time;
    public:
        Logger(uint8_t pin, uint8_t freq);
        void setup();
        void update();
};