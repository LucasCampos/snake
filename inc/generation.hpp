/*
 * generation.hpp
 * Copyright (C) 2020 Lucas Costa Campos <rmk236@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef GENERATION_HPP
#define GENERATION_HPP

#include "snake_brain.hpp"
#include <random>

class Generation
{
public:
    Generation (int N, double mutation_rate);
    virtual ~Generation ();

    void new_gen();

    std::vector<NeuralNetwork> nns;
    std::vector<float> fitness;

private:
    double mutation_rate;

    std::mt19937 gen; //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<float> dist;

    NeuralNetwork cross_breed(const NeuralNetwork& nn1, const NeuralNetwork& nn2);
    void mutate(NeuralNetwork& nn);
};

#endif /* !GENERATION_HPP */
