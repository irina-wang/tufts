; Template for SAT Solver Test Cases 

(record not [arg])   ;; OK if these are duplicates
(record or  [args])
(record and [args])


; make-and only takes in one element list
(val f1 (make-and (list1 'x )))
(val s1 '((x #t)))   

; complementary values with and (x and not x) results in no-solution
(val f2 (make-and (list2 'x (make-not 'x ))))       
(val s2 'no-solution )

; More than one solution exists; s3 should be the first valid solution
(val f3 (make-or (list2 (make-or (list2 'x 'y ))
                        (make-or (list2 (make-not 'x ) 'y )))))
(val s3 '((x #t)))

