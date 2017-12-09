#ifndef CHESSPIECE_H 
#define CHESSPIECE_H

using namespace std; 

class ChessBoard;

class ChessPiece{
 protected:
  string chess_id;
  int initial_rank;
  int initial_file;
  int current_rank;
  int current_file;
  ChessPiece*** board_ptr;
 public:
  ChessPiece(string id,int init_rank, int init_file, ChessPiece*** bod_ptr);
  friend ostream& operator<<(ostream& out,const ChessPiece& cp);
};

#endif
