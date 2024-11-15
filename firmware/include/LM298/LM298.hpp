#include <Arduino.h>

typedef struct Motor
{
    uint8_t in1;
    uint8_t in2;
    uint8_t enablePin;
}Motor;

enum MotorDirection : uint8_t
{
    Forward,
    Backward,
};

enum MotorSpecific : uint8_t
{
    LeftMotor,
    RightMotor,
    AllMotors
};

class LM298
{
    private:
        Motor right;
        Motor left;
    public:
        LM298(uint8_t enableA, uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4, uint8_t enableB);
        void setup();
        void setMotorDirection(MotorSpecific motor, MotorDirection direction);
        void setMotorState(MotorSpecific motor, bool state, uint8_t power);

};