#ifndef BIRD_H
#define BIRD_H

#include <iostream>
#include <box2d/box2d.h>
#include "SFML/Graphics.hpp"
#include "utility.hpp"
#include "entity.hpp"
#include <string>

/**
 * \class Bird
 * \brief Class representing a bird in the game, derived from the Entity class.
 *
 * The Bird class extends the Entity class with specific attributes and behaviors for birds in the game,
 * such as rendering, physics setup, and special skills. It also includes the ability to track the bird's trajectory.
 */
class Bird: public Entity {
public:
    /**
     * \brief Constructor for the Bird class.
     * \param world Reference to the Box2D world for the bird's physics.
     * \param position Initial position of the bird.
     * \param sfb2_scale Scale factor for Box2D to SFML conversion.
     * \param width Width of the bird.
     * \param height Height of the bird.
     * \param image_path Path to the image file used for the bird's texture.
     * \param density Density of the bird, affects physics simulation.
     * \param friction Friction of the bird, affects movement and interactions.
     * \param type String to represent the bird type.
     */
    Bird(b2World& world, sf::Vector2f position, const float sfb2_scale, const float width, const float height, const std::string& image_path, const float density, const float friction, std::string type);

    /**
     * \brief Destructor for the Bird class.
     */
    ~Bird();

    /**
     * \brief Sets up the SFML properties for the bird.
     * \param window Reference to the SFML window for rendering setup.
     */
    void SFMLSetup(const sf::RenderWindow& window);

    /**
     * \brief Renders the bird using SFML.
     * \param window SFML RenderWindow where the bird will be drawn.
     */
    virtual void Render(sf::RenderWindow& window);

    /**
     * \brief Activates the bird's special skill.
     * \param event SFML event triggering the skill.
     * \param window Reference to the SFML window for rendering.
     */
    virtual void UseSkill(const sf::Event& event, const sf::RenderWindow& window){};

    /**
     * \brief Removes any particles or effects associated with the bird.
     */
    virtual void RemoveParticles(){};

    /**
     * \brief Adds a point to the bird's trajectory path.
     * This method helps to visualize the path taken by the bird.
     */
    void addTrajectoryPoint();

    /**
     * \brief Gets the bird's trajectory points.
     * \return A vector of SFML Vector2f representing the trajectory points.
     */
    std::vector<sf::Vector2f> GetTrajectoryPoints();

public:
    b2Body* body; /*!< Box2D body representing the bird in the physics simulation. */
    sf::Texture texture; /*!< Texture of the bird for rendering. */
    sf::Sprite sprite; /*!< Sprite representing the bird. */
    
    const float width; /*!< Width of the bird. */
    const float height; /*!< Height of the bird. */
    std::string image_path; /*!< Path to the bird's texture image. */

    bool isDone = false; /*!< Flag to indicate if the bird's action is complete. */
    
    b2World* world; /*!< Reference to the Box2D world. */

    std::string type; /*!< Type of the bird. */

    std::vector<sf::Vector2f> trajectoryPoints; /*!< Vector of SFML Vector2f for the bird's trajectory points. */
    static constexpr float MIN_DISTANCE = 10.0f; /*!< Minimum distance for trajectory points. */

};

#endif // BIRD_H
