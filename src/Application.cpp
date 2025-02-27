#include "Application.hpp"

sf::Color palette[] = {
    sf::Color(  0x000000ff  ),
    sf::Color(  0xffc300ff  ),
    sf::Color(  0x555555ff  ),
    sf::Color(  0x1111eeff  ),
    sf::Color(  0xff6600ff  ),
    sf::Color(  0x42007aff  ),
    sf::Color(  0x22b14cff  )
};

enum BLOCKS {
    AIR = 0,
    SAND = 1,
    WALL,
    WATER,
    LAVA,
    OBSIDIAN,
    GREEN
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
                tiles[x][y] = BLOCKS::OBSIDIAN;
                continue;
            }
            tiles[x][y] = BLOCKS::AIR;
            // tiles[x][y] = x%2 xor y%2;
        }
    }
}

void draw( sf::RenderWindow *window, int ( &tiles )[ GRID_WIDTH ][ GRID_HEIGHT ], const sf::Sprite& toolbar, sf::Sprite& titlebar, int& current )
{
    // window->clear( sf::Color(0x000000ff) );

    sf::RectangleShape rect({TILE_SIZE, TILE_SIZE});
    
    for ( int x = 0; x < GRID_WIDTH; x++ )
    {
        for ( int y = 0; y < GRID_HEIGHT; y++ )
        {
            rect.setFillColor( palette[ tiles[ x ][ y ] ] );
            rect.setPosition({(float)x*TILE_SIZE, (float)(WIN_HEIGHT - (y+1)*TILE_SIZE + BAR_SIZE)});
            window->draw(rect);
        }
        
    }
    
    window->draw(toolbar);
    window->draw(titlebar);

    rect.setSize({7*TILE_SIZE, TILE_SIZE});
    rect.setFillColor(sf::Color(0xffffffff));
    if (current == 0) rect.setPosition(6*7*TILE_SIZE, BAR_SIZE+WIN_HEIGHT+BAR_SIZE-TILE_SIZE);
    else rect.setPosition((current-1)*7*TILE_SIZE, BAR_SIZE+WIN_HEIGHT+BAR_SIZE-TILE_SIZE);
    window->draw(rect);

    window->display();
}

void update_tiles(int (&tiles)[GRID_WIDTH][GRID_HEIGHT], int& current)
{
    // tiles[64][40] = 1;
    int alea;
    for (int y = 1; y < (GRID_HEIGHT) - 1; y++)
    {
        for (int x = 1; x < (GRID_WIDTH) - 1; x++)
        {
            switch (tiles[x][y])
            {
            case BLOCKS::SAND:
            {
                alea = ((rand()%2) * 2) - 1;
                if (tiles[x][y-1] == BLOCKS::AIR || tiles[x][y-1] == BLOCKS::WATER) {
                    tiles[x][y]   = tiles[x][y-1];
                    tiles[x][y-1] = BLOCKS::SAND;
                }
                else if (tiles[x-alea][y-1] == BLOCKS::AIR || tiles[x-alea][y-1] == BLOCKS::WATER || tiles[x-alea][y-1] == BLOCKS::LAVA) {
                    tiles[x][y]   = tiles[x-alea][y-1];
                    tiles[x-alea][y-1] = BLOCKS::SAND;
                }
                else if (tiles[x+alea][y-1] == BLOCKS::AIR || tiles[x+alea][y-1] == BLOCKS::WATER || tiles[x+alea][y-1] == BLOCKS::WATER) {
                    tiles[x][y]   = tiles[x+alea][y-1];
                    tiles[x+alea][y-1] = BLOCKS::SAND;
                }
                
                break;
            }
            case BLOCKS::WATER:
            {
                alea = ((rand()%2) * 2) - 1;
                if (tiles[x][y-1] == BLOCKS::AIR) {
                    tiles[x][y]   = BLOCKS::AIR;
                    tiles[x][y-1] = BLOCKS::WATER;
                }
                else if (tiles[x][y-1] == BLOCKS::LAVA) {
                    tiles[x][y]   = BLOCKS::AIR;
                    tiles[x][y-1] = BLOCKS::OBSIDIAN;
                }
                else if (tiles[x][y-1] == BLOCKS::WALL && rand()%1000 == 0) {
                    tiles[x][y-1] = BLOCKS::AIR;
                }
                else if (tiles[x-alea][y-1] == BLOCKS::AIR) {
                    tiles[x][y]   = BLOCKS::AIR;
                    tiles[x-alea][y-1] = BLOCKS::WATER;
                }
                else if (tiles[x+alea][y-1] == BLOCKS::AIR) {
                    tiles[x][y]   = BLOCKS::AIR;
                    tiles[x+alea][y-1] = BLOCKS::WATER;
                }
                else if (tiles[x-alea][y] == BLOCKS::AIR) {
                    tiles[x][y]   = BLOCKS::AIR;
                    tiles[x-alea][y] = BLOCKS::WATER;
                }
                else if (tiles[x+alea][y] == BLOCKS::AIR) {
                    tiles[x][y]   = BLOCKS::AIR;
                    tiles[x+alea][y] = BLOCKS::WATER;
                }
                
                break;
            }
            case BLOCKS::LAVA:
            {
                alea = ((rand()%2) * 2) - 1;
                if (tiles[x][y-1] == BLOCKS::AIR) {
                    tiles[x][y]   = BLOCKS::AIR;
                    tiles[x][y-1] = BLOCKS::LAVA;
                }
                else if (tiles[x][y-1] == BLOCKS::WATER) {
                    tiles[x][y]   = BLOCKS::AIR;
                    tiles[x][y-1] = BLOCKS::WALL;
                }
                else if (tiles[x][y-1] == BLOCKS::GREEN) {
                    tiles[x][y]   = BLOCKS::AIR;
                    tiles[x][y-1] = BLOCKS::LAVA;
                }
                else if (tiles[x-alea][y-1] == BLOCKS::AIR) {
                    tiles[x][y]   = BLOCKS::AIR;
                    tiles[x-alea][y-1] = BLOCKS::LAVA;
                }
                else if (tiles[x+alea][y-1] == BLOCKS::AIR) {
                    tiles[x][y]   = BLOCKS::AIR;
                    tiles[x+alea][y-1] = BLOCKS::LAVA;
                }
                else if (tiles[x-alea][y] == BLOCKS::AIR || tiles[x-alea][y] == BLOCKS::GREEN) {
                    tiles[x][y]   = BLOCKS::AIR;
                    tiles[x-alea][y] = BLOCKS::LAVA;
                }
                else if (tiles[x+alea][y] == BLOCKS::AIR || tiles[x+alea][y] == BLOCKS::GREEN) {
                    tiles[x][y]   = BLOCKS::AIR;
                    tiles[x+alea][y] = BLOCKS::LAVA;
                }
                
                break;
            }
            case BLOCKS::GREEN:
            {
                alea =      (rand()%3) - 1;
                int alea2 = (rand()%3) - 1;
                if (tiles[x+alea][y+alea2] == BLOCKS::WATER && rand()%2 == 0)
                {
                    tiles[x+alea][y+alea2] = BLOCKS::GREEN;
                }
                else if (tiles[x+alea][y+alea2] == BLOCKS::WALL)
                {
                    if (rand()%30 == 1)
                    {
                        tiles[x+alea][y+alea2] = BLOCKS::GREEN;
                    }
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
        mousePosition.y = BAR_SIZE + WIN_HEIGHT - mousePosition.y;
        mousePosition /= TILE_SIZE;

        if (mousePosition.x >= 1 && mousePosition.x <= (GRID_WIDTH-2) && mousePosition.y >= 1 && mousePosition.y <= (GRID_HEIGHT-2))
        {
            tiles[mousePosition.x][mousePosition.y] = current;
        }
    }
    
}

bool update_window(sf::RenderWindow* window, int& current, int (&tiles)[GRID_WIDTH][GRID_HEIGHT])
{
    sf::Event event;
    windowPosition = window->getPosition();
    bool out = false;
    sf::Vector2i mPos = sf::Mouse::getPosition();
    while (window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window->close();
            out = true;
            break;

        case sf::Event::MouseButtonPressed:
            if (mPos.y - windowPosition.y > BAR_SIZE + WIN_HEIGHT)
            {
                if (mPos.x - windowPosition.x > WIN_WIDTH - 7*TILE_SIZE)
                {
                    // window->close();
                    // out = true;
                    setup(tiles);
                }
                else
                {
                    current = (int)((mPos.x-windowPosition.x)/(TILE_SIZE*7))+1;
                    if (current == 7) current = 0;
                }
                
            }
            break;
            

        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                window->close();
                out = true;
                break;
            case sf::Keyboard::Num0:
                current = BLOCKS::AIR;
                break;
            case sf::Keyboard::Num1:
                current = BLOCKS::SAND;
                break;
            case sf::Keyboard::Num2:
                current = BLOCKS::WALL;
                break;
            case sf::Keyboard::Num3:
                current = BLOCKS::WATER;
                break;
            case sf::Keyboard::Num4:
                current = BLOCKS::LAVA;
                break;
            case sf::Keyboard::Num5:
                current = BLOCKS::OBSIDIAN;
                break;
            case sf::Keyboard::Num6:
                current = BLOCKS::GREEN;
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
