#include "wood.hpp"

Wood::Wood(sf::Vector2f position, const float sfb2_scale, const float width, const float height, const std::string& image_path, const float density, const float friction, int health) :
    Obstacle(position, sfb2_scale, width, height, "../media/wood.png", density, friction, health) {}
