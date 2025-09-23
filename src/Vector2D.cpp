//
// Created by User on 9/23/2025.
//

#include "Vector2D.h"

#include <cmath>

// Member operator function so we can use += operator on the left hand side
Vector2D& Vector2D::operator+=(const Vector2D &vec) {
    this->x += vec.x;
    this->y += vec.y;
    return *this;
}

Vector2D Vector2D::operator*(float scalar) const {
    return Vector2D(x * scalar, y * scalar);
}

Vector2D & Vector2D::normalize() {
    float length = std::sqrt(x * x + y * y);
    if (length > 0) {
        this->x /= length;
        this->y /= length;
    }

    return *this;
}

// Non-member operator function
Vector2D operator*(float scalar, Vector2D& vec) {
    return Vector2D(vec.x * scalar, vec.y * scalar);
}