#include <Arduino.h>

class TCRT5000
{
    private:
        uint8_t pin;
    public:
        TCRT5000(uint8_t);
        void setup();
        bool read();
};