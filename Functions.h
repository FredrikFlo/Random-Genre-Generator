#pragma once

#include "GenreWindow.h"

#include <thread>
#include <chrono>
#include <windows.h>
#include <random>

void Run(); // dette er hoved logikken bak hva som skjer hver frame
void CheckKeys(GenreWindow &win); // denne sjekker flere av de knappen man trykker på Pc-en
double FixDegrees(double angle); // FixDegrees vil ta en vinkel å lage den om til en vinkel mellom 0 og 360
double RandomDouble(double lower, double upper);// returns a random double between the given range 