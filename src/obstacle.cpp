#include "obstacle.hpp"

Obstacle::Obstacle(sf::Vector2f position, const float sfb2_scale, const float width, const float height, const std::string& image_path, const float density, const float friction, int health) :
    Entity(position, sfb2_scale, density, friction), width(width), height(height), image_path(image_path), health(health) {}

Obstacle::~Obstacle() {
    body->GetWorld()->DestroyBody( body );
}


void Obstacle::Box2dSetup(b2World& world) {
    b2BodyDef ObstacleBodyDef;
    ObstacleBodyDef.type = b2_dynamicBody;
    ObstacleBodyDef.position = toB2Vec2(position, sfb2_scale); 
    b2Body* ObstacleBody = world.CreateBody(&ObstacleBodyDef);

    b2PolygonShape ObstacleShape;
    ObstacleShape.SetAsBox(width/sfb2_scale, height/sfb2_scale);
    b2FixtureDef ObstacleFixtureDef;
    ObstacleFixtureDef.shape = &ObstacleShape;
    ObstacleFixtureDef.density = density;
    ObstacleFixtureDef.friction = friction;
    ObstacleBody->CreateFixture(&ObstacleFixtureDef);
    
    body = ObstacleBody;
    
}


void Obstacle::SFMLSetup(const sf::RenderWindow& window) {
    sf::Texture ObstacleTexture;
    if (!ObstacleTexture.loadFromFile(image_path)) {
        std::cerr << "fail to open " << image_path << std::endl;
    }
    texture = ObstacleTexture;

    sf::Sprite ObstacleSprite;
    ObstacleSprite.setTexture(texture);
    ObstacleSprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
    ObstacleSprite.setScale(2.0 * width / ObstacleTexture.getSize().x, 2.0 * height / ObstacleTexture.getSize().y);
    ObstacleSprite.setPosition(position);

    sprite = ObstacleSprite;
}

void Obstacle::Render(sf::RenderWindow& window){
    if (isDestroyed) {
        return;
    }
    b2Vec2 ObstaclePosition = body->GetPosition();
    sprite.setPosition(toSFVec2(ObstaclePosition, sfb2_scale));
    float ObstacleAngle = body->GetAngle();
    sprite.setRotation(ObstacleAngle * 180/b2_pi);  // Convert the angle from radians to degrees
    window.draw(sprite);
}

bool Obstacle::ShouldBeRemoved(ContactListener& contactListener, b2World& world, sf::Sound& destroyed_sound) {
    // Check if this body is in the set of bodies to destroy
    if (contactListener.bodiesToDestroy.find(body) != contactListener.bodiesToDestroy.end()) {

        health -= 1;
        contactListener.bodiesToDestroy.erase(body);

        if (health <= 0) {
            isDestroyed = true; // Mark for destruction so it won't be rendered or updated again
            destroyed_sound.play();
            // Remove the body from the set to avoid trying to destroy it again
            contactListener.bodiesToDestroy.erase(body);

            return true;
        } else {
            return false;
        }
    } else {
            return false;
    }
}
