#pragma once

#include "minunit.h"

void LowPassFilter_tests();
void RollingMaximum_tests();

#define RUN_TESTS()				\
  mu_run_suite(LowPassFilter_tests);		\
  mu_run_suite(RollingMaximum_tests);
