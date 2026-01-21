#include "GameObject.h"
#include <raylib.h>

class Tank : GameObject {
private:
    double speed = 30;
    Vector2 pos;

public:
    void Move(Direction direction);
};