#include "Application.hpp"

sf::Color palette[] = {
    sf::Color(  0x000000ff  ),
    sf::Color(  0xffc300ff  ),
    sf::Color(  0x555555ff  ),
    sf::Color(  0x1111eeff  )
};

sf::Vector2i windowPosition({0,0});

void setup(int (&tiles)[GRID_WIDTH][GRID_HEIGHT])
{
    srand(time(nullptr));
    for ( int x = 0; x < GRID_WIDTH; x++ )
    {
        for ( int y = 0; y < GRID_HEIGHT; y++ )
        {
            if( (x==0) || (y==0) || (x==GRID_WIDTH -1) || (y==GRID_HEIGHT -1))
            {
                tiles[x][y] = 2;
                continue;
            }
            tiles[x][y] = 0;
            // tiles[x][y] = x%2 xor y%2;
        }
    }
}

void draw( sf::RenderWindow *window, int ( &tiles )[ GRID_WIDTH ][ GRID_HEIGHT ] )
{
    window->clear( sf::Color(0x000000ff) );

    sf::RectangleShape rect({TILE_SIZE, TILE_SIZE});
    
    for ( int x = 0; x < GRID_WIDTH; x++ )
    {
        for ( int y = 0; y < GRID_HEIGHT; y++ )
        {
            rect.setFillColor( palette[ tiles[ x ][ y ] ] );
            rect.setPosition({(float)x*TILE_SIZE, (float)(WIN_HEIGHT - (y+1)*TILE_SIZE)});
            window->draw(rect);
        }
        
    }
    

    window->display();
}

void update_tiles(int (&tiles)[GRID_WIDTH][GRID_HEIGHT], int& current)
{
    tiles[64][40] = 1;
    int alea;
    for (int y = 1; y < (GRID_HEIGHT) - 1; y++)
    {
        for (int x = 1; x < (GRID_WIDTH) - 1; x++)
        {
            switch (tiles[x][y])
            {
            case 0:
                break;
            case 1:
            {
                alea = ((rand()%2) * 2) - 1;
                if (tiles[x][y-1] == 0 || tiles[x][y-1] == 3) {
                    tiles[x][y]   = tiles[x][y-1];
                    tiles[x][y-1] = 1;
                }
                else if (tiles[x-alea][y-1] == 0 || tiles[x-alea][y-1] == 3) {
                    tiles[x][y]   = tiles[x-alea][y-1];
                    tiles[x-alea][y-1] = 1;
                }
                else if (tiles[x+alea][y-1] == 0 || tiles[x+alea][y-1] == 3) {
                    tiles[x][y]   = tiles[x+alea][y-1];
                    tiles[x+alea][y-1] = 1;
                }
                
                break;
            }
            case 3:
            {
                alea = ((rand()%2) * 2) - 1;
                if (tiles[x][y-1] == 0) {
                    tiles[x][y]   = 0;
                    tiles[x][y-1] = 3;
                }
                else if (tiles[x-alea][y-1] == 0) {
                    tiles[x][y]   = 0;
                    tiles[x-alea][y-1] = 3;
                }
                else if (tiles[x+alea][y-1] == 0) {
                    tiles[x][y]   = 0;
                    tiles[x+alea][y-1] = 3;
                }
                else if (tiles[x-alea][y] == 0) {
                    tiles[x][y]   = 0;
                    tiles[x-alea][y] = 3;
                }
                else if (tiles[x+alea][y] == 0) {
                    tiles[x][y]   = 0;
                    tiles[x+alea][y] = 3;
                }
                
                break;
            }
            default:
                break;
            }
        }
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition();
        mousePosition -= windowPosition;
        mousePosition.y = WIN_HEIGHT - mousePosition.y;
        mousePosition /= TILE_SIZE;
        mousePosition.x = std::max(std::min(mousePosition.x, GRID_WIDTH  -2), 1);
        mousePosition.y = std::max(std::min(mousePosition.y, GRID_HEIGHT -2), 1);

        tiles[mousePosition.x][mousePosition.y] = current;
    }
    
}

bool update_window(sf::RenderWindow* window, int& current)
{
    sf::Event event;
    windowPosition = window->getPosition();
    bool out = false;
    while (window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window->close();
            out = true;
            break;

        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
            case sf::Keyboard::Num0:
                current = 0;
                break;
            case sf::Keyboard::Num1:
                current = 1;
                break;
            case sf::Keyboard::Num2:
                current = 2;
                break;
            case sf::Keyboard::Num3:
                current = 3;
                break;
            
            default:
                break;
            }
        
        default:
            break;
        }
    }
    return out;
}