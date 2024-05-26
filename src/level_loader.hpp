#ifndef LEVELLOADER_H
#define LEVELLOADER_H

#include <fstream>
#include <iostream>
#include "json.hpp"
#include "bird.hpp"
#include "obstacle.hpp"
#include "wood.hpp"
#include "stone.hpp"
#include "pig.hpp"
#include <string>
#include "speedboost_bird.hpp"
#include "explosive_bird.hpp"
#include "vertical_bird.hpp"
#include "split_bird.hpp"
#include "bigger_bird.hpp"
#include "star.hpp"
#include <memory>

/**
 * \class LevelLoader
 * \brief Class responsible for loading game levels from external data sources.
 *
 * The LevelLoader class is designed to handle the loading of game objects such as obstacles, pigs, and birds 
 * from level data files. It parses level configuration files and creates game entities accordingly.
 */
class LevelLoader {
public:
    /**
     * \brief Constructor for the LevelLoader class.
     * \param sfb2_scale Scale factor for Box2D to SFML conversion.
     */
    LevelLoader(const float sfb2_scale);

    /**
     * \brief Loads obstacles into the game world.
     * \param world Reference to the Box2D world.
     * \param window Reference to the SFML RenderWindow.
     * \param obstacles Reference to a vector to store unique pointers to Obstacle objects.
     */
    void LoadObstacles(b2World& world, const sf::RenderWindow& window, std::vector<std::unique_ptr<Obstacle>>& obstacles);

    /**
     * \brief Loads pigs into the game world.
     * \param world Reference to the Box2D world.
     * \param window Reference to the SFML RenderWindow.
     * \param pigs Reference to a vector to store unique pointers to Pig objects.
     */
    void LoadPigs(b2World& world, const sf::RenderWindow& window, std::vector<std::unique_ptr<Pig>>& pigs);

    /**
     * \brief Loads birds into the game world.
     * \param world Reference to the Box2D world.
     * \param window Reference to the SFML RenderWindow.
     * \param launch_position Position to launch the birds from.
     * \param birds Reference to a vector to store unique pointers to Bird objects.
     * \param ground_height The height of the ground, used to position birds.
     */
    void LoadBirds(b2World& world, const sf::RenderWindow& window, sf::Vector2f launch_position, std::vector<std::unique_ptr<Bird>>& birds, float ground_height);

    /**
     * \brief Updates the level data based on the provided file path.
     * \param levelFilePath Path to the level data file.
     */
    void UpdateLevelData(const std::string& levelFilePath);

    /**
     * \brief Loads stars.
     * \param window Reference to the SFML RenderWindow.
     * \param stars Reference to a vector to store unique pointers to Star objects.
     */
    void LoadStars(const sf::RenderWindow& window, std::vector<std::unique_ptr<Star>>& stars);


private:
    nlohmann::json levelData; /*!< JSON object containing the level data. */
    const float sfb2_scale; /*!< Scale factor for Box2D to SFML conversion. */
};

#endif // LEVELLOADER_H
