datatype sx = SYMBOL  of string
            | NUMBER  of int
            | BOOLEAN of bool
            | SXLIST  of sx list



     (val f1 (make-and (list1 'x )))
        (check-assert (test-cur-w/-eval f1))
        (check-expect  (find-formula-true-asst f1
                                    (lambda () 'no-solution )     
                                    (lambda (env _ ) env))
                        '((x #t)))

        (val f2 (make-and (list2 'x (make-not 'x ))))
        (check-expect  (find-formula-true-asst f2
                                    (lambda () 'no-solution )     
                                    (lambda (env _ ) env))
                        'no-solution )   


        (val f3 (make-or
                    (list2 (make-or (list2 'x 'y ))
                           (make-or (list2 (make-not 'x ) 'y )))))
        (check-assert (test-cur-w/-eval f3))
        (check-expect (find-formula-true-asst f3
                                    (lambda () 'no-solution )     
                                    (lambda (env _ ) env))
                      '((x #t)))
        