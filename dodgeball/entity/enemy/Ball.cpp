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

void Ball::spawn(Vector2f target) {
    
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
    
}
