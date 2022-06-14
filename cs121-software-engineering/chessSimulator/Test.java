import java.util.*;

public class Test {

    public static <T> boolean listEquals(List<T> list1, List<T> list2) {
        return new HashSet<>(list1).equals(new HashSet<>(list2));
    }

    public static void testAddGetPiece() {
        Board b = Board.theBoard();
        Piece.registerPiece(new BishopFactory());
        Piece p1 = Piece.createPiece("bb");
        b.addPiece(p1, "a3");
        assert b.getPiece("a3") == p1;

        Piece p2 = Piece.createPiece("wb");
        b.addPiece(p2, "a2");
        assert b.getPiece("a2") == p2;  

        assert b.getPiece("a1") == null;
        b.clear();

    }

    public static void bishopTest(){      
        Board b = Board.theBoard();
        Piece.registerPiece(new BishopFactory());
        Piece bish = Piece.createPiece("bb");
        b.addPiece(bish, "f6");
        // ensures creation works
        assert bish.color() == Color.BLACK;		
        assert bish.toString().equals("bb");

        List<String> bishMoves = bish.moves(b, "f6");

        List<String> moveTestList1 = Arrays.asList
                                      ("a1", "b2", "c3", "d4", "e5", 
                                      "g7", "h8", "d8", "e7", "g5", "h4");

        assert b.getPiece("f6") == bish;

        assert listEquals(bishMoves, moveTestList1);

        Piece bish2 = Piece.createPiece("bb");
        b.addPiece(bish2, "d4");

        List<String> moveTestList2 = Arrays.asList
                                    ("e5", "g7", "h8", "d8", "e7", "g5", "h4");

        bishMoves = bish.moves(b, "f6");
        // moves works w/ same color piece obstruction
        assert listEquals(bishMoves, moveTestList2);	

        Piece bish3 = Piece.createPiece("wb");
        b.addPiece(bish3, "e7");

        List<String> moveTestList3 = Arrays.asList
                                      ("e5", "g7", "h8",  "e7", "g5", "h4");

        bishMoves = bish.moves(b, "f6");
        // moves works w/ capture
        assert  listEquals(bishMoves, moveTestList3); 
        b.clear();

    }

    public static void rookMovesTest() {
        Board board = Board.theBoard();
        Piece.registerPiece(new RookFactory());
        Piece rook = Piece.createPiece("br");

        // middle
        assert rook.moves(board, "d5").containsAll(
            new ArrayList<>(Arrays.asList( 
            new String[] {"a5", "b5", "c5", "d1", "d2", "d3", "d4", 
                          "d6", "d7", "d8", "e5", "f5", "g5", "h5"})));

        // corner
        assert rook.moves(board, "h8").containsAll(
            new ArrayList<>(Arrays.asList(  
            new String[] {"h1", "h2", "h3", "h4", "h5", "h6", "h7", 
                          "a8", "b8", "c8", "d8", "e8", "f8", "g8"})));

        // wall
        assert rook.moves(board, "a3").containsAll(
            new ArrayList<>(Arrays.asList(  
            new String[] {"a1", "a2", "a4", "a5", "a6", "a7", "a8",
                          "b3", "c3", "d3", "e3", "f3", "g3", "h3"})));

        // on a nonempty board
        Piece.registerPiece(new BishopFactory());
        Piece bb = Piece.createPiece("bb");
        Piece wb = Piece.createPiece("wb");
        board.addPiece(bb, "a4");
        board.addPiece(wb, "c8");

        assert rook.moves(board, "a8").containsAll(
            new ArrayList<>(Arrays.asList(  
            new String[] {"a5", "a6", "a7", "b8", "c8"})));

        board.clear();
    }

    // Test move lists for queen
    public static void queenTest() {
        Board b = Board.theBoard();
        Piece.registerPiece(new KnightFactory());
        Piece.registerPiece(new QueenFactory());
        Piece blackQueen = Piece.createPiece("bq");
        Piece whiteKnight = Piece.createPiece("wn");
        Piece blackKnight = Piece.createPiece("bn");

        b.addPiece(blackQueen, "d5");

        b.addPiece(whiteKnight, "b7");
              b.addPiece(whiteKnight, "f7");
              b.addPiece(whiteKnight, "b3");
              b.addPiece(whiteKnight, "f3");

        b.addPiece(blackKnight, "d7");
              b.addPiece(blackKnight, "d3");
              b.addPiece(blackKnight, "b5");
              b.addPiece(blackKnight, "f5");

        assert blackQueen.moves(b, "d5").containsAll(
              new ArrayList<>(Arrays.asList(
              new String[] {"c4", "c5", "c6", "d4", "d6", "e4", "e5",
                            "e6", "b7", "f7", "b3", "f3"})));

        b.clear();
    }
    
    public static void knightPieceTest() {
        Board b = Board.theBoard();
        Piece.registerPiece(new KnightFactory());
        Piece bn = Piece.createPiece("bn");
        Piece wn = Piece.createPiece("wn");

        assert bn.toString().equals("bn");
                assert wn.toString().equals("wn");

        b.addPiece(bn, "g1");
                List<String> possMoves = bn.moves(b, "g1");
                assert possMoves.size() == 3;
                assert possMoves.contains("e2");
                assert possMoves.contains("f3");
                assert possMoves.contains("h3");

        b.addPiece(bn, "f3");
                possMoves = bn.moves(b, "g1");
                assert possMoves.size() == 2;
                assert possMoves.contains("e2");
                assert possMoves.contains("h3");

        b.addPiece(wn, "e2");
                possMoves = bn.moves(b, "g1");
                assert possMoves.size() == 2;
                assert possMoves.contains("e2");
                assert possMoves.contains("h3");

        b.clear();
    }

    public static void testPawn() {
        Board b = Board.theBoard();
        Piece.registerPiece(new PawnFactory());
        Piece.registerPiece(new RookFactory());
        Piece.registerPiece(new KnightFactory());
        Piece bp = Piece.createPiece("bp");
        Piece wp = Piece.createPiece("wp");
        Piece wr = Piece.createPiece("wr");
        Piece wn = Piece.createPiece("wn");
        Piece wp2 = Piece.createPiece("wp");
        b.addPiece(bp, "b7");
        b.addPiece(wp, "g2");
        b.addPiece(wr, "a6");
        b.addPiece(wn, "c6");
        b.addPiece(wp2, "b5");
        
        List<String> moves = bp.moves(b, "b7");
        List<String> expected = Arrays.asList("c6", "b6", "a6");

        assert listEquals(moves, expected);

        moves = wp.moves(b, "g2");
        expected = Arrays.asList("g3", "g4");
        assert listEquals(moves, expected);
        b.clear();
    }

    public static void testRook() {       
        Board b = Board.theBoard();
        Piece.registerPiece(new RookFactory());
        Piece.registerPiece(new BishopFactory());
        Piece.registerPiece(new PawnFactory());

        Piece br = Piece.createPiece("br");
        Piece wr = Piece.createPiece("wr"); 
        Piece bp = Piece.createPiece("bp");
        Piece wb = Piece.createPiece("wb");

        b.addPiece(br, "d5");
        b.addPiece(wr, "f7");

        assert br.moves(b, "d3").containsAll(
              new ArrayList<>(Arrays.asList(
              new String[] {"a3", "b3", "c3", "e3", "f3", "g3", "h3",
                            "d4", "d1", "d2"})));

        assert br.moves(b, "h7").containsAll(
              new ArrayList<>(Arrays.asList(
              new String[] {"h1", "h2", "h3", "h4", "h5", "h6", "h8",
                            "g7", "f7"})));     

        b.addPiece(bp, "a5");
        b.addPiece(wb, "c4");

        assert br.moves(b, "c5").containsAll(
              new ArrayList<>(Arrays.asList(
              new String[] {"b5", "c4", "c6", "c7", "c8"})));
        
        b.clear();
    }

    // Tests that:
    // (1) the knight cannot move outside the board
    // (2) the knight cannot capture a piece of its own color
    // (3) the knight can capture a piece of opposing color
    // (4) the moves method does not check whether the piece is actually present
    //     at suggested location
    public static void testKnight() {
        Board b = Board.theBoard();
        Piece.registerPiece(new KnightFactory());

        Piece wn = Piece.createPiece("wn");
        b.addPiece(wn, "c2");
        Piece bn = Piece.createPiece("bn");
        b.addPiece(bn, "b3");

        List<String> moves = wn.moves(b, "a1");
        assert moves.size() == 1;
        assert moves.contains("b3");
        b.clear();
    }

    // Tests that a piece can properly detect it cannot move off the board
    // to the location of another piece.
    public static void testKnightKing() {
    	Board b = Board.theBoard();
        Piece.registerPiece(new KingFactory());
    	Piece.registerPiece(new KnightFactory());
    	Piece king = Piece.createPiece("wk");
        Piece knight = Piece.createPiece("wn");
    	b.addPiece(king, "a1");
        b.addPiece(knight, "c3");
        List<String> king_moves = king.moves(b, "a1");
        assert king_moves.size() == 3;
        king_moves = king.moves(b, "b2");
        assert king_moves.size() == 6;
        assert !king_moves.contains("c3");
        assert !king_moves.contains("a1");
    }

    public static void testKingMoves() {
      Board b = Board.theBoard();

      Piece.registerPiece(new KingFactory());
      Piece.registerPiece(new BishopFactory());
      Piece.registerPiece(new KnightFactory());

      Piece bk = Piece.createPiece("bk");
      Piece wb = Piece.createPiece("wb");
      Piece wn1 = Piece.createPiece("wn");
      Piece wn2 = Piece.createPiece("wn");

      b.addPiece(bk, "h8");
      b.addPiece(wb, "h7");
      b.addPiece(wn1, "b3");
      b.addPiece(wn2, "d1");

      List<String> actualMoves = bk.moves(b, "h8");
      List<String> expectedMoves = new ArrayList<>(Arrays.asList
                                                  ("g8", "g7", "h7"));
      assert listEquals(actualMoves,expectedMoves);

      b.clear();
	  }

    public static void testBlackPawnMoves() {
        Board b = Board.theBoard();
        b.clear();
        Piece.registerPiece(new PawnFactory());
        Piece bp = Piece.createPiece("bp");
        List<String> moves; // Legal locations that this piece could move to.

        // At the opponent's base row.
        moves = bp.moves(b, "a1");
        assert moves.size() == 0;

        // Out of home row and vacant in the front.
        b.clear();
        moves = bp.moves(b, "a6");
        assert moves.size() == 1;
        assert moves.contains("a5");

        // Out of home row and a piece in the front.
        b.clear();
        b.addPiece(Piece.createPiece("wp"), "a5");
        moves = bp.moves(b, "a6");
        assert moves.size() == 0;

        // At home row and vacant in the front.
        b.clear();
        moves = bp.moves(b, "a7");
        assert moves.size() == 2;
        assert moves.contains("a6");
        assert moves.contains("a5");

        // At home row and a piece in the front.
        b.clear();
        b.addPiece(Piece.createPiece("wp"), "a6");
        moves = bp.moves(b, "a7");
        assert moves.size() == 0;

        // At home row and a piece 2 squares away in the front.
        b.clear();
        b.addPiece(Piece.createPiece("wp"), "a5");
        moves = bp.moves(b, "a7");
        assert moves.size() == 1;
        assert moves.contains("a6");

        // Capture opponent's piece by moving one square diagonally toward the
        // opponent.
        b.clear();
        b.addPiece(Piece.createPiece("wp"), "a5");
        b.addPiece(Piece.createPiece("wp"), "b5");
        b.addPiece(Piece.createPiece("wp"), "c5");
        b.addPiece(Piece.createPiece("wp"), "a6");
        b.addPiece(Piece.createPiece("wp"), "c6");
        b.addPiece(Piece.createPiece("wp"), "a7");
        b.addPiece(Piece.createPiece("wp"), "b7");
        b.addPiece(Piece.createPiece("wp"), "c7");
        moves = bp.moves(b, "b6");
        assert moves.size() == 2;
        assert moves.contains("a5");
        assert moves.contains("c5");

        // Cannot capture allies.
        b.clear();
        b.addPiece(Piece.createPiece("bp"), "a5");
        b.addPiece(Piece.createPiece("bp"), "b5");
        b.addPiece(Piece.createPiece("bp"), "c5");
        moves = bp.moves(b, "b6");
        assert moves.size() == 0;

        b.clear();
    }

    public static void test2() {
        Board b = Board.theBoard();
        Piece.registerPiece(new PawnFactory());
        Piece white_pawn = Piece.createPiece("wp");
        b.addPiece(white_pawn, "e2");
        assert b.getPiece("e2") == white_pawn;

        List<String> moves = white_pawn.moves(b, "e2");
          assert moves.size() == 2;
          assert moves.contains("e3");
          assert moves.contains("e4");

        b.addPiece(Piece.createPiece("bp"), "f3");
        moves = white_pawn.moves(b, "e2");
          assert moves.size() == 3;
          assert moves.contains("e3");
          assert moves.contains("e4");
          assert moves.contains("f3");

        b.addPiece(Piece.createPiece("wp"), "d3");
        moves = white_pawn.moves(b, "e2");
          assert moves.size() == 3;
          assert moves.contains("e3");
          assert moves.contains("e4");
          assert moves.contains("f3");

        assert !moves.contains("d3");

        b.addPiece(Piece.createPiece("wp"), "e3");
        moves = white_pawn.moves(b, "e2");
          assert moves.size() == 1;
          assert !moves.contains("e3");
          assert !moves.contains("e4");
          assert moves.contains("f3");

        assert !moves.contains("d3");
          b.clear();
    }

    public static void test_knight() {
        // normal move
        Board b = Board.theBoard();
        Piece.registerPiece(new KnightFactory());
        Piece bn = Piece.createPiece("bn");
        b.addPiece(bn, "b7");
        List<String> moves = bn.moves(b, "d5");
        assert moves.size() == 8;

        Piece.registerPiece(new KnightFactory());
        Piece bn_a8 = Piece.createPiece("bn");
        b.addPiece(bn_a8, "a8");
        List<String> moves_a8 = bn_a8.moves(b, "a8");
        assert moves_a8.size() == 2;

        Piece block = Piece.createPiece("wn");
        b.addPiece(block, "d6");
        List<String> moves_again = bn.moves(b, "d5");
        assert moves_again.size() == 8;

        b.clear();
    }

    public static void queenPieceTest() {
        Board b = Board.theBoard();
        Piece.registerPiece(new QueenFactory());
        Piece.registerPiece(new KnightFactory());

        Piece wq = Piece.createPiece("wq");

        assert(wq.toString()).equals("wq");
        b.addPiece(wq, "e2");
        List<String> possibleMoves = wq.moves(b, "e2");
        // left to right diagnol: "d1, f3, g4, h5"
        // right to left diagnol: "f1, d3, c4, b5, a6"
        // up and down: "e1, e3, e4, e5, e6, e7, e8"
        // "left and right: f2, g2, h2, d2, c2, b2, a2"
        Set<String> expMoves = 
        new HashSet<>(Arrays.asList("d1","f3", "g4", "h5", 
                                    "f1", "d3", "c4", "b5", "a6",
                                    "e1", "e3", "e4", "e5", "e6", 
                                    "e7", "e8", "f2", "g2", "h2", 
                                    "d2", "c2", "b2", "a2"));

        // checks to see if queen moves expectedly without any blockage 
        assert(expMoves.equals(new HashSet<>(possibleMoves)));

        Piece wn = Piece.createPiece("wn");
        b.addPiece(wn, "f3");
        possibleMoves = wq.moves(b, "e2");
        expMoves = new HashSet<>(Arrays.asList("d1", "f1", "d3", "c4", 
                                               "b5", "a6", "e1", "e3", 
                                               "e4", "e5", "e6", "e7", 
                                               "e8", "f2", "g2", "h2", 
                                               "d2", "c2", "b2", "a2"));

      b.clear();
    }

    public static void testKing() {
        Board b = Board.theBoard();
        Piece.registerPiece(new KingFactory());
        Piece bk = Piece.createPiece("bk");
        b.addPiece(bk, "d7");
        // test singleton
        Board c = Board.theBoard();
        Piece q = c.getPiece("d7");
        assert q.toString().equals("bk");
        List<String> moves = q.moves(b, "d7");
        assert moves.size() == 8;
        b.movePiece("d7", "e6");
        assert b.getPiece("e6") == bk;
        assert bk.moves(c, "e6").contains("e5");
        assert bk.moves(c, "e6").contains("e7");
        assert bk.moves(c, "e6").contains("d6");
        assert bk.moves(c, "e6").contains("d5");
        assert bk.moves(c, "e6").contains("d7");
        assert bk.moves(c, "e6").contains("f6");
        assert bk.moves(c, "e6").contains("f5");
        assert bk.moves(c, "e6").contains("f7");
        assert !bk.moves(c, "e6").contains("a1");
        b.clear();
        Board d = Board.theBoard();
        Piece.registerPiece(new KingFactory());
        Piece wk = Piece.createPiece("wk");
        d.addPiece(wk, "d7");
        c.movePiece("d7", "d8");
        assert wk.moves(b, "d8").size() == 5;

        b.clear();
    }

    public static void smotheredMate() {
        //Test which is a common checkmate pattern (without the checkmate)
        Board b = Board.theBoard();
        Piece.registerPiece(new RookFactory());
        Piece.registerPiece(new PawnFactory());
        Piece.registerPiece(new KingFactory());
        Piece.registerPiece(new RookFactory());
        Piece.registerPiece(new QueenFactory());

        Piece bp1 = Piece.createPiece("bp");
        Piece bp2 = Piece.createPiece("bp");
        Piece br1 = Piece.createPiece("br");
        Piece bk = Piece.createPiece("bk");
        Piece wn1 = Piece.createPiece("wn");
        Piece wk = Piece.createPiece("wk");
        Piece wq = Piece.createPiece("wq");

        //Queen threatens to capture king, rook takes queen, knight mates
        b.addPiece(bk, "h8");
        b.addPiece(bp1, "h7");
        b.addPiece(bp2, "g7");
        b.addPiece(br1, "a8");
        b.addPiece(wk, "c2");
        b.addPiece(wq, "b3");
        b.addPiece(wn1, "e5");

        b.movePiece("b3", "g8");
        b.movePiece("a8", "g8");
        b.movePiece("e5", "f7");

        //King should have no legal moves
        List<String> moves = bk.moves(b, "h8");
        assert moves.size() == 0;

        b.clear();
    }

    public static void testMoveRook() { // test move Rook
        Board b = Board.theBoard();
        Piece.registerPiece(new PawnFactory());
        Piece.registerPiece(new RookFactory());
        Piece.registerPiece(new BishopFactory());

        Piece bp = Piece.createPiece("bp");
        Piece wr = Piece.createPiece("wr");
        Piece wp = Piece.createPiece("wp");
        Piece wb = Piece.createPiece("wb");

        b.addPiece(bp, "b7");
        b.addPiece(wr, "a1");
        b.addPiece(wp, "c2");
        b.addPiece(wb, "c1");

        List<String> moves = wr.moves(b, "a1");
        List<String> expected = Arrays.asList("a2", "a3", "a4", "a5", "a6", "a7", "a8", "b1");
        assert listEquals(moves, expected);

        b.clear();
    }
    
    public static void main(String[] args) {
	    testAddGetPiece();
      bishopTest();
      rookMovesTest();
      queenTest();
      knightPieceTest();
      testPawn();
      testRook();
      testKnight();
      testKnightKing();
      testKingMoves();
      testBlackPawnMoves();
      test2();
      test_knight();
      queenPieceTest();
      testKing();
      smotheredMate();
      testMoveRook();
    }

}
