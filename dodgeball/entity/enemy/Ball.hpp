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
    
    Vector2f m_Position;
    CircleShape m_Shape;
    float m_Speed = 100.0f;
    float m_DirectionX = 1.0f;
    float m_DirectionY = 0.0f;
    
public:
    
    Ball(float startX, float startY);
    CircleShape getShape();
    void spawn(Vector2f target);
    void update(Time dt);
    
};

#endif /* Ball_hpp */
