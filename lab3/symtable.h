/*
Filename: symtable.h
Author: Abdur Razzak
Date: Feb 7, 2024
Intentions: This header file will expose Insert, Search and Delete method as per checklist 5.
 It also added the structure defination of SymbTab as per task 3.
 Whoever includes this header, will inherit these method names automatically, however, that file
 has to write the function incomplete bodies.
*/

void Insert(char*, int);
int Search(char*);
void Delete(char*);
struct SymbTab
{
 char *symbol;
 int addr;
 struct SymbTab *next;
};