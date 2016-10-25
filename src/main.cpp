#include "main.h"

int main()
{
    int game_state = 0;
    const int screen_width = 80;
    const int screen_height = 50;
    // std::random_device rnd;

    TCODConsole::setCustomFont("./data/fonts/arial12x12.png", TCOD_FONT_LAYOUT_TCOD | TCOD_FONT_TYPE_GREYSCALE);
    TCODConsole::initRoot(screen_width, screen_height, "7DRL", false);

    // Room test_room;
    // test_room.add_point(15);
    // test_room.add_point(10);
    // test_room.add_point(12);
    // std::vector<int> temp = test_room.return_grid();
    // std::cout << temp[3] << std::endl;

    Engine engine_rl(screen_width, screen_height);

    while(TCODConsole::isWindowClosed() == false)
    {
        engine_rl.render();

        game_state = engine_rl.input();

        if(game_state >= 0)
            engine_rl.update();

        if(game_state == -1)
            break;
    }

    return 0;
}