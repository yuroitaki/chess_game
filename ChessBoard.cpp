#include <iostream>
#include <string>

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

  cout << "A new chess game is started!" << endl << endl;
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

void ChessBoard::submitMove(const char* source, const char* desti){

  int source_rank, source_file, desti_rank, desti_file;
  source_file = source[0] - ASCII_ALP;
  desti_file = desti[0] - ASCII_ALP;
  source_rank = source[1] - ASCII_NO;
  desti_rank = desti[1] - ASCII_NO;

  execute_move(source_rank,source_file,desti_rank,desti_file);
}

void ChessBoard::print(){

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
  buffer_ptr[0] = new Rook (chess_fig[0],chess_idd[0],rank_index,1,board_ptr);
  buffer_ptr[1] = new Knight (chess_fig[1],chess_idd[1],rank_index,2,board_ptr);
  buffer_ptr[2] = new Bishop (chess_fig[2],chess_idd[2],rank_index,3,board_ptr);
  buffer_ptr[3] = new Queen (chess_fig[3],chess_idd[3],rank_index,4,board_ptr);
  buffer_ptr[4] = new King (chess_fig[4],chess_idd[4],rank_index,5,board_ptr);
  buffer_ptr[5] = new Bishop (chess_fig[5],chess_idd[5],rank_index,6,board_ptr);
  buffer_ptr[6] = new Knight (chess_fig[6],chess_idd[6],rank_index,7,board_ptr);
  buffer_ptr[7] = new Rook (chess_fig[7],chess_idd[7],rank_index,8,board_ptr);

  string pawn_idd[8] = {"I","II","III","IV","V","VI","VII","VIII"};
  for (int i=0;i<RANK_SIZE;i++){
    string pawn_fig = make_pawn_piece(id,pawn_idd[i]);
    buffer_ptr[i+8] = new Pawn(pawn_fig,pawn_idd[i],pawn_rank_index,i+1,board_ptr);
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
    if(white_chess_ptr[i]!=NULL){
      int white_rank = white_chess_ptr[i]->get_init_rank();
      int white_file = white_chess_ptr[i]->get_init_file();
      board_ptr[white_rank][white_file] = white_chess_ptr[i];
    }
  }
  for(int i=0;i<CHESS_PIECE_NO;i++){
    if(black_chess_ptr[i]!=NULL){
      int black_rank = black_chess_ptr[i]->get_init_rank();
      int black_file = black_chess_ptr[i]->get_init_file();
      board_ptr[black_rank][black_file] = black_chess_ptr[i];
    }
  }
}

void ChessBoard::visualize_chess_label(){
  
  int count = RANK_SIZE;  
  for (int i=0;i<RANK_SIZE;i++){
    int index = count;
    string rank_label(1,index+ASCII_NO);
    chess_label_ptr[i] = new ChessPiece(rank_label,rank_label,0,index,board_ptr);
    count--;
  }
  for (int i=RANK_SIZE;i<CHESS_PIECE_NO;i++){
    int index = i - RANK_SIZE + 1;
    string file_label(1,index+ASCII_ALP);
    chess_label_ptr[i] = new ChessPiece(file_label,file_label,index,0,board_ptr);
  }
}

void ChessBoard::visualize_index_label(){
  
  for (int i=0;i<RANK_SIZE;i++){
    int index = i+1;
    string rank_label(1,index+ASCII_NO);
    index_label_ptr[i] = new ChessPiece(rank_label,rank_label,RANK_SIZE+1,index,board_ptr);
  }
  for (int i=RANK_SIZE;i<CHESS_PIECE_NO;i++){
    int index = i - RANK_SIZE + 1;
    string file_label(1,index+ASCII_NO);
    index_label_ptr[i] = new ChessPiece(file_label,file_label,index,FILE_SIZE+1,board_ptr);
  }
}

void ChessBoard::resetBoard(){
  initialize_board();
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
