#include "generate_cellular.h"

CellularMap::CellularMap(int t_rnd_seed, int t_map_width, int t_map_height) :
                         m_rnd_seed(t_rnd_seed), 
                         m_map_width(t_map_width), 
                         m_map_height(t_map_height), 
                         m_rnd_engine(t_rnd_seed)
{
    m_grid.resize(m_map_width * m_map_height, 0);
}

CellularMap::~CellularMap()
{
    
}

void CellularMap::set_start_chance(float t_start)
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
                if(m_grid[dx + (dy * m_map_width)] == 1)
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
            m_grid[i] = 1;
        else
            m_grid[i] = 0;
    }

    std::vector<int> temp_grid(m_map_width * m_map_height, 0);
    // print_grid();
    for(int epoch = 0; epoch < t_num_epoch; ++epoch)
    {
        temp_grid = m_grid;
        // print_grid();
        for(int y = 0; y < m_map_height; ++y)
        {
            for(int x = 0; x < m_map_width; ++x)
            {
                int num_adjacent = get_adjacent_cells(x, y);
                // std::cout << num_adjacent << std::endl;
                int rule_result = CELL_IGNORE;

                for(int r = 0; r < m_rules.size(); ++r)
                {
                    if(m_rules[r](num_adjacent) != CELL_IGNORE)
                        rule_result = m_rules[r](num_adjacent);
                }

                if(rule_result == CELL_LIVE)
                    temp_grid[x + (y * m_map_width)] = 1;
                else if(rule_result == CELL_DIE)
                    temp_grid[x + (y * m_map_width)] = 0;
            }
        }
        m_grid = temp_grid;
    }

    return 0;
}

void CellularMap::print_grid() const
{
    for(int y = 0; y < m_map_height; ++y)
    {
        for(int x = 0; x < m_map_width; ++x)
        {
            std::cout << m_grid[x + (y * m_map_width)];
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

std::vector<int> CellularMap::return_grid() const
{
    return m_grid;
}