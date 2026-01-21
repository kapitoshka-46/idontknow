#pragma once
#include "../tank/Tank.h"
#include "GameObject.h"

class Context {
    void ChangeTankSpeed(Tank& tank, double speed);
    void ChangeGameObjectPosition(GameObject& entity, Vector2 newPos)
};