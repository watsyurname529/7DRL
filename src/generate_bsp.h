#ifndef GENERATE_BSP_H
#define GENERATE_BSP_H

#include <iostream>
#include <random>
#include <vector>

#include "libtcod.hpp"
#include "map.h"

struct Node
{
    Node* m_left_leaf;
    Node* m_right_leaf;

    int m_x1, m_y1;
    int m_x2, m_y2;

    Node(Node* t_left_leaf, Node* t_right_leaf);
    Node(Node* t_left_leaf, Node* t_right_leaf,
         int t_x1, int t_y1, int t_x2, int t_y2);
};

class BSPTree
{
    private:
        int m_rnd_seed;
        int m_map_width;
        int m_map_height;
        std::vector<int> m_grid;
        std::mt19937 m_rnd_engine;

        Node* m_root;

        void split_tree(Node* t_root, const int num_splits, const int min_room_width, const int min_room_height);

    public:
        BSPTree(const int t_rnd_seed, const int t_map_width, const int t_map_height);
        ~BSPTree();

        void split_tree(const int num_splits, const int min_room_width, const int min_room_height);
        bool split_node(Node* t_root, const int min_room_width, const int min_room_height);
        void fill_tree();

        std::vector<int> return_grid();        
};

#endif