#include "generate_aux.h"

void aux::bresenham_line(int i1, int i2, std::vector<int>& grid)
{

}

void aux::bresenham_line(int x1, int y1, int x2, int y2, std::vector<int>& grid)
{

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