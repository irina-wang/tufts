; TODO: mark as private
(use big-num.smt)

(class LargeInteger
    [subclass-of Integer]
    [ivars magnitude]

    ; 啊啊啊啊

    (class-method withMagnitude: (aNatural)
        ((self new) magnitude: aNatural))
    (method magnitude: (aNatural) ; private, for initialization
        (set magnitude aNatural)
        self)

    (class-method fromSmall: (anInteger)
      ((anInteger isNegative) ifTrue:ifFalse:
          {(((self fromSmall: 1) + (self fromSmall: ((anInteger + 1) negated)))
              negated)}
          {((LargePositiveInteger new) magnitude: (Natural fromSmall: anInteger))}))

    (method print () (self subclassResponsibility))

    (method isNegative () (self subclassResponsibility))
    (method isNonnegative () ((self isNegative) not))
    (method isStrictlyPositive () ((self isNonnegative) and: (self isZero)))

    (method magnitude () magnitude)

    (method asLargeInteger () self)
    (method isZero () (magnitude isZero))  ; private
    (method = (anInteger) ((self - anInteger)     isZero))
    (method < (anInteger) ((self - anInteger) isNegative))

    (method - (anInteger) (self + (anInteger negated)))

    (method div: (n) (self sdiv: n))
    (method mod: (_) (self error: 'long-division-not-supported ))

    (method decimal () (self subclassResponsibility)) ; private
    (method print () ((self decimal) do: [block (x) (x print)]))

    (method sdiv: (aSmallInteger) (self leftAsExercise))
    (method smod: (aSmallInteger)
        (self -
            ((self sdiv: aSmallInteger) *
             (LargeInteger fromSmall: aSmallInteger))))
)

(class LargePositiveInteger
    [subclass-of LargeInteger]

    ; A (self) = magnitude
    ; invariant message
    (method invariant () true) ; private

    (method decimal ()
        (magnitude decimal))

    (method isNegative () false)

    (method negated () (LargeNegativeInteger withMagnitude: magnitude))

    (method + (anInteger) ; TODO: allow small int
        (anInteger addLargePositiveIntegerTo: self))

    (method addSmallIntegerTo: (aSmallInteger)
        ((LargeInteger fromSmall: aSmallInteger) addLargePositiveIntegerTo: self))

    (method addLargePositiveIntegerTo: (aLargePositiveInteger)
        (LargePositiveInteger withMagnitude:
            (magnitude + (aLargePositiveInteger magnitude))))

    (method addLargeNegativeIntegerTo: (aLargeNegativeInteger)
        [locals neg_mag pos_mag]
        (set neg_mag (aLargeNegativeInteger magnitude))
        (set pos_mag magnitude)
        ((pos_mag > neg_mag) ifTrue:ifFalse:
            {(LargePositiveInteger withMagnitude: (pos_mag - neg_mag))}
            {(LargeNegativeInteger withMagnitude: (neg_mag - pos_mag))}))

;;;;; *
    (method * (anInteger)
        (anInteger multiplyByLargePositiveInteger: self))

    (method multiplyBySmallInteger: (aSmallInteger) ;TODO coerce
        ((LargeInteger fromSmall: aSmallInteger) multiplyByLargePositiveInteger: self))

    (method multiplyByLargeNegativeInteger: (aLargeNegativeInteger)
        (LargeNegativeInteger withMagnitude:
            (magnitude * (aLargeNegativeInteger magnitude))))

    (method multiplyByLargePositiveInteger: (aLargePositiveInteger)
        (LargePositiveInteger withMagnitude:
            (magnitude * (aLargePositiveInteger magnitude))))
;;;;;; *
    ; provided code, but changed isStrictlyPositive to isNonnegative in order to
    ; pass div 0 to Natural class (which will throw an error)
    (method sdiv: (anInteger)
        ((anInteger isNonnegative) ifTrue:ifFalse:
            {(LargePositiveInteger withMagnitude:  (magnitude sdiv: anInteger))}
            {((((self - (LargeInteger fromSmall: anInteger)) - (LargeInteger fromSmall: 1))
                sdiv: (anInteger negated))
                negated)}))
)


(class LargeNegativeInteger
    [subclass-of LargeInteger]

    ; A (self) = - magnitude
    ; invariant message
    (method invariant () true) ; private

    (method negated () (LargePositiveInteger withMagnitude: magnitude))

    ;;;; +
    (method + (anInteger) ; TODO: allow small int
        (anInteger addLargeNegativeIntegerTo: self))

    (method addSmallIntegerTo: (aSmallInteger) ;TODO coerce
        ((LargeInteger fromSmall: aSmallInteger) addLargeNegativeIntegerTo: self))

    (method addLargeNegativeIntegerTo: (aLargeNegativeInteger)
        (LargeNegativeInteger withMagnitude:
            (magnitude + (aLargeNegativeInteger magnitude))))

    (method addLargePositiveIntegerTo: (aLargePositiveInteger)
        [locals neg_mag pos_mag]
        (set pos_mag (aLargePositiveInteger magnitude))
        (set neg_mag magnitude)
        ((pos_mag > neg_mag) ifTrue:ifFalse:
            {(LargePositiveInteger withMagnitude: (pos_mag - neg_mag))}
            {(LargeNegativeInteger withMagnitude: (neg_mag - pos_mag))}))
    ;;;; end +

    ;;;; *
    (method * (anInteger)
        (anInteger multiplyByLargeNegativeInteger: self))

    (method multiplyBySmallInteger: (aSmallInteger) ;TODO coerce
        ((LargeInteger fromSmall: aSmallInteger) multiplyByLargeNegativeInteger: self))

    (method multiplyByLargeNegativeInteger: (aLargeNegativeInteger)
        (LargePositiveInteger withMagnitude:
            (magnitude * (aLargeNegativeInteger magnitude))))

    (method multiplyByLargePositiveInteger: (aLargePositiveInteger)
        (LargeNegativeInteger withMagnitude:
            (magnitude * (aLargePositiveInteger magnitude))))
    ;;;; end *

    (method decimal ()
        ((magnitude isZero) ifTrue:ifFalse:
            {(magnitude decimal)}
            {((magnitude decimal) addFirst: '- )}))

    (method isNegative () ((self isZero) not))

    (method sdiv: (anInteger)
      ((self negated) sdiv: (anInteger negated)))

)
