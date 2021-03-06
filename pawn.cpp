#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "pawn.h"

/* the only chess piece type that is directly a derived class of ChessPiece*/

Pawn::Pawn(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr,ChessBoard* chess_b_ptr):ChessPiece(name,fig,id,init_rank,init_file,bod_ptr,chess_b_ptr){}

Pawn::~Pawn(){}

bool Pawn::check_chess_move(const char* source, const char* desti,int d_rank,int d_file){

  chess_rule();
  
  if(!ChessPiece::check_chess_move(source,desti,d_rank,d_file)){
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


void Pawn::chess_rule(){

  int black_pawn_rank[4] = {1,2,1,1};     //basic moves
  int white_pawn_rank[4] = {-1,-2,-1,-1};
  int pawn_file[4] = {0,0,-1,1};
  int* temp_rank;
  
  if(chess_player == "White")
    temp_rank = white_pawn_rank;
  if(chess_player == "Black")
    temp_rank = black_pawn_rank;
  
  vector<int> buff_rank_vec;
  vector<int> buff_file_vec;

  int leap_rank = current_rank + temp_rank[0];
  int leap_file = current_file + pawn_file[0];
  
  if(check_rule_bound(leap_rank,leap_file)){    //check if out of bound
    if(board_ptr[leap_rank][leap_file]==NULL){  //check if there is any blocking pieces
      
      buff_rank_vec.push_back(temp_rank[0]);    //for 1-step forward
      buff_file_vec.push_back(pawn_file[0]);
      
      if((current_rank==initial_rank)&&(current_file==initial_file)){  
	buff_rank_vec.push_back(temp_rank[1]);    //for the 2-step in the beginning
	buff_file_vec.push_back(pawn_file[1]);
      }
    }
  }
  for(int i=0;i<2;i++){
    int buf_rank = current_rank + temp_rank[i+2];
    int buf_file = current_file + pawn_file[i+2];
    
    if(check_rule_bound(buf_rank,buf_file)){          
      if(board_ptr[buf_rank][buf_file]!=NULL){          
	if(board_ptr[buf_rank][buf_file]->get_chess_player()!=chess_player){
	  
	  buff_rank_vec.push_back(temp_rank[i+2]);    //for the capturing move
	  buff_file_vec.push_back(pawn_file[i+2]);
	}
      }
    }
  }
  for(unsigned i=0;i<buff_rank_vec.size();i++){
    int buff_rank = current_rank + buff_rank_vec[i];
    int buff_file = current_file + buff_file_vec[i];
    possible_rank.push_back(buff_rank);
    possible_file.push_back(buff_file);
  }    
}

void Pawn::build_possible_moves(){
  
  chess_rule();
  ChessPiece::build_possible_moves();
}

