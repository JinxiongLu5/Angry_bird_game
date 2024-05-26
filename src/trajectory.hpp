#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <iostream>
#include <box2d/box2d.h>
#include "SFML/Graphics.hpp"
#include "utility.hpp"

/**
 * \class Trajectory
 * \brief Class responsible for rendering the trajectory of objects in the game.
 *
 * The Trajectory class handles the visual representation of the trajectory path of objects, such as birds, in the game.
 * It includes functionalities for rendering the trajectory using a series of points.
 */
class Trajectory {
public:
    /**
     * \brief Constructor for the Trajectory class.
     * Initializes the trajectory rendering properties.
     */
    Trajectory();

    /**
     * \brief Destructor for the Trajectory class.
     */
    ~Trajectory();

    /**
     * \brief Renders the trajectory path on the game window.
     * \param window Reference to the SFML RenderWindow where the trajectory will be drawn.
     * \param trajectoryPoints A vector of SFML Vector2f representing the points along the trajectory path.
     */
    void Render(sf::RenderWindow& window, std::vector<sf::Vector2f> trajectoryPoints);
    
public:
};

#endif // TRAJECTORY_H
