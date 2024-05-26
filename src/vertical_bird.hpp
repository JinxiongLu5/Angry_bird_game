#ifndef VERTICALBIRD_H
#define VERTICALBIRD_H

#include <iostream>
#include <box2d/box2d.h>
#include "SFML/Graphics.hpp"
#include "utility.hpp"
#include "bird.hpp"

/**
 * \class VerticalBird
 * \brief A specialized Bird class with a vertical movement skill.
 *
 * VerticalBird is a subclass of the Bird class that adds a vertical movement skill.
 * This class includes methods for using its vertical movement skill in the game.
 */
class VerticalBird : public Bird {
public:
    /**
     * \brief Constructor for the VerticalBird class.
     * \param position Initial position of the vertical bird.
     * \param sfb2_scale Scale factor for Box2D to SFML conversion.
     * \param width Width of the vertical bird.
     * \param height Height of the vertical bird.
     * \param image_path Path to the image file used for the bird's texture.
     * \param density Density of the vertical bird, affects physics simulation.
     * \param friction Friction of the vertical bird, affects movement and interactions.
     * \param type Type of the bird, specific to vertical bird in this case.
     */
    explicit VerticalBird(b2World& world, sf::Vector2f position, const float sfb2_scale, const float width, const float height, const std::string& image_path, const float density, const float friction, std::string type);

    /**
     * \brief Default destructor for the VerticalBird class.
     */
    ~VerticalBird()=default;

    /**
     * \brief Activates the vertical bird's special skill.
     * \param event SFML event triggering the skill.
     * \param window Reference to the SFML window for rendering.
     */
    void UseSkill(const sf::Event& event, const sf::RenderWindow& window) override;

    /**
     * \brief Updates the bird's size and speed when the skill is used.
     */
    // void Update() override;

private:
    bool isSkillUsed = false; /*!< Flag indicating whether the vertical movement skill has been used. */
};

#endif // VERTICALBIRD_H

