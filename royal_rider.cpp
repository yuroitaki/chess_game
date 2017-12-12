#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "royal_rider.h"

RoyalRider::RoyalRider(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr):ChessPiece(name,fig,id,init_rank,init_file,bod_ptr){}

RoyalRider::~RoyalRider(){}

bool RoyalRider::check_chess_move(const char* source, const char* desti,int d_rank,int d_file){
  
  if(!check_desti_friendly_fire(d_rank,d_file,desti,source)){
    return false;
  }
  check_friendly_fire();
  return true;
}

void RoyalRider::chess_rule(vector<int>& rank_vec, vector<int>& file_vec){

  vector<int> unwanted_index;
  vector<int> buff_rank_vec;
  vector<int> buff_file_vec;
  int max_position = 7;
  int len = rank_vec.size();
  int factor = 1;

  for(int i=0;i<(max_position*len);i++){
    
    int index = i%len;
    int leap_rank = current_rank + (factor*rank_vec[index]);
    int leap_file = current_file + (factor*file_vec[index]);

    if(check_rule_bound(leap_rank,leap_file)){
      if(board_ptr[leap_rank][leap_file]==NULL){
	if(check_unwanted_index(index,unwanted_index)){
	  
	  buff_rank_vec.push_back(factor*rank_vec[index]);
	  buff_file_vec.push_back(factor*file_vec[index]);
	}
      }
      else{
	if(check_unwanted_index(index,unwanted_index)){
	  
	  buff_rank_vec.push_back(factor*rank_vec[index]);
	  buff_file_vec.push_back(factor*file_vec[index]);
	  unwanted_index.push_back(index);
	}
      }
    }else{
      unwanted_index.push_back(index);
    }
    if(index==len-1){
      factor++;
    }
  }
  for(unsigned i=0;i<buff_rank_vec.size();i++){
    int buff_rank = current_rank + buff_rank_vec[i];
    int buff_file = current_file + buff_file_vec[i];
    possible_rank.push_back(buff_rank);
    possible_file.push_back(buff_file);
  }    
}

bool RoyalRider::check_unwanted_index(int index, vector<int>& unwanted_index){

  for(unsigned i=0;i<unwanted_index.size();i++){
    if(index == unwanted_index[i])
      return false;
  }
  return true;
}

void RoyalRider::build_possible_moves(){
  
  check_friendly_fire();
}
