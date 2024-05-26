#ifndef GROUND_H
#define GROUND_H

#include <iostream>
#include <box2d/box2d.h>
#include "SFML/Graphics.hpp"
#include "utility.hpp"
#include "entity.hpp"

/**
 * \class Ground
 * \brief Class representing the ground in the game, derived from the Entity class.
 *
 * The Ground class is a subclass of Entity that specifically represents the ground
 * in the game world. It includes the functionality for setting up physics and rendering the ground.
 */
class Ground: public Entity {
public:
    /**
     * \brief Constructor for the Ground class.
     * \param position Initial position of the ground.
     * \param sfb2_scale Scale factor for Box2D to SFML conversion.
     * \param boundary_width Width of the ground.
     * \param boundary_height Height of the ground.
     * \param density Density of the ground, affects physics simulation.
     * \param friction Friction of the ground, affects movement and interactions.
     */
    Ground(sf::Vector2f position,  const float sfb2_scale, const float boundary_width, const float boundary_height,  const float density, const float friction);

    /**
     * \brief Default destructor for the Ground class.
     */
    ~Ground()=default;

    /**
     * \brief Sets up the Box2D properties for the ground.
     * \param world Reference to the Box2D world where the ground exists.
     */
    void Box2dSetup(b2World& world);
    
public:
    b2Body* body; /*!< Box2D body representing the ground in the physics simulation. */
    sf::RectangleShape RectShape; /*!< SFML RectangleShape representing the ground visually. */
    
    const float boundary_width; /*!< Width of the ground. */
    const float boundary_height; /*!< Height of the ground. */
};

#endif // GROUND_H
