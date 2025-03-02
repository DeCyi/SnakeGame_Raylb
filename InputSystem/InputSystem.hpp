#ifndef INPUTSYSTEM_HPP
#define INPUTSYSTEM_HPP

#include "raylib.h"

class InputSystem {
public:
    InputSystem();
    void Update();
    Vector2 GetDirection() const;

private:
    Vector2 direction;
};

#endif // INPUTSYSTEM_HPP