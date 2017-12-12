#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "ChessBoard.h"
#include "ChessPiece.h"

using namespace std;

ChessBoard::ChessBoard(){

  turn_count = 0;
  
  board_ptr = new ChessPiece**[RANK_SIZE+2];
  for(int i=0;i<RANK_SIZE+2;i++){
    board_ptr[i] = new ChessPiece*[FILE_SIZE+2];
  }
  
  black_chess_ptr = new ChessPiece* [CHESS_PIECE_NO];
  white_chess_ptr = new ChessPiece* [CHESS_PIECE_NO];
  chess_label_ptr = new ChessPiece* [CHESS_PIECE_NO];
  index_label_ptr = new ChessPiece* [CHESS_PIECE_NO];
  
  for (int i=0;i<RANK_SIZE+2; i++){
    for (int j=0;j<FILE_SIZE+2;j++){
      board_ptr[i][j] = NULL;
    }
  }
  for (int i=0;i<CHESS_PIECE_NO;i++){
    black_chess_ptr[i] = NULL;
    white_chess_ptr[i] = NULL;
    chess_label_ptr[i] = NULL;
    index_label_ptr[i] = NULL;
  }
  visualize_chess_label();
  visualize_index_label();
  create_chess_pieces('+');
  create_chess_pieces('-');
  initialize_board();
  //print();
  cout << "A new chess game is started!" << endl;
}

ChessBoard::~ChessBoard(){
  
  for (int i=0;i<CHESS_PIECE_NO;i++){
    delete black_chess_ptr[i];
    delete white_chess_ptr[i];
    delete chess_label_ptr[i];
    delete index_label_ptr[i];
  }
  delete [] black_chess_ptr;
  delete [] white_chess_ptr;
  delete [] chess_label_ptr;
  delete [] index_label_ptr;
  
  for(int i=0;i<RANK_SIZE+2;i++){
    delete [] board_ptr[i]; 
  }
  delete [] board_ptr;
}

bool ChessBoard::submitMove(const char* source, const char* desti){
  
  turn_count++;
  int source_rank, source_file, desti_rank, desti_file;

  if(!format_move(source,desti,source_rank,source_file,desti_rank,desti_file))
    return false;
  
  if(!check_source(source_rank,source_file,source)){
    return false;
  }
  if(!board_ptr[source_rank][source_file]->check_chess_move(source,desti,desti_rank,desti_file)){
    return false;
  }
  execute_move(source_rank,source_file,desti_rank,desti_file,source,desti);
  
  if(check_state(desti_rank,desti_file)){
    //print();
    return false;
  }
  //print();
  return true;
}


bool ChessBoard::check_state(int d_rank,int d_file){

  string player_name = board_ptr[d_rank][d_file]->get_chess_player();
  ChessPiece** att_ptr;
  ChessPiece** opp_ptr;
  if(player_name=="White"){
    att_ptr = white_chess_ptr;
    opp_ptr = black_chess_ptr;
  }
  if (player_name == "Black"){
    att_ptr = black_chess_ptr;
    opp_ptr = white_chess_ptr;
  }
  int def_rank = opp_ptr[KING_POS]->get_curr_rank();
  int def_file = opp_ptr[KING_POS]->get_curr_file();
  
  check_mate(att_ptr,def_rank,def_file);
  
  return true;
}

bool ChessBoard::check_mate(ChessPiece** atck_ptr,int def_rank,int def_file){

  vector<int>* atck_rank;
  vector<int>* atck_file;
  int count = 0;
  
  while(count<CHESS_PIECE_NO){
    if(check_life_stat(atck_ptr[count])){
      
      atck_ptr[count]->build_possible_moves();
      atck_rank = atck_ptr[count]->get_rank_vec();
      atck_file = atck_ptr[count]->get_file_vec();
    
      for(unsigned j=0; j<(atck_rank->size());j++){
	if((def_rank == (*atck_rank)[j])&&(def_file == (*atck_file)[j])){
	  atck_ptr[count]->clear_vector();
	  return true;
	}
      }
      atck_ptr[count]->clear_vector();
    }
    count++;
  }
  return false;
}

bool ChessBoard::check_life_stat(ChessPiece* test_piece){

  for(unsigned i=0;i<captured_vec.size();i++){
    if(test_piece==captured_vec[i])
      return false;
  }
  return true;
}


bool ChessBoard::check_source(int s_rank,int s_file,const char* source){

  if(board_ptr[s_rank][s_file]==NULL){
    cerr << "There is no piece at position " << source <<"!" << endl;
    return false;
  }
  if(turn_count%2==0){
    if((board_ptr[s_rank][s_file]->get_chess_player())=="White"){
      cerr << "It is not White's turn to move!" << endl;
      return false;
    }
  }
  if(turn_count%2==1){
    if((board_ptr[s_rank][s_file]->get_chess_player())=="Black"){
      cerr << "It is not Black's turn to move!" << endl;
      return false;
    }
  }
  return true;
}

void ChessBoard::execute_move(int s_rank,int s_file, int d_rank,int d_file,const char* source,const char* desti){

  ChessPiece* buff_desti = board_ptr[d_rank][d_file];
  ChessPiece* buff_source =  board_ptr[s_rank][s_file];
  
  if(buff_desti==NULL){
    
    cout << buff_source->get_chess_player() << "'s " << buff_source->get_chess_name() << " moves from " << source << " to " << desti << endl;

    buff_source->set_position(d_rank,d_file);
    board_ptr[d_rank][d_file] = board_ptr[s_rank][s_file];;
    board_ptr[s_rank][s_file] = NULL;
  }
  else{ 
    cout << buff_source->get_chess_player() << "'s " << buff_source->get_chess_name() << " moves from " << source << " to " << desti << " taking " << buff_desti->get_chess_player() << "'s "<< buff_desti->get_chess_name() << endl;

    captured_vec.push_back(board_ptr[d_rank][d_file]);
    buff_source->set_position(d_rank,d_file);
    board_ptr[d_rank][d_file] = board_ptr[s_rank][s_file];
    board_ptr[s_rank][s_file] = NULL;
  }
}

bool ChessBoard::format_move(const char* source, const char* desti,int& s_rank,int& s_file, int& d_rank,int& d_file){

  int len_source = strlen(source);
  int len_desti = strlen(desti);

  if(len_source!=2){
    cerr <<"The format of " <<source << " is wrong as a source square!" << endl;
    return false;
  }
  if(len_desti!=2){
    cerr <<"The format of " <<desti << " is wrong as a destination square!" << endl;
    return false;
  }
  s_file = source[0] - ASCII_ALP;
  d_file = desti[0] - ASCII_ALP;
  int buff_s_rank = source[1] - ASCII_NO;
  int buff_d_rank = desti[1] - ASCII_NO;
  
  if(!check_out_bound(buff_s_rank,s_file)){
    cerr << source <<" is an invalid source square!" << endl;
    return false;
  }
  if(!check_out_bound(buff_d_rank,d_file)){
    cerr << desti <<" is an invalid destination square!" << endl;
    return false;
  }
  int map_rank[8] = {8,7,6,5,4,3,2,1};
  for(int i=0;i<8; i++){
    if(buff_s_rank == map_rank[i])
      s_rank = i+1;
    if(buff_d_rank == map_rank[i])
       d_rank = i+1;
  }
  return true;
}

void ChessBoard::print(){

  for(auto iterator=captured_vec.begin();iterator!=captured_vec.end();iterator++){
    if(*iterator!=NULL)
      cout << **iterator << " ";
    }cout << endl;
  
  for (int i=0;i<RANK_SIZE+2;i++){
    for (int j=0;j<FILE_SIZE+2;j++){
      if(board_ptr[i][j]!=NULL){
	if((i!=0)&&(i!=RANK_SIZE+1)&&(j!=FILE_SIZE+1))
	  cout << *(board_ptr[i][j]) << "  " << '|' << "  ";
	else
	  cout << *(board_ptr[i][j]) << "  " << " " << "  ";
      }
      else{
	if((i!=0)&&(i!=RANK_SIZE+1)&&(j!=FILE_SIZE+1))
	  cout << board_ptr[i][j] << "  " << '|' << "  ";
	else
	  cout << board_ptr[i][j] << "  " << " " << "  ";
      }
    }
    if(i!=RANK_SIZE+1){
      cout << endl;
      cout << "   |-----|-----|-----|-----|-----|-----|-----|-----|" << endl;
      cout << "   |     |     |     |     |     |     |     |     |" << endl;
      }
  }cout << endl << endl;
}

void ChessBoard::create_chess_pieces(char id){

  ChessPiece** buffer_ptr;
  int rank_index,pawn_rank_index;
  string chess_player;
  if (id == '+'){
     buffer_ptr = white_chess_ptr;
     rank_index = 8;
     pawn_rank_index = 7;
  }
  if(id == '-'){
    buffer_ptr = black_chess_ptr;
    rank_index = 1;
    pawn_rank_index = 2;
  }
  string chess_idd[8] = {"LR","LK","LB","Q","K","RB","RK","RR"};
  string chess_fig[8];
  for (int i=0;i<RANK_SIZE;i++){
    chess_fig[i] = make_special_piece(id,chess_idd[i],i);
  }
  
  buffer_ptr[0] = new Rook ("Rook",chess_fig[0],chess_idd[0],rank_index,1,board_ptr);
  buffer_ptr[1] = new Knight ("Knight",chess_fig[1],chess_idd[1],rank_index,2,board_ptr);
  buffer_ptr[2] = new Bishop ("Bishop",chess_fig[2],chess_idd[2],rank_index,3,board_ptr);
  buffer_ptr[3] = new Queen ("Queen",chess_fig[3],chess_idd[3],rank_index,4,board_ptr);
  buffer_ptr[4] = new King ("King",chess_fig[4],chess_idd[4],rank_index,5,board_ptr);
  buffer_ptr[5] = new Bishop ("Bishop",chess_fig[5],chess_idd[5],rank_index,6,board_ptr);
  buffer_ptr[6] = new Knight ("Knight",chess_fig[6],chess_idd[6],rank_index,7,board_ptr);
  buffer_ptr[7] = new Rook ("Rook",chess_fig[7],chess_idd[7],rank_index,8,board_ptr);

  string pawn_idd[8] = {"I","II","III","IV","V","VI","VII","VIII"};
  for (int i=0;i<RANK_SIZE;i++){
    string pawn_fig = make_pawn_piece(id,pawn_idd[i]);
    buffer_ptr[i+8] = new Pawn("Pawn",pawn_fig,pawn_idd[i],pawn_rank_index,i+1,board_ptr);
  }
}

void ChessBoard::initialize_board(){
  
  for (int i=1;i< RANK_SIZE+1;i++){
    board_ptr[i][0] = index_label_ptr[i-1];
    board_ptr[i][FILE_SIZE+1] = chess_label_ptr[i-1];
  }
  for (int j=1;j< FILE_SIZE+1;j++){
    board_ptr[0][j] = index_label_ptr[j+FILE_SIZE-1];
    board_ptr[RANK_SIZE+1][j] = chess_label_ptr[j+FILE_SIZE-1];
  }
  for(int i=0;i<CHESS_PIECE_NO;i++){
    int white_rank = white_chess_ptr[i]->get_init_rank();
    int white_file = white_chess_ptr[i]->get_init_file();
    board_ptr[white_rank][white_file] = white_chess_ptr[i];
  }
  for(int i=0;i<CHESS_PIECE_NO;i++){
    int black_rank = black_chess_ptr[i]->get_init_rank();
    int black_file = black_chess_ptr[i]->get_init_file();
    board_ptr[black_rank][black_file] = black_chess_ptr[i];
  }
}

void ChessBoard::visualize_chess_label(){
  
  int count = RANK_SIZE;  
  for (int i=0;i<RANK_SIZE;i++){
    int index = count;
    string rank_label(1,index+ASCII_NO);
    chess_label_ptr[i] = new ChessPiece("Label",rank_label,rank_label,0,index,board_ptr);
    count--;
  }
  for (int i=RANK_SIZE;i<CHESS_PIECE_NO;i++){
    int index = i - RANK_SIZE + 1;
    string file_label(1,index+ASCII_ALP);
    chess_label_ptr[i] = new ChessPiece("Label",file_label,file_label,index,0,board_ptr);
  }
}

void ChessBoard::visualize_index_label(){
  
  for (int i=0;i<RANK_SIZE;i++){
    int index = i+1;
    string rank_label(1,index+ASCII_NO);
    index_label_ptr[i] = new ChessPiece("Index",rank_label,rank_label,RANK_SIZE+1,index,board_ptr);
  }
  for (int i=RANK_SIZE;i<CHESS_PIECE_NO;i++){
    int index = i - RANK_SIZE + 1;
    string file_label(1,index+ASCII_NO);
    index_label_ptr[i] = new ChessPiece("Index",file_label,file_label,index,FILE_SIZE+1,board_ptr);
  }
}

void ChessBoard::resetBoard(){

  for (int i=0;i<RANK_SIZE+2; i++){
    for (int j=0;j<FILE_SIZE+2;j++){
      if(board_ptr[i][j] != NULL){
	int buff_rank = board_ptr[i][j]->get_init_rank();
	int buff_file = board_ptr[i][j]->get_init_file();
	board_ptr[i][j]->set_position(buff_rank,buff_file);
	board_ptr[i][j]->clear_vector();
	board_ptr[i][j] = NULL;
      }
    }
  }
  for(auto iterator=captured_vec.begin();iterator!=captured_vec.end();iterator++){
    *iterator = NULL;
  }
  turn_count = 0;
  initialize_board();
  //print();
  cout << "A new chess game is started!" << endl;
}

string ChessBoard::make_special_piece(char player_id, string& chess_id, int count){

  const char* buffer_id_arr[16] = {u8"\u2656",u8"\u2658",u8"\u2657",u8"\u2655",u8"\u2654",u8"\u2657",u8"\u2658",u8"\u2656",u8"\u265C",u8"\u265E",u8"\u265D",u8"\u265B",u8"\u265A",u8"\u265D",u8"\u265E",u8"\u265C"};
    
  const char* buffer_id;
  if(player_id == '+'){
    buffer_id = buffer_id_arr[count];
  }
  if(player_id == '-'){
    buffer_id = buffer_id_arr[count+8];
  }
  chess_id+=player_id; 
  string chess_fig;
  chess_fig+=buffer_id;

  return chess_fig;
}

string ChessBoard::make_pawn_piece(char player_id,string& pawn_id){

  const char* buffer_fig;
  if(player_id == '+')
    buffer_fig = u8"\u2659";
  if(player_id == '-')
    buffer_fig = u8"\u265F";
  
  pawn_id+=player_id;
  string pawn_fig;
  pawn_fig+=buffer_fig;
  
  return pawn_fig;
}

bool ChessBoard::check_out_bound(int rank, int file){

  if((rank<1)||(rank>8)){
    return false;
  }
  if((file<1)||(file>8)){
    return false;
  }return true; 
}
