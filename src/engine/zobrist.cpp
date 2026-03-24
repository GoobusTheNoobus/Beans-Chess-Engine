#include "engine/zobrist.hpp"

#include <random>

namespace Eyra
{
    // ======================= Lookups =======================

    Key Zobrist::GetPieceKey(Piece piece, Square square) 
    {
        return piece_keys[piece][square];
    }

    Key Zobrist::GetPieceKey(PieceType pt, Color c, Square square) 
    {
        return piece_keys[MakePiece(pt, c)][square];
    }

    Key Zobrist::SideKey()
    {
        return side_key;
    }

    Key Zobrist::CastlingKey(CastlingRights cr) {
        return castling_keys[cr];
    }

    Key Zobrist::EnPassantKey(Square square) {
        return square != NO_SQUARE ? ep_keys[square & 7] : 0;
    }

    Zobrist::Zobrist() {
        std::mt19937_64 rng(1337);

        for (Piece piece = W_PAWN; piece <= B_KING; ++piece) {
            for (Square square = A1; square <= H8; ++square) {
                piece_keys[piece][square] = rng();
            }
        }

        // XOR if black
        side_key = rng();

        for (CastlingRights cr = 1; cr < 16; ++cr) {
            castling_keys[cr] = rng();
        }

        for (int file = 0; file < 8; ++file) {
            ep_keys[file] = rng();
        }
    }

    


} // namespace Eyra
