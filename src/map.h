#ifndef MAP_H
#define MAP_H

#include <memory>
#include <random>
#include <vector>

#include <libtcod.hpp>
#include "generate_aux.h"

enum TileID
{
    WALL,
    FLOOR,
    FLOOD = 3
};

class Tile
{
    private:
        int m_symbol;
        TCODColor m_fg_color;
        TCODColor m_bg_color_vis;
        TCODColor m_bg_color_hid;

        bool m_explored;
        bool m_block_move;
        bool m_block_sight;

        // Terrain* m_terrain_type;

    public:
        Tile(int t_symbol, const TCODColor& t_fg_color, const TCODColor& t_bg_color_vis, const TCODColor& t_bg_color_hid,
             bool t_explored, bool t_block_move, bool t_block_sight);

        bool block_move() const;
        bool block_sight() const;
        bool is_explored() const;
        void set_explored();
        void draw(int x, int y, bool fov, TCODConsole* canvas = TCODConsole::root) const;
};

class Map
{
    private:
        int m_width;
        int m_height;

        std::vector<std::unique_ptr<Tile>> m_tiles;
        TCODMap* m_fovmap;

    public:
        Map(int t_width, int t_height);
        ~Map();

        bool block_move(int x, int y) const;
        bool block_sight(int x, int y) const;
        bool is_explored(int x, int y) const;
        void render(TCODConsole* canvas = TCODConsole::root) const;
        void add_tile(int x, int y, Tile* t_tile);
        Tile* get_tile(int x, int y) const;

        void grid_to_map(std::vector<int> t_grid);

        void compute_fov(int x, int y, int r) const;
        bool is_in_fov(int x, int y) const;
};

#endif