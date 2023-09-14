//
//  Ball.cpp
//  dodgeball
//
//  Created by リム・イーサン on 12/8/23.
//  Copyright © 2023 リム・イーサン. All rights reserved.
//

#include "Ball.hpp"
#include <iostream>

Ball::Ball()
{
    // Set ball properties
    m_Shape.setRadius(25.0f);
    m_Shape.setFillColor(Color::Red);
}

CircleShape Ball::getShape()
{
    return m_Shape;
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

void Ball::hit()
{
    // Change color on hit
    m_Shape.setFillColor(Color::Blue);
    
    // Ball relieved of duty
    m_Active = false;
    
    // Revert to original difficulty
    m_Speed = 500.0f;
}

void Ball::deactivate()
{
    m_Active = false;
}

void Ball::spawn(IntRect arena, Vector2f target)
{
    // Set arena bounds
    m_Arena.width = arena.width;
    m_Arena.height = arena.height;
    m_Arena.left = arena.left;
    m_Arena.top = arena.left;
    
    // Use this ball
    m_Active = true;
    
    // New ball has not missed
    m_Missed = false;
    
    // Increase the difficulty
    m_Speed += 1;
    
    // Reset color back to red
    m_Shape.setFillColor(Color::Red);
    
    float ballLength = m_Shape.getRadius() * 2;
    
    // Pick a start position
    float startX, startY;
    enum class Side { TOP, BOTTOM, LEFT, RIGHT };

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
    m_Position.x = startX;
    m_Position.y = startY;
    m_Shape.setPosition(m_Position);
    
    /*
     Calculate speed in x and y directions to travel toward target.
     Results m_DirectionX & m_DirectionY to be multiplied with actual distance traveled in update() function.
    */
    float distanceX = target.x - m_Position.x;
    float distanceY = target.y - m_Position.y;
    float straightLineDistance = sqrtf((distanceX * distanceX) + (distanceY * distanceY));
    m_DirectionX = distanceX / straightLineDistance;
    m_DirectionY = distanceY / straightLineDistance;
}

void Ball::update(Time dt)
{
    // Get actual distance travelled in x and y directions
    m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();
    m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();
    m_Shape.setPosition(m_Position);
    
    // If ball leaves the screen, deactivate.
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
