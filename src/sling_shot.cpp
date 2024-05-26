#include "sling_shot.hpp"

SlingShot::SlingShot(sf::Vector2f position, const float sfb2_scale, float inner_radius, float outer_radius, const float density, const float friction):
    Entity(position, sfb2_scale, density, friction), inner_radius(inner_radius), outer_radius(outer_radius) {}

void SlingShot::SFMLSetup() {

    sf::CircleShape circle1(inner_radius);
    circle1.setPosition(sf::Vector2f(position.x - inner_radius, position.y - inner_radius)); // This is the top-left position. Center will be position
    sf::CircleShape circle2(outer_radius);
    circle2.setPosition(sf::Vector2f(position.x - outer_radius, position.y - outer_radius));
    
    innerCircle = circle1;
    outerCircle = circle2;

}

void SlingShot::Launch(const sf::Event& event, const sf::RenderWindow& window, std::unique_ptr<Bird>& flyBird, sf::Sound& dragging_sound, sf::Sound& flying_sound) {

    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    if (event.type == sf::Event::MouseButtonPressed && isPointInsideCircle(sf::Vector2f(mousePosition.x, mousePosition.y), innerCircle))
    {
        // std::cout << "event.mouseButton.button == sf::Mouse::Left: " << (event.mouseButton.button == sf::Mouse::Left) << std::endl;
        // std::cout << "isFirstPressed: " << (isFirstPressed) << std::endl;
        // std::cout << "isPointInsideCircle(sf::Vector2f(mousePosition.x, mousePosition.y), outerCircle): " << (isPointInsideCircle(sf::Vector2f(mousePosition.x, mousePosition.y), outerCircle)) << std::endl;

        if (event.mouseButton.button == sf::Mouse::Left && isFirstPressed && isPointInsideCircle(sf::Vector2f(mousePosition.x, mousePosition.y), outerCircle))
        {
            startPoint.x = event.mouseButton.x;
            startPoint.y = event.mouseButton.y;
            startDragging = true;
            isFirstPressed = false;
            // std::cout << "start draging" << std::endl;
            dragging_sound.play();
            

        }
    }
    else if (event.type == sf::Event::MouseButtonReleased && startDragging)
    {
        // std::cout << "Released" << std::endl;
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (isPointInsideCircle(sf::Vector2f(mousePosition.x, mousePosition.y), outerCircle)) 
            {
            endPoint.x = event.mouseButton.x;
            endPoint.y = event.mouseButton.y;

            }
            else 
            {
            sf::Vector2i mousePositionInt = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosition = sf::Vector2f(mousePositionInt.x, mousePositionInt.y);
            sf::Vector2f center2 = outerCircle.getPosition() + sf::Vector2f(outerCircle.getRadius(), outerCircle.getRadius());
            sf::Vector2f direction = mousePosition - center2;
            float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            sf::Vector2f normalizedDirection = direction / magnitude;
            sf::Vector2f boundaryPosition = center2 + normalizedDirection * outerCircle.getRadius();
            endPoint.x = boundaryPosition.x;
            endPoint.y = boundaryPosition.y;
            }

            startDragging = false;
            direction = startPoint - endPoint;
            b2Vec2 scaledDirection = toB2Vec2(direction, sfb2_scale);
            scaledDirection.x *= window.getSize().x * 2.2;
            scaledDirection.y *= window.getSize().x * 2.2;
            flyBird->body->SetType(b2_dynamicBody); // Change bird body type to dynamic before applying force
            flyBird->body->ApplyForceToCenter(scaledDirection, true);
            isLaunched = true;
            flying_sound.play();
        }
    }

    if (startDragging && isPointInsideCircle(sf::Vector2f(mousePosition.x, mousePosition.y), outerCircle))
    {
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        flyBird->body->SetTransform(toB2Vec2(mousePos, sfb2_scale), flyBird->body->GetAngle());
    }

    if (startDragging && !isPointInsideCircle(sf::Vector2f(mousePosition.x, mousePosition.y), outerCircle))
    {
        sf::Vector2i mousePositionInt = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosition = sf::Vector2f(mousePositionInt.x, mousePositionInt.y);
        sf::Vector2f center2 = outerCircle.getPosition() + sf::Vector2f(outerCircle.getRadius(), outerCircle.getRadius());
        sf::Vector2f direction = mousePosition - center2;
        float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        sf::Vector2f normalizedDirection = direction / magnitude;
        sf::Vector2f boundaryPosition = center2 + normalizedDirection * outerCircle.getRadius();

        flyBird->body->SetTransform(toB2Vec2(boundaryPosition, sfb2_scale), flyBird->body->GetAngle());
    }
}


void SlingShot::Render(sf::RenderWindow& window, std::unique_ptr<Bird>& flyBird) {

    if (startDragging)
    {
        float offsetX = 20.0f;  
        float offsetY = 5.0f;  
        sf::Vector2f birdCenter = toSFVec2(flyBird->body->GetPosition(), sfb2_scale);

        // belt one
        sf::Vector2f circleCenter = innerCircle.getPosition() + sf::Vector2f(innerCircle.getRadius()+offsetX, innerCircle.getRadius()+offsetY);
        float distance = std::sqrt(std::pow(birdCenter.x - circleCenter.x, 2) + std::pow(birdCenter.y - circleCenter.y, 2));
        float angle = std::atan2(birdCenter.y - circleCenter.y, birdCenter.x - circleCenter.x) * 180 / 3.14159265;
        sf::RectangleShape belt_one(sf::Vector2f(distance, 15));  // 5 is the width of the belt. Adjust as needed.
        belt_one.setFillColor(sf::Color(77, 41, 21));  // Brown color
        belt_one.setPosition(circleCenter);
        belt_one.setRotation(angle);
        window.draw(belt_one);  // Draw the belt

        // belt two
        sf::Vector2f circleCenter_2 = innerCircle.getPosition() + sf::Vector2f(innerCircle.getRadius()-offsetX, innerCircle.getRadius()+offsetY);
        float distance_two = std::sqrt(std::pow(birdCenter.x - circleCenter_2.x, 2) + std::pow(birdCenter.y - circleCenter_2.y, 2));
        float angle_two = std::atan2(birdCenter.y - circleCenter_2.y, birdCenter.x - circleCenter_2.x) * 180 / 3.14159265;
        sf::RectangleShape belt_two(sf::Vector2f(distance_two, 15));  // 5 is the width of the belt. Adjust as needed.
        belt_two.setFillColor(sf::Color(77, 41, 21));  // Brown color
        belt_two.setPosition(circleCenter_2);
        belt_two.setRotation(angle_two);
        window.draw(belt_two);  // Draw the belt
    }
}

void SlingShot::MoveView(std::unique_ptr<Bird>& flyBird, sf::View& view, const sf::RenderWindow& window) {
    sf::Vector2f birdPosition = toSFVec2(flyBird->body->GetPosition(), sfb2_scale);
    
    if (birdPosition.x < window.getSize().x * 0.2 || birdPosition.x > window.getSize().x * 0.6) {
        view.setCenter(birdPosition.x, view.getCenter().y);
    } else if (isLaunched) {
        view.setCenter(window.getSize().x / 2.0 , window.getSize().y / 2.0);
    }
}


void SlingShot::CheckAndResetBird(std::unique_ptr<Bird>& flyBird, const sf::RenderWindow& window, sf::Vector2f launch_position, const float ground_height) {
    b2Vec2 velocity = flyBird->body->GetLinearVelocity();
    sf::Vector2f birdPosition = toSFVec2(flyBird->body->GetPosition(), sfb2_scale);
    float birdSpriteHeight = flyBird->sprite.getGlobalBounds().height;
    if ( (isLaunched == true) && ((std::abs(velocity.x) + std::abs(velocity.y)) < 1e-8f) && ( birdPosition.y + birdSpriteHeight/2.0 > ground_height*0.96) ) { /* infer if bird touch the ground by checking y */
        flyBird->isDone = true;
    }
}

void SlingShot::ResetState() {
    startDragging = false;
    isFirstPressed = true; 
    isLaunched = false;
    isFetched = false;
}

void SlingShot::FetchBird(std::unique_ptr<Bird>& flyBird, const sf::RenderWindow& window, sf::Vector2f launch_position) {
    sf::Vector2f birdPosition = toSFVec2(flyBird->body->GetPosition(), sfb2_scale);
    if  (!startDragging && !isFetched && ( (birdPosition.x - launch_position.x > window.getSize().x * 0.05) || (birdPosition.y - launch_position.y > window.getSize().y * 0.05) )) {
        flyBird->body->SetTransform(toB2Vec2(launch_position, sfb2_scale), flyBird->body->GetAngle());
        isFetched = true;
    }
}