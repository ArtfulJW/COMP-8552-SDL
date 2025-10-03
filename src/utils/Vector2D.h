//
// Created by User on 9/23/2025.
//

#ifndef COMP_8552_WEEK1_CLION_VECTOR2D_H
#define COMP_8552_WEEK1_CLION_VECTOR2D_H

class Vector2D {
public:
    float x = 0.0f;
    float y = 0.0f;

    Vector2D()
    {
        float x = 0.0f;
        float y = 0.0f;
    }

    Vector2D(float x, float y): x(x), y(y) {}

    // Return itself; Vector we want to return is on the left
    // Other vector we want to add is on the right
    Vector2D& operator+=(const Vector2D& vec);

    Vector2D& operator-=(const Vector2D& vec);

    Vector2D& operator*=(float scalar);

    Vector2D& operator/=(float scalar);

    Vector2D operator+(const Vector2D& vec);

    Vector2D operator-(const Vector2D& vec);

    // Vector2D has to be on the left, and scalar on the right
    Vector2D operator*(float scalar) const;

    Vector2D operator/(float scalar) const;

    // Vector2D on right, scalar on left.
    // Friend makes this a non-member function to bypass previous (*) definition
    // Still need to provide implementation in source cpp file.
    friend Vector2D operator*(float scalar, Vector2D& vec);

    bool operator==(const Vector2D& vec);

    bool operator!=(const Vector2D& vec);

    // Negation operator
    Vector2D operator-() const;

    Vector2D& normalize();
};

#endif //COMP_8552_WEEK1_CLION_VECTOR2D_H