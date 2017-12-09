#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#define RANK_SIZE 8
#define FILE_SIZE 8
#define CHESS_PIECE_NO 16
#define ASCII_NO 48
#define ASCII_ALP 64

#include "king.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "pawn.h"

class ChessPiece;

class ChessBoard{
 private:
  int turn_count;
  ChessPiece*** board_ptr;
  ChessPiece** black_chess_ptr;
  ChessPiece** white_chess_ptr;
  ChessPiece** chess_label_ptr;
  ChessPiece** index_label_ptr;
 public:
  ChessBoard();
  ~ChessBoard();
  void submitMove(const char* source,const char* desti);
  void execute_move(int s_rank,int s_file, int d_rank,int d_file);
  void print();
  void create_chess_pieces(char id);
  void initialize_board();
  void visualize_chess_label();
  void visualize_index_label();
  void resetBoard();
  string make_special_piece(char player_id,string& chess_id, int count);
  string make_pawn_piece(char player_id,string& pawn_id);
};


#endif
