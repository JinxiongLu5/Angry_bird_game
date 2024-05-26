#include "utility.hpp"

bool isPointInsideCircle(const sf::Vector2f& point, const sf::CircleShape& circle)
{
    sf::Vector2f center = circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius());
    float distance = std::sqrt(std::pow(point.x - center.x, 2) + std::pow(point.y - center.y, 2));
    return distance <= circle.getRadius();
}

b2Vec2 toB2Vec2(const sf::Vector2f& v, const float scale) {
    return b2Vec2(v.x / scale, v.y / scale);
}

sf::Vector2f toSFVec2(const b2Vec2& v, const float scale) {
    return sf::Vector2f(v.x * scale, v.y * scale);
}