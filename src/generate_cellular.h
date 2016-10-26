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

class CellRule
{
    private:
        int m_action;
        int m_threshold;
        std::string m_rule;

    public:
        CellRule(int t_action, int t_threshold, std::string t_rule) : m_action(t_action), m_threshold(t_threshold), m_rule(t_rule)
        {
            if(m_rule != "=" && m_rule != ">" && m_rule != "<")
                std::cout << "Not a valid rule." << std::endl;
        }

        int operator()(int t_adjacent) const
        {
            int result = CELL_IGNORE;

            if(m_rule == "=")
            {
                if(t_adjacent == m_threshold) 
                    result = m_action;
            }
            else if(m_rule == ">")
            {
                if(t_adjacent > m_threshold) 
                    result = m_action;
            }
            else if(m_rule == "<")
            {
                if(t_adjacent < m_threshold)
                    result = m_action;
            }

            return result;
        }
};

class CellularMap
{
    private:
        int m_rnd_seed;
        int m_map_width;
        int m_map_height;
        float m_start_chance;
        
        std::vector<int> m_grid;
        std::vector<Room> m_rooms;
        std::vector<CellRule> m_rules;
        std::mt19937 m_rnd_engine;

        int generate_grid(const int t_num_epoch);
        int get_adjacent_cells(const int x, const int y);
        void flood_fill(const int x, const int y);
        void find_rooms();
        void connect_rooms();

    public:
        CellularMap(const int t_rnd_seed, const int t_map_width, const int t_map_height);
        CellularMap(const int t_rnd_seed, const int t_map_width, const int t_map_height, const float t_start);

        void set_start_chance(const float t_start);
        void add_rule(CellRule& t_rule);
        void generate_single_cavern(const int t_num_epoch, const int t_max_tries = 10);
        void print_rooms();
        void print_grid() const;
        std::vector<int> return_grid() const;
};

#endif