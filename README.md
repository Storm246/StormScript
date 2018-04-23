# General

## About

StormScript is an interpreted, object-oriented, free programming language. 

StormScript is programmed in C++ and is simple to use.

## Basics

StormScript was made on the idea that it is possible to have a strong, object-oriented programming language that has short, easy to remember syntax.

# The Language

## Files

StormScript files have the extension `.sts`
StormScript library files have the extension `.stslib`

## Commands

`do`: initial function

`end`: end current scope

`loop(n)`: loop current scope

### **_PUTTING A VARIABLE DEFINITION IN A LOOP IS BAD PRACTICE AND CAN CAUSE BUGS! DO NOT DO IT!_**

`int name: 0`: int creates an integer variable

`str name: "text"`: creates a string variable

`out var`: prints out

## Hello World Program

```
do{
  out "Hello, World";
}end;
```
