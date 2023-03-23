#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>

enum class WinningDirection { kHorizontal, kVertical, kRightDiag, kLeftDiag };
enum class DiskType { kPlayer1 = 82, kPlayer2 = 66, kEmpty = 32 };

struct Board {
  static constexpr int kBoardWidth = 7;
  static constexpr int kBoardHeight = 6;
  DiskType board[kBoardHeight][kBoardWidth];
};
// The next functions I have to implement myself for this MP

// DONE
void InitBoard(Board& b);

// DONE
void DropDiskToBoard(Board& b, DiskType disk, int col);

// Done, I think
bool CheckForWinner(Board& b, DiskType disk);

// In progress
bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check);

// Passed all the Graded cases, but not all of my test cases, so leaving it done
// for now, may need to improve later
bool SearchForWinnerHorizontal(Board& b, DiskType disk);

// Didn't pass all graded cases, seems to pass all of my test cases, will have
// to come back to later
bool SearchForWinnerVertical(Board& b, DiskType disk);

// Didn't Pass all graded cases, seems to pass all of my test cases, will have
// to come back to later
bool SearchForWinnerLeftDiag(Board& b, DiskType disk);

// DONE
bool SearchForWinnerRightDiag(Board& b, DiskType disk);

// DONE
bool BoardLocationInBounds(int row, int col);

// provided
std::string BoardToStr(const Board& b);
std::string CenterStr(const std::string& str, int col_width);

#endif