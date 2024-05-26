#include "stone.hpp"

Stone::Stone(sf::Vector2f position, const float sfb2_scale, const float width, const float height, const std::string& image_path, const float density, const float friction, int health) :
    Obstacle(position, sfb2_scale, width, height, "../media/stone.png", density, friction, health) {}

void Stone::Render(sf::RenderWindow& window) {

    Obstacle::Render(window);

    if (health == 1) {
        float lineThickness = 5.0f; 
        float diagonalLength = std::sqrt(width * width + height * height);
        sf::RectangleShape line(sf::Vector2f(diagonalLength, lineThickness));
        line.setOrigin(diagonalLength / 2.0f, lineThickness / 2.0f);
        line.setPosition(sprite.getPosition());
        line.setRotation(sprite.getRotation());
        line.setFillColor(sf::Color::Black);

        window.draw(line);

    }
    
}