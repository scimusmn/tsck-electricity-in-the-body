#pragma once

#include <math.h>

#ifdef UNIT_TEST
#include "FakeArduino.h"
#else
#include <Arduino.h>
#endif

#include "Queue.h"

#define PI 3.141592


namespace smm {
  class LowPassFilter {
  public:
    LowPassFilter(double cutoffFrequency)
      : prevTime(millis()), f_c(cutoffFrequency), val(0) {}

    void push(double value) {
      long time = millis();
      double dt = double(time - prevTime)/1000;
      prevTime = time;
	 
      double a = alpha(dt);
      val = a*value + (1-a)*val;
    }
    double value() { return val; }
  private:
    long prevTime;
    double f_c, val;

    double alpha(double dt) {
      return (2*PI*dt*f_c)/((2*PI*dt*f_c) + 1);
    }
  };


  class RollingMaximum {
  public:
    RollingMaximum(double memoryTime, double maxSampleRate) : memoryTime(memoryTime), queue(memoryTime * maxSampleRate)
    {
      max.timestamp = millis();
      max.value = -HUGE_VAL;
      windowSize = memoryTime * maxSampleRate;
    }

    
    void push(double value) {
      unsigned long minTime = millis() - (1000 * memoryTime);
      while(queue.front().timestamp < minTime)
	queue.pop();
      
      if (queue.size() == windowSize)
	queue.pop();

      TimePoint pt = { millis(), value };
      queue.push(pt);

      if (pt.value > max.value)
	max = pt;
    }
    

    double value() {
      unsigned long minTime = millis() - (1000 * memoryTime);
      if (max.timestamp < minTime)
	getNewMax();

      printf("[%.01f @ %d], min %d\n", max.value, max.timestamp, minTime);
      return max.value;
    }
  private:
    size_t windowSize;

    struct TimePoint {
      unsigned long timestamp;
      double value;
    };

    TimePoint max;

    double memoryTime;
    smm::Queue<TimePoint> queue;

    void getNewMax() {
      max.value = -HUGE_VAL;
      for (int i=0; i<queue.size(); i++) {
	int index = (queue.frontIndex + i) % windowSize;
	if (queue.arr[index].value > max.value)
	  max = queue.arr[index];
      }
    }
  };
}
