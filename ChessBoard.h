#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#define RANK_SIZE 8
#define FILE_SIZE 8
#define CHESS_PIECE_NO 16

class ChessPiece;

class ChessBoard{
 private:
  int turn_count;
  ChessPiece*** board_ptr;
  ChessPiece** black_chess_ptr;
  ChessPiece** white_chess_ptr;
  ChessPiece** index_label_ptr;
 public:
  ChessBoard();
  virtual ~ChessBoard();
  void print();
  void create_chess_pieces();
  void initialize_board();
  void visualize_index_label();
};


#endif
