/* Funciton prototype handling c code
This code will keep track how many functions are declared as prototype,
how many of them later implemented.
If there any function is being called and the function is not implemented,
the program should barf

Author: Abdur Razzak
Date: May 3, 2024.
Lab: 9
*/
#include <stdio.h>
// #include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "prototype.h"

/* Insert prototype function into the table */

// PRE:  given elements for an item in the function prototype list
//  POST:  Inserts an item in the prototype table list provided
struct Func_Prototype *Insert_Proto(char *name, int value, int level)
{
 struct Func_Prototype *n = Search_Proto(name);
 if (n != NULL)
 {
  printf("\n\tThe name %s exists at level %d already in the prototype table\n\tDuplicate can't be inserted\n", name, level);
  return (NULL);
 }
 else
 { // insert the prototye into the list
  struct Func_Prototype *p = malloc(sizeof(struct Func_Prototype));
  p->name = name;
  p->level = level; /* assign the level */
  p->value = -1;    // -1 means prototype declared
  p->next = NULL;

  if (first_Proto == NULL)
  {
   first_Proto = p;
  }
  else
  {
   // setting into the list
   p->next = first_Proto;
   first_Proto = p;
  }
  return (p);
 }
}

/* Insert function call to keep track of function prototye into the table */

// PRE:  given elements for an item in the function call list
//  POST:  Inserts an item in the call table list provided
struct Func_Call *Insert_Func_Call(char *name, int line_number)
{
 struct Func_Call *fc = malloc(sizeof(struct Func_Call));
 fc->name = name;
 fc->line_number = line_number;
 fc->next = NULL;
 if (first_Func_Call == NULL)
 { // when no items in the list
  first_Func_Call = fc;
  return fc;
 }

 // if the function is already in call stack, we don't need to keep it on call stack again
 struct Func_Call *p = first_Func_Call;
 struct Func_Call *prev;
 while (p != NULL)
 { // no need to insert if its alaready into the list
  if ((strcmp(p->name, name) == 0))
   return p;
  prev = p;
  p = p->next;
 }
 // function has not called yet, this is first time called
 prev->next = fc;
 return fc;
}

// PRE:   given a name and level to search
//  POST:  returns NULL if not there, otherwise a PTR to the element in the table
// DETAIL:  Will be searching until the end of the list with the name and level
// Search if the prototype is exists
struct Func_Prototype *Search_Proto(char name[])
{
 struct Func_Prototype *p;
 p = first_Proto;
 while (p != NULL)
 {
  if ((strcmp(p->name, name) == 0))
   return p;
  p = p->next;
 }
 return NULL; /* items not found */
}

// PRE:   will recieve funciton prototype object that is intended to delete
//  POST:  from prev->fp->next, the list will be prev->next
// DETAIL: the object will be skipped from next chain as it is already declared fucntion, not a prototype anymore
void Delete_Proto(struct Func_Prototype *fp)
{
 if (fp == first_Proto)
 {
  first_Proto = fp->next;
  return;
 }
 struct Func_Prototype *p = first_Proto->next;
 struct Func_Prototype *prev = first_Proto;
 while (p != NULL)
 { // search until to the end of list
  if (p->name == fp->name)
  {
   prev->next = p->next;
   return;
  }
  prev = p;
  p = p->next;
 }
 // printf("Prototype %s not found, NO DELETE OPS\n", fp->name);
 return;
}

/*Helper function to check any prototyped functions that does not have declaration, gets any call or not*/
// PRE: gets the undeclared prototype count
// POST:
//  Func_call object returns that contains name and line numbers of the function call
//  Null if prototype functions does not get calls
struct Func_Call *check_proto_gets_called(int totoalPrototypeLeft)
{
 struct Func_Prototype *protoHead = first_Proto;
 struct Func_Call *callHead = first_Func_Call;
 // for each leftover prototyped function, checking the call list of that function name
 while (totoalPrototypeLeft--)
 {
  if (callHead == NULL || protoHead == NULL)
   break;
  struct Func_Call *p = callHead;
  while (p != NULL)
  {
   if ((strcmp(p->name, protoHead->name) == 0)) // matched the name
   {
    return p;
   }
   p = p->next;
  }
  protoHead = protoHead->next;
 }
 return NULL;
}