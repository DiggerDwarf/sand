#ifndef APPLICATION_INCLUDED 
#define APPLICATION_INCLUDED

#include <SFML/Graphics.hpp>                 
#include <iostream>
#include <random>

#define BAR_SIZE 140
#define TILE_SIZE 20
#define GRID_HEIGHT WIN_HEIGHT / TILE_SIZE
#define GRID_WIDTH  WIN_WIDTH / TILE_SIZE
#define WIN_HEIGHT 720
#define WIN_WIDTH 1120
#define WIN_TITLE "sand."


void setup(int (&tiles)[GRID_WIDTH][GRID_HEIGHT]);

void draw(sf::RenderWindow *window, int (&tiles)[GRID_WIDTH][GRID_HEIGHT], sf::Sprite& toolbar, sf::Sprite& titlebar);

void update_tiles(int (&tiles)[GRID_WIDTH][GRID_HEIGHT], int& current);

bool update_window(sf::RenderWindow* window, int& current);

#endif