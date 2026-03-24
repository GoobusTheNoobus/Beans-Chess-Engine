#pragma once

#include "core/type.hpp"

#include <ostream>
#include <algorithm>

namespace Eyra {

// ======================= Move Functions =======================

enum MoveFlag: uint8_t 
{
    NORMAL,
    DOUBLE_PUSH,
    CASTLING,
    EN_PASSANT,
    NPROMO,
    BPROMO,
    RPROMO,
    QPROMO
};

// Basic Move Function
inline Move CreateMove(Square from, Square to, MoveFlag flag) 
{
    return
    (((from) & 0x3F) | 
    (((to) & 0x3F) << 6) |  
    (((flag) & 0xF) << 12));
}

// Inline functions for specific moves: only use these
inline Move CreateNormalMove (Square from, Square to) { return CreateMove(from, to, NORMAL); }
inline Move CreateDoublePush (Square from, Square to) { return CreateMove(from, to, DOUBLE_PUSH); }
inline Move CreateCastling   (Square from, Square to) { return CreateMove(from, to, CASTLING); }
inline Move CreateEnPassant  (Square from, Square to) { return CreateMove(from, to, EN_PASSANT); }
template <PieceType pt>
inline Move CreatePromoMove  (Move base) { return base | (NPROMO + (pt - KNIGHT)) << 12; }

inline Square GetFrom     (Move move) { return Square(move & 0x3F); }
inline Square GetTo       (Move move) { return Square((move >> 6) & 0x3F); }
inline MoveFlag GetFlag   (Move move) { return MoveFlag((move >> 12) & 0xF); }

inline std::string MoveToString(Move move) 
{
    

    if (GetFlag(move) >= NPROMO) {
        static const char flag_promo_char[] = "nbrq";
        return SquareToString(GetFrom(move)) + SquareToString(GetTo(move)) + flag_promo_char[GetFlag(move) - NPROMO];
    } else {
        return SquareToString(GetFrom(move)) + SquareToString(GetTo(move));
    }

    
}

struct MoveList {
    Move moves[256];
    int count = 0;

    inline void Push(Move move) { moves[count++] = move; }
    inline Move Pop() { return moves[--count]; }

    Move operator[] (int i) const { return moves[i]; }

    // Iteratable Support
    inline Move* begin() { return moves; }
    inline Move* end() { return moves + count; }
    inline const Move* begin() const { return moves; }
    inline const Move* end() const { return moves + count; }

    inline std::string ToString () const 
    {

        std::string result;

        result.reserve(200);
        for (Move m: *this) {
            result += MoveToString(m) + "\n";
        }

        result += "There are " + std::to_string(count) + " moves in the movelist. \n";

        return result;
    }

    inline bool Contains(Move move) const 
    {
        for (Move m: *this) {
            if (m == move) 
            {
                return true;
            }
        }

        return false;
    }
    
};

// So you can do std::cout << move_list...
inline std::ostream& operator<< (std::ostream& os, const MoveList& list) 
{
    os << (list.ToString());
    return os;
}

} // namespace Eyra


