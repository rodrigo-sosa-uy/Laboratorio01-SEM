#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "controller.c"

void trigger_valve();
void trigger_riego();
void trigger_humedad();
uint8_t map_ph(uint16_t humedad);

#endif