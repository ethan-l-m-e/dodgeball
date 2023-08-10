//
//  Player.cpp
//  dodgeball
//
//  Created by リム・イーサン on 10/8/23.
//  Copyright © 2023 リム・イーサン. All rights reserved.
//

#include "Player.hpp"

Player::Player(float startX, float startY) {
    
    m_Position.x = startX;
    m_Position.y = startY;
    m_Shape.setSize(Vector2f(50, 50));
    m_Shape.setPosition(m_Position);
    
}

RectangleShape Player::getShape() {
    
    return m_Shape;
    
}

void Player::moveUp() {
    
    m_MovingUp = true;
    
}

void Player::stopUp() {
    
    m_MovingUp = false;
    
}

void Player::update(Time dt) {
    
    if (m_MovingUp) {
        
        m_Position.y -= m_Speed * dt.asSeconds();
        
    }
    
    // Moves the shape object associated with player
    m_Shape.setPosition(m_Position);
    
}
