#include "vertical_bird.hpp"

VerticalBird::VerticalBird(b2World& world, sf::Vector2f position, const float sfb2_scale, const float width, const float height, const std::string& image_path, const float density, const float friction, std::string type) :
    Bird(world, position, sfb2_scale, width, height, "../media/vertical.png", density, friction, type) {};

void VerticalBird::UseSkill(const sf::Event& event, const sf::RenderWindow& window) {
    b2Vec2 currentVelocity = body->GetLinearVelocity();

    // if bird is moving/flying && left mouse press && isSkillUsed == false
    if ( ((currentVelocity.x + currentVelocity.y) != 0) && (event.mouseButton.button == sf::Mouse::Left) && (isSkillUsed == false) ) {
        // Tripling the size of the bird
        // sprite.setScale(sprite.getScale().x * 3, sprite.getScale().y * 3);
        
        // Setting x speed to 0 and doubling the y speed
        b2Vec2 currentVelocity = body->GetLinearVelocity();
        b2Vec2 newVelocity(0, 30.0f );
        body->SetLinearVelocity(newVelocity);

        isSkillUsed = true;
    }
}

