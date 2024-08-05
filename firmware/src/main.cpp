#include <Arduino.h>

//HC-SR04
const int ECHO = 19;
const int TRIGGER = 18;

const int ENABLE_A = 13;
const int IN1 = 12;
const int IN2 = 14;
const int IN3 = 27;
const int IN4 = 26; 
const int ENABLE_B = 25; 

volatile long duration;
volatile bool isReaded = false;

void ECHO_CBK()
{
    long nowTime = micros();
    if(digitalRead(ECHO))
    {
        duration = nowTime;
        isReaded = false;
    }
    else
    {
        duration = nowTime - duration;
        isReaded = true;
    }
}

void setup()
{
    Serial.begin(9600);

    pinMode(ECHO, INPUT);
    pinMode(TRIGGER, OUTPUT);
    pinMode(2, OUTPUT);
    digitalWrite(TRIGGER, LOW);
    attachInterrupt(digitalPinToInterrupt(ECHO), ECHO_CBK, CHANGE);

    //Motors
    pinMode(ENABLE_A, OUTPUT);
    digitalWrite(ENABLE_A, HIGH);
    pinMode(ENABLE_B, OUTPUT);
    digitalWrite(ENABLE_B, HIGH);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void getDistance()
{
    digitalWrite(2, !digitalRead(2));
    delay(100);
}

void loop()
{
    getDistance();
    if(isReaded)
    {
        int distance = duration * 0.034 / 2;
        Serial.println(distance);
        digitalWrite(TRIGGER, LOW);
        delayMicroseconds(10);
        digitalWrite(TRIGGER, HIGH);
        delayMicroseconds(10);
        digitalWrite(TRIGGER, LOW);
    }
    // if(distance <= 50)
    //   digitalWrite(ENABLE_B, LOW);
    // else
    //   digitalWrite(ENABLE_B, HIGH);
}