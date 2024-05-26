#ifndef PIG_H
#define PIG_H

#include <iostream>
#include <box2d/box2d.h>
#include "SFML/Graphics.hpp"
#include "utility.hpp"
#include "obstacle.hpp"
#include "scoreManager.hpp"
#include "explosion.hpp"


/**
 * \class Pig
 * \brief Class representing the pig obstacles in the game, derived from the Obstacle class.
 *
 * The Pig class extends the Obstacle class with specific behaviors and properties for pig characters in the game.
 * It includes functionality for determining when a pig should be removed from the game based on collisions and scoring.
 */
class Pig : public Obstacle {
public:
    /**
     * \brief Constructor for the Pig class.
     * \param position Initial position of the pig.
     * \param sfb2_scale Scale factor for Box2D to SFML conversion.
     * \param width Width of the pig.
     * \param height Height of the pig.
     * \param image_path Path to the image file used for the pig's texture.
     * \param density Density of the pig, affects physics simulation.
     * \param friction Friction of the pig, affects movement and interactions.
     * \param health Initial health of the pig, determines its durability.
     */
    Pig(sf::Vector2f position, const float sfb2_scale, const float width, const float height, const std::string& image_path, const float density, const float friction, int health);

    /**
     * \brief Determines if the pig should be removed from the game.
     * \param contactListener Reference to the ContactListener for collision detection.
     * \param world Reference to the Box2D world.
     * \param scoreManager Reference to the ScoreManager to update the score.
     * \param destroyed_sound SFML Sound that plays when the pig is destroyed.
     * \param explosion explosion class for animation.
     * \param window Reference to the SFML RenderWindow where the explosion will be drawn.
     * \return True if the pig should be removed, false otherwise.
     *
     * This function overrides the ShouldBeRemoved method from the Obstacle class to include scoring logic.
     */
    bool ShouldBeRemoved(ContactListener& contactListener, b2World& world, ScoreManager& scoreManager, sf::Sound& destroyed_sound, Explosion& explosion, sf::RenderWindow& window);

};

#endif // PIG_H
