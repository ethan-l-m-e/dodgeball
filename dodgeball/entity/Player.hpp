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
    
    // Screen resolution
    Vector2f m_Screen;
    
    // How fast player moves
    float m_Speed = 500.0f;
    
    // Which direction player is moving
    bool m_MovingUp = false;
    bool m_MovingDown = false;
    bool m_MovingLeft = false;
    bool m_MovingRight = false;
    
public:
    
    // Create player within given screen size
    Player(float startX, float startY, Vector2f screen);
    
    // Get shape object representing player
    RectangleShape getShape();
    
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
    void spawn();
    
    // Call once every frame
    void update(Time dt);
    
};

#endif /* Player_hpp */
