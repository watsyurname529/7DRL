#ifndef ENGINE_H
#define ENGINE_H

#include <memory>
#include <random>
#include <vector>

#include "libtcod.hpp"
#include "generate_aux.h"
#include "generate_bsp.h"
#include "generate_cellular.h"
#include "map.h"
#include "object.h"

class Engine
{
    private:
        int m_screen_width;
        int m_screen_height;

        TCODConsole* m_canvas;
        //std::unique_ptr<TCODConsole> m_canvas;

        std::vector<std::unique_ptr<Object>> m_object_list;
        std::unique_ptr<Object> m_player;
        std::unique_ptr<Map> m_dungeon;

    public:
        Engine(int t_screen_width, int t_screen_height, TCODConsole* t_canvas = TCODConsole::root);
        ~Engine();

        void update();
        void render();
        int input();
};

#endif