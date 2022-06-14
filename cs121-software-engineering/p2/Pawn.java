import java.util.*;

/**
  * Implementation of Pawn piece, including moves.
  */
public class Pawn extends Piece {
    public Pawn(Color c) { 
        this.color = c;
   }

    public String toString() {
        Color c = color();
        if (c.equals(Color.WHITE)) {
            return "wp";
        } else {
            return "bp";
        }
    }

    /* Returns the possible moves of a Pawn given a location */
    public List<String> moves(Board b, String loc) {
	    	List<String> moves = new ArrayList<String>();

        // get current indices of Pawn
	      int[] colrow = indicesFromLocation(loc);
        int col = colrow[0];
        int row = colrow[1];

        // Get pawn's vertical moves
        firstMoves(b, moves, col, row);
        // Get pawn's capture (diagonal) moves
        captureMoves(b, moves, col, row);

        return moves;
    }

    /* Return possible moves of Pawn going forward */
    private void firstMoves(Board b, List<String> moves, int col, int row) {
        List<int[]> validMoves = new ArrayList<int[]>();

        // First move: possibly 1 or 2 moves forward for White pawn
        if (color() == Color.WHITE) {
            int[] oneSquare = new int[]{col, row + 1};
            int[] twoSquares = new int[]{col, row + 2};

            // Add 1 square away if empty 
            if (indicesInBoard(oneSquare)) {
                String firstLoc = locationFromIndices(oneSquare);
                if (spaceVacant(b, firstLoc)) {
                    moves.add(firstLoc);
                    // If one square away is empty then can proceed
                    // Add 2 squares away if row 2 and empty
                    String secondLoc = locationFromIndices(twoSquares);
                    if (row == 1 && indicesInBoard(twoSquares)) {
                        if (spaceVacant(b, secondLoc)) {
                            moves.add(secondLoc);
                        }
                    }
                }
            }
        }

        // First move: possibly 1 or 2 moves forward for White pawn
        if (color() == Color.BLACK) {
            int[] oneSquare = new int[]{col, row - 1};
            int[] twoSquares = new int[]{col, row - 2};

            // Add 1 square away if empty 
            if (indicesInBoard(oneSquare)) {
                String firstLoc = locationFromIndices(oneSquare);
                if (spaceVacant(b, firstLoc)) {
                    moves.add(firstLoc);
                    // If one square away is empty then can proceed
                    // Add 2 squares away if row 2 and empty
                    String secondLoc = locationFromIndices(twoSquares);
                    if (row == 6 && indicesInBoard(twoSquares)) {
                        if (spaceVacant(b, secondLoc)) {
                            moves.add(secondLoc);
                        }
                    }
                }
            }
        }
    }

    /* Return possible moves of Pawn capturing an opponent (diagonal) */
    private void captureMoves(Board b, List<String> moves, int col, int row) {
        List<int[]> captureMoves = new ArrayList<int[]>();

        // Capture moves calculation
        if (color() == Color.WHITE) {
            captureMoves.add(new int[]{col + 1, row + 1});
            captureMoves.add(new int[]{col - 1, row + 1});
        }

        if (color() == Color.BLACK) {
            captureMoves.add(new int[]{col + 1, row - 1});
            captureMoves.add(new int[]{col - 1, row - 1});
        }

        // convert each indices pair to location and check if Pawn can move
        // to that location
        for (int[] move : captureMoves) {
            if (indicesInBoard(move)) {
                String location = locationFromIndices(move);
                if (!spaceVacant(b, location) && isOpponent(b, location)) {
                    moves.add(location);
                }
            }
        }
    }
}