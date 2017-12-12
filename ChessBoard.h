#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#define KING_POS 4
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
  vector<ChessPiece*> captured_vec;
 public:
  ChessBoard();
  ~ChessBoard();
  bool submitMove(const char* source,const char* desti);
  bool format_move(const char* source, const char* desti,int& s_rank,int& s_file, int& d_rank,int& d_file);
  void execute_move(int s_rank,int s_file, int d_rank,int d_file,const char* source,const char* desti);
  bool check_state(int d_rank,int d_file);
  bool save_king(ChessPiece** def_ptr, ChessPiece** atk_ptr,int king_rank,int king_file);
  bool check_mate(ChessPiece** atck_ptr,int king_rank,int king_file);
  bool check_life_stat(ChessPiece* test_piece);
  void print();
  bool check_source(int s_rank,int s_file,const char* source);
  void create_chess_pieces(char id);
  void initialize_board();
  void visualize_chess_label();
  void visualize_index_label();
  void resetBoard();
  string make_special_piece(char player_id,string& chess_id, int count);
  string make_pawn_piece(char player_id,string& pawn_id);
  bool check_out_bound(int rank, int file);
};


#endif
