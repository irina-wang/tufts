;; step 5 

    ; check LIT
    (check-type 3 int) 
    (check-type #t bool) 
    (check-type 'hello sym)

    ; error
    (check-type-error '(#t 2))                          ; mixed type pair

;; step 6 

    ; check IFX
    (check-type (if #t 1 2) int)
    (check-type (if #t 'a 'b) sym)

    ; error
    (check-type-error (if 1 'j 1))                       ; e1 not bool
    (check-type-error (if #t 'j 1))                      ; e2 e3 not equal type

;; step 7

    ; check VAR
    (check-type +     (int int -> int))
    (check-type -     (int int -> int))
    (check-type cons (forall ('a) ('a (list 'a) -> (list 'a)))) 

;; step 9

    ; check VAL
    (val x 3)
    (check-type x int)

    (val y #t)
    (check-type y bool)

    ; error 
    (check-type-error z)  

;; step 10

    ; check APPLY
    (check-type (+ 1 2) int)
    (check-type (* 1 2) int)
    
    ; error
    (check-type-error (+ (1,2)))                ; mixmatch num of arg
    (check-type-error (+ 1 2 8 2))
    (check-type-error (max))
    (check-type-error (max 1))
    (check-type-error (* 8 'k ))                ; mixmatch types
    (check-type-error (min 8 'k )) 

;; step 11

    ; check LET
    (check-type (let ([x 3]) (+ x x)) int)
    (check-type (let ([x #t]) (if x 1 1)) int)

    ; error
    (check-type-error  (let ([x #t]) (max x #t)))
    (check-type-error  (let ([x #t]) (+ x #t)))
    (check-type-error (let ([z 2][y #t]) (+ z y)))
     
;; step 12

    ; check LAMDBA
    (check-type (lambda ([a : int] [b : int]) (+ a b)) (int int -> int))
    (check-type (lambda ([a : int] [b : int]) (max a b)) (int int -> int))
    (check-type (lambda ([a : bool] [b : bool]) (and a b)) (bool bool -> bool))

    ; error
    (check-type-error (lambda ([a : sym] [b : sym]) (+ a b)))
    (check-type-error (lambda ((x : list)) y))

;; step 13

    ; check SET
    (check-type (set x (+ 1 1)) int)
    (check-type-error (set x #f))

    ; check WHILE
    (check-type (while #t (+ 1 1)) unit)
    (check-type-error (while 1 (+ 1 1)))

    ; check BEGIN
    (check-type (begin ) unit)
    (check-type (begin (+ x 1) (+ x 2) (+ x 3)) int)
    (check-type (begin 1 0 #f) bool)

    (check-type-error (begin (+ 1 x) (0) ))
    (check-type-error (begin (+ 1 x) (+ x 2) (- x #t)))
    (check-type-error (begin (+ 1 x) (- x 'a)))

;; step 14

    ; check LETSTAR
    (check-type (let* ([x 1] [y 2]) (+ x y)) int)
    (check-type (let* () (+ x 1)) int)
    (check-type (let* ([x (< 1 5)] [y (< 5 2)]) (and x y)) bool)
    (check-type   (let* ([x #f] [y  x]) (and x y)) bool)

    ; error
    (check-type-error (let* ([x #f] [y 2]) (+ x y)))
    (check-type-error (let* ([x #f] [y 2]) (and x y)))
    (check-type-error (let* ([y k]) y)) 

;; step 15

    ; check LETREC
    (check-type (letrec () 1) int)
    (check-type (letrec ([(f : (-> int)) (lambda () 1)]) (f)) int)

    ; error
    (check-type-error (letrec ([(a : int) 1] [(b : int) 2]) (+ a b)))
    (check-type-error (letrec ([(a : int) 1] [(b : list) '(1 2)]) (cons a b)))


;; step 16

    ; check VALREC
    (val v 1)
    (val vlist 1)
    (val-rec [vr1 : (int -> int)] (lambda ([v : int]) (+ v 1)))
    (val-rec [vr2 : (int -> int)] (lambda ([v : int]) (+ v #f)))
    (val-rec [vr3 : (list -> list)] (lambda ([vlist : list]) (cons 1 vlist)))
    (val-rec [vr3 : (list -> list)] (lambda ([vlist : list]) (cons #t vlist)))

    (check-type vr1 (int -> int))
    (check-type-error vr2)
    (check-type-error vr3)
    (check-type-error vr4)

    ; check DEFINE
    (define bool n ([b : bool])  (if b #f #t))
    (check-type n (bool -> bool))


;; step 17

    ; check TYAPPLY 
    (check-type (@ car int) ((list int) -> int))
    (check-type-error (@ < int))                          ; missing parameter

    ; check TYLAMBDA
    (check-type
        (type-lambda ['a] (lambda ([x : 'a]) x))
        (forall ('a) ('a -> 'a)))
    (check-type
        (type-lambda ['a ]
            (lambda ([x : 'a] )
                ([@ = 'a] x x)))
        (forall ['a] ('a -> bool)))
    
    ; error
    (check-type-error
        (type-lambda ['b] (lambda ([x : 'a]) x)))
    (check-type-error
        (type-lambda ['a] (lambda ([x : 'a]) b)))


;; step 18

    ; check NIL
    (check-type '() (forall ['a] (list 'a )))

    ; check PAIRS 
    (check-type '(1) (list int))                        ; one-elem pair
    (check-type '(1 2) (list int))                      ; two-elem pair
    (check-type '(#t #f #t) (list bool))

    (check-type '(#t #f #t) (list bool))
    