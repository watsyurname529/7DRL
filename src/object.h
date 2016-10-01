#ifndef OBJECT_HPP
#define OBJECT_HPP

struct Point
{
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {}
};

class Object
{
    private:
        Point m_pos;
        int m_char;

        TCODColor m_fg_color;
        TCODColor m_bg_color;

        bool m_block_move;
        bool m_block_sight;

    public:
        Object(Point pos, int ch, const TCODColor &fg, 
               bool t_block_move = true, bool t_block_sight = false);
        Object(int x, int y, int ch, const TCODColor &fg, 
               bool t_block_move = true, bool t_block_sight = false);

        void draw(TCODConsole* canvas = TCODConsole::root) const;
        void move_dx(int dx, int dy);
        void move_abs(int x, int y);
        void move_abs(Point dest);

        int get_x() const;
        int get_y() const;

        bool block_move() const;
        bool block_sight() const;
};

#endif