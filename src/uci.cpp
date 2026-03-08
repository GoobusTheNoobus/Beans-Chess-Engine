#include "uci.hpp"

namespace Eyra
{

void UCI::InfoDepth (int depth, int eval, uint64_t nodes, uint64_t elapsed, const std::vector<Move>& pv) {
    std::string score;

    if (std::abs(eval > MAX_CP)) {
        int mate_distance = (MATE_EVAL - std::abs(eval) + 1) / 2;

        if (eval < 0) {
            mate_distance = -mate_distance;
        }

        score = "mate " + std::to_string(mate_distance);
    } else {
        score = "cp " + std::to_string(eval);
    }

    elapsed = std::max<uint64_t>(elapsed, 1);

    std::cout << "info depth " << depth << 
    " score " << score << 
    " nodes " << nodes << 
    " nps " << (nodes * 1000 / elapsed) << // Max by 1 to prevent division by 0
    " time " << elapsed << 
    " pv ";

    for (Move move: pv) {
        std::cout << MoveToString(move) << ' ';
    }

    std::cout << std::endl;

}

void UCI::InfoString (const std::string& message) {
    std::cout << "info string " << message << std::endl;
}

void UCI::BestMove (Move move, Move ponder) {
    std::cout << MoveToString(move) << std::endl; // TO-DO: Ponder
}

} // namespace Eyra
