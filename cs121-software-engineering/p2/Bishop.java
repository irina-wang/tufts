import java.util.*;

/**
  * Implementation of Bishop piece, including moves.
  */
public class Bishop extends Piece {
    public Bishop(Color c) { 
        this.color = c;
    }

    public String toString() {
        Color c = color();
        if (c.equals(Color.WHITE)) {
            return "wb";
        } else {
            return "bb";
        }
    }

    /* Returns the possible moves of a Bishop given a location */
    public List<String> moves(Board b, String loc) {
        List<String> moves = new ArrayList<String>();
        int max = 8; // board size
        
        // get current indices of Bishop
	      int[] colrow = indicesFromLocation(loc);
        int col = colrow[0];
        int row = colrow[1];

        // Get diagonal left up
        for (int i = 1; i < max; i++) {
            int[] move  = new int[]{col + i, row - i};
            if (!addMoves(b, move, moves)) 
                break;  
        }

        // Get diagonal right up
        for (int i = 1; i < max; i++) {
            int[] move  = new int[]{col - i, row - i};
            if (!addMoves(b, move, moves)) 
                break;     
        }

        // Get diagonal left down
        for (int i = 1; i < max; i++) {
            int[] move  = new int[]{col - i, row + i};
            if (!addMoves(b, move, moves)) 
                break;     
        }


        // Get diagonal right up
        for (int i = 1; i < max; i++) {
            int[] move  = new int[]{col + i, row + i};
            if (!addMoves(b, move, moves)) 
                break;        
        }


        return moves;
    }

    /* Returns true if a move can be added to list of possible moves */
    private Boolean addMoves(Board b, int[] move, List<String> moves) {
        // check if move is in board's boundary
        if (indicesInBoard(move)) {
            String mLoc = locationFromIndices(move);
            // check if move location is vacant 
            if (spaceVacant(b, mLoc)) {
                moves.add(mLoc);
                return true;
            } 
            // check if there exists an opponent at location
            if (!spaceVacant(b, mLoc) && isOpponent(b, mLoc)) {
                moves.add(mLoc);
                return false;
            }
            // check if space is occupied with home piece
            if (!spaceVacant(b, mLoc) && !isOpponent(b, mLoc)) {
                return false;
            }
        } 

        return false;
    }


}