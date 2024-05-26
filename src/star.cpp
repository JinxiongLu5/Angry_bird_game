#include "star.hpp"
#include <iostream>
#include <cmath>

Star::Star(sf::Vector2f position, const std::string& image_path,const float width, const float height) {
    if (!texture.loadFromFile(image_path)) {
        std::cerr << "Failed to load star texture" << std::endl;
    }

    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
    sprite.setScale(2.0 * width / texture.getSize().x, 2.0 * height / texture.getSize().y);
    sprite.setPosition(position);
}

void Star::Render(sf::RenderWindow& window) {
    window.draw(sprite);
}

bool Star::isCollected(const sf::Vector2f& birdPosition, float collectionRadius, sf::Sound& coin_sound) {
    sf::Vector2f starPosition = sprite.getPosition();
    float distance = std::sqrt(std::pow(starPosition.x - birdPosition.x, 2) + std::pow(starPosition.y - birdPosition.y, 2));

    if (distance <= collectionRadius) {
        coin_sound.play();
        return true;
    } else {
        return false;
    }
}



