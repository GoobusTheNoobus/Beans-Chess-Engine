#include <iostream>
#include "misc.hpp"
#include "bitboard.hpp"
#include "uci.hpp"
#include "engine.hpp"

using namespace Eyra;



int main () {
    std::cout << sizeof(TranspositionEntry);

    Bitboards::Init();
    std::cout << ENGINE_NAME << ENGINE_VERSION << " by " << ENGINE_AUTHOR << std::endl;

    UCI::Loop();

    return 0;
}


