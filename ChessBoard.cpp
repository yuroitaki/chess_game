#include <iostream>
#include <string>

#include "ChessBoard.h"
#include "ChessPiece.h"

using namespace std;

ChessBoard::ChessBoard(){

  turn_count = 0;
  
  board_ptr = new ChessPiece**[RANK_SIZE+1];
  for(int i=0;i<RANK_SIZE+1;i++){
    board_ptr[i] = new ChessPiece*[FILE_SIZE+1];
  }
  
  black_chess_ptr = new ChessPiece* [CHESS_PIECE_NO];
  white_chess_ptr = new ChessPiece* [CHESS_PIECE_NO];
  index_label_ptr = new ChessPiece* [CHESS_PIECE_NO];

  for (int i=0;i<RANK_SIZE+1; i++){
    for (int j=0;j<FILE_SIZE+1;j++){
      board_ptr[i][j] = NULL;
    }
  }
  for (int i=0;i<CHESS_PIECE_NO;i++){
    black_chess_ptr[i] = NULL;
    white_chess_ptr[i] = NULL;
    index_label_ptr[i] = NULL;
  }
  create_chess_pieces();
  initialize_board();
}

ChessBoard::~ChessBoard(){
  
  for (int i=0;i<CHESS_PIECE_NO;i++){
    delete black_chess_ptr[i];
    delete white_chess_ptr[i];
    delete index_label_ptr[i];
  }
  delete [] index_label_ptr;
  delete [] black_chess_ptr;
  delete [] white_chess_ptr;
  
  for(int i=0;i<RANK_SIZE+1;i++){
    delete [] board_ptr[i]; 
  }
  delete [] board_ptr;
}

void ChessBoard::print(){

  for (int i=0;i<RANK_SIZE+1;i++){
    for (int j=0;j<FILE_SIZE+1;j++){
      if(board_ptr[i][j]!=NULL){
	if(i!=0)
	  cout << *(board_ptr[i][j]) << "  " << '|' << "  ";
	else
	  cout << *(board_ptr[i][j]) << "  " << " " << "  ";
      }
      else{
	if(i!=0)
	  cout << board_ptr[i][j] << "  " << '|' << "  ";
	else
	  cout << board_ptr[i][j] << "  " << " " << "  ";
      }
    }cout << endl;
    cout << "   |-----|-----|-----|-----|-----|-----|-----|-----|" << endl;
    cout << "   |     |     |     |     |     |     |     |     |" << endl;
  }cout << endl << endl;
}

void ChessBoard::create_chess_pieces(){
  visualize_index_label();
}

void ChessBoard::initialize_board(){
  for (int i=1;i< RANK_SIZE+1;i++){
    board_ptr[i][0] = index_label_ptr[i-1];
  }
  for (int j=1;j< RANK_SIZE+1;j++){
    board_ptr[0][j] = index_label_ptr[j+RANK_SIZE-1];
  }
}

void ChessBoard::visualize_index_label(){
  
  int count = RANK_SIZE;  
  for (int i=0;i<RANK_SIZE;i++){
    int index = count;
    string rank_index = to_string(index);
    index_label_ptr[i] = new ChessPiece(rank_index,0,index,board_ptr);
    count--;
  }
  for (int i=8;i<CHESS_PIECE_NO;i++){
    int index = i - RANK_SIZE +1;
    string file_index = to_string(index);
    index_label_ptr[i] = new ChessPiece(file_index,index,0,board_ptr);
  }
}
