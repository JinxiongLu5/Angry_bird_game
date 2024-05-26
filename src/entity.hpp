#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

/**
 * \class Entity
 * \brief Abstract base class for all entities in the game.
 *
 * Entity class serves as the base for all objects that will be displayed and interacted with in the game.
 * It includes basic properties like position, scale, density, and friction which are common to all entities.
 */
class Entity {
public:
    /**
     * \brief Constructor for the Entity class.
     * \param position Initial position of the entity in the SFML window.
     * \param sfb2_scale Scale factor for converting between SFML and Box2D coordinates.
     * \param density Density of the entity, used in physics calculations.
     * \param friction Friction of the entity, used in physics calculations.
     */
    Entity(sf::Vector2f position, const float sfb2_scale, const float density, const float friction) : position(position), sfb2_scale(sfb2_scale), density(density), friction(friction) {}

    /**
     * \brief Virtual destructor for the Entity class.
     */
    virtual ~Entity() {};

    /**
     * \brief Sets up the Box2D properties for the entity.
     * This function should be overridden in derived classes to customize Box2D setup.
     */
    virtual void Box2dSetup() {};

    /**
     * \brief Sets up the SFML properties for the entity.
     * This function should be overridden in derived classes to customize SFML setup.
     */
    virtual void SFMLSetup() {};

    /**
     * \brief Renders the entity using SFML.
     * This function should be overridden in derived classes to handle the rendering of the entity.
     */
    virtual void Render() {};

    /**
     * \brief Launches the entity.
     * This function should be overridden in derived classes to handle the launching of the entity.
     */
    virtual void Launch() {};

public:
    sf::Vector2f position; /*!< Position of the entity in the SFML window. */
    const float sfb2_scale; /*!< Scale factor for Box2D to SFML conversion. */
    const float density; /*!< Density of the entity, affects physics simulation. */
    const float friction; /*!< Friction of the entity, affects movement and interactions. */
};

#endif
