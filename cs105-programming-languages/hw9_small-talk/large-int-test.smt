(use mixed.smt)

(check-print (LargeInteger fromSmall: 5555555) 5555555)
(check-print (LargeInteger fromSmall: 0) 0)
(check-print (LargeInteger fromSmall: -378) -378)

(check-print (LargeInteger fromSmall: 5555555) 5555555)


;;; + 
(check-print ((LargeInteger fromSmall: 55555) + 5555) 61110)
(check-print ((LargeInteger fromSmall: 55555) + -55556) -1)
(check-print ((LargeInteger fromSmall: 55555) + -50000) 5555)
(check-print ((LargeInteger fromSmall: 55555) + 
              (LargeInteger fromSmall: 5555)) 61110)
(check-print ((LargeInteger fromSmall: 55555) +
              (LargeInteger fromSmall: -55556)) -1)
(check-print ((LargeInteger fromSmall: 55555) +
              (LargeInteger fromSmall: -50000)) 5555)

(check-print ((LargeInteger fromSmall: -50000) - -1) -49999)
(check-print ((LargeInteger fromSmall: -50000) + 49999) -1)
(check-print ((LargeInteger fromSmall: -50000) + 50001) 1)
(check-print ((LargeInteger fromSmall: -55555) + 
              (LargeInteger fromSmall: -5555)) -61110)
(check-print ((LargeInteger fromSmall: -55555) +
              (LargeInteger fromSmall: 55556)) 1)
(check-print ((LargeInteger fromSmall: -55555) +
              (LargeInteger fromSmall: 50000)) -5555)

;;; -
(check-print ((LargeInteger fromSmall: 55555) - -5555) 61110)
(check-print ((LargeInteger fromSmall: 55555) - 55556) -1)
(check-print ((LargeInteger fromSmall: 55555) - 50000) 5555)
(check-print ((LargeInteger fromSmall: 55555) - 
              (LargeInteger fromSmall: -5555)) 61110)
(check-print ((LargeInteger fromSmall: 55555) -
              (LargeInteger fromSmall: 55556)) -1)
(check-print ((LargeInteger fromSmall: 55555) -
              (LargeInteger fromSmall: 50000)) 5555)

(check-print ((LargeInteger fromSmall: -50000) - -1) -49999)
(check-print ((LargeInteger fromSmall: -50000) - -49999) -1)
(check-print ((LargeInteger fromSmall: -50000) - 50001) -100001)
(check-print ((LargeInteger fromSmall: -55555) - 
              (LargeInteger fromSmall: 5555)) -61110)
(check-print ((LargeInteger fromSmall: -55555) -
              (LargeInteger fromSmall: -55556)) 1)
(check-print ((LargeInteger fromSmall: -55555) -
              (LargeInteger fromSmall: -50000)) -5555)

;;; *
(check-print ((LargeInteger fromSmall: 55555) * 5555) 308608025)
(check-print ((LargeInteger fromSmall: 55555) * 
              (LargeInteger fromSmall: 5555)) 308608025)
(check-print ((LargeInteger fromSmall: 55555) *
              (LargeInteger fromSmall: -50000)) -2777750000)
(check-print ((LargeInteger fromSmall: -55555) *
              (LargeInteger fromSmall: 50000)) -2777750000)
(check-print ((LargeInteger fromSmall: 55555) *
              (LargeInteger fromSmall: -50000)) -2777750000)
(check-print ((LargeInteger fromSmall:     0) *
              (LargeInteger fromSmall: 55555)) 0)

;;; smod:
(check-print ((LargeInteger fromSmall: 55555) smod: 5) 0)
(check-print ((LargeInteger fromSmall: 55556) smod: 5) 1)
(check-print ((LargeInteger fromSmall: 55556) smod: -5) -4)
(check-error ((LargeInteger fromSmall: 55556) smod: 0))
(check-print ((LargeInteger fromSmall: -55556) smod: 5) 4)



;;; <
(check-assert (((LargeInteger fromSmall: 44) < (LargeInteger fromSmall: 44)) not))
(check-assert ((LargeInteger fromSmall: -44) < (LargeInteger fromSmall: 44)))
(check-assert ((LargeInteger fromSmall: 45) > (LargeInteger fromSmall: -44)))
(check-assert ((LargeInteger fromSmall: -44) < (LargeInteger fromSmall: -43)))
;----------------------------------------------------------------------------

(class Power
  [subclass-of Object]
  (class-method x:to: (x n) [locals half]
    ((n = 0) ifTrue:ifFalse: 
      {(x coerce: 1)}
      {(set half (self x:to: x (n div: 2)))
       (set half (half * half))
       (((n mod: 2) = 1) ifTrue:
         {(set half (x * half))})
       half})))

(check-expect (Power x:to: 2 3) 8)
(check-expect (Power x:to: 3 4) 81)
(check-expect (Power x:to: (1 / 3) 3) (1 / 27))

(class Double
    [subclass-of Object]
    (class-method by: (n) [locals p]
        (set p n)       ; p == n
        (set p (p + p)) ; p == 2n
        p))

(check-print (Double by: (Power x:to: 2 63)) 18446744073709551616)
(check-expect ((Double by: (Power x:to: 2 63)) decimal)
              '( 1 8 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 6 1 6 ))

;----------------------------------------------------------------------------
