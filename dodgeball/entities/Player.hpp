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
    
    Vector2f m_Position;
    RectangleShape m_Shape;
    float m_Speed = 50.0f;
    bool m_MovingUp = false;
    
public:
    
    Player(float startX, float startY);
    RectangleShape getShape();
    void moveUp();
    void stopUp();
    void update(Time dt);
    
};

#endif /* Player_hpp */
