(* Written by Mengqi Irina Wang(mwang17)
    Oct 21th, 2020 *)

val checkExpectInt        = Unit.checkExpectWith Unit.intString
val checkExpectIntList    = 
                        Unit.checkExpectWith (Unit.listString Unit.intString)
val checkExpectStringList = 
                        Unit.checkExpectWith (Unit.listString Unit.stringString)
val checkExpectISList     =
                        Unit.checkExpectWith (Unit.listString
                            (Unit.pairString Unit.intString Unit.stringString))
val checkExpectIntListList =
                        Unit.checkExpectWith (Unit.listString 
                                              (Unit.listString Unit.intString))
                                                              
(***** ------------ Problem A ------------ *****)

(* function mynull : 'a list -> bool *)
(*      tells whether the list is empty when applied to a list *)
fun mynull []      = true
  | mynull (x::xs) = false

    (* ; Unit Tests *)
        val () = Unit.checkAssert "mynull - true case: list is empty"
                (fn () => mynull []) 

        val () = Unit.checkAssert "nonempty list" 
                (fn () => not (mynull [1, 2, 3]))

(***** ------------  Problem B -------------- *****)

(* function reverse: 'a list->'a list *)
(*      reverse the list when applied to a list *)

fun reverse xs = foldl (op ::) [] xs

(* ; Unit Tests *)
    val () = 
        Unit.checkExpectWith (Unit.listString Unit.intString)
                                                    "reverse - list is empty"
        (fn () => reverse []) 
        (rev [])                                    (* [] *)

    val () = 
        Unit.checkExpectWith (Unit.listString Unit.intString)
                                                    "reverse - normal list"
        (fn () => reverse [1,2]) 
        (rev [1,2])                               (* [2,1] *)
      
    val () = 
        Unit.checkExpectWith (Unit.listString
                            (Unit.pairString Unit.intString Unit.stringString))
                                                    "reverse - mixed pair list"
        (fn () => reverse [(1, "a"), (3, "c")]) 
        (rev [(1, "a"), (3, "c")])                (* [(3, "c"), (1, "a")] *)

    val () = 
         Unit.checkExpectWith (Unit.listString 
                                              (Unit.listString Unit.intString))
                                                    "reverse - list of int list"
        (fn () => reverse [[3], [2]]) 
        (rev [[3], [2]])                          (* [[2], [3]] *) 

(***** minlist *****)

(* function minlist : int list -> int *)
    (* returns the smallest element of a nonempty list of integers *)
fun minlist (x::xs)  = foldl Int.min x xs
  | minlist []       = raise Match

(* ; Unit Tests *)
    val () = 
        Unit.checkExpectWith Int.toString  "minlist -  int list"
        (fn () => minlist [4, 10, 0]) 
        0

    val () = 
        Unit.checkExpectWith Int.toString  "minlist - one elem list"
        (fn () => minlist [7]) 
        7

    val checkExnInt = 
        Unit.checkExnWith Int.toString  "minlist - exception Match"
        (fn () => minlist [])

(***** zip *****)

(*  function zip: 'a list * 'b list -> ('a * 'b) list  *)
    (* Takes a pair of lists (of equal length)
     * Returns the equivalent list of pairs. 
            If the lengths don’t match, raise the exception Mismatch. *) 

exception Mismatch

fun zip ([]   ,    []) = []
  | zip (x::xs, y::ys) = (x, y) :: zip (xs, ys) 
  | zip _              = raise Mismatch

(* ; Unit Tests *)
    val () = 
        Unit.checkExpectWith (Unit.listString 
                          (Unit.pairString Unit.intString Unit.stringString)) 
                                                    "zip - empty case"
        (fn () => zip ([], [])) 
        []     

    val () = 
        Unit.checkExpectWith (Unit.listString 
                          (Unit.pairString Unit.intString Unit.stringString)) 
                                                    "zip - normal case"
        (fn () => zip ([1, 2], ["a", "b"])) 
        [(1, "a"), (2, "b")]                            

    val checkExnInt = 
        Unit.checkExpectWith (Unit.listString 
                          (Unit.pairString Unit.intString Unit.stringString)) 
                                                    "zip - exception Mismatch"
        (fn () => zip ([1, 2], []))
        
(***** ------------ Problem F  *****)
 
datatype sx
  = SYMBOL of string
  | NUMBER of int
  | BOOL   of bool
  | SXLIST of sx list

(* val numbersSx : int list -> sx *)
(*      > takes in an int list xs 
        > returns the SXList *)
fun numbersSx xs = SXLIST (foldr (fn (x,n) => (NUMBER x)::n) [] xs)

(* val flattenSyms : sx -> string list *)
(*      > returns a string list with just the symbols extracted from an 
            ordinary S-expression*)
fun flattenSyms (SYMBOL s)            = [s]
  | flattenSyms (NUMBER n)            = []
  | flattenSyms (BOOL   p)            = []
  | flattenSyms (SXLIST [])           = []
  | flattenSyms (SXLIST (x::xs))      = flattenSyms x 
                                            @ flattenSyms (SXLIST xs)

(* ; Unit Tests *)
    val () = Unit.checkExpectWith
                    (Unit.listString Unit.stringString)
                                                    "flattenSyms - symbol"
                    (fn () => flattenSyms (SYMBOL "s")) ["s"]

    val () = Unit.checkExpectWith
                    (Unit.listString Unit.stringString)
                                                    "flattenSyms - nonsymbol"
                    (fn () => flattenSyms (SXLIST [NUMBER 1, BOOL true])) []
 
    val () = Unit.checkExpectWith
                    (Unit.listString Unit.stringString)
                                                      "flattenSyms - number"
                    (fn () => flattenSyms (NUMBER 3)) []


    val () = Unit.checkExpectWith
                    (Unit.listString Unit.stringString)
                                                      "flattenSyms - bool"
                    (fn () => flattenSyms (BOOL true)) []

    val () = Unit.checkExpectWith
                    (Unit.listString Unit.stringString)
                                                    "flattenSyms - empty list"
                    (fn () => flattenSyms (SXLIST [])) []

    val () =Unit.checkExpectWith
                    (Unit.listString Unit.stringString)
                                                    "flattenSyms - mixed list"
                    (fn () => flattenSyms 
                        (SXLIST [NUMBER 105, SYMBOL "SO",SYMBOL "HARDD"]))
                    ["SO", "HARDD"]

    val () =Unit.checkExpectWith
                    (Unit.listString Unit.stringString)
                                                    "flattenSyms - nested list"
                    (fn () => flattenSyms 
                        (SXLIST [SXLIST [BOOL true, SYMBOL "COMP"],
                                 BOOL true,
                                 SYMBOL "IS",
                                 SXLIST [SYMBOL "KILLING", SYMBOL "ME"]]))
                    ["COMP","IS", "KILLING", "ME"] 

(***** ------------  Arithmetic by pattern matching on constructed data  *****)

datatype nat = ZERO
             | TIMES10PLUS of nat * int

(*  times10plus : (nat * int) -> nat *)
(*      smart constructor for data type nat*)
fun times10plus (ZERO, 0) = ZERO
  | times10plus (m, d)    = TIMES10PLUS (m, d)

(* times10 : nat -> nat *)
(*      > takes in a nat number n
        > returns the 10 times nat number n *)
fun times10 n   = times10plus (n, 0)

(* natOfDigit : int -> nat *)
(*      > takes in a int  
        > returns a nat digit *)
fun natOfDigit d = times10plus (ZERO, d)

(* flip : ('a * 'b -> 'c) -> 'b * 'a -> 'c *)
(*      applied same function on args in flipped order *) 
fun flip f (x, y) = f (y, x)

(* natOfDigits : int list -> nat *)
fun natOfDigits ds = foldl (flip times10plus) ZERO ds

(***** ------------  Problem H. Natural-number conversions ------------  *****)

(* val intOfNat : nat -> int *)
    (* converts a natural number into a machine integer, 
        or if the natural number is too large, raises Overflow. *)

fun intOfNat (ZERO)                = 0
  | intOfNat (TIMES10PLUS (m,d))   = d + intOfNat m * 10

    (* Unit tests *)
        val () =
            Unit.checkExpectWith Unit.intString "intOfNat" 
                (fn () => intOfNat (natOfDigits [1, 2, 3])) 
                123

        val () =
            Unit.checkExpectWith Unit.intString "intOfNat" 
                (fn () => intOfNat (natOfDigits [])) 
                0

(* val natOfInt : int -> nat *)
(*      converts a nonnegative machine integer into a natural number *)
fun natOfInt 0  = ZERO
  | natOfInt n  = times10plus (natOfInt (n div 10), n mod 10)

    (* Unit tests *)
        val () =
            Unit.checkExpectWith Unit.showNothing "natOfInt" 
                (fn () => natOfInt 2018) 
                (TIMES10PLUS(TIMES10PLUS(TIMES10PLUS
                                             (TIMES10PLUS(ZERO, 2), 0), 1), 8))

        val () =
            Unit.checkExpectWith Unit.showNothing "natOfInt" 
                (fn () => natOfInt 0) 
                ZERO                    

(* val natString : nat -> string *)
(*      converts a nat to a string with the most significant digit first *)
fun natString ZERO                     = Int.toString 0
  | natString (TIMES10PLUS (ZERO, d))  = Int.toString d 
  | natString (TIMES10PLUS (m   , d))  = natString m ^ Int.toString d 
 
  
(* Unit tests *)
    val () =
        Unit.checkExpectWith Unit.stringString "natString - normal case w 321"
        (fn () => natString (natOfDigits [3, 2, 1])) 
        "321"

    val () =
        Unit.checkExpectWith Unit.stringString  "natString - normal case w 2018"
        (fn () => natString (natOfDigits [2, 0, 1, 8])) 
        "2018"

    val () =
        Unit.checkExpectWith Unit.stringString  "natString - long case" 
        (fn () => natString (natOfDigits [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
                                          1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                          1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                          1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1])) 
        "111111111111111111111111111111111111111111111111"
(****** --------------- Natural-number arithmetic ----------------- ******)

(* carryIntoNat : nat * int -> nat *)
(*    > takes a natural number 𝑛 and a carry bit 𝑐, 
      > returns 𝑛 + 𝑐. 
        Note: A carry bit is a machine integer that is either 0 or 1.        *)
fun carryIntoNat (n,    0)                 = n
  | carryIntoNat (ZERO, 1)                 = times10plus (ZERO, 1)
  | carryIntoNat (TIMES10PLUS (m,d), 1)    = 
                times10plus (carryIntoNat (m, (d + 1) div 10) , (d + 1) mod 10) 
  | carryIntoNat _                         = raise Match 

(* Unit tests *)
    val () =
        Unit.checkExpectWith Unit.showNothing "carryIntoNat: nat carry 0" 
        (fn () => carryIntoNat (TIMES10PLUS (TIMES10PLUS (ZERO,3), 0), 0)) 
        (TIMES10PLUS (TIMES10PLUS (ZERO,3), 0))          (* 30 + 0  = 30 *)

    val () =
        Unit.checkExpectWith Unit.showNothing "carryIntoNat: ZERO carry 0" 
        (fn () => carryIntoNat (ZERO,0))                  (* 0 + 0  = 0 *)
        ZERO
 
    val () =
        Unit.checkExpectWith Unit.showNothing "carryIntoNat: nat carry 1" 
        (fn () => carryIntoNat (TIMES10PLUS (TIMES10PLUS (ZERO,3), 2), 1)) 
        (TIMES10PLUS (TIMES10PLUS (ZERO,3), 3))           (* 32 + 1  = 33 *)
 
    val () =
        Unit.checkExnWith Unit.showNothing 
                                "carryIntoNat: type error - bit not 1 or 0" 
        (fn () => carryIntoNat (TIMES10PLUS (TIMES10PLUS (ZERO,3), 2), 9)) 

(* addWithCarry : nat * nat * int -> nat  *)
(*    > takes two natural numbers n1 and n2, and a carry bit c 
      > returns n1 + n2 + c                                     ----------- *)
fun addWithCarry (n1, ZERO, c)                           = 
                                                            carryIntoNat (n1, c)
  | addWithCarry (ZERO, n2, c)                           = 
                                                            carryIntoNat (n2, c)
  | addWithCarry (TIMES10PLUS (m1, d1),TIMES10PLUS (m2, d2), c)  =
                                  let val d  = (d1 + d2 + c) mod 10 
                                      val c' = (d1 + d2 + c) div 10 
                                  in times10plus (addWithCarry (m1, m2, c'), d)
                                  end

(* Unit tests *)
    val () =
        Unit.checkExpectWith Unit.showNothing      "addWithCarry: n2 is ZERO" 
        (fn () => 
              addWithCarry (TIMES10PLUS (TIMES10PLUS (ZERO,3), 0), ZERO, 1)) 
        (TIMES10PLUS (TIMES10PLUS (ZERO,3), 1))         (* 30 + 0 + 1 = 31 *)

    val () =
        Unit.checkExpectWith Unit.showNothing       "addWithCarry: n1 is ZERO" 
        (fn () => 
              addWithCarry (ZERO, TIMES10PLUS (TIMES10PLUS (ZERO,5), 0), 0)) 
        (TIMES10PLUS (TIMES10PLUS (ZERO,5), 0))          (* 0 + 50 + 0 = 50 *)

    val () =
        Unit.checkExpectWith Unit.showNothing    "addWithCarry: n1 n2 non-ZERO" 
        (fn () => 
              addWithCarry (TIMES10PLUS (ZERO,7), TIMES10PLUS (ZERO,5), 1)) 
        (TIMES10PLUS (TIMES10PLUS (ZERO,1), 3))          (* 5 + 7 + 1 = 13 *)


(* addNats : nat * nat -> nat *)
(*    > takes two natural numbers n1 and n2, and a carry bit 𝑐, 
      > returns n1 + n2                                                      *)
fun addNats (n1, n2) = addWithCarry (n1, n2, 0)

(* Unit tests *)
    val () =
        Unit.checkExpectWith Unit.showNothing      "addNats: n1 is ZERO" 
        (fn () => addNats (ZERO, TIMES10PLUS (ZERO,5))) 
        (TIMES10PLUS (ZERO,5))                         (* 0 + 5 = 5 *)

    val () =
        Unit.checkExpectWith Unit.showNothing       "addNats: n2 is ZERO" 
        (fn () => addNats (TIMES10PLUS (ZERO,8), ZERO)) 
        (TIMES10PLUS (ZERO,8))                          (* 8 + 0 = 8 *)

    val () =
        Unit.checkExpectWith Unit.showNothing        "addNats: both non-ZERO" 
        (fn () => addNats (TIMES10PLUS (ZERO,8), TIMES10PLUS (ZERO,8))) 
        (TIMES10PLUS (TIMES10PLUS (ZERO,1), 6))          (* 8 + 8 = 16 *)
        

(* borrowFromNat : nat * int -> nat *)
(*    > takes a natural number n and a borrow bit b
      > returns n-b, provided that n-b is a natural number
    Note: If n-b is not a natural number, borrow From Nat raises the exception
        Negative. The borrow bit is a machine integer that is either 0 or 1 *)

exception Negative

fun borrowFromNat (n, 0)                 = n
  | borrowFromNat (ZERO, 1)              = raise Negative
  | borrowFromNat (TIMES10PLUS (m,0), 1) = times10plus (borrowFromNat (m, 1), 9)
  | borrowFromNat (TIMES10PLUS (m,d), 1) = times10plus (m, d - 1)
  | borrowFromNat _                      = raise Match

(* Unit tests *)
    val () =
        Unit.checkExpectWith Unit.showNothing   "borrowFromNat: b is 0" 
        (fn () => borrowFromNat (TIMES10PLUS (ZERO,5), 0))
        (TIMES10PLUS (ZERO,5))                         (* 5 - 0 = 5 *)

    val () =
        Unit.checkExpectWith Unit.showNothing   "borrowFromNat: d is 0, b is 1" 
        (fn () => borrowFromNat (TIMES10PLUS (TIMES10PLUS (ZERO,3), 0), 1))
        (TIMES10PLUS (TIMES10PLUS (ZERO,2), 9))       (* 30 - 1 = 29 *)   

    val () =
        Unit.checkExpectWith Unit.showNothing   "borrowFromNat: d not 0, b is 1"
        (fn () => borrowFromNat (TIMES10PLUS (TIMES10PLUS (ZERO,3), 3), 1))
        (TIMES10PLUS (TIMES10PLUS (ZERO,3), 2))       (* 33 - 1 = 32 *)   

    val () =
        Unit.checkExnWith Unit.showNothing   "borrowFromNat: exception Negative"
        (fn () => borrowFromNat (ZERO, 1))               (* 0 - 1 = -1 < 0 *)  

    val () =
        Unit.checkExnWith Unit.showNothing   "borrowFromNat: exception Match" 
        (fn () => borrowFromNat (TIMES10PLUS (ZERO,8), 3)) (* borrow 3 *)

(* subWithBorrow : nat * nat * int -> nat *)
(*    > takes two natural numbers n1 and n2,and a borrow bit b
      > returns n1 - n2 - b if it is a natural number, 
                        otherwise it raises the Negative exception.         *)

fun subWithBorrow (n1, ZERO, b)                =  borrowFromNat (n1, b)
  | subWithBorrow (TIMES10PLUS (m1, d1), 
                      TIMES10PLUS (m2, d2), b) =
                                let val d  = (d1 - d2 - b) mod 10
                                    val b' = if d1 - d2 - b < 0 then 1 else 0 
                                  in times10plus (subWithBorrow (m1, m2, b'), d)
                                  end
  | subWithBorrow _                           =  raise Negative

(* Unit tests *)
    val () =
        Unit.checkExpectWith Unit.showNothing   "subWithBorrow: n2 is 0" 
        (fn () => subWithBorrow (TIMES10PLUS (TIMES10PLUS (ZERO,3), 3), 
                                                                      ZERO, 1))
        (TIMES10PLUS (TIMES10PLUS (ZERO,3), 2))           (* 33 - 0 - 1= 32 *)

    val () =
        Unit.checkExpectWith Unit.showNothing   "subWithBorrow: n1 - n2 - b" 
        (fn () => subWithBorrow (TIMES10PLUS (TIMES10PLUS (ZERO,3), 0), 
                                 TIMES10PLUS (TIMES10PLUS (ZERO,2), 1), 1))
        (TIMES10PLUS (ZERO, 8))                            (* 30 - 21 - 1= 8 *)

    val () =
        Unit.checkExnWith Unit.showNothing   "subWithBorrow: exception Negative"
        (fn () => subWithBorrow (TIMES10PLUS (TIMES10PLUS (ZERO,2), 0), 
                                 TIMES10PLUS (TIMES10PLUS (ZERO,2), 0), 1))  
                                                     (* 20 - 20 - 1 = -1 < 0 *)

(* subNats : nat * nat -> nat *)
(*    > takes two natural numbers n1 and n2 
      > returns n1 - n2                                                      *)
fun subNats (n1, n2) = subWithBorrow (n1, n2, 0)

(* Unit tests *)
    val () =
        Unit.checkExnWith Unit.showNothing     "subNats: exception Negative" 
        (fn () => subNats (ZERO, TIMES10PLUS (ZERO,5))) 
                                                 (* 0 - 5  = -5 < 0 *)

    val () =
        Unit.checkExpectWith Unit.showNothing   "subNats: n1 - n2" 
        (fn () => subNats (TIMES10PLUS (TIMES10PLUS (ZERO,3), 0), 
                                 TIMES10PLUS (TIMES10PLUS (ZERO,2), 1)))
        (TIMES10PLUS (ZERO, 9))                   (* 30 - 21  = 9 *)

    val () =  (* subtracting too large a number raises Negative and not Match *)
        Unit.checkExnSatisfiesWith natString "1 - 5"
       (fn () => subNats (natOfDigits [1], natOfDigits [5])) 
       ("Negative", fn Negative => true | _ => false)

(* higher-order function unit test *)
fun opsAgree name intop natop n1 n2 = 
                Unit.checkExpectWith Int.toString name
                (fn () => intOfNat (natop (natOfInt n1, natOfInt n2))) 
                (intop (n1, n2) handle Overflow => 0)

    val () = opsAgree "123 + 2018" (op +) addNats 123 2018 
    val () = opsAgree "2018 - 123" (op -) subNats 2018 123 
    val () = opsAgree "100 - 1" (op -) subNats 100 1


val () = Unit.reportWhenFailures ()