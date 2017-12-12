#include <iostream>
#include <string>
#include <vector>

#include "ChessPiece.h"
#include "ChessBoard.h"

using namespace std;

ChessPiece::ChessPiece(string name, string fig,string id,int init_rank, int init_file, ChessPiece*** bod_ptr){
  chess_name = name;
  chess_fig = fig;
  chess_id = id;
  initial_rank = init_rank;
  initial_file = init_file;
  current_rank = init_rank;
  current_file = init_file;
  board_ptr = bod_ptr;;
  set_player();
}

ChessPiece::~ChessPiece(){
}

bool ChessPiece::check_chess_move(const char* source, const char* desti,int d_rank,int d_file){
   
  if(!check_desti_friendly_fire(d_rank,d_file,desti)){
    return false;
  }
  check_move_bound();
  check_friendly_fire();
  return true;
}


bool ChessPiece::verify_desti(int d_rank,int d_file,const char* desti){
  
  for(unsigned i=0;i<possible_rank.size();i++){
    if((d_rank==possible_rank[i])&&(d_file==possible_file[i])){
      return true;
    }
  }
  cerr << chess_player << "'s " << chess_name << " cannot move to " << desti << "!"<<endl;
  return false;
}


bool ChessPiece::check_desti_friendly_fire(int d_rank,int d_file,const char* desti){

  ChessPiece* buff_d_ptr = board_ptr[d_rank][d_file]; 
  if (buff_d_ptr!=NULL){
    if(buff_d_ptr->get_chess_player()==chess_player){
      cerr << buff_d_ptr->get_chess_name() << " at " << desti << " is also " << chess_player << "'s!" << endl;
      return false;
    }
  }return true;
}

void ChessPiece::check_friendly_fire(){
  int count = 0;
  while (count < possible_rank.size()){
    
    int buff_rank = possible_rank[count];
    int buff_file = possible_file[count];
    ChessPiece* buff_test_ptr = board_ptr[buff_rank][buff_file];
    
    if(buff_test_ptr!=NULL){
      if(buff_test_ptr->get_chess_player()==chess_player){
	possible_rank.erase(possible_rank.begin()+count);
	possible_file.erase(possible_file.begin()+count);
	count--;
      }
    }count++;
  }
  // for(unsigned i=0;i<possible_rank.size();i++){
  //   cout << possible_rank[i] << " " << possible_file[i] << endl;
  // }
  // cout << chess_id << endl;
  // cout << endl;
}

void ChessPiece::check_move_bound(){
  
  int count=0;
  while(count<possible_rank.size()){
    int buff_rank = possible_rank[count];
    int buff_file = possible_file[count];
    if(!check_rule_bound(buff_rank,buff_file)){
      possible_rank.erase(possible_rank.begin()+count);
      possible_file.erase(possible_file.begin()+count);
      count--;
    }count++;
  }
  // for(unsigned i=0;i<possible_rank.size();i++){
  //   cout << possible_rank[i] << " " << possible_file[i] << endl;
  // }cout << endl << endl;
}

void::ChessPiece::build_possible_moves(){
  check_move_bound();
}


bool ChessPiece::check_rule_bound(int rank, int file){
  
  if((rank<1)||(rank>8)){
    return false;
  }
  if((file<1)||(file>8)){
    return false;
  }
  return true; 
}

ostream& operator<<(ostream& out, const ChessPiece& cp){
  return out << cp.chess_fig;
}

int ChessPiece::get_init_rank(){
  return initial_rank;
}

int ChessPiece::get_init_file(){
  return initial_file;
}


int ChessPiece::get_curr_rank(){
  return current_rank;
}

int ChessPiece::get_curr_file(){
  return current_file;
}

vector<int>* ChessPiece::get_rank_vec(){
  
  vector<int>* rank_ptr;
  rank_ptr = &possible_rank;
  return rank_ptr;
}

vector<int>* ChessPiece::get_file_vec(){

  vector<int>* file_ptr;
  file_ptr = &possible_file;
  return file_ptr;
}

string ChessPiece::get_chess_player(){
  return chess_player;
}

string ChessPiece::get_chess_name(){
  return chess_name;
}
void ChessPiece::set_player(){
  if(initial_rank>6)
    chess_player = "White";
  if(initial_rank<3)
    chess_player = "Black";
}

void ChessPiece::set_position(int rank, int file){
  current_rank = rank;
  current_file = file;
}

void ChessPiece::clear_vector(){
  possible_rank.clear();
  possible_file.clear();
}
