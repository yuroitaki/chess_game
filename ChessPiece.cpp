#include <iostream>
#include <string>

#include "ChessPiece.h"
#include "ChessBoard.h"

using namespace std;

ChessPiece::ChessPiece(string fig,string id,int init_rank, int init_file, ChessPiece*** bod_ptr){
  chess_fig = fig;
  chess_id = id;
  initial_rank = init_rank;
  initial_file = init_file;
  board_ptr = bod_ptr;;
}

ChessPiece::~ChessPiece(){
}

ostream& operator<<(ostream& out, const ChessPiece& cp){
  return out << cp.chess_fig;
}

int ChessPiece::get_init_rank(){
  return initial_rank;
}

int ChessPiece::get_init_file(){
  return initial_file;
}
