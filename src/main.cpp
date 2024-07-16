#include "Application.hpp"
#include <chrono>

template <typename T>
void swap(T& x1, T& x2)
{
    x1 = x1 ^ x2;
    x2 = x1 ^ x2;
    x1 = x1 ^ x2;
}

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, BAR_SIZE + WIN_HEIGHT + BAR_SIZE), WIN_TITLE, sf::Style::None);
    window.setFramerateLimit(50);
    // window.setVerticalSyncEnabled(false);

    int tiles[GRID_WIDTH][GRID_HEIGHT];

    sf::Sprite toolbar;
    sf::Texture toolbarTexture;
    sf::Sprite titlebar;
    sf::Texture titlebarTexture;

    toolbarTexture.loadFromFile("resources/toolbar.png");
    titlebarTexture.loadFromFile("resources/titlebar.png");

    toolbar.setTexture(toolbarTexture);
    toolbar.setPosition({0, BAR_SIZE + WIN_HEIGHT});
    toolbar.setScale(TILE_SIZE, TILE_SIZE);
    titlebar.setTexture(titlebarTexture);
    titlebar.setPosition({0, 0});
    titlebar.setScale(TILE_SIZE, TILE_SIZE);

    setup(tiles);
    
    int current = 1;
    sf::Clock clock;
    sf::Time total_time;
    while (true)
    {
        if (update_window(&window, current, tiles)) break;

        update_tiles(tiles, current);

        draw(&window, tiles, toolbar, titlebar, current);

        sf::Time dt = clock.restart();
        total_time += dt;

        // std::cout << 1.f/dt.asSeconds() << "\n";
    }

    return 0;
}