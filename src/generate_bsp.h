#ifndef GENERATE_BSP_H
#define GENERATE_BSP_H

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

    public:
        BSPTree(int t_rnd_seed, int t_map_width, int t_map_height);
        ~BSPTree();

        void split_tree(const int num_splits, const int max_room_width, const int max_room_height);
        void split_node(Node* t_root);
        void fill_tree();

        std::vector<int> return_grid();        
};

#endif