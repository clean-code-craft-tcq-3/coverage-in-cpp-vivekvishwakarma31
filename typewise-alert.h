#pragma once

#include <string>
#include <utility>
#include <iterator>
#include <map>
#include <iostream>
using namespace std;

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

enum AlertStatus
{
  ALERT_NOT_SENT = 0,
  ALERT_HIGH_TEMPERATURE,
  ALERT_LOW_TEMPERATURE
};
extern map<CoolingType, pair<int, int>> limit;

AlertStatus checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

std::pair<int, int> getTemperatureBreachValues(CoolingType coolingType);

AlertStatus sendToController(BreachType breachType);
AlertStatus sendToEmail(BreachType breachType,std::string recepient);
void printOnConsole(std::string message);
