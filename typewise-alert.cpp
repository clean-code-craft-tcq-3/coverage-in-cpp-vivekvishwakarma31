#include "typewise-alert.h"
#include <stdio.h>
#include <sstream>
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

AlertStatus checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  AlertStatus alertstatus = (alertTarget == TO_CONTROLLER) ? sendToController(breachType) : sendToEmail(breachType, "a.b@c.com");
  return alertstatus;
}

AlertStatus sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  std::stringstream controllerMessage;
  AlertStatus alertstatus = AlertStatus::ALERT_NOT_SENT;
   switch(breachType) {
    case TOO_LOW:
      controllerMessage<<std::hex<<header<<" : "<<breachType;
      alertstatus = AlertStatus::ALERT_LOW_TEMPERATURE;
      break;
    case TOO_HIGH:
      controllerMessage<<std::hex<<header<<" : "<<breachType;
      alertstatus = AlertStatus::ALERT_HIGH_TEMPERATURE;
      break;
    default:
     alertstatus = AlertStatus::ALERT_NOT_SENT;
     break;
  }
  printOnConsole(controllerMessage.str());
  return alertstatus;
}

AlertStatus sendToEmail(BreachType breachType, std::string recepient) {
std::string emailMessage;
 AlertStatus alertstatus = AlertStatus::ALERT_NOT_SENT;
  switch(breachType) {
    case TOO_LOW:
      emailMessage = "To: "+recepient+" .Hi, the temperature is too low";
      alertstatus = AlertStatus::ALERT_LOW_TEMPERATURE;
      break;
    case TOO_HIGH:
      emailMessage = "To: "+recepient+" .Hi, the temperature is too high";
      alertstatus = AlertStatus::ALERT_HIGH_TEMPERATURE;
      break;
   default:
     alertstatus = AlertStatus::ALERT_NOT_SENT;
     break;
  }
 printOnConsole(emailMessage);
 return alertstatus;
}
void printOnConsole(std::string message)
{
  std::cout << message << std::endl;
}
