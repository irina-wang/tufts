;;;;;;;;;;;;;;;;;;; COMP 105 SCHEME ASSIGNMENT ;;;;;;;;;;;;;;;

;;  Written by Mengqi Irina Wang(mwang17)
;;  Oct 8th, 2020

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise 28 b,e,f

;;------------------------------------------------------------- PART B
;; (max* xs) 
;;      > takes in a non-empty list of integers
;;      > returns the maximum integer of the list

(define max* (xs)
    (foldr max (car xs) (cdr xs)))

        ;; Tests 
        (check-expect     (max* '(1 5 6))     6)    

        ;; Tests (special)
        (check-expect     (max* '(6))         6)     ;; one-elem
        (check-expect     (max* '(1 3 6 4 3)) 6)     ;; duplicates

;;------------------------------------------------------------- PART E
;; (sum xs) 
;;      > takes in a non-empty list of integers
;;      > returns the sum of the list

(define sum (xs)
    (foldr + 0 xs))

    ;; Tests (normal)
        (check-expect     (sum '(1 3))         4)     ;; normal case

    ;; Tests (special)
        (check-expect     (sum '(1))           1)     ;; single elem 
        (check-expect     (sum '(-1))         -1)     ;; neg elem
        (check-expect     (sum '(1 5 2 1))     9)     ;; long normal list

;;------------------------------------------------------------- PART F
;; (product xs) 
;;      > takes in a non-empty list of integers
;;      > returns the product of the list

(define product (xs)
    (foldr * 1 xs))

    ;; Tests (normal)
        (check-expect     (product '(1 5 2 1))     10)    ;; normal case

    ;; Tests (special)
        (check-expect     (product '(1))            1)     ;; single elem 
        (check-expect     (product '(-1 -4 2 -1))  -8)     ;; neg elems
        (check-expect     (product '(1 0 8 2 1))    0)     ;; contain 0


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise 29 a,c

;;------------------------------------------------------------- PART A
;; (append xs ys) 
;;      > Takes in two lists
;;      > Returns a list after appending both lists

(define append (xs ys)
   (foldr cons ys xs))

    ;; Tests (basic)
        (check-expect (append '(1) '(2))      '(1 2))     ;; normal list

    ;; Tests (special)
        (check-expect (append '() '())        '())        ;; empty
        (check-expect (append '(1) '())       '(1))       ;; ys empty list
        (check-expect (append '() '(8))       '(8))       ;; xs empty list
        (check-expect (append '(1 3 4) '(2))  '(1 3 4 2)) ;; longer normal list


;;------------------------------------------------------------- PART C
;; (reverse xs) 
;;      > Takes in a list
;;      > Return the reversed list

(define reverse (xs)
   (foldl cons '() xs))

    ;; Tests (basic)
        (check-expect (reverse '(3 1 2))    '(2 1 3))    ;; normal case

    ;; Tests (special)
        (check-expect (reverse '())         '())         ;; empty
        (check-expect (reverse '(1))        '(1))        ;; one-elem
        (check-expect (reverse '(8 (9 2)))  '((9 2) 8))  ;; lst elem isn't rev

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise 30

;; (map f xs) 
;;      > Takes in a list
;;      > Return the list of results of applying p to the list

(define map (f xs)
    (foldr (lambda (a b) (cons (f a) b)) '() xs))

    ;; Tests (basic)
        (check-expect (map (lambda (x) (* 2 x)) '(1 2 3)) '(2 4 6))  
                                                            ; apply double
        (check-expect (map (lambda (x) (< 0 x)) '(1 2 3)) '(#t #t #t))  
                                                            ; apply comparison

    ;; Tests (special)
        (check-expect (map (lambda (x) (* 2 x)) '())      '())       
                                                            ; empty

;; (filter p? xs) 
;;      > Takes in a list
;;      > Return the list of results with elems satisfied the predicate

(define filter (p? xs) 
    (foldr (lambda (a b) (if (p? a) (cons a b) b)) '() xs))

    ;; Tests (basic)
        (check-expect (filter (lambda (x) (< 0 x)) '(1 2 3)) '(1 2 3)) ; normal
        (check-expect (filter (lambda (x) (> 0 x)) '(1 2 3)) '())   ; nothing
                                                                    ; satisfied
    ;; Tests (special)
        (check-expect (filter (lambda (x) (< 0 x)) '())      '())      ; empty


;; (exists? p? xs) 
;;      > Takes in a list
;;      > Return #t if any elem in the list satisfies p?, and ret #f otherwise

(define exists? (p? xs) 
    (foldr (lambda (a b) (or (p? a) b)) #f xs))

    ;; Tests (basic)
        (check-assert      (exists? (lambda (x) (< 0 x)) '(1 2 3))) ; normal

    ;; Tests (special)
        (check-assert (not (exists? (lambda (x) (< 0 x)) '())))     ; empty 
        (check-assert      (exists? (lambda (x) (< 0 x)) '(-1 -4 3))) 
                                                        ; last elem satisfy p
        (check-assert (not (exists? (lambda (x) (> 0 x)) '(1 2 3)))) ; nothing
                                                                     ;satisfied 

;; (all? p? xs) 
;;      > Takes in a list
;;      > Return #t if all elems in the list satisfy p?, and ret #f otherwise
;; Note that empty case evals to #t

(define all? (p? xs) 
    (foldr (lambda (a b) (and (p? a) b)) #t xs))

    ;; Tests (basic)
        (check-assert   (all? (lambda (x) (< 0 x)) '(1 2 3))) ; normal 

    ;; Tests (special)
        (check-assert       (all? (lambda (x) (< 0 x)) '())) ; empty
        (check-assert (not (all? (lambda (x) (< 0 x)) '(-1 -4 3)))) 
                                                    ; not all satisfy p
        (check-assert (not (all? (lambda (x) (< 0 x)) '(3 2 -3)))) 
                                                    ; last elem not satisfy p
        (check-assert (not (all? (lambda (x) (> 0 x)) '(1 2 3)))) 
                                                    ; nothing satisfies p

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise 38

;; pre-defined - used for testing
(val emptyset (lambda (x) #f)) 
(define member? (x s) (s x))

;;---------------------------------------------------------------- evens
;; evens 
;;      > contains all the even integers

(val evens (lambda (x) (= (mod x 2) 0)))

        ;; Tests (basic)
        (check-assert (not (member? 1 evens))) ; odd
        (check-assert      (member? 2 evens))  ; even
        (check-assert      (member? 0 evens))  ; 0 - even

;;----------------------------------------------------------------- two-digits
;; two-digits
;;   > contains all two-digit (positive) numbers

(val two-digits (lambda (x) (and (> x 9) (< x 100))))

        ;; Tests (basic)
        (check-assert       (member? 82  two-digits))   ; normal two-digits
        (check-assert  (not (member? 1   two-digits)))  ; one-digit
        (check-assert  (not (member? 100 two-digits)))  ; more than two-digits

        ;; Tests (special)
        (check-assert  (not (member? 9   two-digits)))  ; max one-digit
        (check-assert       (member? 99  two-digits))   ; max two-digits
        (check-assert       (member? 10  two-digits))   ; min two-digits
        (check-assert  (not (member? -72 two-digits)))  ; negative


;;----------------------------------------------------------------- add-element
;; add-element (a s)
;;   > returns the set adds a to the set s 

;; laws:
;; (member? x (add-element x s)) == #t                              
;; (member? x (add-element y s)) == (member? x s), where (not (equal? y x))

(define add-element (a s) 
    (lambda (x) (or (equal? x a) (s a))))     

    ;; Tests
        (check-assert      (member? 1 (add-element 1 emptyset)))   ; #1: in-set
        (check-assert (not (member? 4 (add-element 1 emptyset))))  ; #2: out-set
        (check-assert      (member? 1 (add-element 1 evens)))
        
        
;;----------------------------------------------------------------- union
;; union (s1 s2)
;;   > returns the union of sets s1 and s2

;; laws:
;; (member? x (union s1 s2)) == (or (s1 x) (s2 x))


(define union (s1 s2)
    (lambda (a) (or (s1 a) (s2 a))))  

    ;; Tests (basic)
        (check-assert (not (member? 1 (union emptyset emptyset))))  ; empty
        (check-assert      (member? 1 (union (add-element 1 emptyset) 
                                              emptyset)))           ; different
                                                                    ; sets
        (check-assert      (member? 1 (union (add-element 1 emptyset)
                                             (add-element 1 emptyset))))
                                                                    ; same sets
        (check-assert (not (member? 1 (union evens two-digits))))
                                                               ; not in the set


;;----------------------------------------------------------------- inter 
;; inter (s1 s2)
;;   > returns the intersection of sets s1 and s2

;; laws:
;; (member? x (inter s1 s2)) == (and (s1 x) (s2 x)))


(define inter (s1 s2)
    (lambda (a) (and (s1 a) (s2 a))))  

     ;; Tests (basic)
        (check-assert (not (member? 1   (inter emptyset emptyset))))  ; empty
        (check-assert (not (member? 1   (inter (add-element 1 emptyset) 
                                                evens))))           ; null inter
        (check-assert      (member? 22  (inter evens two-digits)))  ; in inter
        (check-assert (not (member? 200 (inter evens two-digits)))) ; in one set
                                                                ; not in inter
        (check-assert (not (member? 2   (inter evens two-digits)))) ; not in 
                                                                    ; inter

;;----------------------------------------------------------------- diff
;; diff (s1 s2)
;;   > returns the set of numbers in s1 but not in s2

;; laws:
;; (member? x (diff s1 s2)) == (and (s1 x) (not (s2 x)))

(define diff (s1 s2)
    (lambda (a) (and (s1 a) (not (s2 a)))))     

    ;; Tests (basic)
        (check-assert (not (member? 1  (diff emptyset emptyset))))  ; empty
        (check-assert      (member? 1  (diff (add-element 1 emptyset) 
                                              emptyset)))           ; in diff
        (check-assert (not (member? 22 (diff evens two-digits))))   ; in both
        (check-assert (not (member? 11 (diff evens two-digits))))   ; in s2, 
                                                                    ; not in s1
        (check-assert (not (member? 303 (diff evens two-digits))))
                                                                    ; in neither
;;----------------------------------------------------------------- PART D

(record set-ops [emptyset member? add-element union inter diff])

;; set-ops-from (eq?)
;;    > Accept one argument (an equality predicate) and will return a record 
;; created by calling make-set-ops

(define set-ops-from (eq?)
    (let ([emptyset      (lambda (x) #f)                                    ] 
          [member?       (lambda (x s) (s x))                               ] 
          [add-element   (lambda (a s) 
                            (lambda (x) (or (eq? a x) (s a))))              ] 
          [union         (lambda (s1 s2) 
                            (lambda (a) (or (s1 a) (s2 a))))                ]
          [inter         (lambda (s1 s2) 
                            (lambda (a) (and (s1 a) (s2 a))))               ] 
          [diff          (lambda (s1 s2) 
                            (lambda (a) (and (s1 a) (not (s2 a)))))         ]) 
        (make-set-ops emptyset member? add-element union inter diff)))

    ;; Tests 
        (check-assert (function? set-ops-from)) 
        (check-assert (set-ops? (set-ops-from =)))

    ;; Additional Tests (created for test purposes)   
        (val atom-set-ops     (set-ops-from =))
        (val atom-emptyset    (set-ops-emptyset    atom-set-ops))
        (val atom-member?     (set-ops-member?     atom-set-ops))
        (val atom-add-element (set-ops-add-element atom-set-ops)) 
        (val atom-union       (set-ops-union       atom-set-ops))
        (val atom-inter       (set-ops-inter       atom-set-ops))
        (val atom-diff        (set-ops-diff        atom-set-ops))

    ;;  Additional Tests (actual tests)  
     ; >> emptyset
        (check-assert (not (atom-emptyset 1))) ; empty set

     ; >> member? 
        (check-assert (not (atom-member? 1 atom-emptyset))) ; empty set
        (check-assert      (atom-member? 2 evens))
        (check-assert (not (atom-member? 5 evens)))

     ; >> add-element
        (check-assert      ((atom-add-element '1 evens) 1))  
        (check-assert (not ((atom-add-element '1 evens) 9)))

     ; >> union
        (val set-two-d-and-evens (atom-union evens two-digits))
        (check-assert            (atom-member? 22 set-two-d-and-evens)) 
        (check-assert (not       (atom-member? 3  set-two-d-and-evens))) 

     ; >> union special 
        ;;; same-set union
        (val set-evens (atom-union evens evens))
        (check-assert            (atom-member? 22 set-two-d-and-evens)) 
        (check-assert (not       (atom-member? 9  set-two-d-and-evens))) 

     ; >> inter
        (check-assert            ((atom-inter evens two-digits) '22)) 
        (check-assert  (not      ((atom-inter evens two-digits) '11))) 
        
        ; >> inter special
        (check-assert  (not      ((atom-inter evens two-digits) '100))) 
        (check-assert  (not      ((atom-inter evens two-digits) '11))) 
        (check-assert  (not      ((atom-inter evens two-digits) '2))) 
        (check-assert  (not      ((atom-inter atom-emptyset atom-emptyset) '2)))
                                                            ; empty 
        (check-assert  (not      ((atom-inter evens atom-emptyset) '2))) 
                                                            ; null inter
    
     ; >> diff
        (check-assert             ((atom-diff evens two-digits) '2)) 
        (check-assert  (not       ((atom-diff evens two-digits) '22))) 
        (check-assert  (not       ((atom-diff evens two-digits) '11))) 
        (check-assert  (not       ((atom-diff evens two-digits) '111))) 

         ; >> diff special
        (check-assert  (not      ((atom-diff atom-emptyset atom-emptyset) '2)))
                                                                        ; empty 

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise F 

;; (flip f)
;;    > Takes in a function f
;;    > Returns a function that takes in two parameters, which applies 
;;  f on the two arguments in opposite order

;; laws:
;;  ((flip f) x y) == (f y x)

(define flip (f)
    (lambda (x y) (f y x)))

        ;; Test (assert function)
        (check-assert (function? (flip <)))
        (check-assert (function? (flip append)))

        ;; Tests (normal)
        (check-expect ((flip <) 3 4)   (> 3 4)) 
        (check-expect ((flip <) 3 3)   (> 3 3)) 
        (check-expect ((flip <) 3 4)   #f) 
        (check-expect ((flip <=) 3 4)  #f) 
        (check-expect ((flip append) '(a b c) '(1 2 3)) '(1 2 3 a b c))       

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise O 

;; (ordered-by? precedes?) 
;;    > Takes one argument—a comparison function that represents a transitive 
;; relation and returns a predicate that tells if a list of values is totally 
;; ordered by that relation.

;; laws: 
;; ((ordered-by? precedes?) '())                  == #t
;; ((ordered-by? precedes?) (cons x '())          == #t
;; ((ordered-by? precedes?) (cons x (cons y zs))) == 
;;                                     (&& (precedes? x y) 
;;                                         ((ordered-by? precedes) (cons y zs)))


(define ordered-by? (precedes?)
   (letrec ([check-ordered-by 
                (lambda (xs)
                    (if (null? xs)
                        #t
                        (if (null? (cdr xs))
                            #t
                            (&& (precedes? (car xs) (cadr xs))
                                (check-ordered-by (cdr xs))))))])
    check-ordered-by))

        ;; Tests (basics)
        (check-assert (function? ordered-by?))
        (check-assert (function? (ordered-by? <)))
        (check-error (ordered-by? < '(1 2 3)))
        
        ;; Tests (normal)
        (check-assert      ((ordered-by? <) '()))           ;; empty case
        (check-assert      ((ordered-by? <) '(1 2 3)))
        (check-assert (not ((ordered-by? >) '(1 2 3))))

         ;; Tests (special)
        (check-assert      ((ordered-by? <=) '(1 2 3))) 
        (check-assert (not ((ordered-by? <) '(3 2 1)))) 
        (check-assert      ((ordered-by? >=) '(3 2 1)))
        (check-assert      ((ordered-by? >=) '(3 3 3)))  
        (check-assert      ((ordered-by? =)  '(3 3 3)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise V

(val the-fault list1) ; build a singleton fault set
(val no-faults '())   ; empty fault set

;; faults/none ()
;;  > Returns a validator that takes a response and always returns the empty 
;; list of faults, no matter what is in the response.

;; laws:
;;    (faults/none response) == ’()

(define faults/none ()
    (lambda (_) no-faults))


;; faults/always (F)
;;  > Returns a validator that takes a response and always returns a singleton 
;; list containing the fault f, no matter what is in the response.

;; laws:
;;    ((faults/always f) response) == (list1 f)

(define faults/always (f)
    (lambda (_) (the-fault f)))


;; (faults/equal key value)
;;   >  Returns a validator that takes a response and if key is bound to value 
;; in the response, returns a singleton list containing key. If key is not 
;; bound to value in the response, the validator returns the empty list of 
;; faults.

;; laws:
;;   ((faults/equal key value) xs) == (the-fault key), if (find key xs) == value
;;   ((faults/equal key value) xs) == '(),             if (find key xs) != value

(define faults/equal (key value)
    (lambda (xs)
        (if (= (find key xs) value) 
            (the-fault key)
            no-faults)))


;; (faults/both V1 V2)
;;   >  Returns a new validator that combines checks from the two validators 
;; V1 and V2. The faults/both validator returns a single list of faults that is
;; formed by taking the union of the faults from V1 with the faults from V2 
;; (with no duplicates).

;; laws:
;;      ((faults/both v1 v2) rsp) == (union (v1 rsp) (v2 rsp))

(val faults/both
    (let* ([member?  (lambda (x s) (exists? ((curry =) x) s))       ] 
           [add-elem (lambda (x s) (if (member? x s) s (cons x s))) ]
           [union    (lambda (faults1 faults2) 
                                (foldr add-elem faults2 faults1))   ]) 
        (lambda (v1 v2)
            (lambda (rsp) (union (v1 rsp) (v2 rsp))))))


;; faults/switch (key validators)
;;   >  Returns a validator that validates the response using a validator 
;; selected from validator table validators: the value of key in the response 
;; is a key used to find a validator in validators.

;; laws:
;;   ((faults/switch key validators) rsp) == 
;;                       ((find (find key rsp) validators) rsp)

;; Note: This only applied if key is bound. If key is unbound in the validator 
;;       table, the validator must halt with a checked run-time error. 


(define faults/switch (key validators)
    (lambda (rsp)
        (let* ([key_in_rsp   (find key rsp)              ]
               [val_in_table (find key_in_rsp validators)])
            (if (function? val_in_table) 
                (val_in_table rsp)
                (error 'validator doesn't exist in the table))))) ;; checked 
                                                            ;; run-time error
    

;; Test (example for the regrade form)
(val regrade-validator  
  (faults/switch 'why
    (bind         'photo
                  (faults/none)
      (bind       'badsubmit
                   (faults/both (faults/equal 'badsubmit_asst '...)
                                (faults/equal 'info #f))
        (bind     'badgrade
                  (faults/both
                      (faults/equal 'badgrade_asst '...)
                      (faults/both
                         (faults/equal 'info #f)
                         (faults/equal 'problem #f)))
          (bind   'recitation
                  (faults/both
                      (faults/equal 'date #f)
                      (faults/equal 'leaders #f))

            (bind '#f
                  (faults/always 'nobutton)
                  '())))))))

    ; Test ( borrowed from validator- tests.scm)
        (check-expect (regrade-validator '([why photo]))
                        '())

        (check-expect (regrade-validator '([why badsubmit]
                                           [info wrong-pdf]
                                           [badsubmit_asst opsem]))
                        '())

        (check-expect (regrade-validator '([why badsubmit]
                                           [badsubmit_asst opsem]
                                           [info #f]))
                        '(info))

        (check-expect (regrade-validator '([why badsubmit]
                                           [info wrong-pdf]
                                           [badsubmit_asst ...]))
                        '(badsubmit_asst))

        (check-expect (regrade-validator '([why badsubmit]
                                           [info #f]
                                           [problem #f]
                                           [badsubmit_asst ...]))
                        '(badsubmit_asst info))

        (check-expect (regrade-validator '([why badgrade]
                                           [info #f]
                                           [problem #f]
                                           [badgrade_asst impcore]))
                        '(info problem))

