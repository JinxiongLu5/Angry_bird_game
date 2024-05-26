#include "level_loader.hpp"

LevelLoader::LevelLoader(const float sfb2_scale) : sfb2_scale(sfb2_scale) {}

void LevelLoader::LoadObstacles(b2World& world, const sf::RenderWindow& window, std::vector<std::unique_ptr<Obstacle>>& obstacles) {

    // Wood
    std::string wood_image_path = "none";
    float wood_density = 0.1;
    float wood_friction = 1.0;
    for (const auto& woodData : levelData["woods"]) {
        float wood_x = window.getSize().x * static_cast<float>(woodData["position"]["x"]);
        float wood_y = window.getSize().y * static_cast<float>(woodData["position"]["y"]);
        float wood_width = window.getSize().x * static_cast<float>(woodData["size"]["width"]);
        float wood_height = window.getSize().y * static_cast<float>(woodData["size"]["height"]);
        sf::Vector2f wood_position = sf::Vector2f( wood_x, wood_y);
        int wood_health = 1;
        obstacles.push_back(std::make_unique<Wood>(wood_position, sfb2_scale, wood_width, wood_height, wood_image_path, wood_density, wood_friction, wood_health));
        obstacles.back()->Box2dSetup(world);
        obstacles.back()->SFMLSetup(window);
    }

    // Stone
    std::string stone_image_path = "none";
    float stone_density = 0.1;
    float stone_friction = 1.0;
    for (const auto& stoneData : levelData["stones"]) {
        float stone_x = window.getSize().x * static_cast<float>(stoneData["position"]["x"]);
        float stone_y = window.getSize().y * static_cast<float>(stoneData["position"]["y"]);
        float stone_width = window.getSize().x * static_cast<float>(stoneData["size"]["width"]);
        float stone_height = window.getSize().y * static_cast<float>(stoneData["size"]["height"]);
        sf::Vector2f stone_position = sf::Vector2f( stone_x, stone_y);
        int stone_health = 2;
        obstacles.push_back(std::make_unique<Stone>(stone_position, sfb2_scale, stone_width, stone_height, stone_image_path, stone_density, stone_friction, stone_health));
        obstacles.back()->Box2dSetup(world);
        obstacles.back()->SFMLSetup(window);
    }
    
}


void LevelLoader::LoadPigs(b2World& world, const sf::RenderWindow& window, std::vector<std::unique_ptr<Pig>>& pigs) {

    std::string pig_image_path = "none";
    float pig_density = 1.0;
    float pig_friction = 1.0;
    for (const auto& pigData : levelData["pigs"]) {
        float pig_x = window.getSize().x * static_cast<float>(pigData["position"]["x"]);
        float pig_y = window.getSize().y * static_cast<float>(pigData["position"]["y"]);
        float pig_width = window.getSize().x * static_cast<float>(pigData["size"]["width"]);
        float pig_height = window.getSize().y * static_cast<float>(pigData["size"]["height"]);
        sf::Vector2f pig_position = sf::Vector2f( pig_x, pig_y);
        int pig_health = 2;
        pigs.push_back(std::make_unique<Pig>(pig_position, sfb2_scale, pig_width, pig_height, pig_image_path, pig_density, pig_friction, pig_health));
        pigs.back()->Box2dSetup(world);
        pigs.back()->SFMLSetup(window);
    }
    
}

void LevelLoader::LoadBirds(b2World& world, const sf::RenderWindow& window, sf::Vector2f launch_position, std::vector<std::unique_ptr<Bird>>& birds, float ground_height) {

    //Birds

    float bird_density = 3.0;
    float bird_friction = 1.0;
    float i = 1;
    
    for (const auto& birdData : levelData["birds"]) {
        sf::Vector2f birdPosition = sf::Vector2f(launch_position.x - 50.0f - (i * 0.5f), ground_height * 0.975f);
        i += 100.0f;
        float bird_width = window.getSize().x * static_cast<float>(birdData["size"]["width"]);
        float bird_height = window.getSize().y * static_cast<float>(birdData["size"]["height"]);
        std::string birdType = static_cast<std::string>(birdData["type"]);
        if ( birdType == "normal") {
            std::string bird_image_path = "../media/normal_bird.png";
            birds.push_back(std::make_unique<Bird>(world, birdPosition, sfb2_scale, bird_width, bird_height, bird_image_path, bird_density, bird_friction, birdType));
        } else if (birdType == "speed") {
            std::string bird_image_path = "../media/speedboost_bird.png";
            float speed_gain = 3.0f;
            birds.push_back(std::make_unique<SpeedBoostBird>(world, birdPosition, sfb2_scale, bird_width, bird_height, bird_image_path, bird_density, bird_friction, speed_gain, birdType));
        } else if (birdType == "explosive") {
            std::string bird_image_path = "../media/explosive_bird.png";
            birds.push_back(std::make_unique<ExplosiveBird>(world, birdPosition, sfb2_scale, bird_width, bird_height, bird_image_path, bird_density, bird_friction, birdType));
        }else if (birdType == "split") {
            std::string bird_image_path = "../media/split_bird.png";
            birds.push_back(std::make_unique<SplitBird>(world, birdPosition, sfb2_scale, bird_width, bird_height, bird_image_path, bird_density, bird_friction, birdType));
        }else if (birdType == "vertical") {
            std::string bird_image_path = "../media/vertical.png";
            birds.push_back(std::make_unique<VerticalBird>(world, birdPosition, sfb2_scale, bird_width, bird_height, bird_image_path, bird_density, bird_friction, birdType));
        } else if (birdType == "bigger") {
            std::string bird_image_path = "../media/bigger_bird.png";
            float scale = 2.0f;
            birds.push_back(std::make_unique<BiggerBird>(world, birdPosition, sfb2_scale, bird_width, bird_height, bird_image_path, bird_density, bird_friction, scale, birdType));
        }
        birds.back()->SFMLSetup(window);
    }
}

void LevelLoader::UpdateLevelData(const std::string& levelFilePath) {
    std::ifstream file(levelFilePath);
    if (file.is_open()) {
        file >> levelData;
    } else {
        std::cerr << "fail to open " << levelFilePath << std::endl;
    }
    file.close();
}

void LevelLoader::LoadStars(const sf::RenderWindow& window, std::vector<std::unique_ptr<Star>>& stars) {
    std::string star_image_path = "../media/star.png";  // Change to the actual star image path

    for (const auto& starData : levelData["stars"]) {
        float star_x = window.getSize().x * static_cast<float>(starData["position"]["x"]);
        float star_y = window.getSize().y * static_cast<float>(starData["position"]["y"]);
        float star_width = window.getSize().x * static_cast<float>(starData["size"]["width"]);
        float star_height = window.getSize().y * static_cast<float>(starData["size"]["height"]);
        sf::Vector2f star_position = sf::Vector2f(star_x, star_y);

        stars.push_back(std::make_unique<Star>(star_position, star_image_path,star_width,star_height));
    }
}