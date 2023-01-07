#pragma once
#include "AccelStepper.h"

// This file is not used in any way at the moment, kept in the folder for future development

// Turns the magnet on
void turnOnMag() {
  digitalWrite(11, HIGH);
  digitalWrite(10 , LOW);
}
// Turns the magnet off
void turnOffMag() {
  digitalWrite(11, LOW);
  digitalWrite(10, LOW);
}