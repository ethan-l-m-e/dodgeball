#include <sstream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

#include "./entity/Player.hpp"
#include "./entity/enemy/Ball.hpp"

using namespace sf;

int MAX_NUM_DODGEBALLS = 10;

int main(int, char const**)
{
    // Game states
    enum class State { PLAYING, GAME_OVER };
    
    // Begin with game over
    State state = State::GAME_OVER;
    
    // How big is the game window
    Vector2f resolution;
    resolution.x = 800.0f;
    resolution.y = 600.0f;
    
    // Game shall be played within window
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
    
    int bestScore = 0;
    Text bestScoreText;
    bestScoreText.setFont(font);
    bestScoreText.setFillColor(Color::White);
    bestScoreText.setCharacterSize(36);
    bestScoreText.setString("Best: 0");
    bestScoreText.setPosition(15, scoreText.getGlobalBounds().height + 10 + 10);
    
    // Game over stats
    Text timePlayedText;
    timePlayedText.setFont(font);
    timePlayedText.setFillColor(Color::White);
    timePlayedText.setCharacterSize(36);
    
    RectangleShape gameOverBackground;
    gameOverBackground.setSize(resolution);
    gameOverBackground.setFillColor(Color(0, 0, 0, 128));
    
    // Game players
    Player player;
    Ball enemies[MAX_NUM_DODGEBALLS];
    int numOfActiveDodgeballs = 1;
        
    player.spawn(arena);
    
    // Seed the random generator
    srand((int) time(0));

    // Time control
    Clock clock;
    float timeSinceLastDifficultyIncrease;
    float timePlayed;
    
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
            
            // Arrow keys pressed: start game
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return && state == State::GAME_OVER) {
                // Switch game state
                state = State::PLAYING;
                
                // Prevent frame jumps
                clock.restart();
                
                // Reset score
                score = 0;
                
                // Reset dodgeballs
                numOfActiveDodgeballs = 1;
                
                // Reset time
                timePlayed = 0.0f;
                timeSinceLastDifficultyIncrease = 0.0f;
                
                // Respawn the player
                player.spawn(arena);
            }
            
            // Handle player controls while game is playing
            if (state == State::PLAYING)
            {
                // Arrow up
                if (event.type == Event::KeyPressed && (event.key.code == Keyboard::Up || event.key.code == Keyboard::W)) {
                    player.moveUp();
                }
                
                // Release up
                if (event.type == Event::KeyReleased && (event.key.code == Keyboard::Up || event.key.code == Keyboard::W)) {
                    player.stopUp();
                }
                
                // Arrow down
                if (event.type == Event::KeyPressed && (event.key.code == Keyboard::Down || event.key.code == Keyboard::S)) {
                    player.moveDown();
                }
                
                // Release down
                if (event.type == Event::KeyReleased && (event.key.code == Keyboard::Down || event.key.code == Keyboard::S)) {
                    player.stopDown();
                }
                
                // Arrow left
                if (event.type == Event::KeyPressed && (event.key.code == Keyboard::Left || event.key.code == Keyboard::A)) {
                    player.moveLeft();
                }
                
                // Release left
                if (event.type == Event::KeyReleased && (event.key.code == Keyboard::Left || event.key.code == Keyboard::A)) {
                    player.stopLeft();
                }
                
                // Arrow right
                if (event.type == Event::KeyPressed && (event.key.code == Keyboard::Right || event.key.code == Keyboard::D)) {
                    player.moveRight();
                }
                
                // Release right
                if (event.type == Event::KeyReleased && (event.key.code == Keyboard::Right || event.key.code == Keyboard::D)) {
                    player.stopRight();
                }
                
            } // End player controls
            
        } // End event polling
        
        if (state == State::GAME_OVER)
        {
            // Stop all other balls
            for (int i = 0; i < MAX_NUM_DODGEBALLS; i++)
            {
                enemies[i].deactivate();
            }
            
        }
        
        if (state == State::PLAYING)
        {
            // Update the scene
            Time dt = clock.restart();
            timePlayed += dt.asSeconds();
            timeSinceLastDifficultyIncrease += dt.asSeconds();
            
            // Increase dodgeball number every 15 seconds
            if (timeSinceLastDifficultyIncrease > 15 && numOfActiveDodgeballs < MAX_NUM_DODGEBALLS)
            {
                numOfActiveDodgeballs++;
                timeSinceLastDifficultyIncrease = 0.0f;
            }
            
            player.update(dt);
            
            for (int i = 0; i < numOfActiveDodgeballs; i++)
            {
                // Check current enemy statuses
                if (!enemies[i].isActive())
                {
                    if (enemies[i].hasMissed())
                    {
                        // Player has successfully dodged
                        score++;
                    }
                    
                    // Update score text
                    std::stringstream ss;
                    ss << "Score: " << score;
                    scoreText.setString(ss.str());
                    if (score > bestScore)
                    {
                        bestScore = score;
                        std::stringstream ss;
                        ss << "Best: " << bestScore;
                        bestScoreText.setString(ss.str());
                    }
                    
                    // Reset missed enemy
                    enemies[i].spawn(arena, player.getCenter());
                }
                else
                {
                    // Enemy still active, update position
                    enemies[i].update(dt);
                }
                
                // Detect collisions
                if (player.getPosition().intersects(enemies[i].getPosition()))
                {
                    enemies[i].hit();
                    
                    // End game
                    state = State::GAME_OVER;
                    
                    // Update game time played
                    std::stringstream ss;
                    ss << "Time Survived: " << roundf(timePlayed * 100) / 100 << "s";
                    timePlayedText.setString(ss.str());
                    FloatRect timePlayedRect = timePlayedText.getGlobalBounds();
                    timePlayedText.setOrigin(timePlayedRect.width / 2.0f, 0.0f);
                    timePlayedText.setPosition(resolution.x / 2, 200);
                }
            }
            
        } // End playing state updates
        
        // Clear screen
        window.clear();
        
        // Draw things here
        window.draw(player.getShape());
        for (int i = 0; i < numOfActiveDodgeballs; i++)
        {
            window.draw(enemies[i].getSprite());
        }
        
        // End of game stats
        if (state == State::GAME_OVER)
        {
            // Blur out rest of the game
            window.draw(gameOverBackground);
            
            window.draw(timePlayedText);
        }

        // Display updated score
        window.draw(scoreText);
        window.draw(bestScoreText);
                
        // Update the window
        window.display();
        
    } // End game loop

    return EXIT_SUCCESS;
}
