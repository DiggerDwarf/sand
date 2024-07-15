#include "Application.hpp"
#include <chrono>

int main(int argc, char* argv[]) {
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), WIN_TITLE, sf::Style::Close);
    window.setFramerateLimit(60);

    int tiles[GRID_WIDTH][GRID_HEIGHT];

    setup(tiles);
    
    int current = 1;

    sf::Clock clock;
    sf::Time total_time;

    while (true)
    {
        if (update_window(&window, current)) break;

        draw(&window, tiles);

        update_tiles(tiles, current);

        sf::Time dt = clock.restart();
        total_time += dt;

        std::cout << 1.f/dt.asSeconds() << "\n";
    }

    return 0;
}