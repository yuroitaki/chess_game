#include <iostream>
#include <string>
#include <vector>

#include "royal_infantry.h"

RoyalInfantry::RoyalInfantry(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr):ChessPiece(name,fig,id,init_rank,init_file,bod_ptr){
}

RoyalInfantry::~RoyalInfantry(){
  cout << "Royal Infantry is deleted!" << " ";
}

bool RoyalInfantry::check_chess_move(const char* source, const char* desti,int d_rank,int d_file){ 
  if(!check_desti_friendly_fire(d_rank,d_file,desti)){
    return false;
  }
  check_move_bound();
  check_friendly_fire();
  return true;
}

void RoyalInfantry::chess_rule(int* buff_rank_arr, int* buff_file_arr)
{
  int len_arr = 8;
  
  for(int i=0;i<len_arr;i++){
    int buff_rank = current_rank + buff_rank_arr[i];
    int buff_file = current_file + buff_file_arr[i];
    possible_rank.push_back(buff_rank);
    possible_file.push_back(buff_file);
  }    
  // for(unsigned i=0;i<possible_rank.size();i++){
  //   cout << possible_rank[i] << " " << possible_file[i] << endl;
  // }
  // cout << chess_id << endl;
  // cout << endl;
}

void RoyalInfantry::build_possible_moves(){

  check_move_bound();
  check_friendly_fire();
}
