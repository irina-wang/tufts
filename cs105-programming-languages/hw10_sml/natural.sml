fun carryIntoNat (n,    0)                 = n
  | carryIntoNat (ZERO, 1)                 = times10plus (ZERO, 1)
  | carryIntoNat (TIMES10PLUS (m,d), 1)    = 
                times10plus (carryIntoNat (m, (d + 1) div 10) , (d + 1) mod 10) 
  | carryIntoNat _                         = raise Match 


fun addWithCarry (n1, ZERO, c)                           = 
                                                            carryIntoNat (n1, c)
  | addWithCarry (ZERO, n2, c)                           = 
                                                            carryIntoNat (n2, c)
  | addWithCarry (TIMES10PLUS (m1, d1),TIMES10PLUS (m2, d2), c)  =
                                  let val d  = (d1 + d2 + c) mod 10 
                                      val c' = (d1 + d2 + c) div 10 
                                  in times10plus (addWithCarry (m1, m2, c'), d)
                                  end



fun carryIntoNat (n,    0)                 = n
  | carryIntoNat (ZERO, 1)                 = times10plus (ZERO, 1)
  | carryIntoNat (TIMES10PLUS (m,d), 1)    = 
                times10plus (carryIntoNat (m, (d + 1) div 10) , (d + 1) mod 10) 
  | carryIntoNat _                         = raise Match 


fun timesWithCarry (n1, ZERO, c)                           = 
                                                            carryIntoNat (n1, c)
  | timesWithCarry (ZERO, n2, c)                           = 
                                                            carryIntoNat (n2, c)
  | timesWithCarry (TIMES10PLUS (m1, d1),TIMES10PLUS (m2, d2), c)  =
                                  let val d  = (d1 + d2 + c) mod 10 
                                      val c' = (d1 + d2 + c) div 10 
                                  in times10plus (addWithCarry (m1, m2, c'), d)
                                  end





fun borrowFromNat (n, 0)                 = n
  | borrowFromNat (ZERO, 1)              = raise Negative
  | borrowFromNat (TIMES10PLUS (m,0), 1) = times10plus (borrowFromNat (m, 1), 9)
  | borrowFromNat (TIMES10PLUS (m,d), 1) = times10plus (m, d - 1)
  | borrowFromNat _                      = raise Match

fun subWithBorrow (n1, ZERO, b)                =  borrowFromNat (n1, b)
  | subWithBorrow (TIMES10PLUS (m1, d1), 
                      TIMES10PLUS (m2, d2), b) =
                                let val d  = (d1 - d2 - b) mod 10
                                    val b' = if d1 - d2 - b < 0 then 1 else 0 
                                  in times10plus (subWithBorrow (m1, m2, b'), d)
                                  end
  | subWithBorrow _                           =  raise Negative


