#ifndef SELECTION_H
#define SELECTION_H

extern void selectorInit();
extern int autonSelection;

enum AutonEnum {
  BLUE_1 = -1, BLUE_2 = -2, BLUE_3 = -3, BLUE_4 = -4, BLUE_5 = -5, 
  RED_1 = 1, RED_2 = 2, RED_3 = 3, RED_4 = 4, RED_5 = 5, 
  NOTHING = 10, SKILLS = 0
};

#endif