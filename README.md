# simplepass
A simple password generator.

## What can it do
Generate random ascii passwords with given parameters.

## Documentation 
See this repo's wiki. Detailed documentation is available. 

## Generating and using an executable
To compile with clang and C++14, use the makefile provided.  
To compile with Visual Studio, Visual Studio Community 2015 recommended.

```
simplepass -r [rule] -l [integer] -s -h 
``` 

* `-l [integer]` Specifies the length of the string where `integer` must be greater than zero and at maximum uint16_t max (65 000-ish).
* `-s` When passed, allows special characters.
* `-r [rule]` Specifies the rule to generate password. Disregards `-l` and `-s` options.  
* `-h` When passed, shows help. 

`simplepass -l 20 -s` is equivalent to `simplepass -r "\.{20}"`.

## Interfacing 
See wiki/Interfacing-into-code

## Goal 
Right now it is a very simple and naive password generator. 
The goal is to eventually integrate with the Budgie desktop (Solus OS).

## Recommended compilation settings
Works well with clang3.8+, with c++14 enabled.  
Works well with Visual Studio Community 2015 (msvc++ and clang3.7).

## Contributions 
Any contributions is welcome. Create an issue to be heard.
