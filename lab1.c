#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/*********************************************************************
 *
 * These C functions use patterns and functionality often found in
 * operating system code. Your job is to implement them. Write some test
 * cases for each function ( stick them in a funciton called it xyzTests() or similar)
 * call your abcTests(), etc functions in main().
 *
 * Write your own tests for each function you are testing, then share/combine
 * tests with a classmate.  Try to come up with tests that will break people's code!
 * Easy tests don't catch many bugs!
 *
 * You may not use any global variables in your solution
 *
 *
 * You must compile in C mode (not C++).  If you compile from the commandline
 * run clang, not clang++. Submit your solution files on Canvas.
 *
 *********************************************************************/



/*********************************************************************
 *
 * byte_sort()
 *
 * specification: byte_sort() treats its argument as a sequence of
 * 8 bytes, and returns a new unsigned long integer containing the
 * same bytes, sorted numerically, with the smaller-valued bytes in
 * the lower-order byte positions of the return value
 * 
 * EXAMPLE: byte_sort (0x0403deadbeef0201) returns 0xefdebead04030201
 * Ah, the joys of using bitwise operators!
 *
 * Hint: you may want to write helper functions for these two functions
 *
 *********************************************************************/

unsigned long byte_sort (unsigned long arg)
{

    /*
    Setup
    */
    unsigned long bytes[8];
    int i;
    unsigned long temp = 0x00000000000000ff; 

    /*
    Each byte goes into an array of size 8 (byte-sized)
    */
    for(i = 0; i < 8; i++) 
    {
        bytes[i] = arg & temp;
        arg = arg >> 8; 
    } 

    /*
    Now sort the byte of 8 array we just created
    */
    for(i = 0; i < 8; i++) 
    {
        int minIndex = i;

        for(int j = i; j < 8; j++) 
        {
            if(bytes[j] <= bytes[minIndex]) 
            {
                minIndex = j; 
            }
        }

        int tempBytes = bytes[i];
        bytes[i] = bytes[minIndex];
        bytes[minIndex] = tempBytes;
    }

    unsigned long answer = 0; 

    for(i = 0; i < 8; i++) 
    {
        answer = answer | (bytes[i] << 8 * i);
    }

    return answer; 

}

/*********************************************************************
 *
 * nibble_sort()
 *
 * specification: nibble_sort() treats its argument as a sequence of 16 4-bit
 * numbers, and returns a new unsigned long integer containing the same nibbles,
 * sorted numerically, with smaller-valued nibbles towards the "small end" of
 * the unsigned long value that you return
 *
 * the fact that nibbles and hex digits correspond should make it easy to
 * verify that your code is working correctly
 * 
 * EXAMPLE: nibble_sort (0x0403deadbeef0201) returns 0xfeeeddba43210000
 *
 *********************************************************************/

unsigned long nibble_sort (unsigned long arg)
{

    /*
    Setup
    */
    unsigned long nibble[16];
    int i;
    unsigned long temp = 0x000000000000000f;

    /*
    Place each byte into an array of size 8
    */
    for(i = 0; i < 16; i++) 
    {
        int minIndex = i;

        for(int j = i; j < 16; j++) 
        {
            if(nibble[j] <= nibble[minIndex]) 
            {
            minIndex = j;
            }
        }

        int tempBytes = nibble[i];
        nibble[i] = nibble[minIndex];
        nibble[minIndex] = tempBytes;
    }

    unsigned long answer = 0;

    for(i = 0; i < 16; i++) 
    {
        answer = answer | nibble[i] << 4 * i;
    }

    return answer; 

}

/*********************************************************************
 *
 * name_list()
 *
 * specification: allocate and return a pointer to a linked list of
 * struct elts
 *
 * - the first element in the list should contain in its "val" field the first
 *   letter of your first name; the second element the second letter, etc.;
 *
 * - the last element of the linked list should contain in its "val" field
 *   the last letter of your first name and its "link" field should be a null
 *   pointer
 *
 * - each element must be dynamically allocated using a malloc() call
 * Note, that since we're using C, not C++ you can't use new/delete!
 * The analog to delete is the free() function
 *
 * - if any call to malloc() fails, your function must return NULL and must also
 *   free any heap memory that has been allocated so far; that is, it must not
 *   leak memory when allocation fails
 *
 *
 * Implement print_list and free_list which should do what you expect.
 * Printing or freeing a nullptr should do nothing
 * Note: free_list might be useful for error handling for name_list... 
 *********************************************************************/

struct elt {
    char value;
    struct elt *link;
};

void free_list(struct elt* head); /*so you can call free_list in name_list if you'd like*/

struct elt *name_list (void)
{
    char name[] = "Polina";
    struct elt *current = NULL;
    struct elt *head = NULL;
    struct elt *previous = NULL;

    head = (struct elt*) malloc(sizeof(struct elt));

    /*
    If call to malloc() fails, returns NULL
    */
    if(head == NULL) 
    {
        return NULL;
    }

    head -> value = name[0];
    previous = head;
    int i;

    for(i = 1; i < 6; i++) 
    {
        current = (struct elt*) malloc(sizeof(struct elt));

        /*
        If call to malloc() fails, returns NULL
        */
        if(current == NULL) 
        {
            free_list(head);
            return NULL;
        }

        current -> value = name[i];

        if(previous != NULL) 
        {
            previous -> link = current;
        }

        previous = current;
    }

        return head;
    }

    void print_list(struct elt* head){

    }

    void free_list(struct elt* head)
    {
        struct elt *next;

        while(head != NULL) 
        {
            next = head->link;
            free(head);
            head = next;
        }
}


/*********************************************************************
 *
 * draw_me()
 *
 * this function creates a file called me.txt which contains an ASCII-art
 * picture of you (it does not need to be very big).
 * 
 * Use the C stdlib functions: fopen, fclose, fprintf, etc which live in stdio.h
 * don't use C++ iostreams
 *
 *
 *********************************************************************/

void draw_me (void)
{

    FILE * me; 

    me = fopen("./me.txt", "w"); 

    fprintf(me, "/\n SOMETHING /\n");

    fclose(me);

}


/*********************************************************************
 *
 * Testing main()
 *
 *********************************************************************/

int main(int argc, char const *argv[])
{

    /*
    byte_sort()
    */
    unsigned long answer = byte_sort(0x0403deadbeef0201); 
    printf("byte_sort: 0x%lx\n", answer);
    // byte_sort(0x0403deadbeef0201);

    /*
    nibble_sort()
    */
    answer = nibble_sort(0x0403deadbeef0201); 
    printf("nibble_sort 0x%lx\n", answer);
    // byte_sort(0x0403deadbeef0201);

    /*
    name_list()
    */


    /*
    draw_me()
    */
   draw_me();
   printf("Got to 4");

}
