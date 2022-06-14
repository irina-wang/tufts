import java.util.*;

/**
  * Implementation of Rook piece, including moves.
  */
public class Rook extends Piece {
    public Rook(Color c) { 
        this.color = c;
   }

    public String toString() {
        Color c = color();
        if (c.equals(Color.WHITE)) {
            return "wr";
        } else {
            return "br";
        }
    }

    /* Returns the possible moves of a Rook given a location */
    public List<String> moves(Board b, String loc) {
        List<String> moves = new ArrayList<String>();
        int max = 8; // board size
        
        // get current indices of the Rook
	      int[] colrow = indicesFromLocation(loc);
        int col = colrow[0];
        int row = colrow[1];

        // Get horizontal up
        for (int i = 1; i < max; i++) {
            int[] move  = new int[]{col, row - i};
            if (!addMoves(b, move, moves)) 
                break;  
        }

        // Get horizontal down
        for (int i = 1; i < max; i++) {
            int[] move  = new int[]{col, row + i};
            if (!addMoves(b, move, moves)) 
                break;     
        }

        // Get vertical left
        for (int i = 1; i < max; i++) {
            int[] move  = new int[]{col - i, row};
            if (!addMoves(b, move, moves)) 
                break;     
        }


        // Get vertical right
        for (int i = 1; i < max; i++) {
            int[] move  = new int[]{col + i, row};
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