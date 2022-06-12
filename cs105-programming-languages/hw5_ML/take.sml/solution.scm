;;;;;;;;;;;;;;;;;;; COMP 105 SCHEME ASSIGNMENT ;;;;;;;;;;;;;;;

;;  Written by Mengqi Irina Wang(mwang17)
;;  Oct 15th, 2020

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  L. Recognizing lists

;; (define list-of? A? v)
;;    > Takes two arguments. The first argument, A?, is a predicate that can 
;;        be applied to any value. The second argument, v, is an arbitrary 
;;        μScheme value.
;;    > Returns #t if v is a list of values, each of which satisfies A?, and
;;        return #f otherwise

;; laws: 
;;   (list-of? A? '())          == #t
;;   (list-of? A?  x)           == #f, if (atom? x) 
;;   (list-of? A?  x)           == #f, if (function? x)
;;   (list-of? A?  (cons x xs)) == (and (A? x) (list-of? A? xs))

(define list-of? (A? v)
    (if (null? v)
         #t
        (if (|| (atom? v) (function? v))
            #f
            (and (A? (car v)) (list-of? A? (cdr v))))))


    ;; Tests (basic)
        (define value? (_) #t)              ;; tell if the argument is a value

        ; Case 1: empty list
        (check-assert      (list-of? number?   '()))           
        (check-assert      (list-of? value?    '()))

        ; Case 2: atom
        (check-assert (not (list-of? number?    1)))          ;; num,  not list
        (check-assert (not (list-of? value?     1)))
        (check-assert (not (list-of? value?     #f)))         ;; bool, not list
        (check-assert (not (list-of? value?     'c )))        ;; symbol not list

        ; Case 3: func
        (check-assert (not (list-of? number?    exists?)))    ;; func, not list

        ; Case 4: list
        (check-assert      (list-of? number?   '(1 2)))       ;; num list
        (check-assert (not (list-of? number?   '(1 'a ))))    ;; non-num list
        (check-assert      (list-of? value? (list3 1 #f 'c ))) ; mixed list
        (check-assert      (list-of? value? (cons 'comp (cons 105 '()))))
                                                               ;; cons form

        (val nested_list (append '((1 2)) '(9 7)))
        (check-assert (not (list-of? number? nested_list)))  ;; nested list 



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  F. Recognizing formulas

(record not [arg])
(record or  [args])
(record and [args])

;; (define formula? A? v)
;;    >  Takes an arbitrary μScheme value
;;    >  Returns #t if the value represents a Boolean formula and #f otherwise

;; laws: 
;;  (formula? v)             = #t,  if (symbol? v)    
;;  (formula? (make-not v))  = (formula? (not-arg v))             ; not
;;  (formula? (make-or  v))  = (list-of? formula? (or-args  v))   ; or
;;  (formula? (make-and v))  = (list-of? formula? (and-args v))   ; and
;;  (formula? v)             = #f,  otherwise   

(define formula? (v)
    (if (symbol? v)
        #t
        (if (&& (not? v) (formula? (not-arg v)))
            #t
            (if (&& (or? v) (list-of? formula? (or-args v)))
                #t
                (&& (and? v) (list-of? formula? (and-args v)))))))

    ;; Tests (normal)
        ; Case 1: non-lists            
        (check-assert      (formula? 'k ))                 ;; symbol
        (check-assert (not (formula?  1)))                 ;; non-symbol elem
        (check-assert (not (formula?  #f)))                ;; non-symbol elem
        (check-assert (not (formula? (max 1 2))))          ;; function

        
        (val test_and (make-and (list2 (make-not 'x ) 'x )))
        (val test_or  (make-or  (list2 (make-not 'x ) test_and)))
        (val test_not (make-not 'test_or ))

        ; Case 2: not
        (check-assert       (formula? test_not))

        ; Case 3: or
        (check-assert       (formula? test_or))
        (check-assert (not  (formula? (cons 'x test_and)))) ;; cons symbol

        ; Case 4: and
        (check-assert       (formula? test_and))
        (check-assert (not  (formula? (cons 1 test_and))))  ;; cons non-formula
        
        ; Case 5: Others
        (check-assert (not (formula? '() )))                ;; empty list
        (check-assert (not (formula? (list2  1  3))))       ;; num list
        (check-assert (not (formula? (list2 't 'y ))))      ;; symbol list


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  E. Evaluating formulas

;; (eval-formula 𝑓 env) 
;;     > Takes two arguments: a formula 𝑓 and an environment
;;                         - Note that env is an association list in which 
;;                              each key is a symbol and each value is a bool
;;     >  Returns #t if the formula is satisfied in the given environment, 
;;        and returns #f otherwise.

;; * (eval-formula f env) may be called only when every variable in formula f 
;;   is bound in env.

;; laws: 
;;  (eval-formula? x  env) = (find x env)                ,  if (symbol? x)    
;;  (eval-formula? f  env) = (not  (eval-formula f env)) ,  if (not? f) 
;;  (eval-formula? fs env) = (all? (lambda (x) (eval-formula x env)) fs),
;;                                                          if (and? fs) 
;;  (eval-formula? fs env) = (exists? (lambda (x) (eval-formula x env)) fs)
;;                                                          if (or? fs) 
;;  (eval-formula? fs env) = 'invalid-form, otherwise


(define eval-formula (f env)
    (if (symbol? f)
        (find f env)     
        (if (not? f)
            (not (eval-formula (not-arg f) env)) 
            (if (or? f)
                (exists? (lambda (v) (eval-formula v env)) (or-args f))
                (if (and? f) 
                    (all? (lambda (v) (eval-formula v env)) (and-args f))
                    (error 'invalid-form ))))))

    ;; Tests
        ; symbol      
        (check-assert  (eval-formula 'u '((u #t))))

        ; not 
        (val test_not (make-not 'k ))                    
        (val env_not '((k #t)))
        (check-assert (not (eval-formula test_not env_not)))       ; (not #t)
        (check-assert      (eval-formula test_not '((k #f))))

        ; and 
        (val test_and (make-and '(k t)))                          ; simple list
        (check-assert (not (eval-formula test_and '((k #t) (t #f))))); && #t #f
        (check-assert      (eval-formula test_and '((k #t) (t #t)))) ; && #t #t

        ; or
        (val test_or (make-or '(k t c))) 
        (check-assert (not (eval-formula test_or '((k #f) (t #f) (c #f))))) ; #f
        (check-assert      (eval-formula test_or '((k #f) (t #f) (c #t))))  ; #t

        ; compounds 
        (val f_not (make-not '(k))) 
        (val f_and (make-and '(t c)))
        (val test_or2 (make-or '(f_not f_and)))  
        (eval-formula test_or2 '((f_not #t) (f_and #t)))      

        ; special cases
        (check-expect     (eval-formula 'u '((j #t))) '())       ; unbound
        (check-error      (eval-formula  1 '((1 #t))))           ; invalid form


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;;  S.  SAT

;; bound? (x env)
;;    > Returns true if find x is a key of a pair in the env
;;                          (x is bound in the env)
(define bound? (x env)
    (exists? (lambda (pair) (equal? x (car pair))) env))

    ; Test
        (check-assert      (bound? 3 '((3 #f))))
        (check-assert (not (bound? 3 '((4 #f)))))


;; find-formula-true-asst (f fail succ)
;;      > Takes three parameters: a formula, a failure continuation, and a
;;  success continuation
;;      > Searches for a satisfying assignment, which is a mapping of 
;;  variables to Booleans that makes the formula true.

; laws:
; (find-formula-asst x bool cur fail succeed)  == 
;                           (find-formula-symbol x bool cur fail succeed),
;                                                            where x is a symbol
; (find-formula-asst (make-not f) bool cur fail succeed) == 
;                           (find-formula-symbol x (not bool) cur fail succeed)
; (find-formula-asst (make-or  f) #t cur fail succeed)   == 
;                           (find-any-asst f #t cur fail succeed)
; (find-formula-asst (make-or  f) #f cur fail succeed)   == 
;                           (find-all-asst f #f cur fail succeed)
; (find-formula-asst (make-and f) #t cur fail succeed)   == 
;                           (find-all-asst f #t cur fail succeed)
; (find-formula-asst (make-and f) #f cur fail succeed)   == 
;                           (find-any-asst f #f cur fail succeed)


; (find-all-asst '()         bool cur fail succeed) == (succeed cur fail)
; (find-all-asst (cons f fs) bool cur fail succeed) == 
;           (find-formula-asst f bool cur
;                                fail 
;                                (lambda (cur fail)               
;                                   (find-all-asst fs bool cur fail succeed)))  


; (find-any-asst '()         bool cur fail succeed) == fail
; (find-any-asst (cons f fs) bool cur fail succeed) == 
;                       (find-formula-asst f bool cur
;                               (lambda ()
;                                   (find-any-asst fs bool cur fail succeed))
;                                succeed) 


; (find-formula-symbol x bool cur fail succeed) == 
;                                              (succeed (bind x bool cur) fail),
;                                                  where x is not bound in cur 
; (find-formula-symbol x bool cur fail succeed) == (succeed cur fail) , 
;                                                  where x is bool in cur 
; (find-formula-symbol x bool cur fail succeed) == (fail), 
;                                                  where x is (not bool) in cur

(define find-formula-true-asst (f fail succ)
    (letrec(
            [find-formula-asst 
                (lambda (f bool cur fail succeed)
                    (if (symbol? f)
                        (find-formula-symbol f bool cur fail succeed)
                            (if (not? f)
                                (find-formula-asst (not-arg f) (not bool) cur 
                                                                fail succeed)
                                (if (or? f)
                                    (if bool
                                        (find-any-asst (or-args f) #t cur 
                                                                fail succeed)
                                        (find-all-asst (or-args f) #f cur 
                                                                fail succeed))
                                    (if (and? f)
                                        (if bool
                                            (find-all-asst (and-args f) #t cur 
                                                                   fail succeed)
                                            (find-any-asst (and-args f) #f cur 
                                                                  fail succeed))
                                        (error 'invalid-form ))))))]       
            [find-all-asst 
                (lambda (f bool cur fail succeed)
                    (if (null? f)
                        (succeed cur fail)
                        (find-formula-asst (car f) bool cur 
                                            fail
                                            (lambda (cur fail)
                                                (find-all-asst (cdr f) bool cur 
                                                                fail 
                                                                succeed)))))]
            [find-any-asst 
                (lambda (f bool cur fail succeed)
                    (if (null? f)
                        (fail)
                        (find-formula-asst (car f) bool cur
                                            (lambda ()
                                                (find-any-asst (cdr f) bool cur 
                                                    fail 
                                                    succeed)) 
                                            succeed)))]
            [find-formula-symbol 
                (lambda (x bool cur fail succeed)
                    (if (not (bound? x cur))               
                        (succeed (bind x bool cur) fail)
                        (if (= bool (find x cur))
                            (succeed cur fail)
                            (fail))))])
        (find-formula-asst f #t '() fail succ)))


    ;; (test-cur-w/-eval f)
        ;;   Use eval-formula to test if environment made by 
        ;; find-formula-true-asst contains the formula 
        (val test-cur-w/-eval (lambda (f)
                                (eval-formula f (find-formula-true-asst f 
                                                    (lambda () 'no-solution )  
                                                    (lambda (env _ ) env))))) 

        ;; Test (basic)
        (check-assert (test-cur-w/-eval  'x ))
        (check-assert (test-cur-w/-eval  (make-not 'y )))
        (check-assert (test-cur-w/-eval  (make-or  (list2 'x 'y ))))
        (check-assert (test-cur-w/-eval  (make-and (list2 'x 'y ))))

        ;; Nested Cases
        (check-assert (test-cur-w/-eval  (make-not (make-not 'y ))))
        (check-assert (test-cur-w/-eval  (make-or  (make-not (make-not 'y )))))
        (check-assert (test-cur-w/-eval  (make-and (make-or  (make-not 'y )))))

       
    ;; Tests provided the assignment
        (use solver-interface-tests.scm)

    ;; Tests created by me
       (use solver-tests.scm)
        (check-expect (find-formula-true-asst f1  
                                              (lambda () 'no-solution ) 
                                              (lambda (env _ ) env))
                      s1)
        (check-expect (find-formula-true-asst f2  
                                              (lambda () 'no-solution ) 
                                              (lambda (env _ ) env)) 
                      s2)
        (check-expect (find-formula-true-asst f3  
                                              (lambda () 'no-solution ) 
                                              (lambda (env _ ) env)) 
                       s3)

        