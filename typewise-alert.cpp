#include "typewise-alert.h"
#include <stdio.h>
using namespace std;
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
        printOnConsole("Limit Not Found!!");
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

  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  std::string alertMessage = (alertTarget == TO_CONTROLLER) ? sendToController(breachType) : sendToEmail(breachType, "a.b@c.com");
  printOnConsole(alertMessage);
}

std::string sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  std::stringstream controllerMessage;
  ss<<std::hex<<header<<" : "<<breachType;
  return controllerMessage.str();
}

std::string sendToEmail(BreachType breachType, std::string recepient)) {
std::string emailMessage;
  switch(breachType) {
    case TOO_LOW:
      emailMessage = "To: "+recepient+" .Hi, the temperature is too low";
      break;
    case TOO_HIGH:
      emailMessage = "To: "+recepient+" .Hi, the temperature is too high";
      break;
  }
  return emailMessage;
}
void printOnConsole(std::string message)
{
  std::cout << message << std::endl;
}
