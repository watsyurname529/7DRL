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