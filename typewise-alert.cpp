#include "typewise-alert.h"
#include <stdio.h>

 map<CoolingType, pair<int, int>> limit = { { CoolingType::PASSIVE_COOLING, { 0, 35 } },
{ CoolingType::HI_ACTIVE_COOLING, { 0, 45 } },
{ CoolingType::MED_ACTIVE_COOLING, { 0, 40 } }
};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

std::pair<int, int> getTemperatureBreachValues(CoolingType coolingType)
{
  std::pair<int, int> breachValues{0,0};
    map<CoolingType, pair<int, int>>::iterator it;
    pair<int, int> PAIR1;
    it = limit.find(coolingType);
    if (it == limit.end())
        printf("Limit Not Found!!");
    else
        breachValues = it->second;
  return breachValues;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  std::pair<int, int> breachValues = getTemperatureBreachValues(coolingType);
  return inferBreach(temperatureInC, breachValues.first, breachValues.second);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  switch(breachType) {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
      break;
    case NORMAL:
      break;
  }
}
