#pragma once
#include "type.hpp"
#include "position.hpp"
#include "movegen.hpp"
#include <chrono>
#include <atomic>
#include <cstring>

using namespace std::chrono;

namespace Eyra {

constexpr int MAX_CP = 10000;
constexpr int INF    = 30001;
constexpr int MATE_EVAL = 30000;

struct SearchInfo {
    int depth = 0;
    uint64_t nodes = 0;

    steady_clock::time_point start_time;
    int max_time_ms = 0;

    std::atomic<bool> stop {false};

    inline void Reset () {
        depth = 0;
        nodes = 0;
        max_time_ms = 0;
        stop.store(false, std::memory_order_relaxed);
    };

};

struct SearchResults {
    Move best_move = 0;
    int score = 0;
};

namespace Engine {
    extern SearchInfo search_info;
    extern Position position;
    extern Move killers[32][2]; // Store 2 killers per each depth

    inline void ResetKillers () {
        std::memset(killers, 0, sizeof(killers));
    }

    inline void StoreKiller (Move move, int ply) {
        // If killer already exist, there is no need to store it.
        if (killers[ply][0] == move) return;
        if (killers[ply][1] == move) return;

        killers[ply][1] = killers[ply][0];
        killers[ply][0] = move;
    }
    
    int Evaluate (Position& pos);
    float EGWeight (Position& pos);

    int Search (Position& pos, int depth, int alpha, int beta);
    int QSearch (Position& pos, int depth, int alpha, int beta);

    SearchResults GetBestMove (Position& pos, int depth, Move pv);

    void Go (int depth_limit, int movetime);

    void Sort (const Position& pos, MoveList& list, Move pv, Move killer_a = 0, Move killer_b = 0);
} // namespace Engine

    

} // namespace Eyra
