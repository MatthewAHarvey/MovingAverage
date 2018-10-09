#ifndef MOVINGAVERAGE_H
#define MOVINGAVERAGE_H

#include <arduino.h>

template <class T>
class MovingAverage{
private:
    //int32_t *window = NULL;
    T *window = NULL;
    uint16_t windowSize = 0;
    uint8_t powerOfTwo = 0;
    uint16_t i = 0; // the current bin to use
    // int32_t sum = 0;
    T sum = T();    //int32_t average = 0;
    T average = T();
    bool windowFull = false;
    
public:
    MovingAverage(uint16_t windowSize){
        // Use a power of 2 for the window size.

        while(windowSize > 1){
            windowSize = windowSize >> 1;
            powerOfTwo++;
        }
        this->windowSize = 1;
        for(int i = 0; i < powerOfTwo; i++){
        this->windowSize *= 2;
        }
        //window = new int32_t[this->windowSize];
        window = new T[this->windowSize];
    }

    MovingAverage(uint16_t windowSize, T seed){
        while(windowSize > 1){
            windowSize = windowSize >> 1;
            powerOfTwo++;
        }
        this->windowSize = 1;
        for(int i = 0; i < powerOfTwo; i++){
        this->windowSize *= 2;
        }
        //window = new int32_t[this->windowSize];
        window = new T[this->windowSize];

        for(int i = 0; i < this->windowSize; i++){
            window[i] = seed;
            sum += seed;
        }
        windowFull = true;
    }

    ~MovingAverage(){
        delete [] window;
        reset();
    }

    T update(T newValue){
        // add a new value to the window and return the new moving average value.
        if(windowFull){
            sum -= window[i]; // remove oldest value
            window[i] = newValue;
            sum += window[i]; // add newest value
            // Serial.print("Sum: ");
            // Serial.print(sum);
            average = sum >> powerOfTwo;
            // Serial.print(", Av: ");
            // Serial.print(average);
            //i = (i + 1) % windowSize;

            if(++i == windowSize) i = 0;
            return average;
        }
        else{
            window[i] = newValue;
            sum = sum + window[i];
            // Serial.print("SUM: ");
            // Serial.print(sum);
            i++;
            average = sum / i;
            // Serial.print(", AV: ");
            // Serial.print(average);
            if(i >= windowSize){
                windowFull = true;
                i = 0;
            }
            return average;
        }
    }


    T updateFloat(T newValue){
        // add a new value to the window and return the new moving average value.
        if(windowFull){
            sum -= window[i]; // remove oldest value
            window[i] = newValue;
            sum += window[i]; // add newest value
            // Serial.print("Sum: ");
            // Serial.print(sum);
            average = sum / windowSize;
            // Serial.print(", Av: ");
            // Serial.print(average);
            // i = (i + 1) % windowSize;
            if(++i == windowSize) i = 0;
            return average;
        }
        else{
            window[i] = newValue;
            sum = sum + window[i];
            // Serial.print("SUM: ");
            // Serial.print(sum);
            i++;
            average = sum / i;
            // Serial.print(", AV: ");
            // Serial.print(average);
            if(i >= windowSize){
                windowFull = true;
                i = 0;
            }
            return average;
        }
    }
    
    T getElement(uint16_t element){
        // For example, if i = 0, the latest value added is returned. Increasing i means increasingly older values. Be careful not to ask for a value older than the length of the window
        return window[(i - 1 - element) % windowSize];
    }
    
    T getAverage(){
        return average;
    }

    uint16_t getWindowSize(){
        return windowSize;
    }

    uint16_t getWindowState(){
        // returns the numbers of slots being used.
        if(!checkWindowFull()){
            return i;
        }
        else{
            return windowSize;
        }
    }

    bool checkWindowFull(){
        return windowFull;
    }
    
    void reset(){
        // empties the window and resets the state of the class.
        i = 0;
        windowFull = false;
        sum = T();
        average = T();
    }

    T reset(T newValue){
        // resets the average and adds one element
        reset();
        for(int i; i < windowSize; i++){
            window[i] = newValue;
        }
    }

};

#endif