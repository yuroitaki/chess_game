#include <iostream>
#include <string>
#include <vector>

#include "ChessPiece.h"
#include "ChessBoard.h"

using namespace std;

ChessPiece::ChessPiece(string name, string fig,string id,int init_rank, int init_file, ChessPiece*** bod_ptr){
  chess_name = name;
  chess_fig = fig;
  chess_id = id;
  initial_rank = init_rank;
  initial_file = init_file;
  current_rank = init_rank;
  current_file = init_file;
  board_ptr = bod_ptr;;

  set_player();
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

string ChessPiece::get_chess_player(){
  return chess_player;
}

string ChessPiece::get_chess_name(){
  return chess_name;
}
void ChessPiece::set_player(){
  if(initial_rank>6)
    chess_player = "White";
  if(initial_rank<3)
    chess_player = "Black";
}
