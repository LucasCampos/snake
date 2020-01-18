/*
 * snake.cpp
 * Copyright (C) 2020 Lucas Costa Campos <rmk236@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "snake.hpp"

Snake::Snake (const NeuralNetwork& nn):brain(nn) {
    age = 0;
    left_to_live= 100;
}

void Snake::grow() {

    tail.resize(tail.size()+1);
    tail.rotate(tail.end()-1);

    left_to_live = std::min(left_to_live+100, 500);
}

void Snake::take_move(Move mov) {
    left_to_live--;
    age++;
    tail.push_back(head);
    head = move(head, mov);
}

Move check_direction(Move new_direction, Move direction) {

    if ((new_direction == Move::UP) && (direction != Move::DOWN))
        return new_direction;

    if ((new_direction == Move::DOWN) && (direction != Move::UP))
        return new_direction;

    if ((new_direction == Move::LEFT) && (direction != Move::RIGHT))
        return new_direction;

    if ((new_direction == Move::RIGHT) && (direction != Move::LEFT))
        return new_direction;

    return direction;

}

void Snake::take_move(const Board& board) {
    left_to_live--;
    age++;
    tail.push_back(head);
    Move new_direction = brain.next_move(board);
    direction = check_direction(new_direction, direction);
    head = move(head, direction);
}

bool Snake::check_collision() const {

    auto it = std::find(tail.begin(), tail.end(), head);
    return it != tail.end();

}

Location Snake::move(Location loc, Move mov) {
    switch(mov) {
        case Move::LEFT:
            loc.x -= 1;
            break;
        case Move::RIGHT:
            loc.x += 1;
            break;
        case Move::DOWN:
            loc.y -= 1;
            break;
        case Move::UP:
            loc.y += 1;
            break;
    }

    return loc;

}



