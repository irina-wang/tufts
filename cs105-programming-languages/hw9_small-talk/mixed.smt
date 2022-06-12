(use large-int.smt)

(class NewSmallIntegerMethods
    [subclass-of Object]

    (method asLargeInteger () (LargeInteger fromSmall: self))

    (method + (aNumber) (aNumber addSmallIntegerTo: self))
    (method addSmallIntegerTo: (anInteger)
        ((primitive addWithOverflow self anInteger
            {((self asLargeInteger) + anInteger)}) value))
    (method addLargeNegativeIntegerTo: (aLargeNegativeInteger)
        ((self asLargeInteger) + aLargeNegativeInteger))
    (method addLargePositiveIntegerTo: (aLargePositiveInteger)
        ((self asLargeInteger) + aLargePositiveInteger))
    
    (method - (aNumber) (self + (aNumber negated)))
    (method negated () 
        ((primitive subWithOverflow 0 self
            {((LargeInteger fromSmall: 0) - (self asLargeInteger))}) value))
    
    (method * (aNumber) (aNumber multiplyBySmallInteger: self))
    (method multiplyBySmallInteger: (aSmallInteger)
        ((primitive mulWithOverflow self aSmallInteger
            {((self asLargeInteger) * aSmallInteger)}) value))
    (method multiplyByLargePositiveInteger: (aLargePositiveInteger)
        ((self asLargeInteger) * aLargePositiveInteger))
    (method multiplyByLargeNegativeInteger: (aLargeNegativeInteger)
        ((self asLargeInteger) * aLargeNegativeInteger))
    
    (method sdiv: (d) (self div: d))
    (method smod: (d) (self mod: d))
)

;; since addAllMethodsFrom was not provided, we did our own one:
(class NewObjectMethods
    [subclass-of Object]
    (method addAllMethodsFrom: (aClass)
        [locals objectMethods aCompiledMethod]
        (set objectMethods (Object methodNames))
        ((aClass methodNames) do:
            [block (aMethod) 
                ((objectMethods includes: aMethod) ifFalse:
                    {(set aCompiledMethod (aClass compiledMethodAt: aMethod))
                    (self addSelector:withMethod: aMethod aCompiledMethod)})])
        aClass))

(Object addSelector:withMethod: 'addAllMethodsFrom: (NewObjectMethods compiledMethodAt: 'addAllMethodsFrom: ))

(SmallInteger addAllMethodsFrom: NewSmallIntegerMethods)
