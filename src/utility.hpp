#ifndef UTILITY_H
#define UTILITY_H

#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"

/**
 * \file utility.hpp
 * \brief Utility functions for the game, facilitating interaction between SFML and Box2D.
 *
 * This file contains utility functions that are used throughout the game to handle common tasks
 * such as coordinate conversions between SFML and Box2D and collision detection utilities.
 */

/**
 * \brief Checks if a point is inside a given circle.
 * \param point The SFML Vector2f representing the point.
 * \param circle The SFML CircleShape representing the circle.
 * \return True if the point is inside the circle, false otherwise.
 *
 * This function is useful for determining if a point (like a mouse click) is within the bounds of a circular object.
 */
bool isPointInsideCircle(const sf::Vector2f& point, const sf::CircleShape& circle);

/**
 * \brief Converts SFML coordinates to Box2D coordinates.
 * \param v The SFML Vector2f to be converted.
 * \param scale The scale factor for conversion.
 * \return The converted Box2D vector (b2Vec2).
 *
 * This function is essential for synchronizing SFML's graphical coordinates with Box2D's physics coordinates.
 */
b2Vec2 toB2Vec2(const sf::Vector2f& v, const float scale);

/**
 * \brief Converts Box2D coordinates to SFML coordinates.
 * \param v The Box2D vector (b2Vec2) to be converted.
 * \param scale The scale factor for conversion.
 * \return The converted SFML Vector2f.
 *
 * This function complements toB2Vec2, converting physics coordinates back into graphical coordinates.
 */
sf::Vector2f toSFVec2(const b2Vec2& v, const float scale);

#endif // UTILITY_H
