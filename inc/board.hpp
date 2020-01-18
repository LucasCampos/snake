/*
 * board.hpp
 * Copyright (C) 2020 Lucas Costa Campos <rmk236@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef BOARD_HPP
#define BOARD_HPP

#include "location.hpp"
#include "snake.hpp"
#include <random>

class Snake;

class Board
{
public:
    Board (int size_x, int size_y, const NeuralNetwork& nn);
    virtual ~Board ()  {};

    bool check_collision() const;

    void try_to_eat();

    int size_x;
    int size_y;

    unsigned score;

    Location fruit;
    Snake snake;

private:

    std::mt19937 gen; //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis_x, dis_y;

    void generate_fruit();
};

#endif /* !BOARD_HPP */
