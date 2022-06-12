;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;
;;;; Code copied from predefined.smt

(class Magnitude
    [subclass-of Object] ; abstract class
    (method =  (x) (self subclassResponsibility)) ; may not inherit
    (method <  (x) (self subclassResponsibility))
    (method >  (y) (y < self))
    (method <= (x) ((self > x) not))
    (method >= (x) ((self < x) not))
    (method min: (aMagnitude)
       ((self < aMagnitude) ifTrue:ifFalse: {self} {aMagnitude}))
    (method max: (aMagnitude)
       ((self > aMagnitude) ifTrue:ifFalse: {self} {aMagnitude}))
)

(class Natural
    [subclass-of Magnitude]
    [ivars base]

    ; I (self) = base <= sqrt(int_max)

    (class-method new () ((super new) init))
    (method init () (set base 32768) self) ; private

    (class-method fromSmall: (anInteger) 
        ((anInteger >= 0) ifTrue:ifFalse:
        {((self new) fmSmall: anInteger)}
        {(self error: 'natural-cant-be-negative )}))
    (method fmSmall: (anInteger) ; private, for initialization
        ((anInteger = 0) ifTrue:ifFalse:
            {(NatZero new)}
            {(NatNonZero first:rest:
                (anInteger mod: base)
                (Natural fromSmall: (anInteger div: base)))}))

    (method = (aNatural)
        (self compare:withLt:withEq:withGt:
            aNatural {false} {true} {false}))
    (method < (aNatural)
        (self compare:withLt:withEq:withGt:
            aNatural {true} {false} {false}))

    (method + (aNatural) (self plus:carry: aNatural 0))
    (method * (aNatural) (self subclassResponsibility))
    (method - (aNatural)
        (self subtract:withDifference:ifNegative:
            aNatural
            [block (x) x]
            {(self error: 'Natural-subtraction-went-negative )}))
    (method subtract:withDifference:ifNegative: (aNatural diffBlock exnBlock)
        ((self < aNatural) ifTrue:ifFalse:
            {(exnBlock value)}
            {(diffBlock value: (self minus:borrow: aNatural 0))}))

    (method sdiv: (n) (self sdivmod:with: n [block (q r) q]))
    (method smod: (n) (self sdivmod:with: n [block (q r) r]))
    (method sdivmod:with: (n aBlock) (self subclassResponsibility))

    (method decimal ()
        [locals lst remaining_num]
        (set lst (List new))
        (set remaining_num self)
        ((self isZero) ifTrue:ifFalse:
            {(lst addLast: 0)}
            {({(remaining_num isZero)} whileFalse:
                {(remaining_num sdivmod:with: 10
                    [block (q r) 
                        (lst addFirst: r)
                        (set remaining_num q)])})})
        lst)

    (method isZero  () (self subclassResponsibility))

    (method print   () ((self decimal) do: [block (x) (x print)]))
)


(class NatZero
    [subclass-of Natural]

    ; A (self) = 0
    ; invariant message
    (method invariant () true) ; private

    (method isZero () true)

    (method * (_) self)

    (method modBase () 0)       ; private
    (method divBase () self)    ; private
    (method timesBase () self)  ; private

    (method plus:carry: (aNatural c)  ; private
        ((c = 0) ifTrue:ifFalse:
            {aNatural}
            {(aNatural plus:carry: (NatNonZero first:rest: 1 self) 0)}))
    (method minus:borrow: (aNatural c)  ; private
        (((c = 0) & (aNatural isZero)) ifTrue:ifFalse:
            {self}
            {(self error: 'result-is-negative )}))

    (method sdivmod:with: (n aBlock)
        ((n = 0) ifTrue:ifFalse:
            {(self error: 'division-by-zero )}
            {(aBlock value:value: self 0)}))

    (method compare:withLt:withEq:withGt: (aNatural ltBlock eqBlock _) ; private
        ((aNatural isZero) ifTrue:ifFalse: eqBlock ltBlock))
)

(class NatNonZero
    [subclass-of Natural]
    [ivars first rest] ; first is least significant digit; rest is the other
    
    ; A (self) = first + rest * base
    ; invariant message
    (method invariant () ((first < base) and: (rest invariant))) ; private

    (class-method first:rest: (anInteger aNatural)
        (((aNatural isZero) and: {(anInteger = 0)}) ifTrue:ifFalse:
            {aNatural}
            {((self new) first:rest: anInteger aNatural)}))
    (method first:rest: (anInteger aNatural)   ; private
        (set first anInteger)
        (set rest aNatural)
        self)

    (method modBase () first)                  ; private
    (method divBase () rest)                   ; private
    (method timesBase () (NatNonZero first:rest: 0 self))    ; private

    (method compare:withLt:withEq:withGt: (aNatural ltBlock eqBlock gtBlock)
        (rest compare:withLt:withEq:withGt:
            (aNatural divBase)
            ltBlock
            {((first = (aNatural modBase)) ifTrue:ifFalse:
                eqBlock
                {((first < (aNatural modBase)) ifTrue:ifFalse:
                    ltBlock gtBlock)})}
            gtBlock))

    (method plus:carry: (aNatural c)      ; private
        [locals sum first_new carry]
        (set sum ((first + c) + (aNatural modBase)))
        (set first_new (sum mod: base))
        (set carry (sum div: base))
        (NatNonZero first:rest: first_new (rest plus:carry: (aNatural divBase) carry)))

    (method minus:borrow: (aNatural b)     ; private
        [locals diff first_new b_new]
        (set diff ((first - b) - (aNatural modBase)))
        (set first_new (diff mod: base))
        ((diff < 0) ifTrue:ifFalse: 
            {(set b_new 1)
             (set diff (diff + base))}
            {(set b_new 0)})
        (NatNonZero first:rest: first_new (rest minus:borrow: (aNatural divBase) b_new)))

    (method * (aNatural)
        [locals a b c d]
        ;  self     *  aNatural
        ; (10a + b) * (10c + d) = 100ac + 10ad + 10bc + bd
        (set a rest)
        (set b first)
        (set c (aNatural divBase))
        (set d (aNatural modBase))
        (((Natural fromSmall: (b * d)) + ((c * (Natural fromSmall: b)) timesBase)) +
         (((a * (Natural fromSmall: d)) timesBase) + (((a * c) timesBase) timesBase))))

    (method isZero () false)

    (method sdivmod:with: (aSmallInteger aBlock)
        [locals curdigit q r]
        (rest sdivmod:with: aSmallInteger
            [block (q2 r2)
                (set curdigit ((r2 * base) + first))
                (set q (curdigit div: aSmallInteger))
                (set r (curdigit mod: aSmallInteger))
                (aBlock value:value: (NatNonZero first:rest: q q2) r)]))
)

