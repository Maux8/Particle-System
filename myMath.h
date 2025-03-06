#ifndef MYMATH_H
#define MYMATH_H
#include <SFML/System/Vector2.hpp>
#include <cmath>

// Addition
inline sf::Vector2f operator+(const sf::Vector2f& left, const sf::Vector2f& right) {
    return sf::Vector2f(left.x + right.x, left.y + right.y);
}

// Subtraction
inline sf::Vector2f operator-(const sf::Vector2f& left, const sf::Vector2f& right) {
    return sf::Vector2f(left.x - right.x, left.y - right.y);
}

// Scalar multiplication
inline sf::Vector2f operator*(const sf::Vector2f& left, float right) {
    return sf::Vector2f(left.x * right, left.y * right);
}

// Scalar division
inline sf::Vector2f operator/(const sf::Vector2f& left, float right) {
    return sf::Vector2f(left.x / right, left.y / right);
}

// Dot product
inline float dot(const sf::Vector2f& left, const sf::Vector2f& right) {
    return left.x * right.x + left.y * right.y;
}

// Magnitude
inline float magnitude(const sf::Vector2f& vector) {
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

// Normalization
inline sf::Vector2f normalize(const sf::Vector2f& vector) {
    float mag = magnitude(vector);
    if (mag != 0) {
        return vector / mag;
    }
    return vector;
}

// Distance
inline float distance(const sf::Vector2f& firstPoint, const sf::Vector2f& secondPoint) {
    return magnitude(firstPoint - secondPoint);
}


#endif