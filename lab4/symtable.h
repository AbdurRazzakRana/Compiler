/*
Filename: symtable.h
Author: Abdur Razzak
Date: Feb 18, 2024
Intentions: This header file will expose Insert, Search and Delete method as per checklist 5.
 It also added the structure defination of SymbTab as per task 3.
 Whoever includes this header, will inherit these method names automatically, however, that file
 has to write the function incomplete bodies.

Modifications:
 A. Lab 4 Specific:
   1. Exposing FeatchAddress() method
*/

struct SymbTab * Insert(char*, int);
struct SymbTab * Search(char*);
void Delete(char*);
int FeatchAddress(char*);
void Display();
struct SymbTab
{
 char *symbol;
 int addr;
 struct SymbTab *next;
};