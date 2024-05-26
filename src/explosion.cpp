#include "explosion.hpp"

Explosion::Explosion() {
    if (!explosionTexture.loadFromFile("../media/explosion.png")) {
        std::cerr << "Failed to load explosion texture" << std::endl;
    }
    explosionSprite.setTexture(explosionTexture);
    explosionSprite.setOrigin(explosionTexture.getSize().x / 2.0f, explosionTexture.getSize().y / 2.0f);
}

Explosion::~Explosion() {}

void Explosion::Render(sf::RenderWindow& window, const sf::Vector2f position) {

    while (explosionScale < maxExplosionScale) {
        explosionSprite.setScale(explosionScale, explosionScale);
        explosionSprite.setPosition(position);
        window.draw(explosionSprite);
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        explosionScale += explosionIncr;
    }
    explosionScale = initialExplosionScale;
}
