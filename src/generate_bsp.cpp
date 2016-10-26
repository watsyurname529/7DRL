#include "generate_bsp.h"

Node::Node(Node* t_left_leaf, Node* t_right_leaf) : 
           m_left_leaf(t_left_leaf),
           m_right_leaf(t_right_leaf)
{

}

Node::Node(Node* t_left_leaf, Node* t_right_leaf, int t_x1, int t_y1, int t_x2, int t_y2) :
           m_left_leaf(t_left_leaf), 
           m_right_leaf(t_right_leaf), 
           m_x1(t_x1), m_y1(t_y1), 
           m_x2(t_x2), m_y2(t_y2)
{

}

BSPTree::BSPTree(int t_rnd_seed, int t_map_width, int t_map_height) :
                 m_rnd_seed(t_rnd_seed), 
                 m_map_width(t_map_width), 
                 m_map_height(t_map_height),
                 m_rnd_engine(t_rnd_seed), 
                 m_root(nullptr)
{
    m_grid.resize(m_map_width * m_map_height, TileID::WALL);
}

BSPTree::~BSPTree()
{

}

void BSPTree::split_tree(const int num_splits, const int min_room_width, const int min_room_height)
{
    if(m_root == nullptr)
        m_root = new Node(nullptr, nullptr, 0, 0, m_map_width, m_map_height);

    split_tree(m_root, num_splits, min_room_width, min_room_height);
}

void BSPTree::split_tree(Node* t_root, const int num_splits, const int min_room_width, const int min_room_height)
{
    bool split_success = false;
    if(num_splits > 0)
    {
        if(t_root -> m_left_leaf == nullptr && t_root -> m_right_leaf == nullptr)
        {
            split_success = split_node(t_root, min_room_width, min_room_height);
        }

        if(split_success == true)
        {
            #if DEBUG == 1
            std::cout << num_splits << " XL " << t_root -> m_left_leaf -> m_x1 << " " << t_root -> m_left_leaf -> m_x2 << std::endl;
            std::cout << num_splits << " YL " << t_root -> m_left_leaf -> m_y1 << " " << t_root -> m_left_leaf -> m_y2 << std::endl;
            std::cout << num_splits << " XR " << t_root -> m_right_leaf -> m_x1 << " " << t_root -> m_right_leaf -> m_x2 << std::endl;
            std::cout << num_splits << " YR " << t_root -> m_right_leaf -> m_y1 << " " << t_root -> m_right_leaf -> m_y2 << std::endl;
            #endif
            
            split_tree(t_root -> m_left_leaf, num_splits - 1, min_room_width, min_room_height);
            split_tree(t_root -> m_right_leaf, num_splits - 1, min_room_width, min_room_height);
        }
    }
}

bool BSPTree::split_node(Node* t_root, const int min_room_width, const int min_room_height)
{
    bool split_success = false;
    bool split_horizontal = false;

    float current_room_width = t_root -> m_x2 - t_root -> m_x1;
    float current_room_height = t_root -> m_y2 - t_root -> m_y1;

    if(current_room_width / current_room_height > 1.25)
        split_horizontal = false;
    else if(current_room_height / current_room_width > 1.25)
        split_horizontal = true;
    else
    {
        std::uniform_int_distribution<int> split_direction(0,1);
        split_horizontal = split_direction(m_rnd_engine);
    }

    if(split_horizontal == false)
    {
        if((current_room_width - min_room_width) > min_room_width)
        {
            std::uniform_int_distribution<int> room_width(min_room_width, current_room_width - min_room_width);
            int split = room_width(m_rnd_engine);

            t_root -> m_left_leaf = new Node(nullptr, nullptr, t_root -> m_x1, t_root -> m_y1,
                                             t_root -> m_x1 + split, t_root -> m_y2);

            t_root -> m_right_leaf = new Node(nullptr, nullptr, t_root -> m_x1 + split, t_root -> m_y1,
                                              t_root -> m_x2, t_root -> m_y2); 
            split_success = true;
        }
    }

    else
    {
        if((current_room_height - min_room_height) > min_room_height)
        {
            std::uniform_int_distribution<int> room_height(min_room_height, current_room_height - min_room_height);
            int split = room_height(m_rnd_engine);

            t_root -> m_left_leaf = new Node(nullptr, nullptr, t_root -> m_x1, t_root -> m_y1,
                                             t_root -> m_x2, t_root -> m_y1 + split);

            t_root -> m_right_leaf = new Node(nullptr, nullptr, t_root -> m_x1, t_root -> m_y1 + split,
                                              t_root -> m_x2, t_root -> m_y2);
            split_success = true;
        } 
    }

    return split_success;
}

void BSPTree::fill_tree()
{
    if(m_root != nullptr)
        fill_tree(m_root);
}

void BSPTree::fill_tree(Node* t_root)
{
    if(t_root -> m_left_leaf != nullptr && t_root -> m_right_leaf != nullptr)
    {
        fill_tree(t_root -> m_left_leaf);
        fill_tree(t_root -> m_right_leaf);
        connect_leaf_center(t_root);
    }

    else
    {
        create_cave_room(t_root);
    }
}

void BSPTree::create_rect_room(Node* t_leaf)
{
    int room_max_width = t_leaf -> m_x2 - t_leaf -> m_x1 - 2;
    int room_max_height = t_leaf -> m_y2 - t_leaf -> m_y1 - 2;

    std::uniform_int_distribution<int> room_width(5, room_max_width);
    std::uniform_int_distribution<int> room_height(5, room_max_height);

    int room_w = room_width(m_rnd_engine);
    int room_h = room_height(m_rnd_engine);

    std::uniform_int_distribution<int> room_x(t_leaf -> m_x1 + 1, t_leaf -> m_x2 - room_w - 1);
    std::uniform_int_distribution<int> room_y(t_leaf -> m_y1 + 1, t_leaf -> m_y2 - room_h - 1);

    int room_x1 = room_x(m_rnd_engine);
    int room_x2 = room_x1 + room_w;
    int room_y1 = room_y(m_rnd_engine);
    int room_y2 = room_y1 + room_h;

    for(int y = room_y1; y < room_y2; ++y)
    {
        for(int x = room_x1; x < room_x2; ++x)
        {
            m_grid.at(x + (y * m_map_width)) = TileID::FLOOR;
        }
    }
}

void BSPTree::create_cave_room(Node* t_leaf)
{
    int room_max_width = t_leaf -> m_x2 - t_leaf -> m_x1 - 2;
    int room_max_height = t_leaf -> m_y2 - t_leaf -> m_y1 - 2;
    std::uniform_int_distribution<int> r_seed(0, 1000);

    CellularMap cave(r_seed(m_rnd_engine), room_max_width, room_max_height);
    CellRule rule_live(CELL_LIVE, 4, ">");
    CellRule rule_die(CELL_DIE, 4, "<");
    cave.set_start_chance(0.55);
    cave.add_rule(rule_live);
    cave.add_rule(rule_die);
    cave.generate_single_cavern(6);

    std::vector<int> grid_cave = cave.return_grid();
    
    int room_x1 = t_leaf -> m_x1 + 1;
    int room_y1 = t_leaf -> m_y1 + 1;
    int room_x2 = t_leaf -> m_x2 - 1;
    int room_y2 = t_leaf -> m_y2 - 1;
    
    int i = 0;
    for(int y = room_y1; y < room_y2; ++y)
    {
        for(int x = room_x1; x < room_x2; ++x)
        {
            m_grid.at(x + (y * m_map_width)) = grid_cave.at(i);
            i++;
        }
    }
}

std::vector<int> BSPTree::return_grid() const
{
    return m_grid;
}

void BSPTree::print_grid() const
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

void BSPTree::connect_leaf_center(Node* t_root)
{
    int left_x = t_root -> m_left_leaf -> m_x1 + (t_root -> m_left_leaf -> m_x2 - t_root -> m_left_leaf -> m_x1) / 2;
    int left_y = t_root -> m_left_leaf -> m_y1 + (t_root -> m_left_leaf -> m_y2 - t_root -> m_left_leaf -> m_y1) / 2;

    int right_x = t_root -> m_right_leaf -> m_x1 + (t_root -> m_right_leaf -> m_x2 - t_root -> m_right_leaf -> m_x1) / 2;
    int right_y = t_root -> m_right_leaf -> m_y1 + (t_root -> m_right_leaf -> m_y2 - t_root -> m_right_leaf -> m_y1) / 2;

    #if DEBUG == 1
    std::cout << "LX " << left_x << " RX " << right_x << std::endl;
    std::cout << "LY " << left_y << " RY " << right_y << std::endl;
    #endif

    if(left_y == right_y)
    {
        for(int x = left_x; x < right_x; ++x)
        {
            m_grid.at(x + (left_y * m_map_width)) = TileID::FLOOR;
        }
    }

    else
    {  
        for(int y = left_y; y < right_y; ++y)
        {
            m_grid.at(left_x + (y * m_map_width)) = TileID::FLOOR;
        }
    }
}