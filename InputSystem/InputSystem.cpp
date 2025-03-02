#include "InputSystem.hpp"

/**
 * @brief Constructor for the InputSystem class.
 * Initializes the direction vector to zero.
 */

InputSystem::InputSystem() {
    direction = { 0.0f, 0.0f }; // Initialize direction to zero
}

/**
 * @brief Updates the input system to handle user input.
 * Checks for keyboard input and updates the direction vector accordingly.
 */
void InputSystem::Update() {
    direction = { 0.0f, 0.0f }; // Reset direction each frame

    if (IsKeyDown(KEY_RIGHT)) {
        direction.x = 1.0f; // Move right
    }
    else if (IsKeyDown(KEY_LEFT)) {
        direction.x = -1.0f; // Move left
    }
    else if (IsKeyDown(KEY_UP)) {
        direction.y = -1.0f; // Move up
    }
    else if (IsKeyDown(KEY_DOWN)) {
        direction.y = 1.0f; // Move down
    }
}

/**
 * @brief Returns the current direction vector.
 * @return The direction vector.
 */
Vector2 InputSystem::GetDirection() const {
    return direction;
}