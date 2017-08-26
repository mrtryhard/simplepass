# simplepass
A regex-like-based password generator. 

## Example
### Custom Rule
"Password that starts with three capitalized letters, followed by one number then followed by any ascii character 5 up to 10 times".  
*This is an example, and may not be the most secure password*.  
```simplepass [A-Z]{3}[0-9][a-zA-Z0-9]{5-10}```  
```DJF8SXcOm7265f```

### Simple / Naive
```simplepass -l 20 -s```  
```yPKt~QRL,DCHt)Gj*:[!```

## Goal
Got tired of thinking and generating hand made passwords for websites.
Also, it is easier to trust a randomly-generated password rather than a
predefined one.

## Documentation 
See this repo's wiki. Detailed documentation is available. 

## Generating and using an executable
To compile with clang and C++14, use the makefile provided.  
To compile with Visual Studio, Visual Studio Community 2017 recommended.

```
simplepass -r <rule> | -l <integer> -s -h 
``` 

* `-l <integer> | --length <integer>` Specifies the length of the string where `integer` must be greater than zero and at maximum uint16_t max (65 000-ish).
* `-s | --specials` When passed, allows special characters.
* `-r <rule> | --rule <rule>` Specifies the rule to generate password. Disregards `-l` and `-s` options.  
* `-h | --help` When passed, shows help. 

## Recommended compilation settings  
Works well with Visual Studio Community 2017 (msvc++ and clang3.8).

## Contributions 
Any contributions is welcome. Create an issue to be heard.
