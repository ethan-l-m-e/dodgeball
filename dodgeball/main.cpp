#include <sstream>
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
    
    Vector2f resolution;
    resolution.x = 800.0f;
    resolution.y = 600.0f;
    
    IntRect arena;
    arena.width = resolution.x;
    arena.height = resolution.y;
    arena.left = 0;
    arena.top = 0;
    
    // Create the main window
    RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "Dodgeball!");
    
    // Scoring
    int score = 0;
    Text scoreText;
    Font font;
    font.loadFromFile(resourcePath() + "Gameplay.ttf");
    scoreText.setFont(font);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(15, 10);
    scoreText.setCharacterSize(36);
    scoreText.setString("Score: 0");
    
    // Game players
    Player player;
    player.spawn(arena);
    
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
            
            if (event.type == Event::KeyPressed &&
                (event.key.code == Keyboard::Up ||
                 event.key.code == Keyboard::Down ||
                 event.key.code == Keyboard::Left ||
                 event.key.code == Keyboard::Right) && state == State::GAME_OVER) {
                
                state = State::PLAYING;
                
                clock.restart();
                
                score = 0;
                
                player.spawn(arena);
            }
            
            if (state == State::PLAYING) {
                
                // Handle player controls when game is playing
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
                
            }
            
        }
        
        if (state == State::GAME_OVER) {
            
            window.clear();
            
            // Draw things here
            window.draw(player.getShape());
            window.draw(enemy.getShape());
            
        }
        
        if (state == State::PLAYING) {
            
            // Update the scene
            Time dt = clock.restart();
            player.update(dt);
            
            if (!enemy.isActive())
            {
                if (enemy.hasMissed())
                {
                    score++;
                }
                
                // Re-throw ball
                enemy.spawn(arena, player.getCenter());
            }
            else
            {
                enemy.update(dt);
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
        
        std::stringstream ss;
        
        ss << "Score: " << score;
        
        scoreText.setString(ss.str());
        
        window.draw(scoreText);
        
        // Update the window
        window.display();
        
    }

    return EXIT_SUCCESS;
}
