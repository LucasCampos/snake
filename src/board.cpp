/*
 * board.cpp
 * Copyright (C) 2020 Lucas Costa Campos <rmk236@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "board.hpp"


Board::Board (int size_x, int size_y, const NeuralNetwork& nn): size_x(size_x), size_y(size_y), score(0), snake(nn) {

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    gen.seed(rd());

    dis_x = std::uniform_int_distribution(1, size_x);
    dis_y = std::uniform_int_distribution(1, size_y);

    /* snake.head.x = dis_x(gen); */
    /* snake.head.y = dis_y(gen); */

    snake.head.x = 1;
    snake.head.y = 1;

    generate_fruit();

    fruit.y = snake.head.y;

};

bool Board::check_collision() const {
    if (
            (snake.head.x == 0) || (snake.head.x == size_x) ||
            (snake.head.y == 0) || (snake.head.y == size_y)
       )
        return true;

    return snake.check_collision();
}

void Board::try_to_eat() {
    if(snake.head == fruit) {
        snake.grow();
        generate_fruit();
        score++;
    }
}

void Board::generate_fruit() {
    //TODO: Avoid fruits appearing on top of snake
    fruit.x = dis_x(gen);
    fruit.y = dis_y(gen);
}
