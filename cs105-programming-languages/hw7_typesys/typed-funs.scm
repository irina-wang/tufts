;; exists p? xs
;;      takes in a function p? and a list xs
;;      returns false when given an empty list
(val
 exists?
 (type-lambda ['a] 
    (letrec [ ( [ exist? : (['a -> bool][list 'a] -> bool)]
                (lambda ([p? : ('a -> bool)]
                         [xs : (list 'a )])
                    (if ([@ null? 'a] xs)
                        #f
                        (if (p? ([@ car 'a] xs))
                            #t
                            (exist? p? ([@ cdr 'a] xs))))))]
            exist?))) 

        (val positive? (lambda ([x : int]) (> x 0)))
        (val exists-int? [@ exists? int])

        (not (exists-int? positive? '(-9 -2 0 -4)))
        (exists-int? positive? '(1 -2 -3 -4))

