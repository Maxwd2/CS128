#include <cassert>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "board.hpp"

int main() {
  Board b{};
  InitBoard(b);
  // b.board[Board::kBoardHeight - 1][Board::kBoardWidth - 1] =
  // DiskType::kEmpty;
  DiskType disk1 = DiskType::kPlayer1;
  DiskType disk2 = DiskType::kPlayer2;
  int count = 1;

  DropDiskToBoard(b, disk1, 1);
  std::cout << count++ << " turn:\n" << BoardToStr(b) << std::endl;
  if (CheckForWinner(b, disk2) || CheckForWinner(b, disk1)) {
    std::cout << "\nWinner" << std::endl;
  }
  DropDiskToBoard(b, disk2, 1);
  std::cout << count++ << " turn:\n" << BoardToStr(b) << std::endl;
  if (CheckForWinner(b, disk2) || CheckForWinner(b, disk1)) {
    std::cout << "\nWinner" << std::endl;
  }
  DropDiskToBoard(b, disk1, 4);
  std::cout << count++ << " turn:\n" << BoardToStr(b) << std::endl;
  if (CheckForWinner(b, disk2) || CheckForWinner(b, disk1)) {
    std::cout << "\nWinner" << std::endl;
  }
  DropDiskToBoard(b, disk2, 0);
  std::cout << count++ << " turn:\n" << BoardToStr(b) << std::endl;
  if (CheckForWinner(b, disk2) || CheckForWinner(b, disk1)) {
    std::cout << "\nWinner" << std::endl;
  }
  DropDiskToBoard(b, disk1, 2);
  std::cout << count++ << " turn:\n" << BoardToStr(b) << std::endl;
  if (CheckForWinner(b, disk2) || CheckForWinner(b, disk1)) {
    std::cout << "\nWinner" << std::endl;
  }
  DropDiskToBoard(b, disk2, 0);
  std::cout << count++ << " turn:\n" << BoardToStr(b) << std::endl;
  if (CheckForWinner(b, disk2) || CheckForWinner(b, disk1)) {
    std::cout << "\nWinner" << std::endl;
  }
  DropDiskToBoard(b, disk1, 2);
  std::cout << count++ << " turn:\n" << BoardToStr(b) << std::endl;
  if (CheckForWinner(b, disk2) || CheckForWinner(b, disk1)) {
    std::cout << "\nWinner" << std::endl;
  }
  DropDiskToBoard(b, disk2, 0);
  std::cout << count++ << " turn:\n" << BoardToStr(b) << std::endl;
  if (CheckForWinner(b, disk2) || CheckForWinner(b, disk1)) {
    std::cout << "\nWinner" << std::endl;
  }
  DropDiskToBoard(b, disk1, 0);
  std::cout << count++ << " turn:\n" << BoardToStr(b) << std::endl;
  if (CheckForWinner(b, disk2) || CheckForWinner(b, disk1)) {
    std::cout << "\nWinner" << std::endl;
  }
  DropDiskToBoard(b, disk2, 5);
  std::cout << count++ << " turn:\n" << BoardToStr(b) << std::endl;
  if (CheckForWinner(b, disk2) || CheckForWinner(b, disk1)) {
    std::cout << "\nWinner" << std::endl;
  }
  DropDiskToBoard(b, disk1, 4);
  std::cout << count++ << " turn:\n" << BoardToStr(b) << std::endl;
  if (CheckForWinner(b, disk2) || CheckForWinner(b, disk1)) {
    std::cout << "\nWinner" << std::endl;
  }
  DropDiskToBoard(b, disk2, 5);
  std::cout << count++ << " turn:\n" << BoardToStr(b) << std::endl;
  if (CheckForWinner(b, disk2) || CheckForWinner(b, disk1)) {
    std::cout << "\nWinner" << std::endl;
  }
  DropDiskToBoard(b, disk1, 6);
  std::cout << count++ << " turn:\n" << BoardToStr(b) << std::endl;
  if (CheckForWinner(b, disk2) || CheckForWinner(b, disk1)) {
    std::cout << "\nWinner" << std::endl;
  }
  DropDiskToBoard(b, disk2, 6);
  std::cout << count++ << " turn:\n" << BoardToStr(b) << std::endl;
  if (CheckForWinner(b, disk2) || CheckForWinner(b, disk1)) {
    std::cout << "\nWinner" << std::endl;
  }
  DropDiskToBoard(b, disk1, 1);
  std::cout << count++ << " turn:\n" << BoardToStr(b) << std::endl;
  if (CheckForWinner(b, disk2) || CheckForWinner(b, disk1)) {
    std::cout << "\nWinner" << std::endl;
  }
  DropDiskToBoard(b, disk2, 6);
  std::cout << count++ << " turn:\n" << BoardToStr(b) << std::endl;
  if (CheckForWinner(b, disk2) || CheckForWinner(b, disk1)) {
    std::cout << "\nWinner" << std::endl;
  }
  DropDiskToBoard(b, disk1, 6);
  std::cout << count++ << " turn:\n" << BoardToStr(b) << std::endl;
  if (CheckForWinner(b, disk2) || CheckForWinner(b, disk1)) {
    std::cout << "\nWinner" << std::endl;
  }
  DropDiskToBoard(b, disk2, 6);
  std::cout << count++ << " turn:\n" << BoardToStr(b) << std::endl;
  if (CheckForWinner(b, disk2) || CheckForWinner(b, disk1)) {
    std::cout << "\nWinner" << std::endl;
  }
  DropDiskToBoard(b, disk1, 5);
  std::cout << count++ << " turn:\n" << BoardToStr(b) << std::endl;
  if (CheckForWinner(b, disk2) || CheckForWinner(b, disk1)) {
    std::cout << "\nWinner" << std::endl;
  }

  if (!CheckForWinner(b, disk1) && !CheckForWinner(b, disk2)) {
    std::cout << BoardToStr(b) << "\nNo Winner" << std::endl;
  }
  /*
  DropDiskToBoard(b, disk1, 1);
  DropDiskToBoard(b, disk1, 1);
  DropDiskToBoard(b, disk2, 1);
  DropDiskToBoard(b, disk2, 1);
  DropDiskToBoard(b, disk2, 1);
  DropDiskToBoard(b, disk2, 1);
  DropDiskToBoard(b, disk1, 3);
  DropDiskToBoard(b, disk2, 3);
  DropDiskToBoard(b, disk2, 3);
  DropDiskToBoard(b, disk1, 3);
  DropDiskToBoard(b, disk1, 4);
  DropDiskToBoard(b, disk2, 4);
  DropDiskToBoard(b, disk2, 2);
  DropDiskToBoard(b, disk2, 2);
  DropDiskToBoard(b, disk1, 2);
  DropDiskToBoard(b, disk2, 2);
  DropDiskToBoard(b, disk2, 2);
  DropDiskToBoard(b, disk1, 5);
  DropDiskToBoard(b, disk1, 6);
  std::cout << BoardToStr(b) << std::endl;
  std::cout << "Horizontal winner: "
            << SearchForWinner(b, disk1, WinningDirection::kHorizontal)
            << std::endl;
  std::cout << "Vertical Winner: "
            << SearchForWinner(b, disk2, WinningDirection::kVertical)
            << std::endl;
  std::cout << "LeftDiag Winner: "
            << SearchForWinner(b, disk2, WinningDirection::kLeftDiag)
            << std::endl;
  std::cout << "RightDiag Winner: "
            << SearchForWinner(b, disk1, WinningDirection::kRightDiag)
            << std::endl;
  DropDiskToBoard(b, disk1, 3);
  if (CheckForWinner(b, disk1)) {
    std::cout << BoardToStr(b) << "\nP1 wins" << std::endl;
  } else if (CheckForWinner(b, disk2)) {
    std::cout << BoardToStr(b) << "\nP2 wins" << std::endl;
  }
  DropDiskToBoard(b, disk2, 2);
  if (CheckForWinner(b, disk1)) {
    std::cout << BoardToStr(b) << "\nP1 wins" << std::endl;
  } else if (CheckForWinner(b, disk2)) {
    std::cout << BoardToStr(b) << "\nP2 wins" << std::endl;
  }
  DropDiskToBoard(b, disk1, 2);
  if (CheckForWinner(b, disk1)) {
    std::cout << BoardToStr(b) << "\nP1 wins" << std::endl;
  } else if (CheckForWinner(b, disk2)) {
    std::cout << BoardToStr(b) << "\nP2 wins" << std::endl;
  }
  DropDiskToBoard(b, disk2, 0);
  if (CheckForWinner(b, disk1)) {
    std::cout << BoardToStr(b) << "\nP1 wins" << std::endl;
  } else if (CheckForWinner(b, disk2)) {
    std::cout << BoardToStr(b) << "\nP2 wins" << std::endl;
  }
  DropDiskToBoard(b, disk1, 1);
  if (CheckForWinner(b, disk1)) {
    std::cout << BoardToStr(b) << "\nP1 wins" << std::endl;
  } else if (CheckForWinner(b, disk2)) {
    std::cout << BoardToStr(b) << "\nP2 wins" << std::endl;
  }
  DropDiskToBoard(b, disk2, 1);
  if (CheckForWinner(b, disk1)) {
    std::cout << BoardToStr(b) << "\nP1 wins" << std::endl;
  } else if (CheckForWinner(b, disk2)) {
    std::cout << BoardToStr(b) << "\nP2 wins" << std::endl;
  }
  DropDiskToBoard(b, disk1, 1);
  if (CheckForWinner(b, disk1)) {
    std::cout << BoardToStr(b) << "\nP1 wins" << std::endl;
  } else if (CheckForWinner(b, disk2)) {
    std::cout << BoardToStr(b) << "\nP2 wins" << std::endl;
  }
  DropDiskToBoard(b, disk2, 0);
  if (CheckForWinner(b, disk1)) {
    std::cout << BoardToStr(b) << "\nP1 wins" << std::endl;
  } else if (CheckForWinner(b, disk2)) {
    std::cout << BoardToStr(b) << "\nP2 wins" << std::endl;
  }
  DropDiskToBoard(b, disk1, 0);
  if (CheckForWinner(b, disk1)) {
    std::cout << BoardToStr(b) << "\nP1 wins" << std::endl;
  } else if (CheckForWinner(b, disk2)) {
    std::cout << BoardToStr(b) << "\nP2 wins" << std::endl;
  }
  DropDiskToBoard(b, disk2, 1);
  if (CheckForWinner(b, disk1)) {
    std::cout << BoardToStr(b) << "\nP1 wins" << std::endl;
  } else if (CheckForWinner(b, disk2)) {
    std::cout << BoardToStr(b) << "\nP2 wins" << std::endl;
  }
  DropDiskToBoard(b, disk1, 0);
  if (CheckForWinner(b, disk1)) {
    std::cout << BoardToStr(b) << "\nP1 wins" << std::endl;
  } else if (CheckForWinner(b, disk2)) {
    std::cout << BoardToStr(b) << "\nP2 wins" << std::endl;
  }
*/
}

/*
  // clang-format off
  DiskType solution[Board::kBoardHeight][Board::kBoardWidth] = {
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty,
  DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, {DiskType::kEmpty,
  DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty,
  DiskType::kEmpty, DiskType::kEmpty}, {DiskType::kEmpty, DiskType::kEmpty,
  DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty,
  DiskType::kEmpty}, {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty,
  DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty,
  DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, {DiskType::kEmpty,
  DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty,
  DiskType::kEmpty, DiskType::kEmpty}
  };
  */