#pragma once

#include <windows.h>
#include <vector>
#include <fstream>
#include <thread>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <iostream>

#include "config.hpp"
#include "types.h"

#define FRAME_DURATION_MS(refreshRate) (1000 / refreshRate)

CONFIG config = {
    "purple",
    65,
    8, 8,
    15,
    "left_alt",
    60
};