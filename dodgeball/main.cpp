#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

#include "./entity/Player.hpp"
#include "./entity/enemy/Ball.hpp"

using namespace sf;

int main(int, char const**)
{
    enum class State { PLAYING, GAME_OVER };
    
    State state = State::GAME_OVER;
    
    // Create the main window
    RenderWindow window(sf::VideoMode(800, 600), "Dodgeball!");
    
    Player player = Player(375, 275);
    
    Ball enemy = Ball();
    
    // Seed the random generator
    srand((int) time(0));

    Clock clock;
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events, keypresses, etc.
        Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                window.close();
            }
            
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return && state == State::GAME_OVER) {
                
                state = State::PLAYING;
                
                clock.restart();
            }
            
        }
        
        if (state == State::GAME_OVER) {
            
            window.clear();
            
            // Draw things here
            window.draw(player.getShape());
            window.draw(enemy.getShape());
            
            player.reset();
            
        }
        
        if (state == State::PLAYING) {
            
            Event movement;
            window.pollEvent(movement);
            // Arrow up
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up) {
                player.moveUp();
            }
            
            // Release up
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Up) {
                player.stopUp();
            }
            
            // Arrow down
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Down) {
                player.moveDown();
            }
            
            // Release down
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Down) {
                player.stopDown();
            }
            
            // Arrow left
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Left) {
                player.moveLeft();
            }
            
            // Release left
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Left) {
                player.stopLeft();
            }
            
            // Arrow right
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Right) {
                player.moveRight();
            }
            
            // Release right
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Right) {
                player.stopRight();
            }
            
            // Update the scene
            Time dt = clock.restart();
            player.update(dt);
            
            if (enemy.isActive()) {
                enemy.update(dt);
            } else {
                // Throw the ball
                enemy.spawn(player.getCenter());
            }
            
            // Detect collision
            if (player.getPosition().intersects(enemy.getPosition())) {
                
                enemy.hit();
                
                // End game
                state = State::GAME_OVER;
                
            }

            // Clear screen
            window.clear();
            
            // Draw things here
            window.draw(player.getShape());
            window.draw(enemy.getShape());
            
        }
        // Update the window
        window.display();
        
    }

    return EXIT_SUCCESS;
}
