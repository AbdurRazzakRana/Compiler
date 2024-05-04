
/* Function prototype handling code
Header file
Author: Abdur Razzak
Date: April 21, 2024.
Lab: 9
The purpose of keeping this prototyping handling file is
a. function can be prototype and implemented later
b. even after the call, funciton may get declared later on
c. checking the parameters of prototyped function and declared functions
d. making it separate helps in clean coding to implement separate concept into separate file
*/
#ifndef _PROTOTYPE
#define _PROTOTYPE
#include <stdio.h>
// #include <malloc.h>
#include <stdlib.h>

// structure to hold function prototype
struct Func_Prototype
{
 char *name; // name of the prototype function
 int value;  // status of prototyped funtion
 int level;  // function prototype should always at level 0, however keeping this variable for future need purpose
 struct Func_Prototype *next;
};
// struct to store function call with name and line number of where the function get called
struct Func_Call
{
 char *name;             // name of the function call
 int line_number;        // line number of function call
 struct Func_Call *next; // next function call object
};

struct Func_Prototype *Insert_Proto(char *name, int value, int level); // insert into table of function prototype
struct Func_Call *Insert_Func_Call(char *name, int line_number);       // insert into table of function call list

struct Func_Prototype *Search_Proto(char *name); // search if a name is exist in function prototype table
void Delete_Proto(struct Func_Prototype *fp);    // Delete a prototype instance from table once it is implemented

static struct Func_Prototype *first_Proto = NULL; /* global pointers into the function prototype table */
static struct Func_Call *first_Func_Call = NULL;  /* global pointers into the function call table */

struct Func_Call *check_proto_gets_called(int totoalPrototypeLeft); // checker function if there any prototyped functions get called

#endif