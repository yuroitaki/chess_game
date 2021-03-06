#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "royal_infantry.h"

/*a derived class of ChessPiece, and a superclass of Knight and King */

RoyalInfantry::RoyalInfantry(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr,ChessBoard* chess_b_ptr):ChessPiece(name,fig,id,init_rank,init_file,bod_ptr,chess_b_ptr){}

RoyalInfantry::~RoyalInfantry(){}

bool RoyalInfantry::check_chess_move(const char* source, const char* desti,int d_rank,int d_file){ 
  if(!check_desti_friendly_fire(d_rank,d_file,desti,source)){
    return false;
  }
  check_move_bound();
  check_friendly_fire();
  return true;
}

/* construct the possible square space based on specified rules */
void RoyalInfantry::chess_rule(int* buff_rank_arr, int* buff_file_arr)
{
  int len_arr = 8;
  
  for(int i=0;i<len_arr;i++){
    int buff_rank = current_rank + buff_rank_arr[i];
    int buff_file = current_file + buff_file_arr[i];
    possible_rank.push_back(buff_rank);
    possible_file.push_back(buff_file);
  }    
}

void RoyalInfantry::build_possible_moves(){

  check_move_bound();
  check_friendly_fire();
}

