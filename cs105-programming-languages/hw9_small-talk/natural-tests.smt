(use big-num.smt)

(val a (Natural fromSmall: 40000))
(val c (Natural fromSmall:  20000))
(val zero (Natural fromSmall: 0))
(val a2 (Natural fromSmall: 40000))

; (check-error (Natural fromSmall: -1))

; isZero
(check-assert (zero isZero))
(check-assert ((c isZero) not))

; =
(check-assert ((a = zero) not))
(check-assert ((zero = a) not))
(check-assert (zero = zero))
(check-assert (a = a))
(check-assert (a = a2))

; other comparison
(check-assert (a > zero))
(check-assert (zero < a))
(check-assert (a > c))

; +
(check-expect (a + zero) a)
(check-expect (zero + a) a)
(check-expect (a + c) (Natural fromSmall: 60000))
(check-print (a + c) 60000)

; -
(check-error (zero - c))
(check-expect (a - c) (Natural fromSmall: 20000))
(check-expect (a - zero) a)

; times
(check-print (a * a) 1600000000)
(check-print (a * c) 800000000)
(check-expect (a * zero) zero)
(check-expect (zero * a) zero)
(check-expect (zero * zero) zero)
(check-print ((Natural fromSmall: 65535) * (Natural fromSmall: 65535)) 4294836225)

; short division
(check-expect (a sdiv: 5) (Natural fromSmall: 8000))
(check-expect (a smod: 5) 0)
(check-expect (a sdiv: 6) (Natural fromSmall: 6666))
(check-expect (a smod: 6) 4)
(check-error  (a sdiv: 0))
(check-error  (a smod: 0))
(check-error  (zero sdiv: 0))
(check-expect (zero sdiv: 6) zero)
(check-expect (zero smod: 6) 0)
