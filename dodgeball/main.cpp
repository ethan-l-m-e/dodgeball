#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

using namespace sf;

int main(int, char const**)
{
    // Create the main window
    RenderWindow window(sf::VideoMode(800, 600), "Dodgeball!");

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
        }

        // Clear screen
        window.clear();
        
        // Draw things here
        
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
