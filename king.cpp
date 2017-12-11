#include <iostream>
#include <string>
#include <vector>

#include "king.h"

King::King(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr):ChessPiece(name,fig,id,init_rank,init_file,bod_ptr){
}

King::~King(){
  cout << "King is deleted!" << " ";
}

bool King::check_chess_move(const char* source, const char* desti,int d_rank,int d_file){
  
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

void King::chess_rule()
{
  int len_arr = 8;
  int buff_rank_arr[len_arr] = {-1,0,1,-1,0,1,-1,1};
  int buff_file_arr[len_arr] = {-1,-1,-1,1,1,1,0,0};
  
  for(int i=0;i<len_arr;i++){
    int buff_rank = current_rank + buff_rank_arr[i];
    int buff_file = current_file + buff_file_arr[i];
    possible_rank.push_back(buff_rank);
    possible_file.push_back(buff_file);
  }    
  for(unsigned i=0;i<possible_rank.size();i++){
    cout << possible_rank[i] << " " << possible_file[i] << endl;
  }cout << endl;
}

