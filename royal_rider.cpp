#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "royal_rider.h"

/* a derived class of ChessPiece, and a superclass of Queen, Rook and Bishop*/

RoyalRider::RoyalRider(string name,string fig,string id,int init_rank,int init_file,ChessPiece*** bod_ptr,ChessBoard* chess_b_ptr):ChessPiece(name,fig,id,init_rank,init_file,bod_ptr,chess_b_ptr){}

RoyalRider::~RoyalRider(){}

bool RoyalRider::check_chess_move(const char* source, const char* desti,int d_rank,int d_file){
  
  if(!check_desti_friendly_fire(d_rank,d_file,desti,source)){
    return false;
  }
  check_friendly_fire();
  return true;
}

/* constructing the possible square space based on specified rules */
void RoyalRider::chess_rule(vector<int>& rank_vec, vector<int>& file_vec){

  vector<int> unwanted_index;   //to skip over a particular move in the basic move vector
  vector<int> buff_rank_vec;    //which are rank_vec and file_vec, due to blockage/out_bound
  vector<int> buff_file_vec;
  int max_position = 7;        //max possible no. of possible square in 1 direction
  int len = rank_vec.size();
  int factor = 1;              //factor multiply w/ the basic move (rank,file) 

  for(int i=0;i<(max_position*len);i++){
    
    int index = i%len;       //to loop over the basic move vector
    int leap_rank = current_rank + (factor*rank_vec[index]);
    int leap_file = current_file + (factor*file_vec[index]);

    if(check_rule_bound(leap_rank,leap_file)){   //check if the new pos. is out of bound
      if(board_ptr[leap_rank][leap_file]==NULL){  //check if there is any piece at that pos.
	if(check_unwanted_index(index,unwanted_index)){ 
	  
	  buff_rank_vec.push_back(factor*rank_vec[index]);
	  buff_file_vec.push_back(factor*file_vec[index]);
	}
      }
      else{
	if(check_unwanted_index(index,unwanted_index)){
	  
	  buff_rank_vec.push_back(factor*rank_vec[index]);  //takes the move that end up
	  buff_file_vec.push_back(factor*file_vec[index]); // on a square with a piece, but
	  unwanted_index.push_back(index);                 // not taking any further move
	}                                                  // i.e. (factored move)    
      }
    }else{
      unwanted_index.push_back(index);
    }
    if(index==len-1){    //queen, bishop, and rook can travel >1 square, hence the factor
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
