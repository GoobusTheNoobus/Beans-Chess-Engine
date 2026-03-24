#pragma once

#include "core/type.hpp"

namespace Eyra
{
    class Zobrist 
    {
    public:
        Key GetPieceKey(Piece piece, Square square);
        Key GetPieceKey(PieceType pt, Color c, Square square);

        Key SideKey();
        Key CastlingKey(CastlingRights cr);
        Key EnPassantKey(Square square);

        Zobrist();

    private:
        Key piece_keys[12][64];
        Key side_key;
        Key castling_keys[16];
        Key ep_keys[8];
        
    };

    inline Zobrist zobrist;
} // namespace Eyra
