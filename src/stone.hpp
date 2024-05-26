#ifndef STONE_H
#define STONE_H

#include <iostream>
#include <box2d/box2d.h>
#include "SFML/Graphics.hpp"
#include "utility.hpp"
#include "obstacle.hpp"

/**
 * \class Stone
 * \brief Class representing stone obstacles in the game, derived from the Obstacle class.
 *
 * The Stone class is a specific type of Obstacle, characterized by its distinct physical properties and appearance.
 * It inherits functionality from the Obstacle class and provides its own rendering implementation.
 */
class Stone : public Obstacle {
public:
    /**
     * \brief Constructor for the Stone class.
     * \param position Initial position of the stone obstacle.
     * \param sfb2_scale Scale factor for Box2D to SFML conversion.
     * \param width Width of the stone.
     * \param height Height of the stone.
     * \param image_path Path to the image file used for the stone's texture.
     * \param density Density of the stone, affects physics simulation.
     * \param friction Friction of the stone, affects movement and interactions.
     * \param health Initial health of the stone, determines its durability.
     */
    Stone(sf::Vector2f position, const float sfb2_scale, const float width, const float height, const std::string& image_path, const float density, const float friction, int health);

    /**
     * \brief Renders the stone using SFML.
     * Overrides the Render method from the Obstacle class to provide specific rendering for the stone.
     * \param window SFML RenderWindow where the stone will be drawn.
     */
    void Render(sf::RenderWindow& window) override;
};

#endif // STONE_H
