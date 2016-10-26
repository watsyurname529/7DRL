#include "generate_cellular.h"

CellularMap::CellularMap(int t_rnd_seed, int t_map_width, int t_map_height) :
                         m_rnd_seed(t_rnd_seed), 
                         m_map_width(t_map_width), 
                         m_map_height(t_map_height), 
                         m_rnd_engine(t_rnd_seed)
{
    m_grid.resize(m_map_width * m_map_height, TileID::WALL);
}

CellularMap::CellularMap(int t_rnd_seed, int t_map_width, int t_map_height, float t_start) :
                         m_rnd_seed(t_rnd_seed), 
                         m_map_width(t_map_width), 
                         m_map_height(t_map_height),
                         m_start_chance(t_start),
                         m_rnd_engine(t_rnd_seed)
{
    m_grid.resize(m_map_width * m_map_height, TileID::WALL);
}

void CellularMap::set_start_chance(const float t_start)
{
    if(t_start > 1.0 || t_start < 0.0)
    {
        std::cout << "Invalid start probability. Must be 0.0 <= P <= 1.0" << std::endl;
        m_start_chance = 0;
    }
    else
        m_start_chance = t_start;
}

void CellularMap::add_rule(CellRule& t_rule)
{
    m_rules.push_back(t_rule);
}

int CellularMap::get_adjacent_cells(const int x, const int y)
{
    int num_adjacent = 0;

    for(int dx = x-1; dx <= x+1; ++dx)
    {
        for(int dy = y-1; dy <= y+1; ++dy)
        {
            // std::cout << "X=" << dx << " Y=" << dy << std::endl;
            if(dx < 0 || dy < 0 || dx >= m_map_width || dy >= m_map_height || (dx == x && dy == y))
                continue;
            else
            {
                if(m_grid.at(dx + (dy * m_map_width)) == 1)
                    num_adjacent += 1;
            }
        }
    }

    return num_adjacent;
}

int CellularMap::generate_grid(const int t_num_epoch)
{
    if(m_rules.size() == 0)
    {
        std::cout << "No rules for generation. Exiting." << std::endl;
        return -1;
    }

    std::uniform_int_distribution<int> start_probability(0, 1);
    for(int i = 0; i < m_grid.size(); ++i)
    {
        if(start_probability(m_rnd_engine) <= m_start_chance)
            m_grid.at(i) = TileID::FLOOR;
        else
            m_grid.at(i) = TileID::WALL;
    }

    std::vector<int> temp_grid(m_map_width * m_map_height, 0);
    for(int epoch = 0; epoch < t_num_epoch; ++epoch)
    {
        temp_grid = m_grid;
        for(int y = 0; y < m_map_height; ++y)
        {
            for(int x = 0; x < m_map_width; ++x)
            {
                int num_adjacent = get_adjacent_cells(x, y);
                int rule_result = CELL_IGNORE;

                for(int r = 0; r < m_rules.size(); ++r)
                {
                    if(m_rules.at(r)(num_adjacent) != CELL_IGNORE)
                        rule_result = m_rules.at(r)(num_adjacent);
                }

                if(rule_result == CELL_LIVE)
                    temp_grid.at(x + (y * m_map_width)) = TileID::FLOOR;
                else if(rule_result == CELL_DIE)
                    temp_grid.at(x + (y * m_map_width)) = TileID::WALL;
            }
        }
        m_grid = temp_grid;
    }

    for(int i = 0; i < m_grid.size(); ++i)
    {
        int x = i % m_map_width;
        int y = i / m_map_width;

        if(y == 0 || y == m_map_height - 1)
            m_grid.at(i) = TileID::WALL;
        else if(x == 0 || x == m_map_width - 1)
            m_grid.at(i) = TileID::WALL;
    }

    return 0;
}

void CellularMap::flood_fill(const int x, const int y)
{
    std::vector<int> stack;
    bool span_above = false;
    bool span_below = false;
    int dx = 0;
    int dy = 0;
    int i = 0;

    const int start_tile = m_grid.at(x + (y * m_map_width));
    stack.push_back(x + (y * m_map_width));

    auto test_tile = [&](int x, int y) -> bool {return m_grid.at(x + (y * m_map_width)) == start_tile;};
    // std::cout << "Lambda output: " << test_tile(x, y) << "\n";

    while(stack.size() > 0)
    {
        i = stack.back();
        dx = i % m_map_width;
        dy = i / m_map_width;
        span_above = false;
        span_below = false;
        stack.pop_back();

        while(dx >= 0 && test_tile(dx, dy) == true)
        {
            dx -= 1;
        }
        dx += 1;

        while(dx < m_map_width && test_tile(dx, dy) == true)
        {
            m_grid.at(dx + (dy * m_map_width)) += TileID::FLOOD;
            if(span_above == false && dy > 0 && test_tile(dx, dy-1) == true)
            {
                stack.push_back(dx + ((dy-1) * m_map_width));
                span_above = true;
            }
            else if(span_above != false && dy > 0 && test_tile(dx, dy-1) == false)
            {
                span_above = false;
            }
            if(span_below == false && dy < (m_map_height - 1) && test_tile(dx, dy+1) == true)
            {
                stack.push_back(dx + ((dy+1) * m_map_width));
                span_below = true;
            }
            else if(span_below != false && dy < (m_map_height - 1) && test_tile(dx, dy+1) == false)
            {
                span_below = false;
            }

            dx += 1;
        }
    }
}

void CellularMap::generate_single_cavern(const int t_num_epoch, const int t_max_tries)
{
    int kill_switch = 0;
    int num_flood_tiles = 0;
    float flood_fraction = 0.0;

    while(flood_fraction < 0.45)
    {
        generate_grid(t_num_epoch);
        flood_fill(m_map_width / 2, m_map_height / 2);

        for(int i = 0; i < m_grid.size(); ++i)
        {
            if(m_grid.at(i) >= (TileID::FLOOD + TileID::FLOOR))
                num_flood_tiles++;
        }

        flood_fraction = num_flood_tiles / static_cast<float>(m_grid.size());
        // std::cout << "Flood Fraction " << flood_fraction << "\n";

        if(kill_switch++ >= t_max_tries)
            break;
    }

    for(int i = 0; i < m_grid.size(); i++)
    {
        if(m_grid.at(i) >= TileID::FLOOD)
            m_grid.at(i) -= TileID::FLOOD;
        else
            m_grid.at(i) = TileID::WALL;
    }
}

void CellularMap::find_rooms()
{
    for(int i = 0; i < m_grid.size(); ++i)
    {
        if(m_grid.at(i) == TileID::FLOOR)
        {
            Room temp_room;
            flood_fill(i % m_map_width, i / m_map_width);
            for(int j = 0; j < m_grid.size(); ++j)
            {
                if(m_grid.at(j) == (TileID::FLOOR + TileID::FLOOD))
                    temp_room.add_point(j);
            }
            m_rooms.push_back(temp_room);
            flood_fill(i % m_map_width, i / m_map_width);
        }
    }
}

void CellularMap::print_rooms()
{
    find_rooms();

    for(int r = 0; r < m_rooms.size(); ++r)
    {
        std::vector<int> room_grid = m_rooms.at(r).return_grid();
        for(int i = 0; i < room_grid.size(); ++i)
        {
            m_grid.at(room_grid.at(i)) = r+2;
        }
    }

    print_grid();
}

void CellularMap::print_grid() const
{
    for(int y = 0; y < m_map_height; ++y)
    {
        for(int x = 0; x < m_map_width; ++x)
        {
            std::cout << m_grid.at(x + (y * m_map_width));
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

std::vector<int> CellularMap::return_grid() const
{
    return m_grid;
}