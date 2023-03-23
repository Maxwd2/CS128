#include "board.hpp"

// you might need additional includes
#include <cassert>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  for (int i = 0; i < Board::kBoardHeight; i++) {
    for (int j = 0; j < Board::kBoardWidth; j++) {
      b.board[i][j] = DiskType::kEmpty;
    }
  }
  // below was minimal to get tests to actually compile and given test case to
  // fail
  // b.board[0][0] = DiskType::kEmpty;
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  if (col >= Board::kBoardWidth || col < 0) {
    throw std::runtime_error("Given column is not within board boundry");
  };
  int full = 0;
  // assert(col <= Board::kBoardWidth && col >= 0);
  for (int i = 0; i < Board::kBoardHeight; i++) {
    if (b.board[i][col] == DiskType::kEmpty) {
      b.board[i][col] = disk;
      break;
    }
    full++;
  }
  if (full == Board::kBoardHeight) {
    throw std::runtime_error("Given column is full");
  }
}

bool CheckForWinner(Board& b, DiskType disk) {
  return SearchForWinner(b, disk, WinningDirection::kLeftDiag) ||
         SearchForWinner(b, disk, WinningDirection::kHorizontal) ||
         SearchForWinner(b, disk, WinningDirection::kVertical) ||
         SearchForWinner(b, disk, WinningDirection::kRightDiag);
}

bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  if (to_check == WinningDirection::kHorizontal) {
    return SearchForWinnerHorizontal(b, disk);
  }
  if (to_check == WinningDirection::kVertical) {
    return SearchForWinnerVertical(b, disk);
  }
  if (to_check == WinningDirection::kLeftDiag) {
    return SearchForWinnerLeftDiag(b, disk);
  }
  if (to_check == WinningDirection::kRightDiag) {
    return SearchForWinnerRightDiag(b, disk);
  }
  return false;
}

// board[kBoardHeight][kBoardWidth]

bool SearchForWinnerHorizontal(Board& b, DiskType disk) {
  for (int width = 0; width < Board::kBoardWidth - 3; width++) {
    for (int height = 0; height < Board::kBoardHeight; height++) {
      if (b.board[height][width] == disk) {
        if (b.board[height][width + 1] == disk &&
            b.board[height][width + 2] == disk &&
            b.board[height][width + 3] == disk) {
          return true;
        }
      }
    }
  }
  return false;
}

/* bool SearchForWinnerHorizontal(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardHeight; i++) {
    for (int j = 0; j < Board::kBoardWidth; j++) {
      int count = 0;
      if (b.board[i][j] == disk) {
        for (int k = 0; k < 4; k++) {
          if (b.board[i][j] == disk) {
            count++;
          }
          j++;
        }
      }
      if (count >= 4) {
        return true;
      }
    }
  }
  return false;
} */

// board[kBoardHeight][kBoardWidth]
bool SearchForWinnerVertical(Board& b, DiskType disk) {
  for (int height = 0; height < Board::kBoardHeight - 3; height++) {
    for (int width = 0; width < Board::kBoardWidth; width++) {
      if (b.board[height][width] == disk) {
        if (b.board[height + 1][width] == disk &&
            b.board[height + 2][width] == disk &&
            b.board[height + 3][width] == disk) {
          return true;
        }
      }
    }
  }
  return false;
}

bool SearchForWinnerLeftDiag(Board& b, DiskType disk) {
  for (int width = 0; width < Board::kBoardWidth - 3; width++) {
    for (int height = 3; height < Board::kBoardHeight; height++) {
      if (b.board[height][width] == disk) {
        if (b.board[height - 1][width + 1] == disk &&
            b.board[height - 2][width + 2] == disk &&
            b.board[height - 3][width + 3] == disk) {
          return true;
        }
      }
    }
  }
  return false;
}

// board[kBoardHeight][kBoardWidth]
bool SearchForWinnerRightDiag(Board& b, DiskType disk) {
  for (int width = 0; width < Board::kBoardWidth - 3; width++) {
    for (int height = 0; height < Board::kBoardHeight - 3; height++) {
      if (b.board[height][width] == disk) {
        if (b.board[height + 1][width + 1] == disk &&
            b.board[height + 2][width + 2] == disk &&
            b.board[height + 3][width + 3] == disk) {
          return true;
        }
      }
    }
  }
  return false;
}

bool BoardLocationInBounds(int row, int col) {
  return (row <= Board::kBoardWidth && col <= Board::kBoardHeight && row >= 0 &&
          col >= 0);
}

/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}

/*
bool SearchForWinnerVertical(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardWidth; i++) {
    for (int j = 0; j < Board::kBoardHeight; j++) {
      int count = 0;
      if (b.board[j][i] == disk) {
        for (int k = 0; k < 4; k++) {
          if (b.board[j][i] == disk) {
            count++;
          } else {
            break;
          }
          j++;
        }
      }
      if (count >= 4) {
        return true;
      }
    }
  }
  return false;
}

{
  // bool diag_win = false;
  if (disk != DiskType::kPlayer1 && disk != DiskType::kPlayer2) {
    throw std::runtime_error("Improper disk");
  }
  for (int i = 0; i < Board::kBoardWidth; i++) {
    for (int j = 0; j < Board::kBoardHeight; j++) {
      if (b.board[j][i] == disk) {
        if (b.board[j - 1][i + 1] == disk && b.board[j - 2][i + 2] == disk &&
            b.board[j - 3][i + 3] == disk) {
          return true;
        }
      }
    }
  }
  return false;
}


bool SearchForWinnerHorizontal(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardHeight; i++) {
    for (int j = 0; j < Board::kBoardWidth; j++) {
      if (b.board[i][j] == disk) {
        if (b.board[i][j + 1] == disk && b.board[i][j + 2] == disk &&
            b.board[i][j + 3] == disk) {
          return true;
        }
      }
    }
  }
  return false;
}
*/
