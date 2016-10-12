#ifndef GENERATE_CELLULAR_H
#define GENERATE_CELLULAR_H

#include <iostream>
#include <random>
#include <vector>

#include "libtcod.hpp"
#include "map.h"

class CellularMap
{
    private:
        int m_rnd_seed;
        int m_map_width;
        int m_map_height;
        std::vector<int> m_grid;
        std::mt19937 m_rnd_engine;

    public:
        CellularMap(const int t_rnd_seed, const int t_map_width, const int t_map_height);
        ~CellularMap();
};

#endif GENERATE_CELLULAR_H