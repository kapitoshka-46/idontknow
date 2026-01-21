#pragma once

#include "Context.h"

enum class Direction {
    Left,
    Right,
    Up,
    Down,
};

class GameObject {
public:
    virtual void Act(Context ctx) = 0;
};