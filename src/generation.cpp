/*
 * generation.cpp
 * Copyright (C) 2020 Lucas Costa Campos <rmk236@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "generation.hpp"
#include <algorithm>
#include <random>
#include <numeric>

#include <fmt/format.h>

Generation::Generation (int N, double mutation_rate):mutation_rate(mutation_rate) {

    fitness.resize(N);
    nns.resize(N);

    dist = std::uniform_real_distribution<float>(0,1);
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    gen.seed(rd());

}
Generation::~Generation () {};

int find_index(const std::vector<float>& cumulative, float point) {
    for (int i = 0; i < cumulative.size(); ++i) {
        if(cumulative[i] > point)
            return i;
    }

    fmt::print("ERROR");
    return -1;
}

void Generation::mutate(NeuralNetwork& nn) {

    for (int i = 0; i < 18; ++i) {
        for (int j = 0; j < 24; ++j) {
            if (dist(gen) < mutation_rate)
                nn.in(i,j) += 0.2*(2*dist(gen)-1);
        }
    }
    for (int i = 0; i < 18; ++i) {
        for (int j = 0; j < 18; ++j) {
            if (dist(gen) < mutation_rate)
                nn.hidden1(i,j) += 0.2*(2*dist(gen)-1);
            if (dist(gen) < mutation_rate)
                nn.hidden2(i,j) += 0.2*(2*dist(gen)-1);
        }
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 18; ++j) {
            if (dist(gen) < mutation_rate)
                nn.out(i,j) += 0.2*(2*dist(gen)-1);
        }
    }
}

NeuralNetwork Generation::cross_breed(const NeuralNetwork& nn1, const NeuralNetwork& nn2) {

    NeuralNetwork nn;
    std::uniform_int_distribution<int> dist(0,1);
    for (int i = 0; i < 18; ++i) {
        for (int j = 0; j < 24; ++j) {
            nn.in(i,j) = (dist(gen)%2 == 0? nn1.in(i,j): nn2.in(i,j));
        }
    }
    for (int i = 0; i < 18; ++i) {
        for (int j = 0; j < 18; ++j) {
            nn.hidden1(i,j) = (dist(gen)%2 == 0? nn1.hidden1(i,j): nn2.hidden1(i,j));
            nn.hidden2(i,j) = (dist(gen)%2 == 0? nn1.hidden2(i,j): nn2.hidden2(i,j));
        }
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 18; ++j) {
            nn.out(i,j) = (dist(gen)%2 == 0? nn1.out(i,j): nn2.out(i,j));
        }
    }

    return nn;

}

void Generation::new_gen() {

    auto it = std::max_element(fitness.begin(), fitness.end());
    auto idx = std::distance(fitness.begin(), it);

    float tot_fitness = std::accumulate(fitness.begin(), fitness.end(), 0);
    auto fit2 = fitness;
    std::transform(fitness.begin(), fitness.end(), fit2.begin(), [&](double x){return x/tot_fitness;});


    std::vector cumulative = std::vector<float>(fit2.size());
    std::partial_sum(fit2.begin(), fit2.end(), cumulative.begin());

    fmt::print("Best of generation: {}\n", *std::max_element(fitness.begin(), fitness.end()));

    int N = nns.size();

    std::vector<NeuralNetwork> new_nns;
    new_nns.resize(N);

    new_nns[0] = nns[idx];

    for (int i = 1; i < N; ++i) {
        int idx1 = find_index(cumulative, dist(gen));
        int idx2 = find_index(cumulative, dist(gen));

        new_nns[i] = cross_breed(nns[idx1], nns[idx2]);
        mutate(new_nns[i]);
        new_nns[i].compress();

    }

    nns = new_nns;
    fmt::print("Done generation\n");

}

