#include <msp430.h>
#include "led.h"

void secondUpdate()  // called every 1/250 sec to call oncePerSecond once per second
{
  secondCount ++;
  if (secondCount >= 250) { // once each second
    secondCount = 0;
    oncePerSecond();
  } }
