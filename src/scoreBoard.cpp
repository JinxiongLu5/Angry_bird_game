#include "scoreBoard.hpp"

ScoreBoard::ScoreBoard(sf::RenderWindow& window) {
    if (!font.loadFromFile("../media/times.ttf")) {
        std::cerr << "fail to load font" << std::endl;
    }

    // Set up the text objects with the loaded font
    nickNameText.setFont(font);

    // Set character size, color, and initial string
    nickNameText.setCharacterSize(150);
    nickNameText.setFillColor(sf::Color(161, 52, 235));
    nickNameText.setString("");

    // Set the position of the texts
    nickNameText.setPosition(window.getSize().x / 2.2, window.getSize().y * 0.72 );

    // load nickname background image
    if (!nickNameTexture.loadFromFile("../media/nickname.png")) {std::cerr << "Failed to load nickname background texture!" << std::endl;}
    nickNameSprite.setTexture(nickNameTexture);
    nickNameSprite.setScale( static_cast<float>(window.getSize().x) / nickNameTexture.getSize().x, static_cast<float>(window.getSize().y) / nickNameTexture.getSize().y); 
    // load highScoreListbackground image
    if (!highScoreListTexture.loadFromFile("../media/highScore_list.png")) {std::cerr << "Failed to load highScore_list background texture!" << std::endl;}
    highScoreListSprite.setTexture(highScoreListTexture);
    highScoreListSprite.setScale( static_cast<float>(window.getSize().x) / highScoreListTexture.getSize().x, static_cast<float>(window.getSize().y) / highScoreListTexture.getSize().y); 
}

void ScoreBoard::GetNickName(sf::RenderWindow& window) {
    bool enterPressed = false;
    std::string userText;
    while (window.isOpen() && !enterPressed) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Catch the text entered event
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    char enteredChar = static_cast<char>(event.text.unicode);
                    if (enteredChar == '\b' && !userText.empty()) { // Handle backspace
                        userText.pop_back();
                    } else if (enteredChar >= 32 && enteredChar <= 126) { // Printable characters
                        userText += enteredChar;
                    }
                    nickNameText.setString(userText);
                    nickNameText.setPosition(window.getSize().x / 2 - static_cast<float>(userText.size()) * 0.03 * window.getSize().x, window.getSize().y * 0.72 );
                }
            }

            // Check for Enter key press
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    enterPressed = true;
                    break;
                }
            }
        }
        window.clear();

        window.draw(nickNameSprite);

        window.draw(nickNameText);

        window.display();
    
    }
    nickName = userText;
}


void ScoreBoard::UploadScoreLocally(int level, float score) {
    nlohmann::json existingData;
    std::ifstream inputFile(scoreFilePath);

    if (inputFile.is_open()) {
        inputFile >> existingData;
        inputFile.close();

        // Convert array to the desired object format if necessary
        if (existingData.is_array()) {
            nlohmann::json convertedData = nlohmann::json::object();
            for (const auto& entry : existingData) {
                std::string levelStr = std::to_string(entry["level"].get<int>());
                std::string name = entry["name"];
                float existingScore = entry["score"];
                if (!convertedData[levelStr].contains(name) || convertedData[levelStr][name] < existingScore) {
                    convertedData[levelStr][name] = existingScore;
                }
            }
            existingData = convertedData;
        }
    } else {
        // File does not exist or cannot be opened, create a new JSON object
        existingData = nlohmann::json::object();
    }

    // Update the score
    std::string levelStr = std::to_string(level);
    if (!existingData[levelStr].contains(nickName) || existingData[levelStr][nickName] < score) {
        existingData[levelStr][nickName] = score;
    }

    // Write the updated data to the file
    std::ofstream outputFile(scoreFilePath);
    if (outputFile.is_open()) {
        outputFile << existingData.dump(4); // Pretty-print with an indent of 4 spaces
        outputFile.close();
    } else {
        std::cerr << "Could not open local_data.json for writing." << std::endl;
    }
}


void ScoreBoard::DrawLevelScore(int level, sf::RenderWindow& window) {
    nlohmann::json scoreData;
    std::ifstream inputFile(scoreFilePath);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open score file: " << scoreFilePath << std::endl;
        return;
    }

    inputFile >> scoreData;
    inputFile.close();

    std::string levelKey = std::to_string(level);
    if (!scoreData.contains(levelKey)) {
        std::cout << "No data for level " << level << std::endl;
        return;
    }

    std::vector<PlayerScore> playerScores;
    for (const auto& item : scoreData[levelKey].items()) {
        playerScores.push_back({item.key(), item.value()});
    }

    // Sort in descending order of scores
    std::sort(playerScores.begin(), playerScores.end(), [](const PlayerScore& a, const PlayerScore& b) {
        return a.score > b.score;
    });

    // Display top 3 scores
    float startY = 250.0f; // Y-coordinate to start drawing from
    int count = 0;
    window.clear();
    window.draw(highScoreListSprite);
    for (const auto& playerScore : playerScores) {
        if (count >= 3) break;

        sf::Text text;
        text.setFont(font);
        text.setString(playerScore.name + ":          " + std::to_string(static_cast<int>(playerScore.score)) + " Stars.");
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        text.setPosition(400.0f, startY);

        window.draw(text);
        
        startY += 40.0f; // Move down for the next entry
        count++;
    }

    window.display();

    std::this_thread::sleep_for(std::chrono::seconds(2));
}


void ScoreBoard::UploadScoresToServer() {
    httplib::Client cli("localhost", 1234);

    nlohmann::json scoreData;
    std::ifstream inputFile(scoreFilePath);
    inputFile >> scoreData;
    inputFile.close();

    if (auto res = cli.Post("/upload_scores", scoreData.dump(), "application/json")) {
        if (res->status == 200) {
            std::cout << "Scores uploaded successfully\n";
        } else {
            std::cout << "Failed to upload scores\n";
        }
    } else {
        auto err = res.error();
        std::cout << "Error: " << err << std::endl;
    }
}

void ScoreBoard::RetrieveAndMergeScores() {
    httplib::Client cli("localhost", 1234);

    // Make a GET request to retrieve the score data from the server
    auto res = cli.Get("/retrieve_scores");
    if (!res || res->status != 200) {
        std::cerr << "Failed to retrieve scores from server." << std::endl;
        return;
    }

    // Parse the retrieved server scores
    nlohmann::json serverScores = nlohmann::json::parse(res->body);

    // Load local scores
    nlohmann::json localScores;
    std::ifstream inputFile(scoreFilePath);
    if (inputFile.is_open()) {
        inputFile >> localScores;
        inputFile.close();
    }

    // Merge server scores with local scores
    for (const auto& [level, players] : serverScores.items()) {
        for (const auto& [name, score] : players.items()) {
            if (!localScores[level].contains(name) || localScores[level][name] < score) {
                localScores[level][name] = score;
            }
        }
    }

    // Write the merged scores back to the local file
    std::ofstream outputFile(scoreFilePath);
    if (outputFile.is_open()) {
        outputFile << localScores.dump(4); // Pretty-print with an indent of 4 spaces
        outputFile.close();
        std::cerr << "Scores received successfully" << std::endl;
    } else {
        std::cerr << "Could not open " << scoreFilePath << " for writing." << std::endl;
    }
}

