//
//  Ball.cpp
//  dodgeball
//
//  Created by リム・イーサン on 12/8/23.
//  Copyright © 2023 リム・イーサン. All rights reserved.
//

#include "Ball.hpp"
#include "ResourcePath.hpp"

Ball::Ball()
{
    // Set ball properties
    m_Shape.setFillColor(Color::Red);
    m_Texture.loadFromFile(resourcePath() + "dodgeball.png");
    m_Sprite.setTexture(m_Texture);
}

CircleShape Ball::getShape()
{
    return m_Shape;
}

Sprite Ball::getSprite()
{
    return m_Sprite;
}

FloatRect Ball::getPosition()
{
    return m_Shape.getGlobalBounds();
}

bool Ball::isActive()
{
    return m_Active;
}

bool Ball::hasMissed()
{
    return m_Missed;
}

void Ball::deactivate()
{
    m_Active = false;
}

void Ball::setInitialRandomisedPosition(IntRect arena)
{
    // Set arena bounds
    m_Arena.width = arena.width;
    m_Arena.height = arena.height;
    m_Arena.left = arena.left;
    m_Arena.top = arena.left;
    
    // Sides of the screen
    enum class Side { TOP, BOTTOM, LEFT, RIGHT };
    
    float ballLength = m_Shape.getRadius() * 2;
    
    // Find where ball center should be
    float startX, startY;
    switch (Side(rand() % 4))
    {
        case Side::TOP:
            startX = rand() % m_Arena.width;
            startY = m_Arena.top - ballLength;
            break;
        case Side::BOTTOM:
            startX = rand() % m_Arena.width;
            startY = m_Arena.height;
            break;
        case Side::LEFT:
            startX = m_Arena.left - ballLength;
            startY = rand() % m_Arena.height;
            break;
        case Side::RIGHT:
            startX = m_Arena.width;
            startY = rand() % m_Arena.height;
            break;
    }
    // Set the results
    m_Position.x = startX;
    m_Position.y = startY;
    m_Shape.setPosition(m_Position);
    m_Sprite.setPosition(m_Position);
}

void Ball::hit()
{
    // Change color on hit
    m_Shape.setFillColor(Color::Blue);
    m_Sprite.setColor(Color::Blue);
    
    // Ball relieved of duty
    m_Active = false;
    
    // Revert to original difficulty
    m_Speed = 500.0f;
}

void Ball::spawn(IntRect arena, Vector2f target)
{
    // Use this ball
    m_Active = true;
    
    // New ball has not missed
    m_Missed = false;
    
    // Choose a size
    m_Shape.setRadius(10.0f + rand() % 40);
    m_Sprite.setScale(m_Shape.getRadius() / 10, m_Shape.getRadius() / 10);
    
    // Increase the difficulty
    m_Speed += 1;
    
    // Reset color back to red
    m_Shape.setFillColor(Color::Red);
    m_Sprite.setColor(Color::Red);
    
    // Pick a start position after setting above
    setInitialRandomisedPosition(arena);
    
    /*
     Calculate speed in x and y directions to travel toward target.
     Results m_DirectionX & m_DirectionY to be multiplied with actual distance traveled in update() function.
    */
    // Get distance from player in X & Y directions
    float distanceX = target.x - m_Position.x;
    float distanceY = target.y - m_Position.y;
    
    // Pythagoras' Theorem
    float straightLineDistance = sqrtf((distanceX * distanceX) + (distanceY * distanceY));
    
    // Get ratio of X & Y to straight-line-distance
    m_DirectionX = distanceX / straightLineDistance;
    m_DirectionY = distanceY / straightLineDistance;
}

void Ball::update(Time dt)
{
    float velocityX = m_DirectionX * m_Speed;
    float velocityY = m_DirectionY * m_Speed;
    
    // Get the distance travelled in X & Y directions
    m_Position.x += velocityX * dt.asSeconds();
    m_Position.y += velocityY * dt.asSeconds();
    
    // Set the new position
    m_Shape.setPosition(m_Position);
    m_Sprite.setPosition(m_Position);
    
    // If ball leaves the screen, deactivate
    float ballLength = m_Shape.getRadius() * 2;
    if (m_Position.x > m_Arena.width ||
        m_Position.x < m_Arena.left - ballLength ||
        m_Position.y > m_Arena.height ||
        m_Position.y < m_Arena.top - ballLength)
    {
        m_Active = false;
        m_Missed = true;
    }
}
