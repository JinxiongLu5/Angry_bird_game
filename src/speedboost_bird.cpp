#include "speedboost_bird.hpp"

SpeedBoostBird::SpeedBoostBird(b2World& world, sf::Vector2f position, const float sfb2_scale, const float width, const float height, const std::string& image_path, const float density, const float friction, float speedGain, std::string type):
    Bird(world, position, sfb2_scale, width, height, "../media/speedboost_bird.png",  density, friction, type), speedGain(speedGain) {};

void SpeedBoostBird::UseSkill(const sf::Event& event, const sf::RenderWindow& window) {

    // std::cout << "SpeedBoostBird UseSkill" << std::endl;

    b2Vec2 currentVelocity = body->GetLinearVelocity();

    // if bird is moving/flying && left mouse press && isSkillUsed == false
    if ( ((currentVelocity.x + currentVelocity.y) != 0) && (event.mouseButton.button == sf::Mouse::Left) && (isSkillUsed == false) ) {
        // Double the speed
        b2Vec2 newVelocity = 2.0f * currentVelocity;
        // Set the new velocity to the body
        body->SetLinearVelocity(newVelocity);
        isSkillUsed = true;
    }

}