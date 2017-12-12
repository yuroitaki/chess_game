#ifndef KING_H
#define KING_H

#include "royal_infantry.h"
#include "ChessBoard.h"

using namespace std;

class King: public RoyalInfantry{
 public:
  King(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr,ChessBoard* chess_b_ptr);
  ~King();
  bool check_chess_move(const char* source, const char* desti,int d_rank,int d_file) override;
  void build_possible_moves() override;
  bool check_castling(const char* source, const char* desti,int d_rank,int d_file);
  bool check_nearby_pieces(int file_diff,int knight_file,int bishop_file,int queen_file,int rook_file,int buff_rank);
  bool check_mate(int file_diff,int knight_file,int bishop_file,int queen_file,int buff_rank,int signal);
  void move_rook(int desti_rank,int rook_file,int desti_file);
};

#endif
