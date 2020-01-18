/*
 * main.cpp
 * Copyright (C) 2020 Lucas Costa Campos <rmk236@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "snake.hpp"
#include "board.hpp"
#include "generation.hpp"

#include <boost/circular_buffer.hpp>
#include <fmt/format.h>
#include <iostream>
#include <chrono>
#include <thread>

void print_snake(const Snake& snake) {

    for (auto i : snake.tail) {
        fmt::print("{} {}, ", i.x, i.y);
    }
    fmt::print("--{} {} ", snake.head.x, snake.head.y);
}

void print_game(const Board& b) {

    const int nx = b.size_x;
    const int ny = b.size_x;

    std::cout << "\033[2J\033[1;1H";
    std::string single_line(nx+1, ' ');
    single_line[0] = '|';
    single_line[nx-1] = '|';
    single_line[nx] = '\n';
    std::string board;
    board.reserve((nx+1)*ny);
    for (int i = 0; i < nx; ++i) {
        board += single_line;
    }

    auto idx = [&](int i, int j) {return (nx+1)*((ny-1) - j) + i;};

    //create top and bottom borders
    for (int i = 0; i < nx; ++i) {
        board[idx(i, 0)] = '-';
        board[idx(i, ny-1)] = '-';
    }

    for (auto l : b.snake.tail) {
        board[idx(l.x, l.y)] = '+';
    }
    board[idx(b.snake.head.x, b.snake.head.y)] = 'x';
    board[idx(b.fruit.x, b.fruit.y)] = 'o';

    std::cout << board << std::endl;

}

float play_game(const NeuralNetwork& nn) {

    Board b(64, 64, nn);
    b.snake.grow();
    while (!b.check_collision() && (b.snake.left_to_live > 0)) {
        b.snake.take_move(b);
        b.try_to_eat();
    }

    return b.score * 1000.0 + b.snake.age;
}

void show_game(const NeuralNetwork& nn) {

    Board b(64, 64, nn);
    b.snake.grow();
    while (!b.check_collision() && (b.snake.left_to_live > 0)) {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        print_game(b);
        b.snake.take_move(b);
        b.try_to_eat();
        fmt::print("SCORE: {}, STEPS_LEFT: {}, AGE: {}\n", b.score, b.snake.left_to_live, b.snake.age);
    }

    fmt::print("DEAD\n");
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int N = 2000;
    Generation gen(N, 0.1);

    for (int g = 0; g < 50; ++g) {
        for (int i = 0; i < N; ++i) {
            gen.fitness[i] = play_game(gen.nns[i]);
        }

        gen.new_gen();
        
    }

    auto it = std::max_element(gen.fitness.begin(), gen.fitness.end());
    auto idx = std::distance(gen.fitness.begin(), it);
    show_game(gen.nns[idx]);

    return 0;
}


