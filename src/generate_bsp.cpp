#include "generate_bsp.h"

Node::Node(Node* t_left_leaf, Node* t_right_leaf) : 
           m_left_leaf(t_left_leaf), m_right_leaf(t_right_leaf) {}

Node::Node(Node* t_left_leaf, Node* t_right_leaf, 
           int t_x1, int t_y1, int t_x2, int t_y2) :
           m_left_leaf(t_left_leaf), m_right_leaf(t_right_leaf), 
           m_x1(t_x1), m_y1(t_y1), m_x2(t_x2), m_y2(t_y2) {}

BSPTree::BSPTree(int t_rnd_seed, int t_map_width, int t_map_height) :
                 m_rnd_seed(t_rnd_seed), m_map_width(t_map_width), m_map_height(t_map_height),
                 m_rnd_engine(t_rnd_seed), m_root(nullptr)
{
    m_grid.resize(m_map_width * m_map_height, 0);
}

void BSPTree::split_tree(const int num_splits, const int max_room_width, const int max_room_height)
{
    int current_split = 0;

}

bool BSPTree::split_node(Node* t_root)
{
    bool split_success = false;

    std::uniform_int_distribution<int> split_direction(0,1);
    if(split_direction(m_rnd_engine) == 0)
    {
        std::uniform_int_distribution<int> room_width(0, t_root -> m_x2);
        int split = room_width(m_rnd_engine);

        t_root -> m_left_leaf = new Node(nullptr, nullptr, t_root -> m_x1, t_root -> m_y1,
                                         t_root -> m_x1 + split, t_root -> m_y2);

        t_root -> m_right_leaf = new Node(nullptr, nullptr, t_root -> m_x1 + split, t_root -> m_y1,
                                          t_root -> m_x2, t_root -> m_y2); 
        split_success = true;
    }

    else
    {
        std::uniform_int_distribution<int> room_height(0, t_root -> m_y2);
        int split = room_height(m_rnd_engine);

        t_root -> m_left_leaf = new Node(nullptr, nullptr, t_root -> m_x1, t_root -> m_y1,
                                         t_root -> m_x2, t_root -> m_y1 + split);

        t_root -> m_right_leaf = new Node(nullptr, nullptr, t_root -> m_x1, t_root -> m_y1 + split,
                                          t_root -> m_x2, t_root -> m_y2);
        split_success = true; 
    }

    return split_success;
}