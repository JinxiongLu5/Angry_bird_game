#ifndef SPLITBIRD_H
#define SPLITBIRD_H

#include "bird.hpp"
#include <vector>
#include <box2d/box2d.h>
#include "SFML/Graphics.hpp"

/**
 * \class SplitBird
 * \brief A specialized Bird class that splits into smaller birds (particles).
 *
 * SplitBird is a subclass of Bird that adds the ability to split into smaller birds
 * represented as particles. This class overrides the UseSkill method to implement
 * the splitting behavior and includes methods to create and render these particles.
 */
class SplitBird : public Bird {
public:
    /**
     * \brief Constructor for the SplitBird class.
     * \param position Initial position of the split bird.
     * \param sb2_scale Scale factor for Box2D to SFML conversion.
     * \param width Width of the split bird.
     * \param height Height of the split bird.
     * \param image_path Path to the image file used for the bird's texture.
     * \param density Density of the split bird, affects physics simulation.
     * \param friction Friction of the split bird, affects movement and interactions.
     * \param type Type of the bird, specific to split bird in this case.
     */
    SplitBird(b2World& world, sf::Vector2f position, const float sb2_scale, const float width, const float height, const std::string& image_path, const float density, const float friction, std::string type);

    /**
     * \brief Destructor for the SplitBird class.
     */
    ~SplitBird();

    /**
     * \brief Activates the split bird's special skill, causing it to split into particles.
     * \param event SFML event triggering the skill.
     * \param window Reference to the SFML window for rendering.
     */
    void UseSkill(const sf::Event& event, const sf::RenderWindow& window) override;

    /**
     * \brief Creates particles representing smaller birds when the skill is used.
     * \param world Pointer to the Box2D world where the splitting occurs.
     * \param center Center point of the splitting in Box2D coordinates.
     */
    void CreateSplitBirdParticles(b2World* world, b2Vec2 center);

    /**
     * \brief Renders the split bird particles using SFML.
     * \param window SFML RenderWindow where the birds will be drawn.
     */
    void Render(sf::RenderWindow& window) override;
    void RemoveParticles() override;
    bool shouldRender = true;


private:
    std::vector<b2Body*> m_particleBodies; /*!< Vector of Box2D bodies representing the split bird particles. */
    sf::Texture particleTexture; /*!< Texture for the split bird particles. */
    std::vector<sf::Sprite> m_particleSprites; /*!< Vector of SFML Sprites for visualizing the split bird particles. */
    bool isSkillUsed = false; /*!< Flag indicating whether the split skill has been used. */
    float splitPower = 100.0f; /*!< Power of the split effect. */
    float splitRadius = 0.005f; /*!< Radius of each split particle. */
    float restitution = 0.99f; /*!< Restitution of the particles. */
    // int delayFrames = 0;
    
};

#endif // SPLITBIRD_H


