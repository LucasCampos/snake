/*
 * snake_brain.hpp
 * Copyright (C) 2020 Lucas Costa Campos <rmk236@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SNAKE_BRAIN_HPP
#define SNAKE_BRAIN_HPP

#include "moves.hpp"
#include "location.hpp"
#include <Eigen/Eigen>
#include <iostream>
#include <cmath>

class Board;

class NeuralNetwork
{
public:
    NeuralNetwork ();
    NeuralNetwork (const NeuralNetwork& nn);
    virtual ~NeuralNetwork ();

    void compress();

    Move decide(const Eigen::Matrix<float, 24, 1>& input);

    Eigen::Matrix<float, 18, 24> in;
    Eigen::Matrix<float, 18, 18> hidden1, hidden2;
    Eigen::Matrix<float, 4, 18> out;

    Eigen::Matrix<float, 4, 24> final_matrix;

};

class SnakeBrain
{
public:
    SnakeBrain ();
    SnakeBrain (const NeuralNetwork& nn);
    virtual ~SnakeBrain () {};
    Move next_move(const Board& board);

private:
    NeuralNetwork nn;

    // The orders are always Left, Right, Down, Up, Down-left, Down-Right, Up-Left, Up-Right;
    // Each set of three entries will have, in order, (distance, hasFood, hasBody)
    Eigen::Matrix<float, 24, 1> state;
};


#endif /* !SNAKE_BRAIN_HPP */
