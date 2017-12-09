#include <iostream>
#include <string>

#include "ChessPiece.h"
#include "ChessBoard.h"

using namespace std;

ChessPiece::ChessPiece(string id,int init_rank, int init_file, ChessPiece*** bod_ptr){
  chess_id = id;
  initial_rank = init_rank;
  initial_file = init_file;
  board_ptr = bod_ptr;
}

ostream& operator<<(ostream& out, const ChessPiece& cp){
  return out << cp.chess_id;
}
