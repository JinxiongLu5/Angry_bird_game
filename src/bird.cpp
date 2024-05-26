#include "bird.hpp"

Bird::Bird(b2World& world, sf::Vector2f position, const float sfb2_scale, const float width, const float height, const std::string& image_path, const float density, const float friction, std::string type) :
    Entity(position, sfb2_scale, density, friction), width(width), height(height), image_path(image_path), type(type)  {
    
    b2BodyDef birdBodyDef;
    birdBodyDef.type = b2_staticBody; // Bird will be static initially 
    birdBodyDef.position = toB2Vec2(position, sfb2_scale); 
    b2Body* birdBody = world.CreateBody(&birdBodyDef);

    b2PolygonShape birdShape;
    birdShape.SetAsBox(width/sfb2_scale, height/sfb2_scale);
    b2FixtureDef birdFixtureDef;
    birdFixtureDef.shape = &birdShape;
    birdFixtureDef.density = density;
    birdFixtureDef.friction = friction;
    birdBody->CreateFixture(&birdFixtureDef);
    
    body = birdBody;
    }

Bird::~Bird() {
    body->GetWorld()->DestroyBody( body );
    // std::cout << "bird destructor" << std::endl;
}

void Bird::SFMLSetup(const sf::RenderWindow& window) {
    sf::Texture birdTexture;
    if (!birdTexture.loadFromFile(image_path)) {
        std::cerr << "fail to open " << image_path << std::endl;
    }
    texture = birdTexture;

    sf::Sprite birdSprite;
    birdSprite.setTexture(texture);
    birdSprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
    birdSprite.setScale(2.0 * width / birdTexture.getSize().x, 2.0 * height / birdTexture.getSize().y);
    birdSprite.setPosition(position);

    sprite = birdSprite;
}

void Bird::Render(sf::RenderWindow& window){

    b2Vec2 birdPosition = body->GetPosition();
    sprite.setPosition(toSFVec2(birdPosition, sfb2_scale));
    float birdAngle = body->GetAngle();
    sprite.setRotation(birdAngle * 180/b2_pi);  // Convert the angle from radians to degrees
    window.draw(sprite);
}


// Define the distanceBetween function
static float distanceBetween(const sf::Vector2f& a, const sf::Vector2f& b) {
    return std::sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

// Implement the addTrajectoryPoint method
void Bird::addTrajectoryPoint() {
    const sf::Vector2f& point = sprite.getPosition();
    if (trajectoryPoints.empty() || distanceBetween(trajectoryPoints.back(), point) > MIN_DISTANCE) {
        trajectoryPoints.push_back(point);
    }
}

// Implement the drawTrajectory method
const float PI = 3.14159265358979323846;

std::vector<sf::Vector2f> Bird::GetTrajectoryPoints() {
    return trajectoryPoints;
}