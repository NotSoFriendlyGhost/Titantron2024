#pragma once

#include <string>

//selector configuration
#define HUE 360
#define DEFAULT 1
#define AUTONS "Left", "Right", "Do Nothing"

namespace selector{

extern int auton;
extern const char *b[];
void init(int hue = HUE, int default_auton = DEFAULT, const char **autons = b);

}