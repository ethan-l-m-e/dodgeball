//
//  Player.cpp
//  dodgeball
//
//  Created by リム・イーサン on 10/8/23.
//  Copyright © 2023 リム・イーサン. All rights reserved.
//

#include "Player.hpp"

Player::Player(float startX, float startY, Vector2f screen) {
    
    m_Position.x = startX;
    m_Position.y = startY;
    m_Shape.setSize(Vector2f(50, 50));
    m_Shape.setPosition(m_Position);
    m_Screen.x = screen.x;
    m_Screen.y = screen.y;
    
}

RectangleShape Player::getShape() {
    
    return m_Shape;
    
}

Vector2f Player::getCenter() {
    
    return m_Position;
    
}

FloatRect Player::getPosition() {
    
    return m_Shape.getGlobalBounds();
    
}

void Player::moveUp() {
    m_MovingUp = true;
}

void Player::moveDown() {
    m_MovingDown = true;
}

void Player::moveLeft() {
    m_MovingLeft = true;
}

void Player::moveRight() {
    m_MovingRight = true;
}

void Player::stopUp() {
    m_MovingUp = false;
}

void Player::stopDown() {
    m_MovingDown = false;
}

void Player::stopLeft() {
    m_MovingLeft = false;
}

void Player::stopRight() {
    m_MovingRight = false;
}

void Player::spawn() {
    
    // Spawn in screen center
    m_Position.x = (m_Screen.x / 2.0f) - (m_Shape.getSize().x / 2.0f);
    m_Position.y = (m_Screen.y / 2.0f) - (m_Shape.getSize().y / 2.0f);
    m_Shape.setPosition(m_Position);
    
    m_MovingUp = false;
    m_MovingDown = false;
    m_MovingLeft = false;
    m_MovingRight = false;
    
}

void Player::update(Time dt) {
    
    if (m_MovingUp) {
        
        m_Position.y -= m_Speed * dt.asSeconds();
        
    }
    
    if (m_MovingDown) {
        
        m_Position.y += m_Speed * dt.asSeconds();
        
    }
    
    if (m_MovingLeft) {
        
        m_Position.x -= m_Speed * dt.asSeconds();
        
    }
    
    if (m_MovingRight) {
        
        m_Position.x += m_Speed * dt.asSeconds();
        
    }
    
    // Prevent movement out of screen
    float playerLength = m_Shape.getSize().x;
    
    if (m_Position.x > m_Screen.x - playerLength) {
        
        m_Position.x = m_Screen.x - playerLength;
        
    }
    
    if (m_Position.x < 0) {
        
        m_Position.x = 0;
        
    }
    
    if (m_Position.y > m_Screen.y - playerLength) {
        
        m_Position.y = m_Screen.y - playerLength;
        
    }
    
    if (m_Position.y < 0) {
        
        m_Position.y = 0;
        
    }
    
    // Moves the shape object associated with player
    m_Shape.setPosition(m_Position);
    
}
