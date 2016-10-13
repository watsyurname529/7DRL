#ifndef GENERATE_CELLULAR_H
#define GENERATE_CELLULAR_H

#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "libtcod.hpp"
#include "map.h"

enum CellState
{
    CELL_IGNORE,
    CELL_LIVE,
    CELL_DIE
};

class CellularMap
{
    private:
        int m_rnd_seed;
        int m_map_width;
        int m_map_height;
        float m_start_chance;
        
        std::vector<int> m_grid;
        std::mt19937 m_rnd_engine;

    public:
        CellularMap(const int t_rnd_seed, const int t_map_width, const int t_map_height);
        ~CellularMap();
};

class CellRule
{
    private:
        int m_result;
        int m_threshold;
        std::string m_rule;

    public:
        CellRule(int t_result, int t_threshold, std::string t_rule) : m_result(t_result), m_threshold(t_threshold), m_rule(t_rule) {}
        int operator()(int t_adjacent) const
        {
            if(m_rule == "=" && t_adjacent == m_threshold)
                return m_result;
            else if(m_rule == ">" && t_adjacent > m_threshold)
                return m_result;
            else if(m_rule == "<" && t_adjacent < m_threshold)
                return m_result;
            else
            {
                std::cout << "Not valid rule." << std::endl;
                return CELL_IGNORE;
            }
        }
};

#endif