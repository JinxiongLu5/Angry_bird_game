#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <SFML/Graphics.hpp>
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

/**
 * \class ScoreBoard
 * \brief Class for managing and displaying the game's scoreboard, including local and server-based scorekeeping.
 *
 * ScoreBoard handles user interactions for inputting nicknames, uploading and retrieving scores, and displaying 
 * level scores. It manages both local score data and online score synchronization.
 */
class ScoreBoard {
public:
    /**
     * \brief Constructor for the ScoreBoard class.
     * \param window Reference to the SFML RenderWindow for user interaction.
     */
    ScoreBoard(sf::RenderWindow& window);

    /**
     * \brief Captures the player's nickname through a graphical interface.
     * \param window Reference to the SFML RenderWindow for displaying the input interface.
     */
    void GetNickName(sf::RenderWindow& window);

    /**
     * \brief Uploads the player's score for a specific level to a local file.
     * \param level The level number for which the score is being recorded.
     * \param score The player's score for the level.
     */
    void UploadScoreLocally(int level, float score);

    /**
     * \brief Displays the high scores for a specific level on the window.
     * \param level The level number for which the scores are displayed.
     * \param window Reference to the SFML RenderWindow for displaying the scores.
     */
    void DrawLevelScore(int level, sf::RenderWindow& window);

    /**
     * \brief Uploads local scores to a remote server for global ranking.
     * Involves network communication to transmit score data to the server.
     */
    void UploadScoresToServer();

    /**
     * \brief Retrieves scores from the server and merges them with local scores.
     * Involves network communication to fetch score data from the server.
     */
    void RetrieveAndMergeScores();

public:
    sf::Font font; /*!< SFML Font used for scoreboard text. */
    sf::Text nickNameText; /*!< SFML Text for displaying the player's nickname. */
    sf::Text levelScoreTitleText; /*!< SFML Text for displaying the title of the level score section. */

    std::string nickName; /*!< Nickname of the player. */
    std::string scoreFilePath = "../media/scores/local_data.json"; /*!< File path to the local score data. */

    sf::Texture nickNameTexture; /*!< SFML Texture for the nickname input interface. */
    sf::Sprite nickNameSprite; /*!< SFML Sprite for the nickname input interface. */

    sf::Texture highScoreListTexture; /*!< SFML Texture for the high score list display. */
    sf::Sprite highScoreListSprite; /*!< SFML Sprite for the high score list display. */

    /**
     * \struct PlayerScore
     * \brief Structure to store a player's name and score.
     *
     * Used for managing and displaying player scores in the game's scoreboard.
     */
    struct PlayerScore {
        std::string name; /*!< Name of the player. */
        float score; /*!< Score of the player. */
    };

};

#endif // SCOREBOARD_H
