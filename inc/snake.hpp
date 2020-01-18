/*
 * snake.hpp
 * Copyright (C) 2020 Lucas Costa Campos <rmk236@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <algorithm>

#include "snake_brain.hpp"
#include "moves.hpp"
#include "location.hpp"

#include <boost/circular_buffer.hpp>

class Board;
class SnakeBrain;

class Snake
{
public:
    Snake (const NeuralNetwork& nn);
    virtual ~Snake (){};
    void take_move(const Board& board);
    void take_move(Move mov);

    void grow();
    bool check_collision() const;

    boost::circular_buffer<Location> tail;
    Location head;

    int age;
    int left_to_live;
private:
    SnakeBrain brain;
    static Location move(Location loc, Move mov);

};


#endif /* !SNAKE_HPP */
