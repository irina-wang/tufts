; bigtests.smt

;;;; TESTS for Naturals
; Summary: times on very large numbers
;          (potential overflow detection, internal array with size > 0)
(check-print ((Natural fromSmall: 65535) * (Natural fromSmall: 65535)) 4294836225)

; Summary: a mix of +, -, *, and sdiv with random numbers
(val zero (Natural fromSmall: 0))
(val rand_nat (Natural fromSmall: 635038))
(val rand_nat2 (Natural fromSmall: 7059871))
(check-print (((zero * rand_num) + (rand_num * rand_num)) - rand_num2)
            403266201573)

; Summary: some comparisons with random numbers
(check-print ((((rand_num < rand_num2) & (rand_num = rand_num)) 
             & (rand_num > zero)) ifTrue:ifFalse:
            {(Natural fromSmall: 1)} {(Natural fromSmall: 0)}) 1)


;;;; TESTS for large Integers
; Summary: +, - and * for random large integers, both positive and negative
(val rand_neg_int (LargeInteger fromSmall: -7059871))
(val rand_pos_int (LargeInteger fromSmall: 635038))
(check-print ((((rand_neg_int - rand_neg_int) * rand_pos_int) - rand_pos_int) + 
             ((rand_neg_int * rand_neg_int) + (rand_neg_int * rand_pos_int))) 
             45358491541505)

; Summary: mod with positive and negative divisor
(check-print ((rand_pos_int smod: 8943) + (rand_neg_int smod: 6350)) 
             1414)

; Summary: comparison
(check-print 
    (((LargeInteger fromSmall: 45) > (LargeInteger fromSmall: -44))
    ifTrue:ifFalse: {(Natural fromSmall: 1)} {(Natural fromSmall: 0)}) 1)


;;;; TESTS for mixed Integers
; Summary: auto rollover to large integer
(check-print (635038 * (635038 * 635038)) 256093845400874872)

; Summary: message sent to a smallint
(check-print (-50001 - (LargeInteger fromSmall: 50000)) -100001)

; Summary: +, - and * for random integers, both positive and negative
(check-print ((((rand_neg_int - -7059871) * rand_pos_int) - 635038) + 
             ((-7059871 * rand_neg_int) + (rand_neg_int * 635038))) 
             45358491541505)


