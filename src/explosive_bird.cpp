#include "explosive_bird.hpp"

ExplosiveBird::ExplosiveBird(b2World& world, sf::Vector2f position, const float eb2_scale, const float width, const float height, const std::string& image_path, const float density, const float friction, std::string type) :
    Bird(world, position, eb2_scale, width, height, "../media/explosive_bird.png", density, friction, type) {}

ExplosiveBird::~ExplosiveBird() {
    // Clean up any remaining particles.
    for (b2Body* particlesBody : m_particleBodies) {
        particlesBody->GetWorld()->DestroyBody(particlesBody);
    }
    m_particleBodies.clear();
}

void ExplosiveBird::UseSkill(const sf::Event& event, const sf::RenderWindow& window) {

    // std::cout << "ExplosiveBird UseSkill" << std::endl;

    sf::Vector2f currentPosition = toSFVec2(body->GetPosition(), sfb2_scale);

    // if bird is moving/flying && left mouse press && isSkillUsed == false
    if ( (currentPosition.x > (window.getSize().x * 0.35)) && (event.mouseButton.button == sf::Mouse::Left) && (isSkillUsed == false) ) {

        b2Vec2 center = body->GetPosition();
        int numRays = 360;
        float blastPower = 100.0f;
        CreateExplosionParticles(body->GetWorld(), center, numRays, blastPower);

        isSkillUsed = true;
    }
}

void ExplosiveBird::CreateExplosionParticles(b2World* world, b2Vec2 center, int numRays, float blastPower) {
    for (int i = 0; i < numRays; i++) {
        float angle = (i / static_cast<float>(numRays)) * 2 * b2_pi;
        b2Vec2 rayDir(sinf(angle), cosf(angle));

        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.fixedRotation = true; // rotation not necessary
        bd.bullet = false; // prevent tunneling at high speed
        bd.linearDamping = 1; // drag due to moving through air
        bd.gravityScale = 10; // ignore gravity
        bd.position = center; // start at blast center
        bd.linearVelocity = blastPower * rayDir;
        b2Body* particlesBody = world->CreateBody(&bd);

        b2CircleShape circleShape;
        float particleRadius = 0.1;
        circleShape.m_radius = particleRadius; 

        b2FixtureDef fd;
        fd.shape = &circleShape;
        fd.density = 60 / static_cast<float>(numRays); // very high - shared across all particles
        fd.friction = 0.1; // friction not necessary
        fd.restitution = 0.99f; // high restitution to reflect off obstacles
        fd.filter.groupIndex = -1; // particles should not collide with each other
        particlesBody->CreateFixture(&fd);
        // Add the new particle to the list for tracking.
        m_particleBodies.push_back(particlesBody);

        // Create the SFML shape for the particle
        sf::CircleShape particleShape(particleRadius * sfb2_scale); // sfb2_scale is your scale factor for drawing
        particleShape.setFillColor(sf::Color(235, 115, 23));
        particleShape.setOrigin(particleRadius * sfb2_scale, particleRadius * sfb2_scale);
        particleShape.setPosition(center.x * sfb2_scale, center.y * sfb2_scale);
        // Add the new SFML shape to the list for tracking
        m_particleShapes.push_back(particleShape);
    }
}

void ExplosiveBird::RemoveParticles() {
    // std::cout << "ExplosiveBird RemoveParticles" << std::endl; 
    auto itBody = m_particleBodies.begin();
    auto itShape = m_particleShapes.begin();

    while (itBody != m_particleBodies.end()) {
        if ((*itBody)->GetLinearVelocity().x  <= 0.05f) {
            // Destroy the Box2D body
            (*itBody)->GetWorld()->DestroyBody(*itBody);
            itBody = m_particleBodies.erase(itBody);

            // Remove the corresponding SFML shape
            if (itShape != m_particleShapes.end()) {
                itShape = m_particleShapes.erase(itShape);
            } else {
                ++itShape;
            }
        } else {
            ++itBody;
            ++itShape;
        }
    }
}


void ExplosiveBird::Render(sf::RenderWindow& window) {
    // std::cout << "ExplosiveBird Render" << std::endl;

    // Render the bird itself (inherited from the Bird class)
    Bird::Render(window);

    // Update SFML shapes to match Box2D body positions
    for (size_t i = 0; i < m_particleBodies.size(); ++i) {
        b2Vec2 bodyPos = m_particleBodies[i]->GetPosition();
        m_particleShapes[i].setPosition(bodyPos.x * sfb2_scale, bodyPos.y * sfb2_scale);
    }

    // Render the explosion particles
    for (auto& shape : m_particleShapes) {
        window.draw(shape);
    }
}