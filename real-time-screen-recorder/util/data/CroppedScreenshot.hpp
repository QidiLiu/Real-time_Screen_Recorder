#pragma once

#include "util/util.h"

struct CroppedScreenshot : public IData {
    int value;

    CroppedScreenshot() : value(0) {}
};

