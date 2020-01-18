/*
 * common.cpp
 * Copyright (C) 2020 Lucas Costa Campos <rmk236@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */


#include "location.hpp"

bool operator==(const Location l1, const Location l2) {
    return (l1.x == l2.x) && (l1.y == l2.y);
}

