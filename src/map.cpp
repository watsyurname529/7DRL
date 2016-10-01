#include "map.h"

Tile::Tile(int t_symbol, const TCODColor& t_fg_color, const TCODColor& t_bg_color, 
           bool t_explored, bool t_block_move, bool t_block_sight) :
           m_symbol(t_symbol), m_fg_color(t_fg_color), m_bg_color(t_bg_color), 
           m_explored(t_explored), m_block_move(t_block_move), m_block_sight(t_block_sight) {}

bool Tile::block_move() const
{
    return m_block_move;
}

bool Tile::block_sight() const
{
    return m_block_sight;
}

bool Tile::is_explored() const
{
    return m_explored;
}

void Tile::draw(int x, int y, TCODConsole* canvas) const
{
    canvas -> setCharBackground(x, y, m_bg_color);
    canvas -> setCharForeground(x, y, m_fg_color);
    canvas -> setChar(x, y, m_symbol);
}

Map::Map(int t_width, int t_height) : m_width(t_width), m_height(t_height) 
{
    for(int idx = 0; idx < m_width * m_height; ++idx)
    {
        m_tiles.push_back(new Tile('#', TCODColor::white, TCODColor::darkGrey, true, true, false));
    }
}

Map::~Map()
{
    for(int idx = 0; idx < m_width * m_height; ++idx)
    {
        delete m_tiles[idx];
    }
}

bool Map::block_move(int x, int y) const
{
    return m_tiles[x + (y * m_width)] -> block_move();
}

bool Map::block_sight(int x, int y) const
{
    return m_tiles[x + (y * m_width)] -> block_sight();
}

bool Map::is_explored(int x, int y) const
{
    return m_tiles[x + (y * m_width)] -> is_explored();
}

void Map::render(TCODConsole* canvas) const
{
    for(int x = 0; x < m_width; ++x)
    {
        for(int y = 0; y < m_height; ++y)
        {
            if(m_tiles[x + (y * m_width)] != NULL)
                m_tiles[x + (y * m_width)] -> draw(x, y, canvas);
        }
    }
}

void Map::add_tile(int x, int y, Tile* t_tile)
{
    delete m_tiles[x + (y * m_width)];
    m_tiles[x + (y * m_width)] = t_tile;
}

Tile* Map::get_tile(int x, int y) const
{
    return m_tiles[x + (y * m_width)];
}