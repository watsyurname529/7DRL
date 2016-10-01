#include "generate_bsp.h"

Node::Node(Node* t_left_leaf, Node* t_right_leaf) : 
           m_left_leaf(t_left_leaf), m_right_leaf(t_right_leaf) {}

Node::Node(Node* t_left_leaf, Node* t_right_leaf, 
           int t_x1, int t_y1, int t_x2, int t_y2) :
           m_left_leaf(t_left_leaf), m_right_leaf(t_right_leaf), 
           m_x1(t_x1), m_y1(t_y1), m_x2(t_x2), m_y2(t_y2) {}

BSPTree::BSPTree(int t_rnd_seed, int t_map_width, int t_map_height) :
                 m_rnd_seed(t_rnd_seed), m_map_width(t_map_width), m_map_height(t_map_height)
{
    m_root = nullptr;
}
