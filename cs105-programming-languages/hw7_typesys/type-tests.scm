
;; Test 1: y not found in env
(check-type-error (lambda ((x : list)) y))       

;; Test 2: begin with all literals; return the last type
(check-type (begin 1 0 #f) bool)  

;; Test 3: begin with all literals; return the last type
(check-type-error (let* ([y z]) y))                  
(check-type   (let* ([x #f] [y  x]) (and x y)) bool)


;; Extra tests
(check-type (begin ) unit)
(check-type cons (forall ('a) ('a (list 'a) -> (list 'a)))) 
(check-type (@ car int) ((list int) -> int))
(check-type
(type-lambda ['a] (lambda ([x : 'a]) x))
(forall ('a) ('a -> 'a)))
(check-type-error (+ 1 #t)) ; extra example 
(check-type-error (lambda ([x : int]) (cons x x))) ; another extra example