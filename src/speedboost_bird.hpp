#ifndef SPEEDBOOSTBIRD_H
#define SPEEDBOOSTBIRD_H

#include <iostream>
#include <box2d/box2d.h>
#include "SFML/Graphics.hpp"
#include "utility.hpp"
#include "bird.hpp"

/**
 * \class SpeedBoostBird
 * \brief A specialized Bird class with a speed-boosting ability.
 *
 * SpeedBoostBird is a subclass of the Bird class that adds a speed-boosting skill.
 * This class includes methods for using its speed-boosting skill in the game.
 */
class SpeedBoostBird: public Bird {
public:
    /**
     * \brief Constructor for the SpeedBoostBird class.
     * \param position Initial position of the speed boost bird.
     * \param sfb2_scale Scale factor for Box2D to SFML conversion.
     * \param width Width of the speed boost bird.
     * \param height Height of the speed boost bird.
     * \param image_path Path to the image file used for the bird's texture.
     * \param density Density of the speed boost bird, affects physics simulation.
     * \param friction Friction of the speed boost bird, affects movement and interactions.
     * \param speedGain The gain in speed when the skill is used.
     * \param type Type of the bird, specific to speed boost bird in this case.
     */
    explicit SpeedBoostBird(b2World& world, sf::Vector2f position, const float sfb2_scale, const float width, const float height, const std::string& image_path, const float density, const float friction, float speedGain, std::string type);

    /**
     * \brief Default destructor for the SpeedBoostBird class.
     */
    ~SpeedBoostBird()=default;

    /**
     * \brief Activates the speed boost bird's special skill.
     * \param event SFML event triggering the skill.
     * \param window Reference to the SFML window for rendering.
     */
    void UseSkill(const sf::Event& event, const sf::RenderWindow& window) override;
    
public:
    bool isSkillUsed = false; /*!< Flag indicating whether the speed boost skill has been used. */
    float speedGain; /*!< The amount of speed gained when the skill is activated. */
};

#endif // SPEEDBOOSTBIRD_H
