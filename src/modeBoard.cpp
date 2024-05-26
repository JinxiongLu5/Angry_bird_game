#include "modeBoard.hpp"
modeBoard::modeBoard(sf::RenderWindow& window){
    if (!font.loadFromFile("../media/times.ttf")) {
        std::cerr << "fail to load font" << std::endl;
    }
    timeInputText.setFont(font);
    timeInputText.setCharacterSize(40); 
    timeInputText.setFillColor(sf::Color(23, 85, 230));
    collectedText.setFont(font); 
    collectedText.setCharacterSize(30);
    collectedText.setFillColor(sf::Color(23, 85, 230));
}

int modeBoard::GetGameMode(sf::RenderWindow& window) {
    int selectedMode = -1;
    sf::Texture modeBackgroundTexture;
    if (!modeBackgroundTexture.loadFromFile("../media/back_mode.png")) {
        std::cerr << "Failed to load mode background texture!" << std::endl;
    }

    // Create a sprite for the background
    sf::Sprite modeBackgroundSprite;
    modeBackgroundSprite.setTexture(modeBackgroundTexture);
    modeBackgroundSprite.setScale(static_cast<float>(window.getSize().x) / modeBackgroundTexture.getSize().x,
                                  static_cast<float>(window.getSize().y) / modeBackgroundTexture.getSize().y);

    // Create a text object to display the current input
    // sf::Text modeInputText;
    modeInputText.setFont(font);
    modeInputText.setCharacterSize(30);
    modeInputText.setFillColor(sf::Color::Black);
    modeInputText.setPosition(400.0f, 600.0f); // Set an appropriate position

    std::string modeInputString = "";

    while (window.isOpen() && selectedMode == -1) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Check for keyboard input
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Num1:
                        selectedMode = 1;
                        modeInputString = "1";
                        break;
                    case sf::Keyboard::Num2:
                        selectedMode = 2;
                        modeInputString = "2";
                        break;
                    case sf::Keyboard::Num3:
                        selectedMode = 3;
                        modeInputString = "3";
                        break;
                    // Add more cases for additional modes
                    default:
                        break;
                }
                modeInputText.setString("Selected Mode: " + modeInputString);
            }
        }

        window.clear();

        // Draw the background first
        window.draw(modeBackgroundSprite);

        // Then draw mode selection instructions
        sf::Text modeText;
        modeText.setFont(font);
        modeText.setString("Select Game Mode:\n1. Mode 1 Normal\n2. Mode 2 Time Limit\n3. Mode 3 Star collection\nPlease input 1, 2 or 3\n"); // Add more modes as needed
        modeText.setCharacterSize(30);
        modeText.setFillColor(sf::Color::Black);
        modeText.setPosition(400.0f, 100.0f); // Set the appropriate position

        window.draw(modeText);

        // Finally, draw the current input
        window.draw(modeInputText);

        window.display();
    }

    return selectedMode;
}

void modeBoard::drawText(sf::RenderWindow &window){
    window.draw(timeInputText);
    window.draw(collectedText);
}

void modeBoard::updatePosition(const sf::View& view) {
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();
    
    // Calculate new positions relative to the view's top-left corner
    sf::Vector2f topLeft = viewCenter - viewSize / 2.f;

    timeInputText.setPosition(topLeft.x + 30, topLeft.y + 140);
    collectedText.setPosition(topLeft.x + 30, topLeft.y + 170); 

}

void modeBoard::setTimeLimit(int seconds) {
    levelTimeLimit = seconds;
    levelStartTime = std::chrono::steady_clock::now();
    timeUp = false;
}

void modeBoard::updateTimer() {
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed = currentTime - levelStartTime;
    int remainingTime = levelTimeLimit - static_cast<int>(elapsed.count());
    timeInputText.setString("Time left: " + std::to_string(remainingTime) + "s");

    if (remainingTime <= 0) {
        timeUp = true;
    }
}

bool modeBoard::isTimeUp() const {
    return timeUp;
}

void modeBoard::checkStarCollection(const sf::Vector2f& birdPosition, std::vector<std::unique_ptr<Star>>& stars, sf::Sound& coin_sound){
    for (const auto& star : stars) {
        if (star->isCollected(birdPosition, 90.0, coin_sound)) {
            stars.erase(std::remove(stars.begin(), stars.end(), star), stars.end());
            collectedText.setString("Star collected: " + std::to_string(3-stars.size()));            
            break;
        }
    }
}
