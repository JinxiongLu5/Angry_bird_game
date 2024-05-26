#include "bigger_bird.hpp"

BiggerBird::BiggerBird(b2World &world,
                       sf::Vector2f position,
                       const float sfb2_scale,
                       const float width,
                       const float height,
                       const std::string &image_path,
                       const float density,
                       const float friction,
                       float scale,
                       std::string type) :
    Bird(world, position, sfb2_scale, width, height, "../media/bigger_bird.png", density, friction, type),
    scale(scale) {};

void BiggerBird::UseSkill(const sf::Event &event, const sf::RenderWindow &window) {

  b2Vec2 currentVelocity = body->GetLinearVelocity();

  // if bird is moving/flying && left mouse press && isSkillUsed == false
  if (((currentVelocity.x + currentVelocity.y) != 0) && (event.mouseButton.button == sf::Mouse::Left) && !isSkillUsed) {

    // Double the size
    b2PolygonShape birdShape;
    birdShape.SetAsBox(scale * width / sfb2_scale, scale * height / sfb2_scale);
    b2FixtureDef birdFixtureDef;
    birdFixtureDef.shape = &birdShape;
    birdFixtureDef.density = density;
    birdFixtureDef.friction = friction;
    this->body->CreateFixture(&birdFixtureDef);
    this->sprite.setScale(scale * 2.0 * width / this->texture.getSize().x,
                          scale * 2.0 * height / this->texture.getSize().y);
    isSkillUsed = true;

  }

}