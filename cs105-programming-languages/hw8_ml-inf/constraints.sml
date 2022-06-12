val constraints =
[ TYVAR "a" ~ TYCON "bool" /\ TYVAR "a" ~ TYCON "int",

  CONAPP (TYCON "list", [TYCON "bool"]) ~ TYCON "bool",

  CONAPP (TYCON "pair", [TYVAR "a", TYCON "bool"]) ~ 
  CONAPP (TYCON "pair", [TYVAR "b"])
]
