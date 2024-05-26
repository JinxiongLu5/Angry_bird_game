#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <iostream>
#include <box2d/box2d.h>
#include "SFML/Graphics.hpp"
#include "utility.hpp"
#include <chrono>
#include <thread>

/**
 * \class Explosion
 * \brief Class representing an explosion effect in the game.
 *
 * The Explosion class handles the visual representation of an explosion effect. 
 * It includes functionalities for rendering the explosion animation and managing its properties like scale and increment.
 */
class Explosion {
public:
    /**
     * \brief Constructor for the Explosion class.
     * Initializes the explosion properties.
     */
    Explosion();

    /**
     * \brief Destructor for the Explosion class.
     */
    ~Explosion();

    /**
     * \brief Renders the explosion effect at a specified position.
     * \param window Reference to the SFML RenderWindow where the explosion will be drawn.
     * \param position SFML Vector2f indicating the position of the explosion.
     */
    void Render(sf::RenderWindow& window, const sf::Vector2f position);
    
public:
    sf::Texture explosionTexture; /*!< SFML Texture for the explosion image. */
    sf::Sprite explosionSprite; /*!< SFML Sprite for rendering the explosion. */
    float explosionScale = 0.05f; /*!< Current scale of the explosion. */
    const float maxExplosionScale = 0.07f; /*!< Maximum scale of the explosion. */
    const float explosionIncr = 0.005f; /*!< Increment value for the explosion scale per frame. */
    const float initialExplosionScale = 0.05f; /*!< Initial scale of the explosion. */
};

#endif // EXPLOSION_H
