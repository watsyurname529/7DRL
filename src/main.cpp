#include "main.h"

int main()
{
    int game_state = 0;
    const int screen_width = 80;
    const int screen_height = 50;

    TCODConsole::setCustomFont("./data/fonts/arial12x12.png", TCOD_FONT_LAYOUT_TCOD | TCOD_FONT_TYPE_GREYSCALE);
    TCODConsole::initRoot(screen_width, screen_height, "7DRL", false);

    Engine* engine_rl = new Engine(screen_width, screen_height);

    BSPTree test_tree(12257, screen_width, screen_height);
    test_tree.split_tree(5, 10, 10);
    test_tree.fill_tree();
    test_tree.print_grid();

    while(TCODConsole::isWindowClosed() == false)
    {
        engine_rl -> render();

        game_state = engine_rl -> input();

        if(game_state >= 0)
            engine_rl -> update();

        if(game_state == -1)
            break;
    }

    return 0;
}