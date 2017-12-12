#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>

#include "king.h"

King::King(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr,ChessBoard* chess_b_ptr):RoyalInfantry(name,fig,id,init_rank,init_file,bod_ptr,chess_b_ptr){
}

King::~King(){}

bool King::check_chess_move(const char* source, const char* desti,int d_rank,int d_file){

  if(check_castling(source,desti,d_rank,d_file)){     //to check if castling is possible
    return true;
  }
  
  int len_arr = 8;
  int buff_rank_arr[len_arr] = {-1,0,1,-1,0,1,-1,1};  //basic moves
  int buff_file_arr[len_arr] = {-1,-1,-1,1,1,1,0,0};
  int* rank_ptr = buff_rank_arr;
  int* file_ptr = buff_file_arr;
  
  chess_rule(rank_ptr,file_ptr);
  
  if(!RoyalInfantry::check_chess_move(source,desti,d_rank,d_file)){
    possible_rank.clear();
    possible_file.clear();
    return false;
  }
  if(!verify_desti(d_rank,d_file,desti)){
    possible_rank.clear();
    possible_file.clear();
    return false;
  }
  possible_rank.clear();
  possible_file.clear();
  return true;
}

void King::build_possible_moves(){
  
  int len_arr = 8;
  int buff_rank_arr[len_arr] = {-1,0,1,-1,0,1,-1,1};
  int buff_file_arr[len_arr] = {-1,-1,-1,1,1,1,0,0};
  int* rank_ptr = buff_rank_arr;
  int* file_ptr = buff_file_arr;
  
  chess_rule(rank_ptr,file_ptr);
  RoyalInfantry::build_possible_moves();
}

bool King::check_castling(const char* source, const char* desti,int d_rank,int d_file){
  
  int rank_diff = current_rank - d_rank;
  int file_diff = current_file - d_file;
  int buff_rank,knight_file,bishop_file,rook_file,queen_file;
  int signal;
  string which_side;
  
  if(chess_player=="White"){
    buff_rank = 8;
    signal = BLACK;
  }
  if(chess_player=="Black"){
    buff_rank = 1;
    signal = WHITE;
  }
  if(file_diff<0){
    knight_file = 7;
    bishop_file = 6;
    rook_file = 8;
    which_side = "kingside";
  }
  if(file_diff>0){
    knight_file = 2;
    bishop_file = 3;
    queen_file = 4;
    rook_file = 1;
    which_side = "queenside";
  }
  if((rank_diff != 0)||(abs(file_diff) != 2)){    //to check if its a castling move
    return false;
  }
  if((current_rank!=initial_rank)||(current_file!=initial_file)){
    cout << "Castling cannot be performed by a King that has moved!" << endl;
    return false;
  }
  if(chessboard_ptr->get_check_status()==CHECKED){
    cout << chess_player <<"'s King is under check, castling is not allowed!" << endl;
    return false;
  }
  if(!check_nearby_pieces(file_diff,knight_file,bishop_file,queen_file,rook_file,buff_rank)){
    return false;
  }
  if(!check_mate(file_diff,knight_file,bishop_file,queen_file,buff_rank,signal)){
    return false;
  }
  cout << chess_player<<"'s "<< chess_name << " is castling with its Rook on the " << which_side << "!"<<endl;
  if(file_diff > 0)
    move_rook(buff_rank,rook_file,queen_file);
  if(file_diff < 0)
    move_rook(buff_rank,rook_file,bishop_file);
  return true;
}

/*to ensure empty space between and check rook state */
bool King::check_nearby_pieces(int file_diff,int knight_file,int bishop_file,int queen_file,int rook_file,int buff_rank){

  if(board_ptr[buff_rank][rook_file] == NULL){
    return false;
  }
  if(board_ptr[buff_rank][rook_file]->get_chess_name() != "Rook"){
      return false;
  }
  if(board_ptr[buff_rank][rook_file]->get_chess_player() != chess_player){
      return false;
  }
  if((board_ptr[buff_rank][knight_file]!=NULL)||(board_ptr[buff_rank][bishop_file]!=NULL)){
    cout << "Castling can only be performed when there is no piece between King and Rook!" << endl;
    return false;
  }
  if(file_diff>0){     // in the case of a queenside castling
    if(board_ptr[buff_rank][queen_file]!=NULL){
      cout << "Castling can only be performed when there is no piece between King and Rook!" << endl;
      return false;
    }
  }
  int curr_rank = board_ptr[buff_rank][rook_file]->get_curr_rank();
  int curr_file = board_ptr[buff_rank][rook_file]->get_curr_file();
  int init_rank = board_ptr[buff_rank][rook_file]->get_init_rank();
  int init_file = board_ptr[buff_rank][rook_file]->get_init_file();
  
  if((curr_rank!=init_rank)||(curr_file!=init_file)){
    cout << "Castling cannot be performed by a Rook which has moved!" << endl;
    return false;
  }
  return true;
}

/*check if the pass-by and destination square is under check */
bool King::check_mate(int file_diff,int knight_file,int bishop_file,int queen_file,int buff_rank,int signal){

  //get the opponent array of chess pieces
  ChessPiece** buff_chess_ptr = chessboard_ptr->get_chess_ptr(signal); 

  //check for the square that is knight inital position
  if(chessboard_ptr->check_mate(buff_chess_ptr,buff_rank,knight_file)){
    cout << "The square that "<< chess_player <<"'s King will pass by or land on is under check!" << endl;
    return false;
  }
  //check for the square that is bishop initial position
  if(chessboard_ptr->check_mate(buff_chess_ptr,buff_rank,bishop_file)){
    cout << "The square that "<< chess_player <<"'s King will pass by or land on is under check!" << endl;
    return false;
  }
  if(file_diff>0){     //in the case of queenside
    if(chessboard_ptr->check_mate(buff_chess_ptr,buff_rank,queen_file)){
      cout << "The square that "<< chess_player <<"'s King will pass by or land on is under check!" << endl;
    return false;
    }
  }
  return true;
}

/* to move rook on the chess board as the second move in addition to the king*/
void King::move_rook(int desti_rank,int rook_file,int desti_file){

  char char_rook_file = char(rook_file + ASCII_ALP);      
  char char_desti_file = char(desti_file + ASCII_ALP);
  int buff_rank;
  
  int map_rank[8] = {8,7,6,5,4,3,2,1};       //convert back to chess format
  for(int i=0;i<8; i++){
    if(desti_rank == map_rank[i])
      buff_rank = i+1;
  }
  char char_desti_rank = char(buff_rank + ASCII_NO);

  const char source [3] = {char_rook_file,char_desti_rank,'\0'};
  const char desti [3] = {char_desti_file,char_desti_rank,'\0'};

  chessboard_ptr->execute_move(desti_rank,rook_file,desti_rank,desti_file,source,desti);
}
