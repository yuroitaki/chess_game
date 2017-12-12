#include <iostream>
#include <string>
#include <vector>

#include "king.h"

King::King(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr):RoyalInfantry(name,fig,id,init_rank,init_file,bod_ptr){
}

King::~King(){

}

bool King::check_chess_move(const char* source, const char* desti,int d_rank,int d_file){

  int len_arr = 8;
  int buff_rank_arr[len_arr] = {-1,0,1,-1,0,1,-1,1};
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
