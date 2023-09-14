//
//  Ball.hpp
//  dodgeball
//
//  Created by リム・イーサン on 12/8/23.
//  Copyright © 2023 リム・イーサン. All rights reserved.
//

#ifndef Ball_hpp
#define Ball_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

using namespace sf;

class Ball
{
    
private:
    
    // Ball's current position
    Vector2f m_Position;
    
    // Circle representing ball
    CircleShape m_Shape;
    
    // Ball sprite
    Sprite m_Sprite;
    
    // Ball texture
    Texture m_Texture;
    
    // Arena defining the bounds of screen
    IntRect m_Arena;
    
    // How fast ball moves
    float m_Speed = 500.0f;

    // Ratio of x or y direction vs straight-line-distance travelled
    float m_DirectionX = 1.0f;
    float m_DirectionY = 0.0f;
    
    // Is ball being used
    bool m_Active = false;
    
    // Has ball flown out of screen
    bool m_Missed = false;
    
    // Random position just out of screen
    void setInitialRandomisedPosition(IntRect arena);
    
public:
    
    Ball();
    
    // Get shape object representing ball
    CircleShape getShape();
    
    // Get sprite object representing ball
    Sprite getSprite();
    
    // Where is the ball
    FloatRect getPosition();
    
    // Check if ball is being used
    bool isActive();
    
    // Used to help count scores
    bool hasMissed();
    
    // Ball collides with another object
    void hit();
    
    // Deactivate when game state change
    void deactivate();
    
    // Spawning and activating a ball
    void spawn(IntRect arena, Vector2f target);
    
    // Called every frame
    void update(Time dt);

};

#endif /* Ball_hpp */
