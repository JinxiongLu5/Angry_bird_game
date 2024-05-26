#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * \class ScoreManager
 * \brief Class responsible for managing and displaying the game score, throwables left, enemies left, and the current level.
 *
 * ScoreManager handles the game's scoring system, including tracking and updating the score and displaying game-related statistics 
 * such as the number of throwables left, enemies left, and the current level. It also manages the display of the game's result (win/lose).
 */
class ScoreManager {
public:
    /**
     * \brief Constructor for the ScoreManager class.
     * \param window Reference to the SFML RenderWindow for displaying score and game information.
     */
    ScoreManager(sf::RenderWindow& window);

    /**
     * \brief Adds points to the current score.
     * \param p The number of points to add.
     */
    void addPoints(int p);

    /**
     * \brief Sets the current score.
     * \param p The number of points to set.
     */
    void setPoints(int p);

    /**
     * \brief Sets the number of throwables left.
     * \param t The number of throwables left to set.
     */
    void setThrowablesLeft(int t);

    /**
     * \brief Sets the number of enemies left.
     * \param e The number of enemies left to set.
     */
    void setEnemiesLeft(int e);

    /**
     * \brief Sets the current level number.
     * \param l The level number to set.
     */
    void setLevel(int l);

    /**
     * \brief Draws the current score on the given window.
     * \param window SFML RenderWindow where the score will be drawn.
     */
    void drawScore(sf::RenderWindow &window);

    /**
     * \brief Draws the game result (win/lose) on the given window.
     * \param window SFML RenderWindow where the result will be drawn.
     */
    void drawResult(sf::RenderWindow &window);

    /**
     * \brief Updates the position of the score display based on the current view.
     * \param view The SFML View to align the score display with.
     */
    void updatePosition(const sf::View& view);

    /**
     * \brief Gets the number of enemies left.
     * \return The number of enemies left.
     */
    int getEnemiesLeft();

    /**
     * \brief Gets the number of throwables left.
     * \return The number of throwables left.
     */
    int getThrowablesLeft();

    /**
     * \brief Gets the current score.
     * \return The current score.
     */
    int getPoints();

private:
    int points; /*!< Current points scored in the game. */
    int throwablesLeft; /*!< Number of throwables left in the game. */
    int enemiesLeft; /*!< Number of enemies left to defeat in the game. */
    int levelNumber; /*!< Current level number in the game. */

    sf::Font font; /*!< SFML Font used for the score text. */
    sf::Text pointsText; /*!< SFML Text for displaying points. */
    sf::Text throwablesLeftText; /*!< SFML Text for displaying throwables left. */
    sf::Text enemiesLeftText; /*!< SFML Text for displaying enemies left. */
    sf::Text WinText; /*!< SFML Text for displaying the win message. */
    sf::Text LoseText; /*!< SFML Text for displaying the lose message. */
    sf::Text LevelText; /*!< SFML Text for displaying the level number. */

    sf::Texture resultTexture; /*!< SFML Texture for displaying the game result. */
    sf::Sprite resultSprite; /*!< SFML Sprite for displaying the game result. */

    void updateText(); /*!< Updates the text objects with the latest game information. */
};

#endif // SCOREMANAGER_H
