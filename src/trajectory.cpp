#include "trajectory.hpp"

Trajectory::Trajectory() {}

Trajectory::~Trajectory() {}

void Trajectory::Render(sf::RenderWindow& window, std::vector<sf::Vector2f> trajectoryPoints) {
    if (trajectoryPoints.size() < 2) return;

    sf::Color trajectoryColor(255, 255, 255, 50); 

    float radius = 3.5f; // Set the radius of the circles

    for (size_t i = 0; i < trajectoryPoints.size(); ++i) {
        sf::CircleShape circle(radius);
        circle.setPosition(trajectoryPoints[i].x - radius, trajectoryPoints[i].y - radius); // Center the circle on the point
        circle.setFillColor(trajectoryColor);

        window.draw(circle);
    }
}