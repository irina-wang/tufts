;;;;;;;;;;;;;;;;;;; COMP 105 SCHEME ASSIGNMENT ;;;;;;;;;;;;;;;

;;  Written by Mengqi Irina Wang(mwang17)
;;  Oct 4th, 2020

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise 1

;; (check-head? xs ys) 
;;      > takes in two lists
;;      > returns #t when the head(first few elems) of ys matches all of xs
;;            and #f otherwise 

;; laws:
;;   (match-head? '()         ys)           == #t
;;   (match-head? xs          '())          == #f, when xs != '()
;;   (match-head? (cons a as) (cons b bs))  == (&& (= a b) (match-head? as bs)

(define match-head? (xs ys)
     (if (null? xs)
        #t
        (if (null? ys)
            #f
            (&& (= (car xs) (car ys))
                (match-head? (cdr xs) (cdr ys))))))

        ;; Tests (basic)
        (check-assert     (match-head? '()  '()))     ;; #1: 1stlist empty 
        (check-assert (not(match-head? '(1) '())))    ;; #2: 2ndlist is empty
        (check-assert     (match-head? '(1) '(1 2)))  ;; #3: #t
        (check-assert (not(match-head? '(2) '(1 2)))) ;; #4: #f

        ;; Tests (special)
        (check-assert     (match-head? '(1 2) '(1 2)))  ;; #3: two equal lists


;; (contig-sublist? xs ys) 
;;    > takes in two lists
;;    > returns #t if the first list is a contiguous subsequence of the second,
;;      and returns #f otherwise

;; laws: 
;;   (contig-sublist? '()         ys)          == #t
;;   (contig-sublist? xs          '())         == #f, when xs != '()
;;   (contig-sublist? (cons a as) (cons b bs)) ==  
;;                                     (or (match-head? (cons a as) (cons b bs))
;;                                         (contig-sublist? (cons a as) bs))
;;                                                                 , when a = b
;;   (contig-sublist? (cons a as) (cons b bs)) == 
;;                                             (contig-sublist? (cons a as) bs)
;;                                                               , otherwise


;; Note: use || shortcircuit in case 3. 

(define contig-sublist? (xs ys)
    (if(null? xs)
        #t
        (if(null? ys)
            #f
              (if (= (car xs) (car ys))
                (|| (match-head? xs ys) 
                    (contig-sublist? xs (cdr ys)))
                (contig-sublist? xs (cdr ys))))))


    ;; Tests (basic)
        (check-assert      (contig-sublist? '()    '()))          ;; Case 1
        (check-assert (not (contig-sublist? '(1)   '())))         ;; Case 2
        (check-assert (not (contig-sublist? '(1 2) '(1 3 2))))    ;; Case 3 
        (check-assert      (contig-sublist? '(1 2) '(1 3 1 2)))   ;; Case 3 
        (check-assert      (contig-sublist? '(1 2) '(6 1 3 1 2))) ;; Case 4 

    ;; Tests (special)
        (check-assert (not (contig-sublist? '(1 2) '(1 3 9 2))))  ;; sublist, 
                                                                  ;; not contig 
        (check-assert (not (contig-sublist? '(1 2 3) '(1 2))))    ;; longer xs 
                                                                  ;; than ys 


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise 8

;; (mirror xs) 
;;      > Takes in a S-expression or a list of S-expressions
;;      > Returns a list in which every elem/list in xs is recursively mirrored

;; laws:
;;   (mirror '())          == '()
;;   (mirror  x )          == x
;;   (mirror (cons y ys))  == (append (mirror ys) (mirror y))

(define mirror (xs)
   (if (null? xs)
       xs
       (if (atom? xs)                
            xs
            (append (mirror (cdr xs)) (list1 (mirror (car xs)))))))

        ;; Tests (basic)
        (check-expect (mirror '())                '())        ;; #1
        (check-expect (mirror '(1))               '(1))       ;; #2
        (check-expect (mirror '(1 2 3))           '(3 2 1))   ;; #3 normal case

        ;; Tests (special)
        (check-expect (mirror '((1 8 5) 3))       '(3 (5 8 1)))    
                                                              ;; s-exp is a list
        (check-expect (mirror '((1 8 5) (7 3) 4)) '(4 (3 7) (5 8 1)))     
                                                              ;; multiple lists


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise 31


;; (takewhile p? xs) 
;;      > Takes a predicate and a list
;;      > Returns the longest prefix of the list in which every element 
;;        satisfies the predicate

;; laws:
;;   (takewhile p? '())         == '()
;;   (takewhile p? (cons y ys)) == (cons y (takewhile p? ys)),if (p? y)
;;   (takewhile p? (cons y ys)) == '(), if not (p? y)


(define takewhile (p? xs)
    (if (null? xs)
        xs
        (if (p? (car xs))
            (cons (car xs) (takewhile p? (cdr xs)))
            '())))

        ;; Tests (normal)
        (define even? (x) (= (mod x 2) 0))
            ;; defined only for testing purpose, makes test cases more obvious
            ;; could use (lambda (x) (= (mod x 2) 0)) instead

        (check-expect (takewhile even? '())                '())       ;; #1
        (check-expect (takewhile even? '(2 4 6 7 8 10 12)) '(2 4 6))  ;; #2
        (check-expect (takewhile even? '(1 3 7))           '())       ;; #3

;; (dropwhile p? xs) 
;;      > Takes a predicate and a list
;;      > Returns whatever is left over after removing the longest prefix in 
;;        which every element satisfies the predicate 


;; laws:
;;   (dropwhile p? '())         == '()
;;   (dropwhile p? (cons y ys)) == (dropwhile p? ys), if (p? y)
;;   (dropwhile p? (cons y ys)) == (cons y ys), if not (p? y)


(define dropwhile (p? xs)
    (if (null? xs)
        xs
        (if (p? (car xs))
            (dropwhile p? (cdr xs))
            xs)))

        ;; Tests (normal)
        (define even? (x) (= (mod x 2) 0))
            ;; defined only for testing purpose, makes test cases more obvious
            ;; could use (lambda (x) (= (mod x 2) 0)) instead

        (check-expect (dropwhile even? '())                '())          ;; #1
        (check-expect (dropwhile even? '(2 4 6 7 8 10 12)) '(7 8 10 12)) ;; #2
        (check-expect (dropwhile even? '(1 3 7))           '(1 3 7))     ;; #3

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise C

;; (zip xs ys) 
;;      > Takes a pair of lists of EQUAL length
;;      > Returns a list of pairs by associating corresponding values in the 
;;        two lists

;; laws: 
;;   (zip '()         '())         == '()
;;   (zip (cons a as) (cons b bs)) == (cons (list2 a b) (zip as bs))

(define zip (xs ys)
    (if (or (null? xs) (null? ys))
        '()
        (cons (list2 (car xs) (car ys)) 
                (zip (cdr xs) (cdr ys)))))

        ;; Tests (normal)
        (check-expect (zip '() '()) '())                     ;; #1: empty-list
        (check-expect (zip '(1 3) '(a b)) '((1 a) (3 b)))    ;; #2: normal case


;; (unzip ps) 
;;      > Takes in a list of pairs, the list has even num of elements 
;;      > Returns a pair of lists
;;      > Note, taking in an empty list would return a pair of empty lists


(define unzip (ps)
    (if (null? ps)
        '(() ())
        (list2 (map car ps) (map cadr ps)))) 

        ;; Tests (normal)
        (check-expect (unzip '()) '(() ()))                  ;; #1: empty-list
        (check-expect (unzip '((1 a) (2 b))) '((1 2) (a b))) ;; #2: normal case

    ;; Test properties of zip and unzip 
    (check-expect (zip (car (unzip '((1 a) (2 b)))) 
                       (cadr (unzip '((1 a) (2 b))))) '((1 a) (2 b)))
    (check-expect (unzip (zip '(1 3) '(a b))) (list2 '(1 3) '(a b)))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise D


;; (arg-max f xs) 
;;      > Takes in a function f that maps a value in set A to a number
;;              and a nonempty list as of values in set A
;;      > Returns an element a in as for which (f a) is the largest in the list

;; laws:
;;   (arg-max f (cons y ys)) == y,            when (null? ys)
;;   (arg-max f (cons y ys)) == y,            when (f y) >= (f arg-max(ys))
;;   (arg-max f (cons y ys)) == (arg-max ys), otherwise

;; Explanation:
;;     Base case is when there's only one element, because we are not supposed 
;; to use length function, I use null? to check the cdr of the list, which does
;; the same thing as checking if the length is 1. 

;; Note: 
;;      From the laws we know that at least we need to make 2 calls to arg-max; 
;; But in order to achieve better than exponential runtime, we declare a 
;; variable that record the values. 

(define arg-max (f xs)
    (if (null? (cdr xs)) 
        (car xs)            
        (let ([max_var (arg-max f (cdr xs))])
            (if (>= (f (car xs)) (f max_var))
                (car xs)
                max_var))))

        ;; Tests (normal)
        (define square (a) (* a a))
            ;; defined only for testing purpose, makes test cases more obvious
            ;; could use (lambda (a) (* a a)) instead

        (check-expect (arg-max square '(5))          5)   ;; #1: one elem
        (check-expect (arg-max square '(5 5 3 2 1))  5)   ;; #2: max in car
        (check-expect (arg-max square '(5 5 3 8 1))  8)   ;; #2: max in cdr

        ;; Tests (special)
        (check-expect (arg-max car '((105 PL) (160 Algorithms) (170 Theory))) 
                                                              '(170 Theory))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  Exercise E

(record point [x y])

;; (rightmost-point ps) 
;;      > Takes a nonempty list of point records
;;      > Returns the one with the largest x coordinate
  

(define rightmost-point (ps)
    (arg-max point-x ps))

        ;; Tests (normal)
        (check-expect (rightmost-point 
                        '((make-point 1 2) (make-point 3 4) (make-point 5 6))) 
                        '(make-point 5 6))

        ;; Tests (special)
        (check-expect (rightmost-point 
                        '((make-point 5 6) (make-point 3 4) (make-point 1 2))) 
                        '(make-point 5 6))                     ;; reverse order
        (check-expect (rightmost-point '((make-point 3 1))) (make-point 3 1))
                                                               ;; one elem
        (check-expect (rightmost-point 
                        '((make-point 0 6) (make-point 1 4) (make-point 1 2))) 
                        '(make-point 1 4))                     ;; same x
        (check-expect (rightmost-point 
                        '((make-point 0 6) (make-point 0 6))) 
                        '(make-point 0 6))                     ;; same points
        