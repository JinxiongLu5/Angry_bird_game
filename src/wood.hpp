#ifndef WOOD_H
#define WOOD_H

#include <iostream>
#include <box2d/box2d.h>
#include "SFML/Graphics.hpp"
#include "utility.hpp"
#include "obstacle.hpp"

/**
 * \class Wood
 * \brief Class representing wooden obstacles in the game, derived from the Obstacle class.
 *
 * The Wood class is a type of Obstacle, specific to wooden structures in the game.
 * It inherits common obstacle features and properties from the Obstacle class and can be customized further if needed.
 */
class Wood : public Obstacle {
public:
    /**
     * \brief Constructor for the Wood class.
     * \param position Initial position of the wooden obstacle.
     * \param sfb2_scale Scale factor for Box2D to SFML conversion.
     * \param width Width of the wooden obstacle.
     * \param height Height of the wooden obstacle.
     * \param image_path Path to the image file used for the wood's texture.
     * \param density Density of the wood, affects physics simulation.
     * \param friction Friction of the wood, affects movement and interactions.
     * \param health Initial health of the wood, determines its durability.
     */
    Wood(sf::Vector2f position, const float sfb2_scale, const float width, const float height, const std::string& image_path, const float density, const float friction, int health);

    // Destructor is defaulted in this class; no specific destruction needed.
    // ~Wood()=default;

};

#endif // WOOD_H
