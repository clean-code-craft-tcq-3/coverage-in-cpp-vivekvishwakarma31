#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(35, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(25, 20, 30) == NORMAL);
  REQUIRE(inferBreach(20, 20, 30) == NORMAL);
  REQUIRE(inferBreach(30, 20, 30) == NORMAL);
}

TEST_CASE("gets breach values based on cooling type")
{
  //Get HIGH and LOW breach values.
  std::pair<int, int> breachValues = getTemperatureBreachValues(PASSIVE_COOLING);
  REQUIRE(breachValues.first == 0);
  REQUIRE(breachValues.second == 35);
  breachValues = getTemperatureBreachValues(HI_ACTIVE_COOLING);
  REQUIRE(breachValues.first == 0);
  REQUIRE(breachValues.second == 45);
  breachValues = getTemperatureBreachValues(MED_ACTIVE_COOLING);
  REQUIRE(breachValues.first == 0);
  REQUIRE(breachValues.second == 40);
}

TEST_CASE("classifies Temperature Breach") {
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,5) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,40) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,-1) == TOO_LOW);
  
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,10) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,50) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,-1) == TOO_LOW);
  
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,20) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,45) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING,-1) == TOO_LOW);
}

TEST_CASE("Check and Alert based on cooling type)
{
  REQUIRE(checkAndAlert(TO_CONTROLLER,PASSIVE_COOLING,5) ==  ALERT_NOT_SENT);
  REQUIRE(checkAndAlert(TO_CONTROLLER,PASSIVE_COOLING,40) == ALERT_HIGH_TEMPERATURE);
  REQUIRE(checkAndAlert(TO_CONTROLLER,PASSIVE_COOLING,-1) == ALERT_LOW_TEMPERATURE);
  
  REQUIRE(checkAndAlert(TO_CONTROLLER,HI_ACTIVE_COOLING,10) ==  ALERT_NOT_SENT);
  REQUIRE(checkAndAlert(TO_CONTROLLER,HI_ACTIVE_COOLING,50) == ALERT_HIGH_TEMPERATURE);
  REQUIRE(checkAndAlert(TO_CONTROLLER,HI_ACTIVE_COOLING,-1) == ALERT_LOW_TEMPERATURE);
  
  REQUIRE(checkAndAlert(TO_CONTROLLER,MED_ACTIVE_COOLING,20) ==  ALERT_NOT_SENT);
  REQUIRE(checkAndAlert(TO_CONTROLLER,MED_ACTIVE_COOLING,45) == ALERT_HIGH_TEMPERATURE);
  REQUIRE(checkAndAlert(TO_CONTROLLER,MED_ACTIVE_COOLING,-1) == ALERT_LOW_TEMPERATURE);
  
  REQUIRE(checkAndAlert(TO_EMAIL,PASSIVE_COOLING,5) ==  ALERT_NOT_SENT);
  REQUIRE(checkAndAlert(TO_EMAIL,PASSIVE_COOLING,40) == ALERT_HIGH_TEMPERATURE);
  REQUIRE(checkAndAlert(TO_EMAIL,PASSIVE_COOLING,-1) == ALERT_LOW_TEMPERATURE);
  
  REQUIRE(checkAndAlert(TO_EMAIL,HI_ACTIVE_COOLING,10) ==  ALERT_NOT_SENT);
  REQUIRE(checkAndAlert(TO_EMAIL,HI_ACTIVE_COOLING,50) == ALERT_HIGH_TEMPERATURE);
  REQUIRE(checkAndAlert(TO_EMAIL,HI_ACTIVE_COOLING,-1) == ALERT_LOW_TEMPERATURE);
  
  REQUIRE(checkAndAlert(TO_EMAIL,MED_ACTIVE_COOLING,20) ==  ALERT_NOT_SENT);
  REQUIRE(checkAndAlert(TO_EMAIL,MED_ACTIVE_COOLING,45) == ALERT_HIGH_TEMPERATURE);
  REQUIRE(checkAndAlert(TO_EMAIL,MED_ACTIVE_COOLING,-1) == ALERT_LOW_TEMPERATURE);
}
