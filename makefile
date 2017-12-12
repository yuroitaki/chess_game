OBJ = ChessMain.o ChessBoard.o ChessPiece.o royal_infantry.o royal_rider.o king.o rook.o knight.o bishop.o queen.o pawn.o
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

royal_infantry.o: royal_infantry.h

royal_rider.o: royal_rider.h

king.o: king.h

rook.o: rook.h

knight.o: knight.h

bishop.o: bishop.h

queen.o: queen.h

pawn.o: pawn.h

clean:
	rm -f $(OBJ) $(EXE)

.PHONY: clean
