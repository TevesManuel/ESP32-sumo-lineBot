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
        LM298(uint8_t enableA, uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4, uint8_t enableB);
        void setup();
};