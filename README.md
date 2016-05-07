# simplepass
A simple password generator.

## What can it do
Generate random ascii passwords with given parameters.

## How to use it
```
#include "generator.hpp"
// ...
Generator g(length, allowSpecialChars); 
char *pass = g.generate(); 
```

## Goal 
Right now it is a very simple and naive password generator. 
The goal is to eventually integrate with the Budgie desktop (Solus OS).

## Recommended compilation settings
Works well with clang3.8+, with c++14 enabled. 

## Contributions 
Any contributions is welcome. Create an issue to be heard.