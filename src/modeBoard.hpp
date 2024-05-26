#ifndef MODEBOARD_H
#define MODEBOARD_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

#include <chrono>
#include <thread>
#include "httplib.h"
#include "star.hpp" 

/**
 * \class modeBoard
 * \brief Class responsible for managing the game mode, timer, and star collection in the game.
 *
 * modeBoard handles user interactions for selecting the game mode, updating and displaying the game timer, and managing star collection. 
 * It provides functionalities for time management and checking star collection relative to the bird's position.
 */
class modeBoard {
public:
    /**
     * \brief Constructor for the modeBoard class.
     * \param window Reference to the SFML RenderWindow for user interaction and display.
     */
    modeBoard(sf::RenderWindow& window);

    /**
     * \brief Gets the selected game mode through a user interface.
     * \param window Reference to the SFML RenderWindow where the input interface is drawn.
     * \return Integer representing the selected game mode.
     */
    int GetGameMode(sf::RenderWindow& window);

    /**
     * \brief Updates the position of the mode board display based on the current view.
     * \param view The SFML View to align the mode board display with.
     */
    void updatePosition(const sf::View& view);

    /**
     * \brief Sets the remaining time for the level.
     * \param p The remaining time in seconds.
     */
    void setTime(int p);

    /**
     * \brief Draws the mode board text on the given window.
     * \param window SFML RenderWindow where the text will be drawn.
     */
    void drawText(sf::RenderWindow &window);

    /**
     * \brief Sets the time limit for the level.
     * \param seconds The time limit in seconds.
     */
    void setTimeLimit(int seconds);

    /**
     * \brief Updates the timer for the level, typically called each frame.
     */
    void updateTimer();

    /**
     * \brief Checks if the time limit for the level is up.
     * \return True if the time is up, false otherwise.
     */
    bool isTimeUp() const;

    /**
     * \brief Checks and updates star collection based on the bird's position.
     * \param birdPosition The current position of the bird.
     * \param stars Reference to a vector storing unique pointers to Star objects.
     */
    void checkStarCollection(const sf::Vector2f& birdPosition, std::vector<std::unique_ptr<Star>>& stars, sf::Sound& coin_sound);

public:
    sf::Font font; /*!< SFML Font used for mode board text. */
    sf::Text modeInputText; /*!< SFML Text for displaying the game mode input. */
    sf::Text timeInputText; /*!< SFML Text for displaying the time input. */
    sf::Text collectedText; /*!< SFML Text for displaying the collected items. */
    std::chrono::steady_clock::time_point levelStartTime; /*!< Start time of the current level. */
    int levelTimeLimit; /*!< Time limit for the level. */
    bool timeUp; /*!< Flag indicating if the time for the level is up. */

};

#endif
