#include "map.h"

Tile::Tile(int t_symbol, const TCODColor& t_fg_color, const TCODColor& t_bg_color_vis, const TCODColor& t_bg_color_hid,
           bool t_explored, bool t_block_move, bool t_block_sight) :
           m_symbol(t_symbol), 
           m_fg_color(t_fg_color), 
           m_bg_color_vis(t_bg_color_vis), 
           m_bg_color_hid(t_bg_color_hid),
           m_explored(t_explored), 
           m_block_move(t_block_move), 
           m_block_sight(t_block_sight)
{

}

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

void Tile::set_explored()
{
    m_explored = true;
}

void Tile::draw(int x, int y, bool fov, TCODConsole* canvas) const
{
    canvas -> setCharForeground(x, y, m_fg_color);
    canvas -> setChar(x, y, m_symbol);

    if(fov == true)
        canvas -> setCharBackground(x, y, m_bg_color_vis);
    else
        canvas -> setCharBackground(x, y, m_bg_color_hid);
}

Room::Room()
{

}

// Room::Room(std::vector<int>& t_grid)
// {
//     m_room_grid = t_grid;
// }

Room::Room(const Room& t_room)
{
    m_room_grid = t_room.m_room_grid;
}

void Room::add_point(const int i)
{
    m_room_grid.push_back(i);
}

void Room::set_room_grid(std::vector<int>& t_grid)
{
    m_room_grid = t_grid;
}

std::vector<int> Room::return_grid() const
{
    return m_room_grid;
}

Map::Map(int t_width, int t_height) : m_width(t_width), m_height(t_height) 
{
    m_fovmap = new TCODMap(m_width, m_height);

    for(int idx = 0; idx < m_width * m_height; ++idx)
    {
        m_tiles.push_back(new Tile('#', TCODColor::white, TCODColor::darkGrey, TCODColor::darkerGrey, true, true, false));
    }
}

Map::~Map()
{
    for(int idx = 0; idx < m_tiles.size(); ++idx)
    {
        delete m_tiles[idx];
    }
    delete m_fovmap;
}

bool Map::block_move(int x, int y) const
{
    return m_tiles.at(x + (y * m_width)) -> block_move();
}

bool Map::block_sight(int x, int y) const
{
    return m_tiles.at(x + (y * m_width)) -> block_sight();
}

bool Map::is_explored(int x, int y) const
{
    return m_tiles.at(x + (y * m_width)) -> is_explored();
}

void Map::render(TCODConsole* canvas) const
{
    for(int x = 0; x < m_width; ++x)
    {
        for(int y = 0; y < m_height; ++y)
        {
            if(m_tiles.at(x + (y * m_width)) != nullptr)
            {
                if(is_in_fov(x, y))
                    m_tiles.at(x + (y * m_width)) -> draw(x, y, true, canvas);
                else if(m_tiles.at(x + (y * m_width)) -> is_explored())
                    m_tiles.at(x + (y * m_width)) -> draw(x, y, false, canvas);
            }
        }
    }
}

void Map::add_tile(int x, int y, Tile* t_tile)
{
    delete m_tiles.at(x + (y * m_width));
    m_tiles.at(x + (y * m_width)) = t_tile;
}

Tile* Map::get_tile(int x, int y) const
{
    return m_tiles.at(x + (y * m_width));
}

void Map::grid_to_map(std::vector<int> t_grid)
{
    for(int y = 0; y < m_height; ++y)
    {
        for(int x = 0; x < m_width; ++x)
        {
            int idx = x + (y * m_width);
            delete m_tiles.at(idx);
        
            if(t_grid.at(idx) == 1)
            {
                m_tiles.at(idx) = new Tile(' ', TCODColor::black, TCODColor::sepia, TCODColor::darkerSepia, false, false, false);
                m_fovmap -> setProperties(x, y, true, true);
            }
            else
            {
                m_tiles.at(idx) = new Tile('#', TCODColor::white, TCODColor::darkGrey, TCODColor::darkerGrey, false, true, true);
                m_fovmap -> setProperties(x, y, false, false);
            }
        }
    }
}

void Map::compute_fov(int x, int y, int r) const
{
    m_fovmap -> computeFov(x, y, r, true, FOV_SHADOW);
}

bool Map::is_in_fov(int x, int y) const
{
    if(m_fovmap -> isInFov(x, y))
    {
        m_tiles.at(x + (y * m_width)) -> set_explored();
        return true;
    }
    else
        return false;
}