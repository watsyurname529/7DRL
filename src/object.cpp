#include "libtcod.hpp"
#include "object.h"

Object::Object(Point pos, int ch, const TCODColor &fg, bool t_block_move, bool t_block_sight) :
    m_pos(pos), m_char(ch), m_fg_color(fg), m_block_move(t_block_move), m_block_sight(t_block_sight) {}

Object::Object(int x, int y, int ch, const TCODColor &fg, bool t_block_move, bool t_block_sight) :
    m_pos(m_pos.x = x, m_pos.y = y), m_char(ch), m_fg_color(fg),
    m_block_move(t_block_move), m_block_sight(t_block_sight) {}

void Object::draw(TCODConsole* canvas) const
{
    canvas -> setCharForeground(m_pos.x, m_pos.y, m_fg_color);
    canvas -> setChar(m_pos.x, m_pos.y, m_char);
}

void Object::move_dx(int dx, int dy)
{
    m_pos.x += dx;
    m_pos.y += dy;
}

void Object::move_abs(int x, int y)
{
    m_pos.x = x;
    m_pos.y = y;
}

void Object::move_abs(Point dest)
{
    m_pos = dest;
}

int Object::get_x() const
{
    return m_pos.x;
}

int Object::get_y() const
{
    return m_pos.y;
}

bool Object::block_move() const
{
    return m_block_move;
}

bool Object::block_sight() const
{
    return m_block_sight;
}