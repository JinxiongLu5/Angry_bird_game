#ifndef EXPLOSIVEBIRD_H
#define EXPLOSIVEBIRD_H

#include <iostream>
#include <vector>
#include <box2d/box2d.h>
#include "SFML/Graphics.hpp"
#include "bird.hpp"

/**
 * \class ExplosiveBird
 * \brief A specialized Bird class with explosive abilities.
 *
 * ExplosiveBird is a subclass of the Bird class that adds explosive capabilities.
 * It includes methods for using its explosive skill, creating explosion particles, 
 * and rendering these effects in the game.
 */
class ExplosiveBird : public Bird {
public:
    /**
     * \brief Constructor for the ExplosiveBird class.
     * \param position Initial position of the explosive bird.
     * \param eb2_scale Scale factor for Box2D to SFML conversion.
     * \param width Width of the explosive bird.
     * \param height Height of the explosive bird.
     * \param image_path Path to the image file used for the bird's texture.
     * \param density Density of the explosive bird, affects physics simulation.
     * \param friction Friction of the explosive bird, affects movement and interactions.
     * \param type Type of the bird, specific to explosive bird in this case.
     */
    explicit ExplosiveBird(b2World& world, sf::Vector2f position, const float eb2_scale, const float width, const float height, const std::string& image_path, const float density, const float friction, std::string type);

    /**
     * \brief Destructor for the ExplosiveBird class.
     */
    ~ExplosiveBird();

    /**
     * \brief Activates the explosive bird's special skill.
     * \param event SFML event triggering the skill.
     * \param window Reference to the SFML window for rendering.
     */
    void UseSkill(const sf::Event& event, const sf::RenderWindow& window) override;

    /**
     * \brief Creates explosion particles in the game world.
     * \param world Pointer to the Box2D world where the explosion occurs.
     * \param center Center point of the explosion in Box2D coordinates.
     * \param numRays Number of rays (particles) to emit in the explosion.
     * \param blastPower Strength of the explosion.
     */
    void CreateExplosionParticles(b2World* world, b2Vec2 center, int numRays, float blastPower);

    /**
     * \brief Removes particles created by the explosion.
     */
    void RemoveParticles() override;

    /**
     * \brief Renders the explosive bird and its effects using SFML.
     * \param window SFML RenderWindow where the bird and effects will be drawn.
     */
    void Render(sf::RenderWindow& window) override;

public:
    std::vector<b2Body*> m_particleBodies; /*!< Vector of Box2D bodies representing the explosion particles. */
    std::vector<sf::CircleShape> m_particleShapes; /*!< Vector of SFML CircleShapes for visualizing the explosion particles. */
    bool isSkillUsed = false; /*!< Flag indicating whether the explosive skill has been used. */
};

#endif // EXPLOSIVEBIRD_H
