import java.util.*;

/**
  * Implementation of Knight piece, including moves.
  */
public class Knight extends Piece {
    public Knight(Color c) { 
        this.color = c;
   }

    public String toString() {
        Color c = color();
        if (c.equals(Color.WHITE)) {
            return "wn";
        } else {
            return "bn";
        }
    }

    /* Returns the possible moves of a Knight given a location */
    public List<String> moves(Board b, String loc) {
	      List<String> moves = new ArrayList<String>();
        List<int[]> indicesMoves = new ArrayList<int[]>();
        
        // get current indices of Knight
	      int[] colrow = indicesFromLocation(loc);
        int col = colrow[0];
        int row = colrow[1];

        // add all possible moves in indices value to a list

        // 2 squares up, 1 square right
        indicesMoves.add(new int[]{col + 1, row - 2});
        // 2 squares up, 1 square left
        indicesMoves.add(new int[]{col - 1, row - 2});

        // 2 squares down, 1 square right
        indicesMoves.add(new int[]{col + 1, row + 2});
        // 2 squares down, 1 square left
        indicesMoves.add(new int[]{col - 1, row + 2});

        // 2 squares right, 1 square up
        indicesMoves.add(new int[]{col + 2, row - 1});
        // 2 squares right, 1 square down
        indicesMoves.add(new int[]{col + 2, row + 1});

        // 2 squares left, 1 square up
        indicesMoves.add(new int[]{col - 2, row - 1});
        // 2 squares left, 1 square down
        indicesMoves.add(new int[]{col - 2, row + 1});

        // convert each indices pair to location and 
        // check if Knight can move to that location
        for (int[] move : indicesMoves) {
            if (indicesInBoard(move)) {
                String location = locationFromIndices(move);
                if (spaceVacant(b, location)) {
                    moves.add(location);
                } 
                if (!spaceVacant(b, location) && isOpponent(b, location)) {
                    moves.add(location);
                }
            }
        }

        return moves;
    }

}