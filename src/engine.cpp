#include "engine.h"

Engine::Engine(int t_screen_width, int t_screen_height, TCODConsole* t_canvas) :
               m_screen_width(t_screen_width), m_screen_height(t_screen_height),
               m_canvas(t_canvas)
{
    TCODConsole::setCustomFont("../data/fonts/arial12x12.png", TCOD_FONT_LAYOUT_TCOD | TCOD_FONT_TYPE_GREYSCALE);
    TCODConsole::initRoot(m_screen_width, m_screen_height, "pathRL", false);

    m_dungeon = new Map(m_screen_width, m_screen_height);
    for(int w = 20; w < 40; w++)
    {
        for(int h = 10; h < 60; h++)
        {
            m_dungeon -> add_tile(w, h, new Tile(' ', TCODColor::black, TCODColor::black, false, false, false));
        }
    }

    m_player = new Object(30, 40, '@', TCODColor::white, true, false);
}

Engine::~Engine()
{
    delete m_player;

    for(auto& obj : m_object_list)
    {
        delete obj;
    }
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

        switch(key.vk)
        {
            case TCODK_UP:
                if(m_dungeon -> block_move(m_player -> get_x(), m_player -> get_y() - 1) == false)
                    m_player -> move_dx(0, -1);
                break;
            case TCODK_DOWN:
                if(m_dungeon -> block_move(m_player -> get_x(), m_player -> get_y() + 1) == false)
                    m_player -> move_dx(0, 1);
                break;
            case TCODK_LEFT:
                if(m_dungeon -> block_move(m_player -> get_x() - 1, m_player -> get_y()) == false)
                    m_player -> move_dx(-1, 0);
                break;
            case TCODK_RIGHT:
                if(m_dungeon -> block_move(m_player -> get_x() + 1, m_player -> get_y()) == false)
                    m_player -> move_dx(1, 0);
                break;
            case TCODK_ESCAPE:
                game_code = -1;
                break;
            default:
                break;
        }

        return game_code; 
}