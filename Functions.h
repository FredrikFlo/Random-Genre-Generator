#pragma once

#include "GenreWindow.h"

#include <thread>
#include <chrono>
#include <windows.h>
#include <random>

void Run();
void CheckKeys(GenreWindow &win);
double RandomDouble(double lower, double upper);// returns a random double between the given range 