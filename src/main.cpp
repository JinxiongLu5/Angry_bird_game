#include <iostream>

#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "utility.hpp"
#include "ground.hpp"
#include "bird.hpp"
#include "obstacle.hpp"
#include "sling_shot.hpp"
#include "speedboost_bird.hpp"
#include "explosive_bird.hpp"
#include "level_loader.hpp"
#include "obstacle.hpp"
#include "scoreManager.hpp"
#include "scoreBoard.hpp"
#include "explosion.hpp"
#include "trajectory.hpp"

#include "modeBoard.hpp"

#include "contactListener.hpp"

#include <chrono>
#include <thread>

// #include <filesystem>
#include <dirent.h>

const float SCALE = 30.0f; // Used to scale between SFML and Box2D coordinates

int main()
{
    
    // Initialize SFML window
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Angry Bird");
    sf::View view(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y));
    window.setFramerateLimit(60);

    // load background image
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("../media/bg.png")) {std::cerr << "Failed to load background texture!" << std::endl;}
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale( 4.0 * static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x, static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y); // the map width is 4x window width

    // initialize explosion animation
    Explosion explosion;
    // initialize trajectory and its points vector
    Trajectory trajectory;
    std::vector<sf::Vector2f> trajectoryPoints;
    std::vector<sf::Vector2f> currentTrajectoryPoints;

    // load music and sound 
    sf::Music bgmMusic;
    if (!bgmMusic.openFromFile("../media/bgm.ogg")) {return -1;}
    bgmMusic.setLoop(true);
    bgmMusic.play();
    sf::SoundBuffer dragging_buffer;
    if (!dragging_buffer.loadFromFile("../media/Dragging.ogg")) {return -1;}
    sf::Sound dragging_sound;
    dragging_sound.setBuffer(dragging_buffer);
    sf::SoundBuffer destroyed_buffer;
    if (!destroyed_buffer.loadFromFile("../media/Destroy.ogg")) {return -1;}
    sf::Sound destroyed_sound;
    destroyed_sound.setBuffer(destroyed_buffer);
    sf::SoundBuffer flying_buffer;
    if (!flying_buffer.loadFromFile("../media/Flying.ogg")) {return -1;}
    sf::Sound flying_sound;
    flying_sound.setBuffer(flying_buffer);
    sf::SoundBuffer coin_buffer;
    if (!coin_buffer.loadFromFile("../media/coin.ogg")) {return -1;}
    sf::Sound coin_sound;
    coin_sound.setBuffer(coin_buffer);

    // ScoreBoard
    ScoreBoard scoreBoard(window);
    scoreBoard.GetNickName(window);

    // mode board
    modeBoard modeBoard(window);
    int gameMode = modeBoard.GetGameMode(window);
    if (gameMode == 2) {
        modeBoard.setTimeLimit(60); 
    }

    // load levels vector
    std::vector<std::string> levels;

    // const std::filesystem::path dirPath{"../media/levels"};
    // for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
    //     if (std::filesystem::is_regular_file(entry.status())) { 
    //         levels.push_back(entry.path().filename());
    //     }
    // }

    DIR *dir = opendir("../media/levels");
    if (dir == nullptr) {
        std::cerr << "Failed to open directory!" << std::endl;
        return -1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_REG) {
            // Add the file to your levels vector
            levels.push_back(entry->d_name);
        }
    }
    closedir(dir);
    
    std::sort(levels.begin(), levels.end(), [](const std::string& a, const std::string& b) {return a < b;});
    int level_idx = 3;

    // define launch position
    const float LAUNCHER_X_SF = window.getSize().x * 0.32;
    const float LAUNCHER_Y_SF = window.getSize().y * 0.63;
    const sf::Vector2f LAUNCH_POSITION = sf::Vector2f(LAUNCHER_X_SF, LAUNCHER_Y_SF);

    // Initialize Box2D world with gravity
    b2Vec2 gravity(0.0f, 9.8f);
    b2World world(gravity);

    // ContactListener
    ContactListener contactListener;
    world.SetContactListener(&contactListener);

    // Ground
    const float GROUND_HEIGHT = window.getSize().y * 0.81;
    sf::Vector2f ground_position = sf::Vector2f(0.0, 0.0);
    const float boundary_width = window.getSize().x * 4.0;
    const float boundary_height = GROUND_HEIGHT;
    float ground_density = 0.0f;
    float ground_friction = 1.0f;
    Ground ground(ground_position, SCALE, boundary_width, boundary_height, ground_density, ground_friction);
    ground.Box2dSetup(world);

    // Slingshot
    float inner_radius = 30.0f;
    float outer_radius = 90.0f;
    float slingshot_density = 0.0;
    float slingshot_friction = 0.0;
    SlingShot slingshot(LAUNCH_POSITION, SCALE, inner_radius, outer_radius, slingshot_density, slingshot_friction);
    slingshot.SFMLSetup();

    // Pointer vectors
    std::vector<std::unique_ptr<Obstacle>> obstacles;
    std::vector<std::unique_ptr<Pig>> pigs;
    std::vector<std::unique_ptr<Bird>> birds;
    std::vector<std::unique_ptr<Star>> stars;

    // LevelLoader
    std::string levelFilePath;
    LevelLoader loadel(SCALE);

    // ScoreManager
    ScoreManager scoreManager(window);

    /*-------------------------------------------------------------------------------------------------*/
    /*-------------------------------------------------------------------------------------------------*/
    /*-------------------------------------------------------------------------------------------------*/
    for (size_t level_idx = 0; level_idx < levels.size(); level_idx++) {
        pigs.clear();
        obstacles.clear();
        birds.clear();
        stars.clear();
        
        levelFilePath = "../media/levels/"+levels[level_idx];
        loadel.UpdateLevelData(levelFilePath);

        loadel.LoadObstacles(world, window, obstacles);
        loadel.LoadPigs(world, window, pigs);
        loadel.LoadBirds(world, window, LAUNCH_POSITION, birds, GROUND_HEIGHT);
        if (gameMode == 3){
            loadel.LoadStars(window, stars);
        }

        scoreManager.setPoints(0);
        scoreManager.setThrowablesLeft(static_cast<int>(birds.size()));
        scoreManager.setEnemiesLeft(static_cast<int>(pigs.size()));
        scoreManager.setLevel(level_idx+1);

        slingshot.ResetState();
    /*-------------------------------------------------------------------------------------------------*/
    /*-------------------------------------------------------------------------------------------------*/
        while (window.isOpen())
        {
            // if choose mode 2
            if (gameMode == 2){
                modeBoard.updateTimer();
                if (modeBoard.isTimeUp()) {
                    // Handle time up logic, e.g., clear birds, pigs, obstacles, etc.
                    birds.clear();
                    pigs.clear();
                    obstacles.clear();
                    break;
                }
            }

            modeBoard.checkStarCollection(birds[0]->sprite.getPosition(), stars, coin_sound);
            
            // Destory Birds and birds exit
            if ( birds[0]->isDone == true) {
                
                trajectoryPoints = birds[0]->GetTrajectoryPoints();
                birds.erase(birds.begin());
                scoreManager.setThrowablesLeft(static_cast<int>(birds.size()));

                if (birds.size() == 0) {
                    window.clear();
                    view.setCenter(window.getSize().x * 0.5 , window.getSize().y * 0.5 );
                    window.setView(view);
                    scoreManager.drawResult(window);
                    window.display();
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    break;
                } else {
                    slingshot.ResetState();
                    view.setCenter(window.getSize().x / 2.0 , window.getSize().y / 2.0);
                }
            } 

            // pigs exit
            if (pigs.size()==0) {
                window.clear();
                view.setCenter(window.getSize().x * 0.5 , window.getSize().y * 0.5 );
                window.setView(view);
                scoreManager.drawResult(window);
                window.display();
                std::this_thread::sleep_for(std::chrono::seconds(2));
                break;
            }

            slingshot.FetchBird(birds[0], window, LAUNCH_POSITION);

            // Poll event
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return 0;
                }

                slingshot.Launch(event, window, birds[0], dragging_sound, flying_sound);
                birds[0]->UseSkill(event, window);
                
            }

            // CheckAndResetBird
            slingshot.CheckAndResetBird(birds[0], window, sf::Vector2f(LAUNCHER_X_SF, LAUNCHER_Y_SF), GROUND_HEIGHT);

            // Move view
            slingshot.MoveView(birds[0], view, window);

            // Update the world
            world.Step(1/60.f, 8, 3);
            
            // Destroy Obstacles
            obstacles.erase(
                std::remove_if(
                    obstacles.begin(),
                    obstacles.end(),
                    [&contactListener, &world, &destroyed_sound](const std::unique_ptr<Obstacle>& o) {
                        return o->ShouldBeRemoved(contactListener, world, destroyed_sound);
                    }
                ),
                obstacles.end()
            );

            // Destroy pigs
            pigs.erase(
                std::remove_if(
                    pigs.begin(),
                    pigs.end(),
                    [&contactListener, &world, &scoreManager, &destroyed_sound, &explosion, &window](const std::unique_ptr<Pig>& p) {
                        return p->ShouldBeRemoved(contactListener, world, scoreManager, destroyed_sound, explosion, window);
                    }
                ),
                pigs.end()
            );

            /*-------------------------------------------------------------------------------------------------*/

            // clear the scene
            window.clear();

            // set view
            window.setView(view);

            // draw the background
            window.draw(backgroundSprite);

            // Update position for time
            modeBoard.updatePosition(view);

            // draw time info
            modeBoard.drawText(window);

            // draw slingshot belts
            slingshot.Render(window, birds[0]);

            // draw bird, obstacles, pigs
            for (size_t i = 0; i < birds.size(); ++i) {
                birds[i]->RemoveParticles();
                birds[i]->Render(window);
            }

            for (auto it = obstacles.begin(); it != obstacles.end(); ++it) {
                (*it)->Render(window);
            }

            for (auto it = pigs.begin(); it != pigs.end(); ++it) {
                (*it)->Render(window);
            }

            for (auto& star : stars) {
                star->Render(window);
            }

            // Draw the score manager
            scoreManager.updatePosition(view);
            scoreManager.drawScore(window);

            // Draw trajectory
            if (slingshot.isLaunched) {
                birds[0]->addTrajectoryPoint();
            }

            currentTrajectoryPoints = birds[0]->GetTrajectoryPoints();
            
            trajectory.Render(window, trajectoryPoints);
            trajectory.Render(window, currentTrajectoryPoints);

            window.display();

        }

        scoreBoard.UploadScoreLocally(level_idx+1, static_cast<int>(birds.size()) * scoreManager.getPoints()); // Stars is #birdLeft * #Points(#PigsKilled)
        scoreBoard.UploadScoresToServer();
        scoreBoard.RetrieveAndMergeScores();
        scoreBoard.DrawLevelScore(level_idx+1, window);
    /*-------------------------------------------------------------------------------------------------*/
    /*-------------------------------------------------------------------------------------------------*/
    /*-------------------------------------------------------------------------------------------------*/
    
    }
  
    return 0;
}
