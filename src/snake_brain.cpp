/*
 * snake_brain.cpp
 * Copyright (C) 2020 Lucas Costa Campos <rmk236@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "snake_brain.hpp"
#include "board.hpp"
#include <algorithm>

NeuralNetwork::NeuralNetwork () {
    in.setRandom();
    hidden1.setRandom();
    hidden2.setRandom();
    out.setRandom();

    compress();
}

NeuralNetwork::NeuralNetwork (const NeuralNetwork& nn) {
    in = nn.in;
    hidden1 = nn.hidden1;
    hidden2 = nn.hidden2;
    out = nn.out;

    compress();
}

NeuralNetwork::~NeuralNetwork () {};

void NeuralNetwork::compress() {
    final_matrix= out * hidden2 * hidden1 * in;
}

Move NeuralNetwork::decide(const Eigen::Matrix<float, 24, 1>& input) {
    auto resulting_vector = final_matrix * input;
    double loc_max = resulting_vector[0];
    int final_idx = 0;
    for (int i = 1; i < 4; ++i) {
        if (loc_max < resulting_vector[i]) {
            loc_max = resulting_vector[i];
            final_idx = i;
        }
    }

    return Move(final_idx);
}

SnakeBrain::SnakeBrain () {
};

SnakeBrain::SnakeBrain (const NeuralNetwork& nn): nn(nn) {
};

float pyth(float x, float y) {
    return sqrt(x*x + y*y);
}

std::tuple<float, float> search(const Board& board, int dx, int dy) {

    Location p = board.snake.head;
    float hasFood = 0;
    float hasTail = 0;

    while(
            (p.x > 0) && (p.x < board.size_x) &&
            (p.y > 0) && (p.y < board.size_y)
         ) {

        p.x += dx;
        p.y += dy;

        if (p == board.fruit)
            hasFood = 1;

        if (hasTail < 1) {
            auto it = std::find(board.snake.tail.begin(), board.snake.tail.end(), p);
            if(it != board.snake.tail.end())
                hasTail = 1;
        }
    }

    return std::make_tuple(hasFood, hasTail);

}

Move SnakeBrain::next_move(const Board& board) {

    Location h = board.snake.head;
    int nx = board.size_x;
    int ny = board.size_y;

    int idx = 0;
    { //L
        state[idx + 0] = h.x;
        state[idx + 0] = 1.0/state[idx + 0];
        auto [a,b] = search(board, -1, 0);
        state[idx + 1] = a;
        state[idx + 2] = b;
        idx += 3;
    }
    { //R
        state[idx + 0] = nx - h.x;
        state[idx + 0] = 1.0/state[idx + 0];
        auto [a,b] = search(board, 1, 0);
        state[idx + 1] = a;
        state[idx + 2] = b;
        idx += 3;
    }
    { //D
        state[idx + 0] = h.y;
        state[idx + 0] = 1.0/state[idx + 0];
        auto [a,b] = search(board, 0, -1);
        state[idx + 1] = a;
        state[idx + 2] = b;
        idx += 3;
    }
    { //U
        state[idx + 0] = ny - h.x;
        state[idx + 0] = 1.0/state[idx + 0];
        auto [a,b] = search(board, 0, 1);
        state[idx + 1] = a;
        state[idx + 2] = b;
        idx += 3;
    }
    { //DL
        state[idx + 0] = pyth(h.x, h.y);
        state[idx + 0] = 1.0/state[idx + 0];
        auto [a,b] = search(board, -1, -1);
        state[idx + 1] = a;
        state[idx + 2] = b;
        idx += 3;
    }
    { //DR
        state[idx + 0] = pyth(nx - h.x, h.y);
        state[idx + 0] = 1.0/state[idx + 0];
        auto [a,b] = search(board, 1, -1);
        state[idx + 1] = a;
        state[idx + 2] = b;
        idx += 3;
    }
    { //UL
        state[idx + 0] = pyth(h.x, ny - h.y);
        state[idx + 0] = 1.0/state[idx + 0];
        auto [a,b] = search(board, -1, 1);
        state[idx + 1] = a;
        state[idx + 2] = b;
        idx += 3;
    }
    { //DL
        state[idx + 0] = pyth(nx - h.x, ny - h.y);
        state[idx + 0] = 1.0/state[idx + 0];
        auto [a,b] = search(board, 1, 1);
        state[idx + 1] = a;
        state[idx + 2] = b;
        idx += 3;
    }

    /* std::cout << state << std::endl; */

    return nn.decide(state);

    /* return Move::RIGHT; */

}
