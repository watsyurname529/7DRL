#ifndef ENGINE_H
#define ENGINE_H

#include <vector>

#include "libtcod.hpp"
#include "map.h"
#include "object.h"

class Engine
{
    private:
        int m_screen_width;
        int m_screen_height;

        TCODConsole* m_canvas;

        std::vector<Object*> m_object_list;
        Object* m_player;
        Map* m_dungeon;

    public:
        Engine(int t_screen_width, int t_screen_height, TCODConsole* t_canvas = TCODConsole::root);
        ~Engine();

        void update();
        void render();
        int input();
};

#endif