import java.util.*;

/**
  * Implementation of Queen piece, including moves.
  */
public class Queen extends Piece {
    public Queen(Color c) { 
        this.color = c;
   }

    public String toString() {
        Color c = color();
        if (c.equals(Color.WHITE)) {
            return "wq";
        } else {
            return "bq";
        }
    }

    /* Returns the possible moves of a Queen given a location */
    public List<String> moves(Board b, String loc) {
        List<String> moves = new ArrayList<String>();

        // Create an instance of bishop and rook 
        registerPiece(new BishopFactory());
        registerPiece(new RookFactory());
        Bishop shadowBishop = new Bishop(color());
        Rook shadowRook = new Rook(color());

        // Queen's moves is the combination of Bishop's and Rook's
        List<String> bishopMoves = shadowBishop.moves(b, loc);
        List<String> rookMoves = shadowRook.moves(b, loc);

        // Add all Bishop's and Rook's possible moves 
        moves.addAll(bishopMoves);
        moves.addAll(rookMoves);

        return moves;
    }

}