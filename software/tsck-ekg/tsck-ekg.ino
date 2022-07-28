#define HUGE_VAL -100000

#include "Diablo_Graph.h"
#include "SignalProcessing.h"

#define LO_PIN 5
#define DISPLAY_RESET_PIN 4

smm::DiabloGraph graph(&Serial, DISPLAY_RESET_PIN);

#define CUTOFF_FREQ 10
const double MEMORY_TIME = 1.5;
#define MAX_SAMPLE_RATE 100

smm::LowPassFilter filter(CUTOFF_FREQ);
smm::RollingMaximum maximum(MEMORY_TIME, MAX_SAMPLE_RATE);
smm::RollingMaximum minimum(MEMORY_TIME, MAX_SAMPLE_RATE);

void setup() {
   pinMode(LO_PIN, INPUT);
   Serial.begin(9600);
   graph.setup();
}

void loop()
{
  bool leadsOff = digitalRead(LO_PIN);
  if (!leadsOff) {
    double raw = ((double) analogRead(A0))/1024;
    filter.push(raw);
    maximum.push(filter.value());
    minimum.push(-filter.value());

    const double graph_max = maximum.value();
    const double graph_min = -minimum.value();

    const double signal = (filter.value() - graph_min)/(graph_max - graph_min);
    
    graph.push(signal);
  }
}
