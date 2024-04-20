/*
Code Collected: https://forgetcode.com/C/101-Symbol-table
Edited By: Abdur Razzak
Date: Feb 18, 2024
Lab Title: LAB 4
Modificattions:
    A. Lab 4 Specific Modifications:
        1. Introduced FeatchAddress method which will take input string, 
            a target variable to look for and will return the address of that varialbe 

    B. Previous Modifications:
        Removed MODIFY completely
            1. The indentation of the code is corrected. Also comments are made.
            2a. Removed all occurrence of 'label' and changed symbol[10] 
                to *symbol in symtable.h file at struct defination.
            2b. Insert and Search method are introduced parameters (char *symbol, int address) and (char *symbol ) respectively.
                Because all the input are allowed to take inside main method and passed through parameters.
                Insert method used strdup() built in method to copy the symbol into pointer's symbol.
            3. Created symbletable.h file; exposed insert, search and struct SymbTab defination from that file.
            4. Added that .h file here.
            8. header file is created with all of the method prototype.
            8a. Since we are not allowed to take input outside main, introduced function parameters to pass required valus from main.

        Answer to the questions:
            5. Added the runtime screenshots into the pdf file
            6. Main data structure of this code is structure poniter. There are 3 fields in each SymbTab object.
                A pointer variable symbol to hold char array, an integer variable address and a SymbTab pointer variable
                to point to next object. There are two such SymbTab pointer variable is used to keep track of first and
                last objects of the list. FOr example if there are 3 such objects, it will be build such as A -> B -> C.
                A->next is B, B->next is C and C->next is Null. 'first' pointer will be pointed to A and the 'last' pointer
                will be pointed to C.

            7. malloc() is an in-build method allocate memory dynamically in the heap for an object with specific size 
                and returns a pointer that address that memory block. For example, struct SymbTab *p, will create null pointer to p.
                When it calles malloc(sizeof(struct SymbTab)), it receives a physical memory reference of size SymbTab having
                3 fields init.
        Checklist:
            1. Commented out before each function header.
            2. insertion process, first, last pointer variables are explained
            3. Removed the label completely
            4. main is only taking the inputs and called the required methods with necessary parameters passing
            5. Insert and Search and Delete are exposed from symtable.h file
            6. both c and h header files are commented
            7. make file running properly and cmmented
            8. lab3.pdf added
            9. PRE, POST added
            10. while/if/for statements are commented
            11. symbol array are changed to pointer
            12. stdup() is used
            13. input symbols has s[100] length.

*/

#include <stdio.h>
/* #include<conio.h> */
// #include <malloc.h>
#include <string.h>
#include <stdlib.h>

/*symtable.h header file added*/
#include "symtable.h"
int size = 0;

/* Added function paramenter in Delete method.
As per instruction 8a, user input only allowed in main method, therefore passing the symbol as parameter*/


/* As per instruction 3, created symbtab.h file and exposed 
the Insert, Search and struct definition from there. */

struct SymbTab *first, *last;

/*Insert method is responsible to insert the symbol and the addess into the symble table.
Input: 2, a symble and an address
Output: return the pointer position of the newly inserted object, 
    prints "Symbol inserted", if the symbol is successfully inserted into the table.
Process: 
    first, it will allocate the memory for a structure SymbTab and put the reference into p.
    then, the symbol and address are set the SymbTab symbol and address variable and set the next pointer to null.
    There are two pointer variable first and last, first will point to the first element of the linked list
    the last will point to the last element of the linked list.
    When there is only one object, both first and last will point to the same object, however, if there are more than 
    one objects in the list, then the current last's next object is set to p and p is then the new last.
PRE Ptr: first character string
POST PTR: first character string fi there no elements before or last elements if there were items previously
*/
struct SymbTab * Insert( char *symbol, int address)
{
    struct SymbTab *p;
    // allocating memory for p ponter variable with the size of SymbTab
    p = malloc(sizeof(struct SymbTab));

    // assigning the values into the pointer
    p->symbol = strdup(symbol);
    p->addr = address;
    p->next = NULL;

    // if size = 0, that means the list is only 1 item and hence both first and last ponter will point same object
    // else the object is set to the last pointer
    if (size == 0)
    {
        first = p;
        last = p;
    }
    else
    {
        last->next = p;
        last = p;
    }
    size++;
    printf("\n\tSymbol inserted\n");
    
    return last;
}

/* The Display method displays the current symbol table.
It does not take any input and also return nothing.
Just printing the table is the task of this method
PRE Ptr: first character string
POST PTR: NULL
*/
void Display()
{
    int i;
    struct SymbTab *p;
    p = first;
    printf("\n\tSYMBOL\t\tADDRESS\n");
    // This loop is responsible to traverse the ponter from first to last
    for (i = 0; i < size; i++)
    {
        printf("\t%s\t\t%d\n", p->symbol, p->addr);
        p = p->next;
    }
}

/*The intention of Search method to search the given symbol from the address table.
If the address is found, it returns 1, otherwise, if not found, it returns 0.
Input: the symbol to search
output: 0 if its not found in the table. 1 if the address is found.
PRE Ptr: character string
POST PTR: matching structure or NULL
*/
struct SymbTab * Search (char *symbol)
{
    int i, flag = 0;
    struct SymbTab *p;
    p = first;
    // This loop will search the symbol from the table be looking up each object fro link list
    for (i = 0; i < size; i++)
    {
        // checks if the p->symble and lookup char stirng is equal or not
        if (strcmp(p->symbol, symbol) == 0){
            return p;
        }
        p = p->next;
    }
    return p;
}

/*This method is responsible to delete a symbol from the symbol table
Input: takes the symbol that need to be deleted
Output: nothing, it just prints the output symbol table to make understand the item is deleted successfully
PRE Ptr: first character string
POST PTR: NULL or previous string of the item is just deleted
*/
void Delete(char *symbol)
{
    struct SymbTab *p, *q;
    p = first;
    // if the object found it at the begining, it will consider 2nd object as the first one 
    if (strcmp(first->symbol, symbol) == 0)
        first = first->next;
    else if (strcmp(last->symbol, symbol) == 0)
    {
        q = p->next;
        // this loop is responsible to find the position of the symbol at the end from the table
        while (strcmp(q->symbol, symbol) != 0)
        {
            p = p->next;
            q = q->next;
        }
        p->next = NULL;
        last = p;
    }
    else
    {
        q = p->next;
        // this loop will find the element from the middle of the list and delete from there
        while (strcmp(q->symbol, symbol) != 0)
        {
            p = p->next;
            q = q->next;
        }
        p->next = q->next;
    }
    size--;
    printf("\n\tAfter Deletion:\n");
    Display();
}

/*
(6 of lab4)
The FeatchAddress method is responsible get the address of a variable that
is listed in symbol table.

Input: takes the name of the variable as a string
Output: integer address of that variable.
PRE Ptr: first symbol object
POST PTR: The object where the target symbol is found
*/
int FeatchAddress(char *s){
    // Check if the variable is null.
    if (s == NULL){
        // variable is null, barf
        printf("\n----BARF------\nVariable is null\n");
        exit(0);
    }
    int i;
    struct SymbTab *p;
    p = first;
    // Search the location of the symbol in linked list, if found, return the address
    for (i = 0; i < size; i++)
    {
        // checks if the p->symble and lookup char stirng is equal or not
        if (strcmp(p->symbol, s) == 0){
            return p->addr;
        }
        p = p->next;
    }

    // This line should not be executed as we called Search beofre calling FeatchAddress.
    // However, putting exit because otherwise since we defined a return type 
    // "int FeatchAddress" as an int, we need to return something.
    exit(1);
}