#include "scoreManager.hpp"

ScoreManager::ScoreManager(sf::RenderWindow& window) : points(0), throwablesLeft(0), enemiesLeft(0) {
    // Initialize the text objects
    if (!font.loadFromFile("../media/times.ttf")) {
        std::cerr << "fail to load font" << std::endl;
    }

    // Set up the text objects with the loaded font
    pointsText.setFont(font);
    throwablesLeftText.setFont(font);
    enemiesLeftText.setFont(font);
    WinText.setFont(font);
    LoseText.setFont(font);
    LevelText.setFont(font);

    // Set character size, color, and initial string
    pointsText.setCharacterSize(40);
    pointsText.setFillColor(sf::Color(23, 85, 230));
    pointsText.setString("Points: 0");

    throwablesLeftText.setCharacterSize(40);
    throwablesLeftText.setFillColor(sf::Color(23, 85, 230));
    throwablesLeftText.setString("Throwables: 0");

    enemiesLeftText.setCharacterSize(40);
    enemiesLeftText.setFillColor(sf::Color(23, 85, 230));
    enemiesLeftText.setString("Enemies: 0");

    LevelText.setCharacterSize(40);
    LevelText.setFillColor(sf::Color(250, 138, 17));
    LevelText.setString("Level: 0");

    WinText.setCharacterSize(40);
    WinText.setFillColor(sf::Color(23, 85, 230));
    WinText.setString("");

    LoseText.setCharacterSize(40);
    LoseText.setFillColor(sf::Color(23, 85, 230));
    LoseText.setString("");

    // Set the position of the texts
    pointsText.setPosition(30, 20);
    throwablesLeftText.setPosition(30, 60);
    enemiesLeftText.setPosition(30, 100);
    WinText.setPosition(300 , window.getSize().y / 2.0);
    LoseText.setPosition(300 , window.getSize().y / 2.0);
    LevelText.setPosition(window.getSize().x / 2.0, 10);

    // load result background image
    if (!resultTexture.loadFromFile("../media/result.png")) {std::cerr << "Failed to load highScore_list background texture!" << std::endl;}
    resultSprite.setTexture(resultTexture);
    resultSprite.setScale( static_cast<float>(window.getSize().x) / resultTexture.getSize().x, static_cast<float>(window.getSize().y) / resultTexture.getSize().y); 

}

void ScoreManager::addPoints(int p) {
    points += p;
    updateText();
}

void ScoreManager::setPoints(int p) {
    points = p;
    updateText();
}

void ScoreManager::setThrowablesLeft(int t) {
    throwablesLeft = t;
    updateText();
}

void ScoreManager::setEnemiesLeft(int e) {
    enemiesLeft = e;
    updateText();
}

void ScoreManager::setLevel(int l) {
    levelNumber = l;
    updateText();
}

void ScoreManager::drawScore(sf::RenderWindow &window) {
    window.draw(pointsText);
    window.draw(throwablesLeftText);
    window.draw(enemiesLeftText);
    window.draw(LevelText);
}

void ScoreManager::updateText() {
    pointsText.setString("Points: " + std::to_string(points));
    throwablesLeftText.setString("Throwables: " + std::to_string(throwablesLeft));
    enemiesLeftText.setString("Enemies: " + std::to_string(enemiesLeft));
    LevelText.setString("Level " + std::to_string(levelNumber));
}

void ScoreManager::updatePosition(const sf::View& view) {
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();
    
    // Calculate new positions relative to the view's top-left corner
    sf::Vector2f topLeft = viewCenter - viewSize / 2.f;

    pointsText.setPosition(topLeft.x + 30, topLeft.y + 20);
    throwablesLeftText.setPosition(topLeft.x + 30, topLeft.y + 60);
    enemiesLeftText.setPosition(topLeft.x + 30, topLeft.y + 100);
}

int ScoreManager::getEnemiesLeft() {
    return enemiesLeft;
}

int ScoreManager::getThrowablesLeft() {
    return throwablesLeft;
}

int ScoreManager::getPoints() {
    return points;
}


void ScoreManager::drawResult(sf::RenderWindow &window) {
    window.draw(resultSprite);
    if (enemiesLeft==0) {
        WinText.setString("You Win! " + std::to_string(throwablesLeft - 1) + " Throwables Left");
        window.draw(WinText);
    } else {
        LoseText.setString("You Lose! " + std::to_string(enemiesLeft) + " Enemies Left !");
        window.draw(LoseText);
    }
}