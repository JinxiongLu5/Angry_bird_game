#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <iostream>
#include <box2d/box2d.h>
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "utility.hpp"
#include "entity.hpp"

#include "contactListener.hpp"

/**
 * \class Obstacle
 * \brief Class representing obstacles in the game, derived from the Entity class.
 *
 * The Obstacle class extends the Entity class with attributes and behaviors specific to obstacles in the game,
 * such as their health, the ability to render them, and checking if they should be removed based on collisions.
 */
class Obstacle : public Entity {
public:
    /**
     * \brief Constructor for the Obstacle class.
     * \param position Initial position of the obstacle.
     * \param sfb2_scale Scale factor for Box2D to SFML conversion.
     * \param width Width of the obstacle.
     * \param height Height of the obstacle.
     * \param image_path Path to the image file used for the obstacle's texture.
     * \param density Density of the obstacle, affects physics simulation.
     * \param friction Friction of the obstacle, affects movement and interactions.
     * \param health Initial health of the obstacle, determines its durability.
     */
    Obstacle(sf::Vector2f position, const float sfb2_scale, const float width, const float height, const std::string& image_path, const float density, const float friction, int health);

    /**
     * \brief Destructor for the Obstacle class.
     */
    ~Obstacle();

    /**
     * \brief Sets up the Box2D properties for the obstacle.
     * \param world Reference to the Box2D world where the obstacle exists.
     */
    void Box2dSetup(b2World& world);

    /**
     * \brief Sets up the SFML properties for the obstacle.
     * \param window Reference to the SFML window for rendering.
     */
    void SFMLSetup(const sf::RenderWindow& window);

    /**
     * \brief Renders the obstacle using SFML.
     * \param window SFML RenderWindow where the obstacle will be drawn.
     */
    virtual void Render(sf::RenderWindow& window);

    /**
     * \brief Determines if the obstacle should be removed from the game.
     * \param contactListener Reference to the ContactListener for collision detection.
     * \param world Reference to the Box2D world.
     * \param destroyed_sound SFML Sound that plays when the obstacle is destroyed.
     * \return True if the obstacle should be removed, false otherwise.
     */
    virtual bool ShouldBeRemoved(ContactListener& contactListener, b2World& world, sf::Sound& destroyed_sound);
    
public:
    b2Body* body; /*!< Box2D body representing the obstacle in the physics simulation. */
    sf::Texture texture; /*!< Texture of the obstacle for rendering. */
    sf::Sprite sprite; /*!< Sprite representing the obstacle. */
    
    const float width; /*!< Width of the obstacle. */
    const float height; /*!< Height of the obstacle. */
    std::string image_path; /*!< Path to the obstacle's texture image. */

    bool isDestroyed = false; /*!< Flag to indicate if the obstacle is destroyed. */
    int health; /*!< Health of the obstacle, affects its durability. */
};

#endif // OBSTACLE_H
