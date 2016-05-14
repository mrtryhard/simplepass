# simplepass
A simple password generator.

## What can it do
Generate random ascii passwords with given parameters.

## Using compiled binary
To compile with clang and C++14, use the `make` command provided.

```
simplepass -l [integer] -s -h
``` 

* `-l [integer]` Specifies the length of the string where `integer` must be greater than zero and at maximum uint16_t max (65-ish).
* `-s` When passed, allows special characters.
* `-h` When passed, shows help. 

## Using headers && cpp
```
#include "generator.hpp"
// ...
Generator g(length, allowSpecialChars); 
char *pass = g.generate(); 
/* You do not need to delete[] pass. When Generator goes out of scope, it will be freed. Be aware. */
```

## Goal 
Right now it is a very simple and naive password generator. 
The goal is to eventually integrate with the Budgie desktop (Solus OS).

## Recommended compilation settings
Works well with clang3.8+, with c++14 enabled. 

## Contributions 
Any contributions is welcome. Create an issue to be heard.