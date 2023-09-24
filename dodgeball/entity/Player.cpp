//
//  Player.cpp
//  dodgeball
//
//  Created by リム・イーサン on 10/8/23.
//  Copyright © 2023 リム・イーサン. All rights reserved.
//

#include "Player.hpp"
#include "ResourcePath.hpp"

Player::Player()
{
    // Set the player hitbox size
    m_Shape.setSize(Vector2f(30, 50));
    
    // Center the player hitbox
    m_Shape.setOrigin(15, 25);
    
    // Load textures and sprite
    m_IdleTexture.loadFromFile(resourcePath() + "player-idle.png"); // 10 frames
    m_RunTexture.loadFromFile(resourcePath() + "player-run.png"); // 8 frames
    m_Sprite.setTexture(m_IdleTexture);
    m_TextureRect = IntRect(0, 0, 70, 70);
    m_Sprite.setTextureRect(m_TextureRect);
    
    // Center the sprite
    m_Sprite.setOrigin(35, 35);
    
    // Set elapsed time
    m_TimeSinceLastSpriteUpdate = 0.0f;
}

RectangleShape Player::getShape()
{
    return m_Shape;
}

Sprite Player::getSprite()
{
    return m_Sprite;
}

void Player::flipSprite()
{
    // Set the correct direction
    if (m_MovingLeft)
    {
        m_Sprite.setScale(-1, 1);
    }
    if (m_MovingRight)
    {
        m_Sprite.setScale(1, 1);
    }
}

void Player::animate(Time dt) {
    
    // Accumulate time passed since sprite frame change
    m_TimeSinceLastSpriteUpdate += dt.asSeconds();
    
    // Update sprite frame every 0.1 seconds
    if (m_TimeSinceLastSpriteUpdate > 0.1)
    {
        m_TimeSinceLastSpriteUpdate = 0.0f;
        
        int left = m_Sprite.getTextureRect().left;
        
        if (isMoving())
        {
            m_Sprite.setTexture(m_RunTexture);
            
            // Sprite sheet is 70 x 560, last frame starts at 510
            if (left >= m_RunTexture.getSize().x - 70)
            {
                // Loop back to first frame
                m_TextureRect.left = 0;
            }
            else
            {
                // Move to the next frame
                m_TextureRect.left += 70;
            }
        }
        // Else player is idle
        else
        {
            m_Sprite.setTexture(m_IdleTexture);
            
            // Sprite sheet is 70 x 700, last frame starts at 630
            if (left >= m_IdleTexture.getSize().x - 70)
            {
                // Loop back to first frame
                m_TextureRect.left = 0;
            }
            else
            {
                // Move to the next frame
                m_TextureRect.left += 70;
            }
        }
        
        // Update the texture coordinates
        m_Sprite.setTextureRect(m_TextureRect);
    }
}

bool Player::isMoving()
{
    if (m_MovingUp ||
        m_MovingDown ||
        m_MovingLeft ||
        m_MovingRight)
    {
        return true;
    }
    
    return false;
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
    m_Position.x = (m_Arena.width / 2.0f);
    m_Position.y = (m_Arena.height / 2.0f);
    m_Shape.setPosition(m_Position);
    m_Sprite.setPosition(m_Position);
    
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
    float horizontalPlayerRadius = m_Shape.getSize().x / 2;
    float verticalPlayerRadius = m_Shape.getSize().y / 2;
    
    if (m_Position.x > m_Arena.width - horizontalPlayerRadius)
    {
        m_Position.x = m_Arena.width - horizontalPlayerRadius;
    }
    
    if (m_Position.x < m_Arena.left + horizontalPlayerRadius)
    {
        m_Position.x = m_Arena.left + horizontalPlayerRadius;
    }
    
    if (m_Position.y > m_Arena.height - verticalPlayerRadius)
    {
        m_Position.y = m_Arena.height - verticalPlayerRadius;
    }
    
    if (m_Position.y < m_Arena.top + verticalPlayerRadius)
    {
        m_Position.y = m_Arena.top + verticalPlayerRadius;
    }
    
    // Moves the shape object associated with player
    m_Shape.setPosition(m_Position);
    m_Sprite.setPosition(m_Position);
    
    // Animate the sprite
    animate(dt);
    flipSprite();
}
