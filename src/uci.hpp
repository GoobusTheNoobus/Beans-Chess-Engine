#pragma once
#include "type.hpp"
#include "misc.hpp"
#include "move.hpp"
#include <iostream>

namespace Eyra::UCI {

void InfoDepth  (int depth, int score, uint64_t nodes, uint64_t elasped, const std::vector<Move>& pv);
void InfoString (const std::string& message);

void BestMove (Move move, Move ponder=0);
    
} // namespace Eyra::UCI
