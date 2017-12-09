#ifndef CHESSPIECE_H 
#define CHESSPIECE_H

using namespace std; 

class ChessBoard;

class ChessPiece{
 protected:
  string chess_name;
  string chess_fig;
  string chess_id;
  int initial_rank;
  int initial_file;
  string chess_player;
  int current_rank;
  int current_file;
  ChessPiece*** board_ptr;
 public:
  ChessPiece(string name,string fig,string id,int init_rank, int init_file, ChessPiece*** bod_ptr);
  virtual ~ChessPiece();
  friend ostream& operator<<(ostream& out,const ChessPiece& cp);
  int get_init_rank();
  int get_init_file();
  string get_chess_name();
  string get_chess_player();
  void set_player();
};


#endif
