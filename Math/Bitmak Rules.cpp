// a+b = 2(a&b) + a⊕b
// a+b = a|b + a&b

// a⊕b = ~(a&b) & (a∣b)

// a|b = a⊕b + a&b

// a⊕(a&b) = (a|b)⊕b

// b⊕(a&b) = (a|b)⊕a

// a⊕b = (a&b)⊕(a|b)

// a-b = (a⊕(a&b))-((a|b)⊕a)

// a-b = ((a|b)⊕b)-((a|b)⊕a)

// a-b = (a⊕(a&b))-(b⊕(a&b))

// a-b = ((a|b)⊕b)-(b⊕(a&b))




// abs( x - y ) = max(x - y , y - x)
