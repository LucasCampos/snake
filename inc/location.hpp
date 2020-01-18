/*
 * location.hpp
 * Copyright (C) 2020 Lucas Costa Campos <rmk236@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef LOCATION_HPP
#define LOCATION_HPP

struct Location{
    int x = 0;
    int y = 0;
};


bool operator==(const Location l1, const Location l2);
#endif /* !LOCATION_HPP */
