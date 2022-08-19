#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) 
{
  if(value < lowerLimit) 
  {
    return TOO_LOW;
  }
  if(value > upperLimit) 
  {
    return TOO_HIGH;
  }
  return NORMAL;
}

double coolingTypeLowerLimit[] = {35,45,40};

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) 
{
  double lowerLimit = 0;
  double upperLimit = coolingTypeLowerLimit[coolingType];

  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

bool checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);

  bool AlertSentSuccessfully = false;
  switch(alertTarget) 
  {
    case TO_CONTROLLER:
      AlertSentSuccessfully = sendToController(breachType);
      break;
    case TO_EMAIL:
      AlertSentSuccessfully = sendToEmail(breachType);
      break;
  }
  return(AlertSentSuccessfully);
}

bool sendToController(BreachType breachType)
{
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
  return(true);
}

const char* breachMessage[3] = {"Low" , "High" , "Normal"};

bool sendToEmail(BreachType breachType) 
{
  const char* recepient = "a.b@c.com";
  printf("To: %s\n", recepient);
  printf("Hi, the temperature is %s\n",breachMessage[breachType]);
  return(true);
}
