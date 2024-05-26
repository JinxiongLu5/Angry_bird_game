#include "ground.hpp"

Ground::Ground(sf::Vector2f position,  const float sfb2_scale, const float boundary_width, const float boundary_height, const float density, const float friction) :
    Entity(position, sfb2_scale, density, friction), boundary_width(boundary_width), boundary_height(boundary_height) {}

void Ground::Box2dSetup(b2World& world) {
    // Ground
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position = toB2Vec2(position, sfb2_scale);  
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    // Define the ground shape.
    b2EdgeShape edgeShape;
    // Define fixture for the ground
    b2FixtureDef groundFixtureDef;
    groundFixtureDef.density = density; // Since it's static and shouldn't move
    groundFixtureDef.friction = friction; // Set the desired friction value here

    const float ROOF_HEIGHT = - 1 * boundary_height/sfb2_scale;

    // ground
    edgeShape.SetTwoSided(b2Vec2(0.0f, boundary_height/sfb2_scale), b2Vec2(boundary_width/sfb2_scale, boundary_height/sfb2_scale));
    groundFixtureDef.shape = &edgeShape;
    groundBody->CreateFixture(&groundFixtureDef);

    // left wall
    edgeShape.SetTwoSided(b2Vec2(0.0f, ROOF_HEIGHT), b2Vec2(0.0f, boundary_height/sfb2_scale));
    groundFixtureDef.shape = &edgeShape;
    groundBody->CreateFixture(&groundFixtureDef);

    // roof
    edgeShape.SetTwoSided(b2Vec2(0.0f, ROOF_HEIGHT), b2Vec2(boundary_width/sfb2_scale, ROOF_HEIGHT));
    groundFixtureDef.shape = &edgeShape;
    groundBody->CreateFixture(&groundFixtureDef);

    // right wall
    edgeShape.SetTwoSided(b2Vec2(boundary_width/sfb2_scale, ROOF_HEIGHT), b2Vec2(boundary_width/sfb2_scale, boundary_height/sfb2_scale));
    groundFixtureDef.shape = &edgeShape;
    groundBody->CreateFixture(&groundFixtureDef);

    body = groundBody;
}
