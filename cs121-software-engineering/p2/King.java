import java.util.*;

public class King extends Piece {
    public King(Color c) { 
        this.color = c;
   }

    public String toString() {
        Color c = color();
        if (c.equals(Color.WHITE)) {
            return "wk";
        } else {
            return "bk";
        }
    }

    public List<String> moves(Board b, String loc) {
        List<String> moves = new ArrayList<String>();
        List<int[]> indicesMoves = new ArrayList<int[]>();
        
        // get current indices of King
	      int[] colrow = indicesFromLocation(loc);
        int col = colrow[0];
        int row = colrow[1];

        // add all possible moves in indices value to a list

        // Left-right 
        indicesMoves.add(new int[]{col + 1, row});
        indicesMoves.add(new int[]{col - 1, row});

        // Up-down
        indicesMoves.add(new int[]{col, row + 1});
        indicesMoves.add(new int[]{col, row - 1});

        // Diagonal up
        indicesMoves.add(new int[]{col + 1, row + 1});
        indicesMoves.add(new int[]{col - 1, row + 1});

        // Diagonal down
        indicesMoves.add(new int[]{col + 1, row - 1});
        indicesMoves.add(new int[]{col - 1, row - 1}); 

        // convert each indices pair to location and check if King can move
        // to that location
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