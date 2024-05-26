#ifndef STAR_H
#define STAR_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/**
 * \class Star
 * \brief Class representing a collectible star in the game.
 *
 * The Star class handles the visual representation and collection logic of stars in the game. 
 * It includes functionalities for rendering the star and checking if it has been collected by the bird.
 */
class Star {
public:
    /**
     * \brief Constructor for the Star class.
     * \param position The initial position of the star.
     * \param image_path Path to the image file used for the star's texture.
     * \param width Width of the star.
     * \param height Height of the star.
     */
    Star(sf::Vector2f position, const std::string& image_path, const float width, const float height);

    /**
     * \brief Renders the star in the game window.
     * \param window Reference to the SFML RenderWindow where the star will be drawn.
     */
    void Render(sf::RenderWindow& window);

    /**
     * \brief Checks if the star is collected based on the bird's position and collection radius.
     * \param birdPosition The current position of the bird.
     * \param collectionRadius The radius within which the bird can collect the star.
     * \return True if the star is collected, false otherwise.
     */
    bool isCollected(const sf::Vector2f& birdPosition, float collectionRadius, sf::Sound& coin_sound);

private:
    sf::Texture texture; /*!< SFML Texture for the star image. */
    sf::Sprite sprite; /*!< SFML Sprite for rendering the star. */
};

#endif // STAR_H
