//
//  Player.cpp
//  dodgeball
//
//  Created by リム・イーサン on 10/8/23.
//  Copyright © 2023 リム・イーサン. All rights reserved.
//

#include "Player.hpp"

Player::Player()
{
    // How big is the player
    m_Shape.setSize(Vector2f(50, 50));
}

RectangleShape Player::getShape()
{
    return m_Shape;
}

Vector2f Player::getCenter()
{
    return m_Position;
}

FloatRect Player::getPosition()
{
    return m_Shape.getGlobalBounds();
}

void Player::moveUp()
{
    m_MovingUp = true;
}

void Player::moveDown()
{
    m_MovingDown = true;
}

void Player::moveLeft()
{
    m_MovingLeft = true;
}

void Player::moveRight()
{
    m_MovingRight = true;
}

void Player::stopUp()
{
    m_MovingUp = false;
}

void Player::stopDown()
{
    m_MovingDown = false;
}

void Player::stopLeft()
{
    m_MovingLeft = false;
}

void Player::stopRight()
{
    m_MovingRight = false;
}

void Player::spawn(IntRect arena)
{
    m_Arena.width = arena.width;
    m_Arena.height = arena.height;
    m_Arena.left = arena.left;
    m_Arena.top = arena.top;
    
    // Spawn in screen center
    m_Position.x = (m_Arena.width / 2.0f) - (m_Shape.getSize().x / 2.0f);
    m_Position.y = (m_Arena.height / 2.0f) - (m_Shape.getSize().y / 2.0f);
    m_Shape.setPosition(m_Position);
    
    // Start player from a still position
    m_MovingUp = false;
    m_MovingDown = false;
    m_MovingLeft = false;
    m_MovingRight = false;
}

void Player::update(Time dt)
{
    if (m_MovingUp)
    {
        m_Position.y -= m_Speed * dt.asSeconds();
    }
    
    if (m_MovingDown)
    {
        m_Position.y += m_Speed * dt.asSeconds();
    }
    
    if (m_MovingLeft)
    {
        m_Position.x -= m_Speed * dt.asSeconds();
    }
    
    if (m_MovingRight)
    {
        m_Position.x += m_Speed * dt.asSeconds();
    }
    
    // Prevent movement out of screen
    float playerLength = m_Shape.getSize().x;
    
    if (m_Position.x > m_Arena.width - playerLength)
    {
        m_Position.x = m_Arena.width - playerLength;
    }
    
    if (m_Position.x < m_Arena.left)
    {
        m_Position.x = m_Arena.left;
    }
    
    if (m_Position.y > m_Arena.height - playerLength)
    {
        m_Position.y = m_Arena.height - playerLength;
    }
    
    if (m_Position.y < m_Arena.top)
    {
        m_Position.y = m_Arena.top;
    }
    
    // Moves the shape object associated with player
    m_Shape.setPosition(m_Position);
}
