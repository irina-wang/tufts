import java.io.File;  
import java.io.FileNotFoundException;  
import java.util.Scanner; 

/**
  * Implementation of the Chess game. Read in a layout and moves file to 
  * populate the board and simulate chess moves.
  */
public class Chess {
    public static void main(String[] args) {
        Board b = Board.theBoard();

        if (args.length != 2) {
            System.out.println("Usage: java Chess layout moves");
        }
    
        Piece.registerPiece(new KingFactory());
        Piece.registerPiece(new QueenFactory());
        Piece.registerPiece(new KnightFactory());
        Piece.registerPiece(new BishopFactory());
        Piece.registerPiece(new RookFactory());
        Piece.registerPiece(new PawnFactory());
        b.registerListener(new Logger());

        createBoardLayout(b, args[0]);
        simulateBoardMoves(b, args[1]);

        // Leave the following code at the end of the simulation:
        System.out.println("Final board:");
        b.iterate(new BoardPrinter());
    }

    /* Read in layout file and populate board with chess pieces */
    private static void createBoardLayout(Board b, String layoutFile) {
        try {
            File layout = new File(layoutFile);
            Scanner reader = new Scanner(layout);
            while (reader.hasNextLine()) {
                String data = reader.nextLine();
                processLayoutLine(b, data);
            }
            reader.close();
        } catch (FileNotFoundException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }


    /* Read in moves file and simulate board with chess moves */
    private static void simulateBoardMoves(Board b, String movesFile) {
        try {
            File layout = new File(movesFile);
            Scanner reader = new Scanner(layout);
            while (reader.hasNextLine()) {
                String data = reader.nextLine();
                processMovesLine(b, data);
            }
            reader.close();
        } catch (FileNotFoundException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

    /* Given a line, parse and add a chess piece accordingly */
    private static void processLayoutLine(Board b, String line) {
        // Checks if first character of line is a # 
        if (line.charAt(0) == '#') {
            return;
        } 

        // Checks if line has at least 5 characters representing (xn=cp)
        if (line.length() < 5) {
            throw new IncorrectLayoutFormat();
        } 

        // extract characters from line
        char x = line.charAt(0);
        char n = line.charAt(1);
        char c = line.charAt(3);
        char p = line.charAt(4);

        // validate input within correct range
        validateColumnInput(x);
        validateRowInput(n);
        validateColorInput(c);
        validatePieceKindInput(p);

        String location = "" + x + n;
        String pieceKind = "" + c + p;

        Piece piece = Piece.createPiece(pieceKind);
        b.addPiece(piece, location);
        return;
    }

    /* Given a line, parse and move a chess piece accordingly */
    private static void processMovesLine(Board b, String line) {
        // Checks if first character of line is a comment
        if (line.charAt(0) == '#') {
            return;
        } 

        // Checks if line has at least 5 chars representing (xn=ym)
        if (line.length() < 5) {
            throw new IncorrectLayoutFormat();
        } 

        // extract characters from line
        char x = line.charAt(0);
        char n = line.charAt(1);
        char y = line.charAt(3);
        char m = line.charAt(4);

        // validate input within correct range
        validateColumnInput(x);
        validateRowInput(n);
        validateColumnInput(y);
        validateRowInput(m);

        // Combine chars into location strings
        String from = "" + x + n;
        String to = "" + y + m;

        b.movePiece(from, to);
        return;
    }

    /* Validate if col char is not from a to h, else throw an exception */
    private static void validateColumnInput(char x) {
        if (x < 'a' || x > 'h') {
            throw new IncorrectLayoutFormat();
        }
    }

    /* Validate if row char is not form 1 to 8, else throw an exception */
    private static void validateRowInput(char n) {
        if (n < '1' || n > '8') {
            throw new IncorrectLayoutFormat();
        }
    }

    /* Validate if color char is not b or w, else throw an exception */
    private static void validateColorInput(char c) {
        if (!(c == 'b' || c == 'w')) {
            throw new IncorrectLayoutFormat();
        }
    }

    /* Validate if color is of correct format, if not throw an exception. */
    private static void validatePieceKindInput(char p) {
        if (!(p == 'k' || p == 'q' || p == 'n' || p == 'b' ||
              p == 'r' || p == 'p')) {
           throw new IncorrectLayoutFormat();
        }
    }
}