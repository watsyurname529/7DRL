#ifndef GENERATE_AUX_H
#define GENERATE_AUX_H

#include<random>
#include<vector>

namespace aux
{
    void bresenham_line(int i1, int i2, std::vector<int>& grid);
    void bresenham_line(int x1, int y1, int x2, int y2, std::vector<int>& grid);
}

class Room
{
    private:
        std::vector<int> m_room_grid;

    public:
        Room();
        // Room(std::vector<int>& t_grid);
        Room(const Room& t_room);

        void add_point(const int i);
        void set_room_grid(std::vector<int>& t_grid);
        std::vector<int> return_grid() const;

        template<class RND>
        int get_random_point(RND& rand_gen) const
        {
            int rnd_point = -1;

            if(m_room_grid.size() > 0)
            {
                std::uniform_int_distribution<int> choose_random(0, m_room_grid.size() - 1);
                rnd_point = m_room_grid[choose_random(rand_gen)];
            }

            return rnd_point;
        }        
};

#endif