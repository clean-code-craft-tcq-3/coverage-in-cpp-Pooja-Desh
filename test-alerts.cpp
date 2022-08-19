#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") 
{
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(-12, 0, 35) == TOO_LOW);
  REQUIRE(inferBreach(-12, 0, 40) == TOO_LOW);
  REQUIRE(inferBreach(-12, 0, 45) == TOO_LOW);

  REQUIRE(inferBreach(47, 0, 35) == TOO_HIGH);
  REQUIRE(inferBreach(30, 0, 35) == NORMAL);

  REQUIRE(inferBreach(45, 0, 40) == TOO_HIGH);
  REQUIRE(inferBreach(35, 0, 40) == NORMAL);

  REQUIRE(inferBreach(47, 0, 45) == TOO_HIGH);
  REQUIRE(inferBreach(30, 0, 45) == NORMAL);

}

TEST_CASE("Temperature breach acoording to cooling type")
{
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -3) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 25) == NORMAL);
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 35) == TOO_HIGH);

  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -10) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 31) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 43) == TOO_HIGH);

  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -5) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 43) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 47) == TOO_HIGH);

}

TEST_CASE("Alerter via email and controller")
{
  BatteryCharacter batteryInfo;

  batteryInfo.coolingType = MED_ACTIVE_COOLING;
  REQUIRE(checkAndAlert(TO_EMAIL, batteryInfo, 43) == true);
  
  batteryInfo.coolingType = HI_ACTIVE_COOLING;
  REQUIRE(checkAndAlert(TO_CONTROLLER, batteryInfo, 43) == true);
}


