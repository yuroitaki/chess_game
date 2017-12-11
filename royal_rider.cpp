#include <iostream>
#include <string>
#include <vector>

#include "royal_rider.h"

RoyalRider::RoyalRider(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr):ChessPiece(name,fig,id,init_rank,init_file,bod_ptr){
}

RoyalRider::~RoyalRider(){
  cout << "RoyalRider is deleted!" << " ";
}

bool RoyalRider::check_chess_move(const char* source, const char* desti,int d_rank,int d_file){
  
  if(!check_friendly_fire(d_rank,d_file,desti)){
    return false;
  }
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
	  //  cout << " pushed in " << index << endl;
	}
      }
      else{
	if(check_unwanted_index(index,unwanted_index)){
	  buff_rank_vec.push_back(factor*rank_vec[index]);
	  buff_file_vec.push_back(factor*file_vec[index]);
	  unwanted_index.push_back(index);
	  //	  cout << "pushed in unwanted null " << index << endl;
	}
      }
    }else{
      unwanted_index.push_back(index);
      //cout << " unwanted bound " << index << endl;
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
  for(unsigned i=0;i<possible_rank.size();i++){
    cout << possible_rank[i] << " " << possible_file[i] << endl;
  }cout << endl;
}

bool RoyalRider::check_unwanted_index(int index, vector<int>& unwanted_index){

  for(unsigned i=0;i<unwanted_index.size();i++){
    if(index == unwanted_index[i])
      return false;
  }
  return true;
}



  /*  while((count < (max_position*len1))&&(rank_vec.size()!=0)){
    int index  = count%rank_vec.size();
    int leap_rank = current_rank + (factor*rank_vec[index]);
    int leap_file = current_file + (factor*file_vec[index]);
    int len = rank_vec.size();
    
    if(check_rule_bound(leap_rank,leap_file)){
      if(board_ptr[leap_rank][leap_file]==NULL){
	buff_rank_vec.push_back(factor*rank_vec[index]);
	buff_file_vec.push_back(factor*file_vec[index]);
      }
      else{
	buff_rank_vec.push_back(factor*rank_vec[index]);
	buff_file_vec.push_back(factor*file_vec[index]);
	rank_vec.erase(rank_vec.begin()+index);
      	file_vec.erase(file_vec.begin()+index);
	count--;
      }
    }
    else{
	rank_vec.erase(rank_vec.begin()+index);
      	file_vec.erase(file_vec.begin()+index);
	count--;
    }
    if(index==len-1){
       factor++;

    }
    count++;
  }
  */
