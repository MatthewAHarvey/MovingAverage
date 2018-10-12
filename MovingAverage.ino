#include "MovingAverage.h"

// Moving average example
// http://cpp.sh/3qpyo

const uint32_t baudrate = 250000;
const uint16_t windowSize = 512;
MovingAverage <int> av(windowSize);
// MovingAverage <int> avInt(windowSize);
// MovingAverage <int32_t> avInt32(windowSize);
// MovingAverage <int8_t> avInt8(windowSize);
int i = 0;

void setup(){
    Serial.begin(baudrate);
    Serial.println();
    Serial.println("Connected to MovingAverageTest.ino");
    Serial.print("windowSize: ");
    Serial.println(av.getWindowSize());
}

void loop(){
    long t0 = micros();
    long t1 = micros();
    Serial.println(t1-t0);
    t0 = micros();
    for(uint8_t j = 0; j < 100; j++){
        // av.updateFloat(i);
        //av.update(i);
        av.updateSum(i);
    }
    t1 = micros();
    Serial.println(t1-t0);

    Serial.print("Average: ");
    Serial.print(av.getAverage());
    i++;
    Serial.print(", Bins: ");
    for(int i = 0; i < av.getWindowState(); i++){
        Serial.print(av.getElement(i));
        Serial.print(", ");
    }
    Serial.println();

    delay(100);
}