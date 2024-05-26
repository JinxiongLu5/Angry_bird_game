#include "pig.hpp"

Pig::Pig(sf::Vector2f position, const float sfb2_scale, const float width, const float height, const std::string& image_path, const float density, const float friction, int health) :
    Obstacle(position, sfb2_scale, width, height, "../media/pig.png", density, friction, health) {}

bool Pig::ShouldBeRemoved(ContactListener& contactListener, b2World& world, ScoreManager& scoreManager, sf::Sound& destroyed_sound, Explosion& explosion, sf::RenderWindow& window) {
    // Check if this body is in the set of bodies to destroy
    if (contactListener.bodiesToDestroy.find(body) != contactListener.bodiesToDestroy.end()) {

        health -= 1;
        contactListener.bodiesToDestroy.erase(body);

        if (health <= 0) {
            destroyed_sound.play();
            explosion.Render(window, position);

            isDestroyed = true; // Mark for destruction so it won't be rendered or updated again

            // Remove the body from the set to avoid trying to destroy it again
            contactListener.bodiesToDestroy.erase(body);
            scoreManager.addPoints(1);
            scoreManager.setEnemiesLeft(scoreManager.getEnemiesLeft() - 1);

            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}