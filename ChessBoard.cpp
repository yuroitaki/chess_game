#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include "ChessBoard.h"
#include "ChessPiece.h"

using namespace std;

ChessBoard::ChessBoard(){

  turn_count = 0;
  check_status = NOT_CHECKED;
  
  board_ptr = new ChessPiece**[RANK_SIZE+2];      //creating the chess board interface
  for(int i=0;i<RANK_SIZE+2;i++){
    board_ptr[i] = new ChessPiece*[FILE_SIZE+2];
  }  
  black_chess_ptr = new ChessPiece* [CHESS_PIECE_NO];
  white_chess_ptr = new ChessPiece* [CHESS_PIECE_NO];
  chess_label_ptr = new ChessPiece* [CHESS_PIECE_NO];     //for visualization purpose
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
  create_chess_pieces('+');     // +/- are symbols used for White & Black chess identity
  create_chess_pieces('-');
  initialize_board();
  // print();                     can choose to print out the chess board
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

/* governs the entire flow from checking input to checking checkmate */
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
    //    print();
    return false;
  }
  // print();
  return true;
}

/* check for checkmate or stalemate */
bool ChessBoard::check_state(int d_rank,int d_file){

  string atk_name = board_ptr[d_rank][d_file]->get_chess_player();
  string def_name;
  ChessPiece** atk_ptr;
  ChessPiece** def_ptr;
  if(atk_name=="White"){
    atk_ptr = white_chess_ptr;
    def_ptr = black_chess_ptr;
    def_name = "Black";
  }
  if(atk_name == "Black"){
    atk_ptr = black_chess_ptr;
    def_ptr = white_chess_ptr;
    def_name = "White";
  }
  int king_rank = def_ptr[KING_POS]->get_curr_rank();
  int king_file = def_ptr[KING_POS]->get_curr_file();
  
  if(check_mate(atk_ptr,king_rank,king_file)){        
    if(save_king(def_ptr,atk_ptr,king_rank,king_file)){
      cout << def_name << " is in check" <<endl;
      check_status = CHECKED;
      return false;
    }
    cout << def_name << " is in checkmate" << endl;
    return true;
  }
  if(!save_king(def_ptr,atk_ptr,king_rank,king_file)){    
    cout << def_name << " is in stalemate" << endl;
    return true;
  }
  check_status = NOT_CHECKED;
  return false;
}

/* check if any defending chess piece can stop checkmate */
bool ChessBoard::save_king(ChessPiece** def_ptr, ChessPiece** atk_ptr,int king_rank,int king_file){
  vector<int>* def_rvec;               
  vector<int>* def_fvec;
  int count = 0;
  int ori_king_rank = king_rank;
  int ori_king_file = king_file;
  
  while(count<CHESS_PIECE_NO){
    if(check_life_stat(def_ptr[count])){     //to only use un-captured pieces to save king
      
      def_ptr[count]->build_possible_moves();    //construct possible move for the pieces
      def_rvec = def_ptr[count]->get_rank_vec();  //rvec = rank vector, fvec = file vector
      def_fvec = def_ptr[count]->get_file_vec();
      
      for(unsigned j=0; j<(def_rvec->size());j++){

	int buff_rank = (*def_rvec)[j];
	int buff_file = (*def_fvec)[j];
	int source_rank = def_ptr[count]->get_curr_rank();
	int source_file = def_ptr[count]->get_curr_file();
    	ChessPiece* ori_desti_ptr = board_ptr[buff_rank][buff_file];

	board_ptr[source_rank][source_file] = NULL;    //assign the piece to the possible pos.
	board_ptr[buff_rank][buff_file] = def_ptr[count];

	if(count == KING_POS){
	  king_rank = buff_rank;
	  king_file = buff_file;
	}
	else{
	  king_rank = ori_king_rank;
	  king_file = ori_king_file;
	}
	if(!check_mate(atk_ptr,king_rank,king_file)){  //check if still under checkmate
	  
	  def_ptr[count]->clear_vector();
	  board_ptr[source_rank][source_file] = def_ptr[count];
	  board_ptr[buff_rank][buff_file] = ori_desti_ptr;
       	  return true;
	}
	board_ptr[source_rank][source_file] = def_ptr[count];
	board_ptr[buff_rank][buff_file] = ori_desti_ptr;
      }def_ptr[count]->clear_vector();
    }count++;
  }return false;
}

/* check if under checkmate condition */
bool ChessBoard::check_mate(ChessPiece** atck_ptr,int king_rank,int king_file){

  vector<int>* atck_rvec;
  vector<int>* atck_fvec;
  int count = 0;
  
  while(count<CHESS_PIECE_NO){
    if(check_life_stat(atck_ptr[count])){
      
      atck_ptr[count]->build_possible_moves();
      atck_rvec = atck_ptr[count]->get_rank_vec();
      atck_fvec = atck_ptr[count]->get_file_vec();
    
      for(unsigned j=0; j<(atck_rvec->size());j++){   //compare possible pos. with king pos.
	if((king_rank == (*atck_rvec)[j])&&(king_file == (*atck_fvec)[j])){
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

/* check if a piece is captured or not  */
bool ChessBoard::check_life_stat(ChessPiece* test_piece){

  for(unsigned i=0;i<captured_vec.size();i++){
    if(test_piece==captured_vec[i])
      return false;
  }
  return true;
}

/* check player turn and source square  */
bool ChessBoard::check_source(int s_rank,int s_file,const char* source){

  if(board_ptr[s_rank][s_file]==NULL){
    cout << "There is no piece at position " << source <<"!" << endl;
    return false;
  }
  if(turn_count%2==0){
    if((board_ptr[s_rank][s_file]->get_chess_player())=="White"){
      cout << "It is not White's turn to move!" << endl;
      return false;
    }
  }
  if(turn_count%2==1){
    if((board_ptr[s_rank][s_file]->get_chess_player())=="Black"){
      cout << "It is not Black's turn to move!" << endl;
      return false;
    }
  }
  return true;
}

/* implement the legal move of a piece on the chess board  */
void ChessBoard::execute_move(int s_rank,int s_file, int d_rank,int d_file,const char* source,const char* desti){

  ChessPiece* buff_desti = board_ptr[d_rank][d_file];
  ChessPiece* buff_source =  board_ptr[s_rank][s_file];
  
  if(buff_desti==NULL){
    
    cout << buff_source->get_chess_player() << "'s " << buff_source->get_chess_name() << " moves from " << source << " to " << desti << endl;

    buff_source->set_position(d_rank,d_file);          //update the current pos. of the piece
    board_ptr[d_rank][d_file] = board_ptr[s_rank][s_file];;
    board_ptr[s_rank][s_file] = NULL;
  }
  else{ 
    cout << buff_source->get_chess_player() << "'s " << buff_source->get_chess_name() << " moves from " << source << " to " << desti << " taking " << buff_desti->get_chess_player() << "'s "<< buff_desti->get_chess_name() << endl;

    captured_vec.push_back(board_ptr[d_rank][d_file]);   //collect the captured piece
    buff_source->set_position(d_rank,d_file);
    board_ptr[d_rank][d_file] = board_ptr[s_rank][s_file];
    board_ptr[s_rank][s_file] = NULL;
  }
}

/* format the input source and destination */
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
  int map_rank[8] = {8,7,6,5,4,3,2,1};   //change the rank from chess format to matrix form
  for(int i=0;i<8; i++){
    if(buff_s_rank == map_rank[i])
      s_rank = i+1;
    if(buff_d_rank == map_rank[i])
       d_rank = i+1;
  }
  return true;
}

/* to visualize the chess board */
void ChessBoard::print(){

  for(auto iterator=captured_vec.begin();iterator!=captured_vec.end();iterator++){
    if(*iterator!=NULL)                    //to visualize captured pieces
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
    chess_fig[i] = make_special_piece(id,chess_idd[i],i);   // ASCII symbol of the piece
  }
  
  buffer_ptr[0] = new Rook ("Rook",chess_fig[0],chess_idd[0],rank_index,1,board_ptr,this);
  buffer_ptr[1] = new Knight ("Knight",chess_fig[1],chess_idd[1],rank_index,2,board_ptr,this);
  buffer_ptr[2] = new Bishop ("Bishop",chess_fig[2],chess_idd[2],rank_index,3,board_ptr,this);
  buffer_ptr[3] = new Queen ("Queen",chess_fig[3],chess_idd[3],rank_index,4,board_ptr,this);
  buffer_ptr[4] = new King ("King",chess_fig[4],chess_idd[4],rank_index,5,board_ptr,this);
  buffer_ptr[5] = new Bishop ("Bishop",chess_fig[5],chess_idd[5],rank_index,6,board_ptr,this);
  buffer_ptr[6] = new Knight ("Knight",chess_fig[6],chess_idd[6],rank_index,7,board_ptr,this);
  buffer_ptr[7] = new Rook ("Rook",chess_fig[7],chess_idd[7],rank_index,8,board_ptr,this);

  string pawn_idd[8] = {"I","II","III","IV","V","VI","VII","VIII"};
  for (int i=0;i<RANK_SIZE;i++){
    string pawn_fig = make_pawn_piece(id,pawn_idd[i]);
    buffer_ptr[i+8] = new Pawn("Pawn",pawn_fig,pawn_idd[i],pawn_rank_index,i+1,board_ptr,this);
  }
}

/* allocate each piece to their initial position*/
void ChessBoard::initialize_board(){
  
  for (int i=1;i< RANK_SIZE+1;i++){             //allocating the 'index' piece for visualization
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

/* creating index in chess format for the visualized chess board*/
void ChessBoard::visualize_chess_label(){
  
  int count = RANK_SIZE;  
  for (int i=0;i<RANK_SIZE;i++){
    int index = count;
    string rank_label(1,index+ASCII_NO);
    chess_label_ptr[i] = new ChessPiece("Label",rank_label,rank_label,0,index,board_ptr,this);
    count--;
  }
  for (int i=RANK_SIZE;i<CHESS_PIECE_NO;i++){
    int index = i - RANK_SIZE + 1;
    string file_label(1,index+ASCII_ALP);
    chess_label_ptr[i] = new ChessPiece("Label",file_label,file_label,index,0,board_ptr,this);
  }
}

/* creating index in matrix format for the visualized chess board*/
void ChessBoard::visualize_index_label(){
  
  for (int i=0;i<RANK_SIZE;i++){
    int index = i+1;
    string rank_label(1,index+ASCII_NO);
    index_label_ptr[i] = new ChessPiece("Index",rank_label,rank_label,RANK_SIZE+1,index,board_ptr,this);
  }
  for (int i=RANK_SIZE;i<CHESS_PIECE_NO;i++){
    int index = i - RANK_SIZE + 1;
    string file_label(1,index+ASCII_NO);
    index_label_ptr[i] = new ChessPiece("Index",file_label,file_label,index,FILE_SIZE+1,board_ptr,this);
  }
}

/* resurrect and re-allocate all chess pieces */
void ChessBoard::resetBoard(){

  for (int i=0;i<RANK_SIZE+2; i++){
    for (int j=0;j<FILE_SIZE+2;j++){
      if(board_ptr[i][j] != NULL){
	int buff_rank = board_ptr[i][j]->get_init_rank();
	int buff_file = board_ptr[i][j]->get_init_file();
	board_ptr[i][j]->set_position(buff_rank,buff_file);  //update chess pos.
	board_ptr[i][j]->clear_vector();
	board_ptr[i][j] = NULL;
      }
    }
  }
  for(auto iterator=captured_vec.begin();iterator!=captured_vec.end();iterator++){
    *iterator = NULL;           //empty the captured vector
  }
  turn_count = 0;
  initialize_board();
  //print();
  cout << "A new chess game is started!" << endl;
}

/* assign proper ASCII symbol and unique id to the chess piece */
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

ChessPiece** ChessBoard::get_chess_ptr(int signal){
  
  if(signal==WHITE){
    return white_chess_ptr;
  }
  if(signal==BLACK){
    return black_chess_ptr;
  }
  return white_chess_ptr;
}


int ChessBoard::get_check_status(){
  return check_status;
}
