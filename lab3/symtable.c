/*
Code Collected: https://forgetcode.com/C/101-Symbol-table
Edited By: Abdur Razzak
Date: Feb 7, 2024
Lab Title: LAB 3 -- Symbol Table Tools
Modificattions:
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
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
/*symtable.h header file added*/
#include "symtable.h"
int size = 0;

/* Added function paramenter in Delete method.
As per instruction 8a, user input only allowed in main method, therefore passing the symbol as parameter*/


/* As per instruction 3, created symbtab.h file and exposed 
the Insert, Search and struct definition from there. */

void Display();

struct SymbTab *first, *last;

/*The is the main method that gets call when the program executes
It the only method that takes user input and calles necessary functions based on user operation selection*/

/*changed return type from void to int to avoid warning and errors*/
int main()
{
    int op, y;
    char la[100];
    /* This do while loop will continously take user input untill user press 6 or hit eof*/
    do
    {
        printf("\n\tSYMBOL TABLE IMPLEMENTATION\n");
        printf("\n\t1.INSERT\n\t2.DISPLAY\n\t3.DELETE\n\t4.SEARCH\n\t6.END\n");
        printf("\n\tEnter your option : ");
        scanf("%d", &op);
        // This switch case will decide operation based on user input. For example, case-1 for insertation.
        switch (op)
        {
        case 1: // Case 1 is for inserting a symble and address into the symbol table
            // As we can only take input from main method, inputs are taken here
            printf("\n\tEnter the symbol : ");
            scanf("%s", la);
            y = Search(la);
            // if the items is found into the current symbol table, it will return 1, no need to insert.
            // if its 0, that  means else will executed and insert the object.
            if (y == 1)
                printf("\n\tThe symbol exists already in the symbol table\n\tDuplicate can.t be inserted");
            else {
                printf("\n\tEnter the address : ");
                scanf("%d", &y);
                // calling the insert method with symbol and address parameter
                Insert(la, y);
            }
            break;
        case 2:  // Case 2 is for displaying symbols and addresses the object
            Display();
            break;
        case 3:  // This case is for Searching the symbol in to the table
            // in order to delete symbol, we need to take input of symbol and taking the input into the main method and calling
            printf("\n\tEnter the symbol to be deleted : ");
            scanf("%s", la);
            y = Search(la);
            // if y=0, that means the syble is not there in the table. Nothing to delete.
            // else y =1 means, Item is already found, ready to delete the item. 
            if (y == 0)
                printf("\n\tSymbol not found\n");
            else
                Delete(la);
            break;
        case 4: // This case is responsible for Searching the item from the symble table.
            printf("\n\tEnter the symbol to be searched : ");
            scanf("%s", la);
            y = Search(la);
            printf("\n\tSearch Result:");
            // if y=1, that means the symbol is in the table.
            // else y =1 means, Item is already found, ready to delete the item. 
            if (y == 1)
                printf("\n\tThe symbol is present in the symbol table\n");
            else
                printf("\n\tThe symbol is not present in the symbol table\n");
            break;
        case 6: // this case is for exit
            exit(0);
        }
    } while (op < 6);

} /* end of main */

/*Insert method is responsible to insert the symbol and the addess into the symble table.
Input: 2, a symble and an address
Output: Does not return anything, just prints "Symbol inserted", if the symbol is successfully inserted into the table.
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
void Insert( char *symbol, int address)
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
int Search(char *symbol)
{
    int i, flag = 0;
    struct SymbTab *p;
    p = first;
    // This loop will search the symbol from the table be looking up each object fro link list
    for (i = 0; i < size; i++)
    {
        // checks if the p->symble and lookup char stirng is equal or not
        if (strcmp(p->symbol, symbol) == 0)
            flag = 1;
        p = p->next;
    }
    return flag;
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
