#include <iostream>
#include <vector>

#include "libtcod.hpp"
#include "map.h"
#include "object.h"

int main()
{
    bool game_over = false;

    const int screen_x = 80;
    const int screen_y = 50;

    const int player_x = 40;
    const int player_y = 25;

    Object player(player_x, player_y, '@', TCODColor::white);
    Object npc(player_x + 5, player_y + 5, 'N', TCODColor::green);

    std::vector<Object*> object_list;
    object_list.push_back(&npc);
    object_list.push_back(&player);

    TCODConsole::setCustomFont("../data/fonts/arial12x12.png", TCOD_FONT_LAYOUT_TCOD | TCOD_FONT_TYPE_GREYSCALE);
    TCODConsole::initRoot(screen_x, screen_y, "pathRL", false);

    Map dungeon(80, 50);
    for(int i = 0; i < 80; ++i)
    {
        Tile* new_tile = new Tile('#', TCODColor::white, TCODColor::grey, true, true, false);
        dungeon.add_tile(i, 0, new_tile);
        dungeon.add_tile(i, 49, new_tile);
    }

    for(int x = 0; x < 80; ++x)
    {
        for(int y = 0; y < 50; ++y)
        {
            if(dungeon.get_tile(x, y) == NULL)
                dungeon.add_tile(x, y, new Tile(' ', TCODColor::black, TCODColor::black, false, false, false));
        }
    }
    // Tile* test_tile = new Tile('#', TCODColor::white, TCODColor::grey, false, false, false);
    // dungeon.add_tile(39, 39, test_tile);

    while(TCODConsole::isWindowClosed() == false && game_over == false)
    {
        TCODConsole::root -> clear();
        dungeon.render();
        for(const auto& obj : object_list)
        {
            obj -> draw();
        }
        TCODConsole::flush();

        TCOD_key_t key;
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);

        switch(key.vk)
        {
            case TCODK_UP:
                if(dungeon.block_move(player.get_x(), player.get_y() - 1) == false)
                    player.move_dx(0, -1);
                break;
            case TCODK_DOWN:
                if(dungeon.block_move(player.get_x(), player.get_y() + 1) == false)
                    player.move_dx(0, 1);
                break;
            case TCODK_LEFT:
                if(dungeon.block_move(player.get_x() - 1, player.get_y()) == false)
                    player.move_dx(-1, 0);
                break;
            case TCODK_RIGHT:
                if(dungeon.block_move(player.get_x() + 1, player.get_y()) == false)
                    player.move_dx(1, 0);
                break;
            case TCODK_ESCAPE:
                game_over = true;
                break;
            default:
                break;
        }
    }

    return 0;
}