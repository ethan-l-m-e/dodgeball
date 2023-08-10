#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

using namespace sf;

int main(int, char const**)
{
    // Create the main window
    RenderWindow window(sf::VideoMode(800, 600), "Dodgeball!");
    
    RectangleShape player;
    
    player.setSize(Vector2f(50, 50));
    
    player.setPosition(375, 275);
    
    float playerSpeed = 50.0f;
    
    bool moveUp = false;

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
            
            // Arrow up
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Up) {
                moveUp = true;
            } else {
                moveUp = false;
            }
        }
        
        // Update the scene
        Time dt = clock.restart();
        
        if (moveUp) {
            Vector2f newPosition = player.getPosition();
            newPosition.y -= playerSpeed * dt.asSeconds();
            player.setPosition(newPosition.x, newPosition.y);
        }

        // Clear screen
        window.clear();
        
        // Draw things here
        window.draw(player);
        
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
