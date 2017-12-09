OBJ = ChessMain.o ChessBoard.o ChessPiece.o
EXE = chess
CXX = g++
CXXFLAGS = -Wall -g -std=c++11

$(EXE): $(OBJ)
	$(CXX) $(OBJ) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

ChessMain.o: ChessBoard.h

ChessBoard.o: ChessBoard.h

ChessPiece.o: ChessPiece.h 

clean:
	rm -f $(OBJ) $(EXE)

.PHONY: clean
