import java.util.*;

/**
  * Implementation/interface of a chess Piece.
  */
abstract public class Piece {
    private static HashMap<Character, PieceFactory> piecesInfo = new HashMap<>();
    public Color color;

    /* Register a piece kind with a piece factory */
    public static void registerPiece(PieceFactory pf) {
        piecesInfo.put(pf.symbol(), pf);
    }

    /* Return a newly created piece given the name */
    public static Piece createPiece(String name) {
        // Get the color and symbol from piece name
        char color  = name.charAt(0);
        char symbol = name.charAt(1);
        PieceFactory pf = piecesInfo.get(symbol);
        Piece p;

        if (color == 'b') {
            p = pf.create(Color.BLACK);
        } else if (color == 'w') {
            p = pf.create(Color.WHITE);
        } else {
            throw new IncorrectLayoutFormat();
        }

        return p;
    }

    public Color color() {
	    return color;
    }

    abstract public String toString();

    /* Get possible moves of a piece given a location */
    abstract public List<String> moves(Board b, String loc);

    /* Convert a location to pair of indicies on the board */
    public int[] indicesFromLocation(String loc) {
        int[] colrow = new int[2];

        int colIndex = loc.charAt(0) - 'a';
        int rowIndex = Integer.parseInt(String.valueOf(loc.charAt(1))) - 1;

        colrow[0] = colIndex;
        colrow[1] = rowIndex;

        return colrow;
    } 

    /* Convert a pair of indices on the board to location string */
    public String locationFromIndices(int[] colrow) {
        int col = colrow[0];
        int rowIndex  = colrow[1] + 1;  
        char colIndex = (char) (col + 'a');

        String loc = colIndex + Integer.toString(rowIndex);
        return loc;
    }

    /* Check if location is empty on the board */
    public Boolean spaceVacant(Board b, String loc) {
        return (b.getPiece(loc) == null);
    }

    /* Check if piece at current location is an opponent */
    public Boolean isOpponent(Board b, String loc) {
        Piece p = b.getPiece(loc);
        return !color().equals(p.color());
    }

    /* Check if given indices are within bounds of chess board */
    public Boolean indicesInBoard(int[] indices) {
        int colIndex = indices[0];
        int rowIndex = indices[1];

        if (colIndex < 0 || colIndex > 7) {
            return false;
        }

        if (rowIndex < 0 || rowIndex > 7) {
            return false;
        }

        return true;
    }
}