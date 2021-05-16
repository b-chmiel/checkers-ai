#ifndef BOARD_H
#define BOARD_H

#include "constants.h"
#include "piece.h"
#include "player.h"
#include "position.h"
#include <map>
#include <vector>

namespace board {
enum MoveType {
    ILLEGAL,
    SHORT,
    LONG
};
class Checkerboard {
public:
    player::PlayerType currentPlayer = player::PlayerType::PLAYER1;
    piece::Piece state[constants::BOARD_HEIGHT][constants::BOARD_WIDTH];
    Checkerboard();
    void Show();
    bool Move(const std::vector<Position> path);
    bool IsGameCompleted();

private:
    std::map<player::PlayerType, int> piecesAlive;
    std::string GetFieldIcon(int i, int j);
    void PrintLettersBelow();
    piece::Piece GetFieldPiece(const Position& position);
    std::string GetFieldNumber(int i);
    std::string GetFieldString(int i, int j);
    void MovePiece(const Position& from, const Position& to, MoveType move);
    MoveType ValidatedMoveType(const Position& from, const Position& to);
    MoveType GetMoveType(const Position& from, const Position& to);
    bool ValidateShortMove(const Position& from, const Position& to);
    bool ValidateLongMove(const Position& from, const Position& to);
    bool IsPiecePromotion(const Position& position);
    bool IsEndPositionForPlayer(const Position& position, player::PlayerType player);
    void PromotePiece(const Position& position);
    void Capture(const Position& from, const Position& to);
};
}
#endif