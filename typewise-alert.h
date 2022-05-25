#pragma once

#include <string>
#include <utility>
#include <iterator>
#include <map>
#include <vector>

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

extern map<CoolingType, pair<int, int>> limit;

void checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

std::pair<int, int> getTemperatureBreachValues(CoolingType coolingType);

std::string sendToController(BreachType breachType);
std::string sendToEmail(BreachType breachType,std::string recepient));
void printOnConsole(std::string message);
