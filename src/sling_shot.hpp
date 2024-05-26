#ifndef SLINGSHOT_H
#define SLINGSHOT_H

#include <iostream>
#include <box2d/box2d.h>
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>

#include "utility.hpp"
#include "bird.hpp"
#include "entity.hpp"
#include <cmath>

/**
 * \class SlingShot
 * \brief Class representing the slingshot in the game, derived from the Entity class.
 *
 * The SlingShot class extends the Entity class with specific functionalities related to the slingshot mechanism 
 * in the game, including setup, bird launching, rendering, and managing the slingshot state.
 */
class SlingShot : public Entity {
public:
    /**
     * \brief Constructor for the SlingShot class.
     * \param position Initial position of the slingshot.
     * \param sfb2_scale Scale factor for Box2D to SFML conversion.
     * \param inner_radius Radius of the inner circle of the slingshot.
     * \param outer_radius Radius of the outer circle of the slingshot.
     * \param density Density of the slingshot, affects physics simulation.
     * \param friction Friction of the slingshot, affects interaction with birds.
     */
    SlingShot(sf::Vector2f position, const float sfb2_scale, float inner_radius, float outer_radius, const float density, const float friction);

    /**
     * \brief Default destructor for the SlingShot class.
     */
    ~SlingShot()=default;

    /**
     * \brief Sets up the SFML properties for the slingshot.
     */
    void SFMLSetup();

    /**
     * \brief Launches a bird using the slingshot.
     * \param event SFML event for user interaction.
     * \param window Reference to the SFML window.
     * \param flyBird Unique pointer to the bird to be launched.
     * \param dragging_sound Sound played during dragging.
     * \param flying_sound Sound played when bird is launched.
     */
    void Launch(const sf::Event& event, const sf::RenderWindow& window, std::unique_ptr<Bird>& flyBird, sf::Sound& dragging_sound, sf::Sound& flying_sound);

    /**
     * \brief Renders the slingshot and the bird being aimed or launched.
     * \param window Reference to the SFML window for rendering.
     * \param flyBird Unique pointer to the bird being rendered.
     */
    void Render(sf::RenderWindow& window, std::unique_ptr<Bird>& flyBird); 

    /**
     * \brief Moves the view based on the bird's position after being launched.
     * \param flyBird Unique pointer to the launched bird.
     * \param view SFML View to be adjusted.
     * \param window Reference to the SFML window.
     */
    void MoveView(std::unique_ptr<Bird>& flyBird, sf::View& view, const sf::RenderWindow& window);

    /**
     * \brief Checks if the bird has landed and resets it if necessary.
     * \param flyBird Unique pointer to the bird.
     * \param window Reference to the SFML window.
     * \param launch_position The original launching position of the bird.
     * \param ground_height Height of the ground, used to determine if the bird has landed.
     */
    void CheckAndResetBird(std::unique_ptr<Bird>& flyBird, const sf::RenderWindow& window, sf::Vector2f launch_position, const float ground_height);

    /**
     * \brief Resets the slingshot to its initial state.
     */
    void ResetState();

    /**
     * \brief Fetches a new bird for the slingshot.
     * \param flyBird Unique pointer to the new bird to be fetched.
     * \param window Reference to the SFML window.
     * \param launch_position The position where the new bird is placed.
     */
    void FetchBird(std::unique_ptr<Bird>& flyBird, const sf::RenderWindow& window, sf::Vector2f launch_position);
    
public:
    const float inner_radius; /*!< Inner radius of the slingshot. */
    const float outer_radius; /*!< Outer radius of the slingshot. */

    sf::CircleShape innerCircle; /*!< SFML CircleShape representing the inner circle of the slingshot. */
    sf::CircleShape outerCircle; /*!< SFML CircleShape representing the outer circle of the slingshot. */
    sf::Vector2f startPoint, endPoint, direction; /*!< Points and direction for launching the bird. */
    bool startDragging = false; /*!< Flag indicating if the slingshot is being dragged. */
    bool isFirstPressed = true; /*!< Flag to record the starting point of the drag. */

    bool isLaunched = false; /*!< Flag indicating if a bird has been launched. */
    bool isFetched = false; /*!< Flag indicating if a new bird has been fetched. */
};

#endif // SLINGSHOT_H
