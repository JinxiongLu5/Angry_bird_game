#include "split_bird.hpp"
#include <iostream>
#include <thread>
#include <chrono>

SplitBird::SplitBird(b2World& world, sf::Vector2f position, const float sfb2_scale, const float width, const float height, const std::string& image_path, const float density, const float friction, std::string type)
    : Bird(world, position, sfb2_scale, width, height, "../media/split_bird.png", density, friction, type) {
        if (!particleTexture.loadFromFile("../media/split_bird.png")) {
            // Handle the error, for example, log the error or use a default image
            std::cout<<"wrong";
        }
    }

SplitBird::~SplitBird() {
    for (b2Body* particleBody : m_particleBodies) {
        particleBody->GetWorld()->DestroyBody(particleBody);
    }
    m_particleBodies.clear();
}

void SplitBird::UseSkill(const sf::Event& event, const sf::RenderWindow& window) {
    sf::Vector2f currentPosition = toSFVec2(body->GetPosition(), sfb2_scale);

    if ((currentPosition.x > (window.getSize().x * 0.35)) && (event.mouseButton.button == sf::Mouse::Left) && !isSkillUsed) {
        b2Vec2 center = body->GetPosition();
        
        CreateSplitBirdParticles(body->GetWorld(), center);
        isSkillUsed = true;
        // std::this_thread::sleep_for(std::chrono::seconds(3));
        // body->GetWorld()->DestroyBody( body ); 
        float upwardSpeed = 10.0f; 
        body->SetLinearVelocity(b2Vec2(0.0f, upwardSpeed));
        shouldRender = false;
    }
}

void SplitBird::CreateSplitBirdParticles(b2World* world, b2Vec2 center) {
    int numParticles = 3;
    float angleIncrement = 360.0f / numParticles;
    for (int i = 0; i < numParticles; i++) {
        // float angle = (i / static_cast<float>(numParticles)) * 2 * b2_pi;
        // b2Vec2 rayDir(sinf(angle), cosf(angle));
        float angleDegrees = angleIncrement*(1+0.1*i);
        float angleRadians = angleDegrees * (b2_pi / 180.0f); // Convert degrees to radians

        // Calculate the directional vector for the particle
        b2Vec2 rayDir(sinf(angleRadians), 0.5);

        b2BodyDef bd;
        bd.type = b2_dynamicBody;
        bd.position = center;
        bd.linearVelocity = b2Vec2((splitPower-70)*sinf(angleRadians), 0.1*splitPower);
        b2Body* particleBody = world->CreateBody(&bd);

        b2CircleShape circleShape;
        // circleShape.m_radius = particleTexture.getSize().x / 2.0f, particleTexture.getSize().y / 2.0f;

        b2FixtureDef fd;
        fd.shape = &circleShape;
        fd.density = density;
        fd.restitution = restitution;
        particleBody->CreateFixture(&fd);

        m_particleBodies.push_back(particleBody);

        sf::Sprite particleSprite;
        particleSprite.setTexture(particleTexture);
        // std::cout<<sfb2_scale;
        particleSprite.setOrigin(particleTexture.getSize().x / 2.0f, particleTexture.getSize().y / 2.0f);
        particleSprite.setScale(2.0 * width / particleTexture.getSize().x, 2.0 * height / particleTexture.getSize().y); // Adjust scale as needed
        // std::cout<<sfb2_scale;
        particleSprite.setPosition(center.x * sfb2_scale, center.y * sfb2_scale);

        m_particleSprites.push_back(particleSprite);
    }
}
void SplitBird::RemoveParticles() {
    // std::cout << "ExplosiveBird RemoveParticles" << std::endl; 
    auto itBody = m_particleBodies.begin();
    auto itShape = m_particleSprites.begin();

    while (itBody != m_particleBodies.end()) {
        if ((*itBody)->GetLinearVelocity().x  <= 0.05f) {
            // Destroy the Box2D body
            (*itBody)->GetWorld()->DestroyBody(*itBody);
            itBody = m_particleBodies.erase(itBody);

            // Remove the corresponding SFML shape
            if (itShape != m_particleSprites.end()) {
                itShape = m_particleSprites.erase(itShape);
            } else {
                ++itShape;
            }
        } else {
            ++itBody;
            ++itShape;
        }
    }
}

void SplitBird::Render(sf::RenderWindow& window) {
    if (shouldRender) {
        Bird::Render(window);
    }

    for (size_t i = 0; i < m_particleSprites.size(); ++i) {
        if (i < m_particleBodies.size()) {
            b2Vec2 bodyPos = m_particleBodies[i]->GetPosition();
            m_particleSprites[i].setPosition(bodyPos.x * sfb2_scale, bodyPos.y * sfb2_scale);
            window.draw(m_particleSprites[i]);
        }
    }
}
