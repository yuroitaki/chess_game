#ifndef CHESSPIECE_H 
#define CHESSPIECE_H

#include <vector>

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
  vector<int> possible_rank;
  vector<int> possible_file;
  ChessPiece*** board_ptr;
  ChessBoard* chessboard_ptr;
 public:
  ChessPiece(string name,string fig,string id,int init_rank, int init_file,ChessPiece*** bod_ptr,ChessBoard* chess_b_ptr);
  virtual ~ChessPiece();
  virtual bool check_chess_move(const char* source, const char* desti,int d_rank,int d_file);
  virtual void build_possible_moves();
  bool verify_desti(int d_rank,int d_file,const char* desti);
  void check_move_bound();
  bool check_desti_friendly_fire(int d_rank,int d_file,const char* desti,const char* source);
  void check_friendly_fire();
  bool check_rule_bound(int rank, int file);
  friend ostream& operator<<(ostream& out,const ChessPiece& cp);
  int get_init_rank();
  int get_init_file();
  int get_curr_rank();
  int get_curr_file();
  string get_chess_player();
  vector<int>* get_rank_vec();
  vector<int>* get_file_vec();
  string get_chess_name();
  void set_player();
  void set_position(int rank,int file);
  void clear_vector();
};


#endif
