#include "engine.h"

Engine::Engine(int t_screen_width, int t_screen_height, TCODConsole* t_canvas) :
               m_screen_width(t_screen_width),
               m_screen_height(t_screen_height),
               m_canvas(t_canvas)
{
    m_dungeon = std::unique_ptr<Map>(new Map(m_screen_width, m_screen_height));

    std::random_device rnd;
    // BSPTree test_tree(rnd(), m_screen_width, m_screen_height);
    // test_tree.split_tree(5, 15, 15);
    // test_tree.fill_tree();

    CellularMap test_cell(rnd(), m_screen_width, m_screen_height);
    CellRule rule_live(CELL_LIVE, 4, ">");
    CellRule rule_die(CELL_DIE, 4, "<");
    test_cell.set_start_chance(0.55);
    test_cell.add_rule(rule_live);
    test_cell.add_rule(rule_die);
    // test_cell.generate_grid(5);
    test_cell.generate_single_cavern(5);
    // test_cell.print_grid();
    // test_cell.print_rooms();

    m_dungeon -> grid_to_map(test_cell.return_grid());

    m_player = std::unique_ptr<Object>(new Object(m_screen_width / 2, m_screen_height / 2, '@', TCODColor::white, true, false));
    m_dungeon -> compute_fov(m_player -> get_x(), m_player -> get_y(), 10);
}

Engine::~Engine()
{

}

void Engine::update()
{

}

void Engine::render()
{
    m_canvas -> clear();
    m_dungeon -> render(m_canvas);
    for(auto& obj : m_object_list)
    {
        obj -> draw(m_canvas);
    }
    m_player -> draw(m_canvas);
    
    TCODConsole::flush();
}

int Engine::input()
{
        int game_code = 0;

        TCOD_key_t key;
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);

        bool compute_fov = false;

        switch(key.vk)
        {
            case TCODK_UP:
            case TCODK_KP8:
                if(m_dungeon -> block_move(m_player -> get_x(), m_player -> get_y() - 1) == false)
                {
                    m_player -> move_dx(0, -1);
                    compute_fov = true;
                }
                break;
            case TCODK_DOWN:
            case TCODK_KP2:
                if(m_dungeon -> block_move(m_player -> get_x(), m_player -> get_y() + 1) == false)
                {
                    m_player -> move_dx(0, 1);
                    compute_fov = true;
                }
                break;
            case TCODK_LEFT:
            case TCODK_KP4:
                if(m_dungeon -> block_move(m_player -> get_x() - 1, m_player -> get_y()) == false)
                {
                    m_player -> move_dx(-1, 0);
                    compute_fov = true;
                }
                break;
            case TCODK_RIGHT:
            case TCODK_KP6:
                if(m_dungeon -> block_move(m_player -> get_x() + 1, m_player -> get_y()) == false)
                {
                    m_player -> move_dx(1, 0);
                    compute_fov = true;
                }
                break;
            case TCODK_KP7:
                if(m_dungeon -> block_move(m_player -> get_x() - 1, m_player -> get_y() - 1) == false)
                {
                    m_player -> move_dx(-1, -1);
                    compute_fov = true;
                }
                break;
            case TCODK_KP9:
                if(m_dungeon -> block_move(m_player -> get_x() + 1, m_player -> get_y() - 1) == false)
                {
                    m_player -> move_dx(1, -1);
                    compute_fov = true;
                }
                break;
            case TCODK_KP3:
                if(m_dungeon -> block_move(m_player -> get_x() + 1, m_player -> get_y() + 1) == false)
                {
                    m_player -> move_dx(1, 1);
                    compute_fov = true;
                }
                break;
            case TCODK_KP1:
                if(m_dungeon -> block_move(m_player -> get_x() - 1, m_player -> get_y() + 1) == false)
                {
                    m_player -> move_dx(-1, 1);
                    compute_fov = true;
                }
                break;
            case TCODK_ESCAPE:
                game_code = -1;
                break;
            default:
                break;
        }

        if(compute_fov == true)
            m_dungeon -> compute_fov(m_player -> get_x(), m_player -> get_y(), 10);

        return game_code; 
}