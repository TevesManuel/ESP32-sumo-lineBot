#include <Arduino.h>

class HC_SR04
{
    private:
        uint8_t echoPin;
        uint8_t triggerPin;
        static HC_SR04* instance;
        bool isReaded = false;
        volatile long duration;

        static void isrCbk();
        void handleInterrupt();
    public:
        uint16_t distance = 0;
        HC_SR04(uint8_t echoPin, uint8_t triggerPin);
        void setup();
        void update();
};
