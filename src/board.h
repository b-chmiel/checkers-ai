#ifndef BOARD_H
#define BOARD_H

#include "constants.h"
#include "piece.h"
#include "player.h"
#include "point.h"
#include "position.h"
#include <map>
#include <vector>

namespace board
{
enum class MoveType
{
    ILLEGAL,
    SHORT,
    LONG
};

class Checkerboard
{
public:
    player::PlayerType currentPlayer = player::PlayerType::PLAYER1;
    piece::Piece state[constants::BOARD_HEIGHT][constants::BOARD_WIDTH];
    Checkerboard();
    void Show() const;
    bool IsMoveValid(const Point& from, const Point& to, player::PlayerType) const;
    bool Move(const std::vector<Position>& path);
    bool IsGameCompleted();
    void Move(const std::vector<Point>& path);

private:
    std::map<player::PlayerType, int> piecesAlive;

    void PrintLettersBelow() const;
    piece::Piece GetFieldPiece(const Point& position) const;
    std::string GetFieldIcon(int i, int j) const;
    std::string GetFieldNumber(int i) const;
    std::string GetFieldString(int i, int j) const;
    bool IsInitiallyEmpty(const Point& point, int middleRow);

    void ChangePositionOfPiece(const Point& from, const Point& to, MoveType move);
    bool IsPiecePromotion(const Point& position) const;
    bool IsEndPositionForPlayer(const Point& position, player::PlayerType player) const;
    void PromotePiece(const Point& position);
    void Capture(const Point& from, const Point& to);
    bool IsAnyMovePossible() const;
    MoveType GetMoveType(const Point& from, const Point& to) const;
    bool ValidateShortMove(const Point& from, const Point& to) const;
    bool ValidateLongMove(const Point& from, const Point& to) const;
};
}
#endif