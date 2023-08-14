//
//  Ball.cpp
//  dodgeball
//
//  Created by リム・イーサン on 12/8/23.
//  Copyright © 2023 リム・イーサン. All rights reserved.
//

#include "Ball.hpp"

Ball::Ball(float startX, float startY) {
    
    m_Position.x = startX;
    m_Position.y = startY;
    m_Shape.setRadius(25.0f);
    m_Shape.setPosition(m_Position);
    m_Shape.setFillColor(Color::Red);
    
}

CircleShape Ball::getShape() {
    
    return m_Shape;
    
}

FloatRect Ball::getPosition() {
    
    return m_Shape.getGlobalBounds();
    
}

bool Ball::isActive() {
    
    return m_isActive;
    
}

void Ball::hit() {
    
    m_Shape.setFillColor(Color::Blue);
    
}

void Ball::spawn(Vector2f target) {
    
    m_isActive = true;
    m_Shape.setFillColor(Color::Red);
    m_Position.x = -50.0f;
    m_Position.y = 100.0f;
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

void Ball::update(Time dt) {
    
    m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();
    m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();
    m_Shape.setPosition(m_Position);
    
    // If ball leaves the screen, deactivate.
    // TODO: Replace hard-coded values with screen resolution variables.
    if (m_Position.x > 800 ||
        m_Position.x < -50 ||
        m_Position.y > 600 ||
        m_Position.y < -50)
    {
        
        m_isActive = false;
        
    }
    
}
