import java.util.*;

/**
  * Implementation of a Chess board
  */
public class Board {

    private static Board instance = new Board();
    private List<BoardListener> bls = new ArrayList<BoardListener>();
    private Piece[][] pieces = new Piece[8][8];

    private Board() { }
    
    /* Create an singleton instance of Board */
    public static Board theBoard() {
        return instance;
    }

    /* Returns piece at given loc or null if no such piece exists */
    public Piece getPiece(String loc) {
	    int[] colrow = indicesFromLocation(loc);
      validateLocation(colrow);

      int col = colrow[0];
      int row = colrow[1];

      return pieces[col][row];
    }

    /* Add a piece to location, throw RuntimeException if location already 
     * has a piece 
     */
    public void addPiece(Piece p, String loc) {
        int[] colrow = indicesFromLocation(loc);
        validateLocation(colrow);

        int col = colrow[0];
        int row = colrow[1];

        if (pieces[col][row] != null) {
            throw new RuntimeException();
        }

        pieces[col][row] = p;
    }

    /* Move a piece from one location to another, throw an exception if move 
     * is invalid 
     */
    public void movePiece(String from, String to) {
        // Check for invalid moving locations
        int[] fromLocation = indicesFromLocation(from);
        int[] toLocation = indicesFromLocation(to);
        validateLocation(fromLocation);
        validateLocation(toLocation);

        // Get rows and cols indices of each location
        int fromCol = fromLocation[0];
        int fromRow = fromLocation[1];
        int toCol = toLocation[0];
        int toRow = toLocation[1];

        // Check that there is a piece at from
        if (pieces[fromCol][fromRow] == null) {
            throw new InvalidLocationException();
        }

        // Check that move is valid for piece
        Piece attacker = getPiece(from);
        List<String> moves = attacker.moves(this, from);
        if (moves.contains(to)) {            
            Logger logger = new Logger();

            // location from becomes vacant
            pieces[fromCol][fromRow] = null;     
            // location to is empty then add piece    
            // if not empty, capture opponent piece then add
            if (pieces[toCol][toRow] == null) {
                addPiece(attacker, to);
                // notify all listeners on move
                for (BoardListener b : bls) {
                    b.onMove(from, to, attacker);
                }
            } else { 
                Piece captured = pieces[toCol][toRow];
                pieces[toCol][toRow] = null;
                addPiece(attacker, to);
                // notify all listeners on capture
                for (BoardListener b : bls) {
                    b.onMove(from, to, attacker);
                    b.onCapture(attacker, captured);
                }
            }
        } else {
            throw new MoveInvalidException();
        }
    }

    /* Clear out the entire chess board */
    public void clear() {
        for (int c = 0; c < 8; c++) {
            for (int r = 0; r < 8; r++) {
                pieces[c][r] = null;
            }
        }
    }

    /* Add a listener that should be called at the appropriate times */
    public void registerListener(BoardListener bl) {
        bls.add(bl);
    }

    /* Removes a listener so it will subsequently not be notified of events */
    public void removeListener(BoardListener bl) {
        bls.remove(bl);
    }

    /* Removes all listeners */
    public void removeAllListeners() {
        bls.clear();
    }

    /* Visit every square of the board */
    public void iterate(BoardExternalIterator bi) {
	      for (int r = 0; r < 8; r++) {
            for (int c = 0; c < 8; c++) {
                String loc = locationFromIndices(new int[]{c,r});
                Piece p = getPiece(loc);
                bi.visit(loc, p);
            }
        }
    }

    /* Convert a location to pair of indicies on the board */
    private int[] indicesFromLocation(String loc) {
        int[] colrow = new int[2];

        int colIndex = loc.charAt(0) - 'a';
        int rowIndex = Integer.parseInt(String.valueOf(loc.charAt(1))) - 1;

        colrow[0] = colIndex;
        colrow[1] = rowIndex;

        return colrow;
    } 

    /* Convert a pair of indices into location string */
    private String locationFromIndices(int[] colrow) {
        int col = colrow[0];
        int rowIndex  = colrow[1] + 1;  
        char colIndex = (char) (col + 'a');

        String loc = colIndex + Integer.toString(rowIndex);
        return loc;
    }

    /* Validate string location provided, throw an exception if invalid */
    private void validateLocation(int[] location) {
        int colIndex = location[0];
        int rowIndex = location[1];

        if (colIndex < 0 || colIndex > 7) {
            throw new InvalidLocationException();
        }

        if (rowIndex < 0 || rowIndex > 7) {
            throw new InvalidLocationException();
        }
    }
}
