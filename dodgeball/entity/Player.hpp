//
//  Player.hpp
//  dodgeball
//
//  Created by リム・イーサン on 10/8/23.
//  Copyright © 2023 リム・イーサン. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

using namespace sf;

class Player

{
    
private:
    
    // Player's current position
    Vector2f m_Position;
    
    // Square representing player
    RectangleShape m_Shape;
    
    // Player sprite
    Sprite m_Sprite;
    
    // Player textures
    Texture m_IdleTexture;
    Texture m_RunTexture;
    
    // IntRect to read correct portion of texture
    IntRect m_TextureRect;
    
    // Flip the sprite when changing directions
    void flipSprite();
    
    // Animation of sprite
    void animate(Time dt);
    
    // Elapsed time for calculating which sprite frame to use
    float m_TimeSinceLastSpriteUpdate;
    
    // Screen resolution
    IntRect m_Arena;
    
    // How fast player moves
    float m_Speed = 500.0f;
    
    // Which direction player is moving
    bool m_MovingUp = false;
    bool m_MovingDown = false;
    bool m_MovingLeft = false;
    bool m_MovingRight = false;
    
    // Is player moving at all
    bool isMoving();
    
public:
    
    // Create player within given screen size
    Player();
    
    // Get shape object representing player
    RectangleShape getShape();
    
    // Get sprite object representing player
    Sprite getSprite();
    
    // Where is the center of player
    Vector2f getCenter();
    
    // Where is the player
    FloatRect getPosition();
    
    // Moving the player
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    
    // Stopping the player
    void stopUp();
    void stopDown();
    void stopLeft();
    void stopRight();
    
    // Respawning the player
    void spawn(IntRect arena);
    
    // Call once every frame
    void update(Time dt);
    
};

#endif /* Player_hpp */
