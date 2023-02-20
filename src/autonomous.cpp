#include "lib/auton.hpp"
#include "main.h"
#include "route/route.hpp"
#include "selection.h"
void autonomous() {
  switch (autonSelection) {
    case RED_1:
      routes::auton1();
      break;
    case RED_2:
      routes::auton2();
      break;
    case RED_3:
      break;
    case RED_4:
      break;
    case RED_5:
      break;
    case BLUE_1:
      routes::auton1();
      break;
    case BLUE_2:
      routes::auton2();
      break;
    case BLUE_3:
      break;
    case BLUE_4:
      break;
    case BLUE_5:
      break;
    case SKILLS:
      routes::skills();
      break;
  }
}