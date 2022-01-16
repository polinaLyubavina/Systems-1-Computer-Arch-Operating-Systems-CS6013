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
    int i;
    unsigned long temp = 0x00000000000000ff; 
    unsigned long bytes[8];
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
    unsigned long temp = 0x000000000000000f;
    unsigned long nibble[16];
    int i;

    /*
    Place each nibble into the nibble array
    */
   for(i = 0; i < 16; i++) 
   {
       nibble[i] = arg & temp;
       arg = arg >> 4; 
   }

    /*
    So
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
    /*
    All nodes begin life set to null.
    */
    struct elt *current = NULL;
    struct elt *head = NULL;
    struct elt *next = NULL;
    char name[] = "POLINA";

    /*
    Allocates memory for struct on the heap.
    Keeps track of the head.
    */
    head = (struct elt*) malloc(sizeof(struct elt));

    /*
    If fails to allocate memory, returns NULL
    */
    if(head == NULL) 
    {
        return NULL;
    }

    head -> value = name[0];
    current = head;
    
    /*
    Makes nodes in linked list
    */
    for(int i = 1; i < 6; i++) 
    {
        /*
        Allocates memory for struct on the heap.
        Next pointer defaults to null.
        */
        next = (struct elt*) malloc(sizeof(struct elt));

        /*
        If fails to allocate memory, returns NULL
        */
        if(next == NULL) 
        {
            free_list(head);
            return NULL;
        }

        next -> value = name[i];
        current -> link = next;
        current = next; 
    }

    return head;
}

void print_list(struct elt* head)
{

    struct elt* current = head;
    
    /*
    Goes from node to node until the linked list is empty,
    printing out each node's value along the way.
    */
    while(current != NULL) 
    {
        printf("%c", current -> value);
        current = current -> link; 
    }
}

void free_list(struct elt* head)
{
    struct elt* current = head;
    struct elt* next = NULL;

    /*
    Finds what the next node is, frees the current node,
    then updates current to be next. 
    */
    while(current != NULL) 
    {
        next = current->link;
        free(current);
        current = next;
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

    fprintf(me, "OOOOOOOOOOOOOO000000O000000000000000000000000000000O00000OkdccodxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxkkkkkkkkkkkOOOOOOOOOOOOO000000000000OO00000Ox;;x0KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK0000000000000000000000000OOOOOOOKK00kollooooooooooooooooooooooooooooddooo:cdoododdddddooodk0O0K0000000Oxolodl\n \
OO0000OOOOOOO0000000000000000000000000000000000000000O00000Oko::cdxxxxxxxxkkkkkkkkkkkkOOOOOOOOOOOOOO0000000000000000000000000000000000000000Ol,:x00K00000000000000000000000000000000000000000000000000000000KKKKKKKKKKK0K0OOOO0K00Odolloooooooooooooooooooooddddddddddoo::ddoddddddddooodk000KKK000000kdlodl\n \
000000000000000000000000000000000000000000000000000000O000000Oxl:cokOOOOOOOOOOOOOOOOOOOOOOOOOOO000000000000000000000000000000000000000000000Oxc;ck0OOOOOOOOOOOOOOOOOOOO000000000000000KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK0OOOOO0K00koolloooooooooooddoodddddddddddddddddoc:ododdddddddodook00000000000Okdoodl\n \
000000000OOOOOOOO0OOOOOOOOOOOOOOOOOOOOOOOOOOOO00000000000000000OxlcdkO00OOOOO0000000000000000000000000000000000000000000000000000000000000000Odc:dOO0000000000000KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK0OOOOO000Oxoollooooooodddddddddddddddddddddddddoc:ododdodddddodddk000K00000000kxoodo\n \
OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO0000OOOkO0000000000000000000000000000000000000000000000000000KKK00KKKKK000000000Odlox0KKKKK000000KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKOOOOOO000kdooolooooddddddddddddddddddddddddddddol:ododdodddddddddk000K000000KKkxoodo\n \
OOOOOOOOOOOOOOOOOOOOkkkkkOOOOOOOOOOkkkkkkkkkkkkkkkkkkkOOOOOOOOOOOO0O0OkO0000000000000000000000000000000000000000000000000000KK000KKKKKK00KKKKK0OxodOKK0KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK0OOOOOO00Oxodooloddddddddddddddddddddddddddddddddl:lxoddoddxxdddddk000000K00KK0kxoodd\n \
OOkkOOOkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkxxxxxxxxxxxxxxxxkxxkkkkkkkO0000000000000000000000000000000000000000000000000000000000000000000000O00kOKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKXXXXXXXXXKKK000OO0000kdddooloddddddddddddddddddddddddddddddddo:lxdddoddxxdddddx000KKK000000kxdodd\n \
NXK00OOkkkkkkkkkkkkkkkxxxxxxxxxxxxxxxxxxxxxxkkkkkkkkkkkkkkOOOOOO0OOO0000OxxkOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO0Odx0KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKXXXXKKKKKKXXXKKKKKKXXKKKKKKKKK00000000Oxdddooloddddddddddddddddddddddddddddddddo:lxddxoodxxddddddO00KKKKK0KK0Okdodx\n \
WWWWWNNX0kxkxkkkkkkkkkkkkkkkkOOOOOOOOOOOOO0000000000000000000000000000000OxlldkkOkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkOOOOOOOOOOOOOOO0000Oxok0KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK00000000000O0K0OkddddoooodddddddddddddddddddddddddddddddddccxddxdodxxxdddddkO0KKKKKKKK0Okdodx\n \
WNXK0OkxdlokO00000000000000000000000000000000000000000000000000000000000KK0kl;:odxkkkkkkkkkkkkkkkkkkkOOOOOOOOOOOOO00000000000000000000KK0KK000KKKK0koodk0KKKKKKKKKK00000000000000000000000000000000000000KKKKKKKKKKKKK0OOOO0K0Oxdddddooodddddddddddddddddddxxxxxxxxxxxxddccdddxdddxxxdddddk00KKKK000K00kxodx\n \
xolc:;;,,,,;ok00000000000000000000000000000000000000000000000000000000000000Oxc;:oxO00000000000000000000000000000000000000000KKK0KKKKKKKKKKKKKKKKK0Oxc,ck0OO00O00000OOOOOOOOOOkkOOOOO00000KKKKKKKKKKKKKKKKKKKKKKKKKKKK0OOOO00OOxdddddooodddddddddddddddddxxxxxxxxxxxxxxxdlcdxdxddddxxdddodkO00KKKK00K00kxoox\n \
,,,,'''''',;;cdkO00000000000000000000000000000000000OOOOO000000OOOOOOOOOOOOO0OOxlokkOK000000000000000000000000KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK0kl;;lO0KK00KKKK0000000OOkOOkkOkkOOOOOO00KKKKKKKKKKKKKKKXKKKKKKKKKK00OO00OOxddddddoooddddddddddddddddxxxxxxxxxxxxxxxxdl:dxdxdoddxxdddddkOO0KKKK0KK00kxdox\n \
',,,,;::;;ccclloxOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOkkkkkkkkkkkOkkOOkO0K000000000KK0000000K0000KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK0xlccx0KKKKKKK000000OkkxxdolllllcccldkO00KKKKKXXXXXXXXXXXXXXXXKKK000OO00Okdddddddooodddddddddddddxxxxxxxxxxxxxxxxxxxdl:oxdxddddxxdddddxO00KKKKKKK00kxdod\n \
:c:;:cc:;:cllllok0OOOOOOOOOOOOOkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkOOOkk000000000000000000000000000000000000000000000000000000000000K0OO0xkKKKKKK0000Okxdllc:::;;;;,,,,,,;cok0KKKXXXXXXXXXXXXXXXXXKKK000000OOxdddddddooodddddddxxxxxxxxxxxxxxxxxxxxxxxxxxo:oxdxxddddxdddddkO00KKKKKKK00Oxdod\n \
cc:;ccl:;:llllldO00000OOOOOOkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkOOOOOOOOOOOOOOOO0000OO0000kdoxOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO00000doO0000Okkxolc:;;;;;;;;;,''''',,,,,;lx0KKKKKKKKKKKKKKKKKKKKK0000K0OkdddxOkdddoodddxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo:lxddxdoddxdodddk000KKKKK000KOxxod\n \
cc::clll:clooooxO00000000000OkkOOOOOOOO000000000000000000000000KKKKKK0000KK0KK0K0000000OdcldxkkkkkkkkkkkkkkkkkkkkOOOOOOOOOOOOOOOOOOO000000000000K00KKKKK0xcokOkxoc:;;;;;;;;;;;;;;,,'...'',;;;;:ok00KKKKKKKKKKKKKKK0K000O0K0OxdddKXkdddooddxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxo:lxddxddddxdddddk0000K0KKK00KOxxod\n \
lolcllodolooodoxO000000000000OOkO00000000000000000000000000000000000000000000000000000000koccdkOOOOOOOOOOO0000000000000KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK0xlcll:;;;;;;;,,,,,,,,'''''','.'',,;;;;:lxO0KKKKXXXXXXXXXXKK0000KKOkdddOXOddddoodxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxd:cxddxdoddxddoddk000KKKKKKKKK0xxod\n \
ooolooddoooddddk000000000000OOOxdxO00000000000000000000000000000000000000000000OO00OOOOOOOOkoxOO0KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKXKKKK0Oko:;;;,,,,,,;,,,''''......',;'',,;::::;;:cxO0KXXXXXXXXXXXXXK000000kxddxKKxddddooxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxdccxxdxdoddxxdodxkO0000KK00K000kxdo\n \
odooooddoodddddk000000000000OOOxoodxkOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOkkkkkkkkkkkkkkkkkkkOOOO0OO00000000000000000000000000000000KKKKKKKKKKKKKKKKK00kdoc;;,,'',,,,;,'...........',,,,,;;;;;;;;::::ok0KKXXXXXXXXKKKK000K0OkdddOXOdddddodxxxxxkkkxxxxxxxxxxkkkkxxxxxxxxxxxdccdxdxdodddxdoddxO0000K00KKKK0kxdo\n \
odooodddoodddddO000000000000OOkdooddddddkOOkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkOOOOOOOOOOOOO00OkkOOOOOOOOO000OOOO00000000000000000000000000000OOko:;;,,''''',',,'...'',,,,,,,;;,,,,,,''.....',;;:lxO0KKKKKKKKKKKK000K0OxddxOOxdddddooxxxxxxkkxxxxxxxxxkkkkkxxxxxxxxxxxxl:dxdxdoddddddddxO000KKKK0000Kkol:\n \
ddoodddoodxxxdxO000000000000OOkdlloooollkK000OkkkkOOOOOOOOOOOOOOO00000000000000000KKKKKKKKKK00KKKKOxdxkOOOOOOOOOOOOOOOOOOOOOO00000000000000000000kdl;,,,,'.''''',,...',;;;::cccllcc:::;;,'.........';cdkO0KKKKKKKKK000KKOkxdddddddddddoodxxxxxxxxxxxxxxxxxxxxxxxxkkkkkkkkxl:dxdxdoddddddddxO000KKKKKKKKKklcc\n \
ddodxddooxxxxdxO000000O00000OOkoooddxxddOKKKK0kk0KK0KKKKKKKKKKKKKKKKKK0000000000000000000000000000K0kookO00000000000000KKKKKKKKKKKKKKKKKKKKKKKKK0dc,,,,'...'''',,..',;:clloddxxxxxxdddoolc;,'........,:oxk0XXXXXXXK000K0Oxddddddddddddoodxxxxxxxxxxxxxxxxkkkkkkkkkkkkkkkkxo:oxdxxodddddddddO0000KKKKKK0KOxdo\n \
ddodxddoooooooxO000000OO000OOOxooodxxxddOKKKK0doxkO00000000000000000000000OOOOOOOOOOOOOOOOOOOOOOOOOOOOkO00KKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKK0d:,,,,''.''''',,..',;:clodxxkkkOOOOOOOkkxxol:;'.......';coxOKXXXXXK00KK0kdodddddddddddoodxxxxxxxxxxxxxkkkkkkkkkkkkkkkkkOOko:oxdxxdddddddoodk0000KKKKKKKKOxdo\n \
doloooooooddddx0000000O00OOOOOxooodddddd0KKKKOdooolodxkOOOOOOOOkOkkkkkkkkkkkkkkkkkkkkkkkkkkkkOOOOOOOOOO0K0OO0000000000000000000000000000000000kd:,,,,'...'''''''.',;:clddxxkkkkOOOOOOOOOOkkdoc:,.. ....';cclk0KKKKK0KK0Oxooddddddddddddoxxxxxxxxkkkkkkkkkkkkkxxxdddddddddol:lxddxddddddddodk0K00KKKKKK000xdo\n \
dooddddoddxxddk0O0O00OO00OOOOOxooodddddx0KKKKOdool:,';:clldxkOOOOOOOOOOOOOOOOOO00000000000000000KKKKKK0KKK0OxdkOOOOOOOOOOOOOOOO00000000000000Oo:,,,,'...''''..'..',;clodxkkOOOOOOkkkOOOOOkkkxol:'.......';:clkKKXKK00KKOxoodddddddxxxdooxxxxxddddddddddddddoooooooooddddddo:lxddxdddddddoodk0KK0KKKKKK000xdd\n \
dooddddodddddxO0OOO0OOOO0OOOOkxooddxxxdx0KKK0kdool:'',,,,,,cd0K0000KKKKKKKKKKKKKKKKKKK0000000000000000000000kodO00000000KKKKKKKKKKKKKKKKKKKKKx:,',,'....'','..''',;:lodxkkkOOOOOOOOOO0OOOOkkkxoc;..  ...'';cldOKXKK0O0KKkoooooooooooooooooooooooooodddddxxxxxxxxxxxxxxxxxxo:cxddxdddddddoodk0KKKKKK0KKK00kdd\n \
ddddddooddxxdxO00OOOOOOOOOOOOkdodxxxxxdkKKKK0kdool:'',,,,,,,;cdO000000000000000000OOOOOOOOOOOOOOOOOOOOOOOOOOOOO0K0000KK00KKKKKKKKKKKKK0K0000x:,''''......','.''''';:loddxkkkkkkkkkkOOOOOOOOkkxdl;..  ...'',;cokKKK0OO0NNOoloooooooddddoodxxxxxxxxxxxxxxxkkkkkkkkkkkkkkkkkxd:cxddxddddddddodk0KKKKKKKKK00Kkll\n \
dddxxdodxxxxdxO00OOOOOOOOOOOOkdodxkkxxdkKKKK0kdool:'',,,,,,,,,,:loxxxkkkkkkkkkkkkkkkkkkkOOOOOOOOOOOOOOOO0000000000OOOO0OOOOOO00000000000000kc,'''''......,,''''......'',:codddxxxxxxxxxxxxkkxxxo;..  ...'',;::lONKxx0NMW0ddxxxxxxxxxxxdodxxxkkkkkkkkkkkkkkkkkkOkkkkkkkkkkkxccxddxdodddddooox0K00KKKKKKK0Kklc\n \
ddxxddodxxddoxOOOOOOOOOOOOOOOkdodxkkxxdOKKKK0xoool;'',,,,,,,,,,,,,,;;;lk0000000000000000000000KKKKKKKKKKKKKKKKKKKK0OxOK0000000000K0KKKKKKKKd;,'..'......',,,'.''..''''...';clodddool:,',,;:::coo;..  ...'',;;;;lxxxk0WMW0ddxkkkkkkkkkkdodkkkkkkkkkkkkOOOOOOOOOOOOOOOOOkkkkxccdxdxdodddddooox0KK0KK00KKKKKOdd\n \
ddxdoddddddooxOOOOO0OOOOOOOOOxdodxkkkxdOKKKK0xoool;'',,,,,,,,,,,,,,,,,,:dO00000000000000000OOOOOOOOOOOOOOOOO000000000KXX0O0OOOOO0OOOOO000K0o,,'..'......';,,,..'..',;;;;,,,;clooolc;,,,;:ccllc::,.  ...'''';;,,;:oxxONMWKddkkkkkkkkkkkdoxkkkkkkOOOOOOOOOOOOOOOOOOOOOOOOkkkxlcdxdxdooddddooodO0000KKKKK0KKOdo\n \
odxddddddddook0OOOOOOOOOOOOOOxddxkkkkxx0K00KOxoooc;',,,,,,,,,,,,,,,,,,,,,:lodddxkOOOOOOOOOOOOOOOO00000000000000K0KKK00000OKXKOO0KKKKXXXXXNXo,,'.........',,,,'.... ....',,,;cdxxoc::::ccloollc:;'. ...''''';;'.,;:dkONMWKxdkkkkkkkkkkkdoxkkkkkOOOOOOOOOOOOOOOOOOOOOOOOOkkkxl:dxoxdooodooooodk0K00KK000KKK0dl\n \
ooxxdoodxxdook0OOOOOOOOOOOOOOxddxxkkxxx0KKKKOdoooc,.,,,,,,,,,,,,,,,,,,,,,,,',,,,cdO0000000000000000000000000KKKKKKKKKKKKKKXNWNXXNWWNWWNNNWXl','........',,,,,''.......'',;;;lk0koc:;;,,'',,,;,,,'........'',,..',;:oONMWKddkkkkkkkkkkkxoxkkkOOOOOOOOOOOOOOOOOOOOOOOOOOOOkkxl:oxoxdloooooooodk0K0000KKKKKKKdc\n \
oodxdlldxxdodO0OOOOOOOOOOOOOOxdodxxxxdx0KKK0Oddooc,.,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,;ccllcok0XK0KKKKXXXXXXXXXXXXXXNNNNNNNNNXKKNNXXXXXXKKK000x:'''........',,,,,'''''',,;;::cccdO0kolc:;,'......',,'''......',;'...',;;dXMWKddkkkkOOOkkkkxodkkkOOOOOOOOOOOOOOOOOOOOOOOOOOOOkkxo:oxoddoooooooolok00000O0KKKKKKd:\n \
lldddlcoddoodOOOOOOOOOOOOOOOOdoddxddddx0K0K0kddolc,',,,,,,,,,,,,,,,,,,,,,,',,,',,,','''':OWWNNNNNNNNNNNNNXXXXXXXKK0000OOOkkxxxxxxdddddddddc,'''........',,,,'.',,,,:cclllllldO0kxdollc::;,,,;;;,''...  ..',,.....',;;xNWKddkkkkOOOkkkkxodkkkOOOOOOOOOOOOOOOOOOOOOOOOOOOOkkko:lxoddolloooollokO000KKKKKKKKKxo\n \
cloooccoddoldOOOOOOOOOOOOOOOkdoooollolx0K000kddol:,',,,,,,,,,,,,,,,,,,,,,,,,,,,,,'','',,oXMWNNXKK00OOOOkkxxdddoodxxdccldkxkd;codocldoooddd:'..'........',,,'..',;:::looollloxOOkxxxxxoc;,;;;;,''..     .'',,.......,;;dK0ddkkkkOOOkkkkxodkkOOOOOOOOOOOOOOOOOOOOOOOOOOOOOkkkd:lxoddollloooolok0O00KXKKKK00Kko\n \
clooocclodolxOOOOOOOOOOOOOOOkdllooooookKK000kddol:'',,,,,,,,,,,,,,,,,'',,,,,,',,'',,',,,dNM0occ:::::::::;;,,;;;;okko;cxOkOo;codocldoddddxc. ..........',,'...',;:lc:loc::ldxOOkxddddc;;::ccc:,'..    ..',,.........';;cdookkkkOOOOkkkxodkOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOkd:cdoddollloooolox00000KKK000O0ko\n \
:ccoocccllccxOOOOOOOOOOOOOOOkdllooooookK0000xodol:'',,,,,,,,,,,,,,,,,'',,'',,',,',,,',,,dNM0l,...',,,,,,,'.',;;;okko;;cxOkOo,cooocldoodddxc.  ..........,'.....'';clc:c:;;:ldxxdoolc;;cloddol:'...   ..',,'.........'',;:loxkkOOOOOOkkxodkOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOkd:cdoodollloooolox0K0K00KK0000KOo\n \
:clol:ccllclkOOOOOOOOOOOOOOOkddoddddddOK000Oxodol;'',,,,,,,,,,,,,,,,,'',,''',',,''''',;cOWWKl,...',,,,,,,'.',,,,okkl;;cxOkOo,:lllcldddddxxl........... .'........';cll:,,'',:c:;;c:,;codxddl:,...   ...''............'',,:lxkkkkOOOOkkkodkOOOOOOOOOOO000OO00OOOOOOOOOOOOOOOxc:doodolllooolllx0KKXKKKKKKKKX0o\n \
clldolllooodkOOOOOOOOOOOOOkkxxxddddddxO0000Oxddol;'',,,,,,,,,,,,,,,,,,',,'',,',,'',,',lxk0NKo,..........'.....',lkkl;;cxOkOo,coolcldddddxxd;..  ...... .'..........';cc;,,,;::;,,;;:coodool:,'.......................'''';:ldxkkkOOOOOkddkOOOOOOOOOOOOOOO00000OO0OOOOOOOOOOxc:ododolllloollldOKKKKXKKKKXKXKd\n \
dddxxddddddxOOOOOOOOOOOOOOkxxxxxxxxxxx00000Odddoc;',,,,,,,,,,,,,,,,,,,',,,,,,'','',,,cdddd0Xd;,'..'''''''..',,,;okkl,;cxOkOl,clllcodddddxxxl..  ...... .....   ......',,',,;;;;::::lolllllc;'.... ...................';,',;:clodxkkkxkxodkkOOOOOOOOOOOOO0000000OOOOOOOOOOOOxc:ododollloooollok0KKXXKKKKXXXKd\n \
dddddddddddxOOOOOOOOOOOOOkxxxxddxxxxxk0K000kdodoc;',,,;;,,,,,,,,,,,,,,,,,,',,,',,',,cOK0kx0N0c;,',,;;;;::;;::::cdkkc,;ckOkOo;;::ccodddddxxkxl'.  ...........     .........'',;clc::llllllc;,'...  ...................':c:,,:cccllllooooloxkOOOOOOOOOOOOOO000O00OOOOOOOOOOOOxc:oolooooooooolloxOKKXXXXXXXKXXx\n \
dddddddddddkOOOOOOOOOOOOOkxddddddxxxxk00000kddooc,',;,:c;,,,,,,,,,,,,,,,,,,,,,,;;,;;:oxxk0XWKl;::lllolllllllcccldkkc,;lkOkOo::::ccodddddxkxkko;.......'..  ....................',,;cclllc;,;'..  ...  ...............;oxd:,,cdddoooooooloxkkOxdkOOOOOOOOOO0OOOOOOOOOOOOOOOOxl:ldoddoodoooollox0KKXXXXXXXXXXk\n \
xddddddddddkOOOOOOOOOOOOOkxddddddxxxxk00000kddolc,,:c:coc,,;;;;;::::::::::::cccccc::cc:lOWNX0l,;:ll::;;;:cccccccdkx:,;lkOkkc.',;ccodddddxkkkkkxoc,...............'',,,''',;;;;,'',,;;cllc;;;'.  .... .....  .........cOOxo:,:okkkkkkxxxookOOOdlxkOOOOOOOOOOOOOOOOOOOOOOOOOOkl;oxoddodollollloxO0KKXXXXXKKKXk\n \
xdddddddddxkOOOOOOOOOOOOOkxdddddxxxxxk0000Oxddolc,;lookOd;,,;;;;:cc:::;::::;:c:;;,',;::cOX00k;.'';;'.....''',;;:dkx:,;lkkkkc....:codddddxkkkkkkkkxl;'...''......',,;:::::;;:::;;:cclllooc;;;.. .....................'dXKkoc;,cdxxkxxxxdooddddlldxxxkkOOOOOOOOOOOOOOOOOOOOOOkl:x0xkkoollllllloxO0KKXXXXXKKKKk\n \
xxxdddddxdxkOOOOOOOOOOOOOkxxxxxxxxxxxO0000Oxddol:,',',oOd;'''''',:;'''.',;,',;,.....''';OXxkk;.................,dkx;,;lkkkkl,'.':coddddxxkkkkkkkkkkxc'....','.....',;:cllllllllloollooolc:;'.  .....................;kNNOoc;,;:ccc:::;:cc;;;;:cdxxxxdddxkkOOOOOOOOOOOOOOOOOko:dXOOOollllllllodO0KKXXXKKKKKXO\n \
xxddddddddxOOOOOOOOOOOOOkxxxxxxxxxxxxO0000Oxodol:'';,;lxo;''''''''............'........;OXxxx;.................,dkd;',lkkkkc',;:ccoddddxkkkkkkkkkkkko:;;,;:clc;;,,,;:coddxxdddddoooooolll:,.   ....................'cONN0dc:;;::::::;;;cc;:::::oddxkOkxxdddddxxxxxxxxxdddddol:dKOOOollllllolodkO0KKXXK00KKK0\n \
xxxxdxddxdxOOOOOOOOOOOOOkxxxxxxxxxxxxO0000Oxoool;''''':dl,',''''.......................:0Xddd'.................,dkd;';lkkkk;...,ccoddddxkkkkkkkkkkkkd:;;;cdolllcclcccodxkkxxdxxxxdoooollo:.......................',:lONN0dlc:;:;;;;;,,,cc;,,,,;:;,;:lccoddolllllllloodddddddl:oKOkOdllllllllodkO0KKKXK00KKXK\n \
xxxxxxxxxdkOOOOOOOOOOOOOkxxxxxxxxxxxxO0O00kdoooc;'',,,:o:'.'...........................cKKoll'.................,dkd,,;okkkk;...,ccoddddxxkkkkkkkkkkkd:;;;cddollllollllooddddddxxdooooolcoo;,...','..............',;;c0WWKxdc::;;;,,,,,,ld:;;;,:lc::::cclddoxkkkOOkkkxxxxxxkkd:lK0kOdllllllllldk00KKKKKKKXXXX\n \
xkxxxxxxdxkOOOOOOOOOOOOOkxxxxxxxxxxxxO0OOOkdoolc;',;,;oxl,,,'''........................cKKoc;..................:dko,,;okkkx;.'.,ccoddddddxddddddddddl,.''cddooollllllllllllooooolllcc:;:xkdc;:::::;,'.........,,:cccl0WMXOkoccccccccc::okoclccldollllllllllloooxkxO00OOOxdddl;c00kOxlllllllllok00KKKKKKKXXKK\n \
xllooldxxxkOOOOOOOOOOOkkkxxxxxxxxxxxk000OOkdoolc,',;,;cdc,,,,,'''''''.,o:..........  ..cXKo:'..................:xko,';okkOx,.,,:lloooooodddddddddddxo;'',lxddooolloollcccccccccccc::::;ckOkoclccccc:;,,,'..',;::cccclOWMKkkdcc:::::cc:;lkdlloloxdoooooooooooooooooodddxxxxdlc;cO0xOxllllllllllxO00KKKKKKKK0K\n \
xddolodxxxkOOOOOOOOOOOkkkxxxxxxxxxxxk000OOxooolc,',;,,:c:,,,,,,,,''''':kl..............lX0l:'       ...........:xko,';okkOx,,oodxxkkkkkkOOOOOOOOOOOOkc;;cdddddooooooollllccccccccccccc::dOkkxxxdolllccc:,;:::ccccccclOWMKkkdc:::::::::,lkdlooloxxdoooooooooooooooooooollc:;;;;:O0xOxlllllllcllxO00KKKKKKKKKX\n \
dkkxddxxxxkOOOOOOOOOOOkkkxxxxxxxxxxxk0OOOOxoool:,',;,,,;;,,,,,,,,'''''cOo..............oX0l:'.      ...........:xkl,';okkOd,;dodkkkkkOOOOOOO000O00O0Ol:codddddddoooooooooolllllllllllccccdkOOOOOOkkkxxxddooooolc::c:lOWWXkkdc:::::::::;lkdlooloxxdooooooooooodooooooooool:;;;;:kKxkkllllllllllxO0KKKKKKKKKKK\n \
loodxxooodkOOOOOOOOOOOkkkxxxxxxxxxxxk0OOOOxoool:,',,,,,,,,,,,,,,,'''''cOo..............dX0l:'..       .........:xkl'';dkkOd,;dddkOOOOOOO000000000000kocodddddddddddddddddooooooooololllccldkOOOOOOOOOOOOOOOOOOxccodxxONMXkkdc::ccc::::;ckxoooooxxdoddddddddddddddoooooool::;;;;xKxkkllllllllllxOO0KKKKKKKK0K\n \
dxdol:'',lkOOOOOOOOOOOkOkxxxxxxxxxxxO0OOOkdooll:'',,,,,,,,,,,,,,,'''''ckc.............'dNOl:'..................cxkl'';dkkOd,;oodkOOOOOOO000000000000OdoddddddddddddddddddddddooooooooolllllodxkOOOOOOOOO0K0OOOxclkOOO0NWN0Oxoolodc::::;ckxoodooxkxddddddddddddddddoooooolc:;;;;dKxkkllllllllllxOOO0KK000000K\n \
doooc,..'oOOOOOOOOOOOOOOkxxxxxxxxxxxO0OOOkdoooc;',;;;,,:oo:,,,,,,''''':o;.............'xNkc:..................'lxkc'';dkkOd,'cldkOOOOOOO0000000000OkxdddddddddddxxxxdxxxddddddddddddooolllolllodxkOOOOOOO0OOO0klokOOO0NWNKOkOOkxddooooclkkxxxxdkkxxxxxxxxxxkkkkkxxdddddddooll:;dKkxkollllllllldOOO0KKK00OOO0\n \
ollc,...,dOOOOOOOOOOOOOkkxxxxxxxxxxxOOOOOkdoool;',;;;;;cxkc,',,,,''''',,'.............,kNkc:.................',lxxc',:dkkko''codkOOOOOO00000KK0OkxddddddddddddddddxxxxxxxdddddddddddoooooooooooooodxxkOOOOOOO0kookOOO0NWNKOkOOOOOOOOOOkkkOK00OxkO000000000KK0KKKK00000000OOOkl,oKkxkollllllllldkOk000000OOO0\n \
:,,,....;xOOOOOOOOOOOOOkxxxxxxxxxxxxOOOOOxoodol;',;;;;;,,,,',,,,'''''''''.''..........,kNkc:.....    .........'lxxc'';dkkkd,.;ldkOOOOOO0KKK0OkxdddddddddddddddddddxxxxxxxxxdddddddddoooooooddooooooooodxkkOOOOkookOOO0NWNKOOOOOOOOOOOOkkkOKKK0xkOKKKKKKKKKKKKKKKKK0000000OOOkl,l0kxkolllllllllokOkO00000OOOO\n \
........:xOOOOOOOOOOOOOkxxxxxxxxxxxxOOOOOxoodol;',;;;;;,,,,,,,,,''''''''''''..........,OXxc;..'.. ............'lxxl:oxO0Okkdo:,ckOOOOOOOOkxxddddddddddddddddddddddxxxxxxxxxxxxxxxxdooooooooooddddxxddoodddxxxkxxxxxxkkOO0OOOOOOOOOOOOOOkkO000kooxk000000000000OkxxkOOOOOOOkkxl,l0kdkdlllllllllokOkO000OOOOOO\n \
.......'ckOOOOOOOOOOOOOkxxxxxxxxxxxkOOOOkxooool;',;;;;;,,,,,,,,,'','''''''''..........;OXdc;..'.. .'.......   'codkOO000K0OkkxoodxkxxxxddddddddddddooooooddddddddddxxxxxxxxxxkkkxdooooddddxxxkkOOOOOkxxdddxxxxxxxxxxkkkkOOOO0KKKK00OOOkkkkOOOxlcokOOOOOOOOOOOOOkxxOOOOOOOkkkxl,cOkdkdllllllllloxkkO00OOkOOO0\n \
,,','..'lOOOOOOOOOOOOkOkxxxxxxxxxxxkOOOOkdooool;',;;;;;,,,,,,,,,'','''''''''..........:0Xdc;..'.. .''......  .,'.',cdkkkO0K0kxxdooooddddddddddddddddooooooooooooddddddxxxxxkkkkxddddxkkkOOOOOOOOOOOOOOkxxxxxxxxxxkkkkkkkkO0KK00O00OkxxkkkkOOOklcoxkkOOOOOOOOOOOOdxOkOOOOOkkxxo,:OOdkdclllllllllxkkkOO00OOO00\n \
Oxokdccok0KKOOOOOOOOOkOkxxxxxxxxxxxkOOOOkdooooc,',;;;;;,,,,,,,,''','''''''''..........:0Ko:;..'.........''. .',',,,,;lxkkkOK0kxdooooodddddddddddddddddddoooooooooodddddxxkkkkkkkkkkkOOOOOOOOOOOO000000OOOkkkkkkkkkkkkkkk0K0OOOOkdolll:;lxkOOkklcoxkOOOOOOOOOOOOOdxOkkOOOOkkxxo;:kOdxdllllllllclxkkkkOOOOOOOO\n \
kxox0KKKKXXK0OOOOOOOOOOkxxxxxxxxxxxkOOOOkxddddl;,;;;;;;,,,,,,''''''''''''''...........cKKo:;..';l,.  .cdkxo;,:oollcc::cdkkkOKKkddooooooooodddddddddxxdddddddoooooodxxkkkkkkkkkkOOOOOOOOOOOOOOOOOO0000000OOOkkkkkkkkkkkOK0Okkkxolcoxkkklcxkkkkkl:odxkOOOOOOOOOOOOxxOkkkkkkkxddc,;kOdxxllllllllcldkkxkkOOOkkOO\n \
xoccxO0KK0KKK0OOOOOOOOOkxxxxxxxxxxxkOOOOOkOOkxd:,;;;;;;,,,,,,'''''''''''..'...........cK0o:,..,co:. .lXNNNNKxxxxdoollc:cdxxxk0KkddooooooooododdddxxxxkkkxxxxxxxkxkkkOkkkkkkkkkOOOOOOO0OOOOOOOOOOOOOO000000OOkkkkkkkkO00OkkkkdlcoxkkOOkkxxkkkxxl:lodxxkkkkkkkkkkkddkkkkkkxxollc;;xOdxxlllllllllldxxkkkkOOkkkk\n \
dl;cxOOkkOOOOOOOOOOOOOkkxxxxxxxxxxxOOOOOOO00Okxc;;;;;;;,,,,,,',''''''''''''...........lK0l:,..,:l:..;kXXNNXOxxkkkdoollcccdxxxkKKxdddoooooooooodddxxxxkkkkkkkkkkOOOOOOOOOOOkOOOOOOOOOOOOOOOOOOOOOOOOOOO0000OOkkkxxxkOKOkkkxxolodxkkkkkkkxxxkxxxl:loooxxxkkkkkkkkkdokxxxxxxxddol;;dOdxxllllllllllodxxxxxkkxxdd\n \
kxxkkOkxdxkOOOOOOOOOOOkkkkxxxxxxxxxOOOOO0O00Oxxo:;;;;;,,,,,,,,,''''''''''.'...........lK0l:'..,,,,,,;lddxxkxxxkkkxdoollccldxdxkK0xddddolloooooddddddxxxxxxkkkkOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO000OOkkkxxxk0KOxxxxxolodxxkkkkkkkkxxxxxdl:llldxxdodxkkxxxxdoxkxxxxxdoddl;,oOddxllllllllllodxxxxkkkxxdd\n \
doxOkxkOkxkOkOOOOOOOOOOkkkxkkxxxxxkOOOOO0O00kxxdl;;;;;,,,,,,,,,'''''''''.''...........oKOl:'..,cxkkxxxkkkxdxxkkkkkxdoollccoddddkKOxxdddoloooodddxxxxkxxxkkkkOOOOOOOkkOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO00OOOkxxxxxk0Kkxxdddooddxkkkkkkkkkkxxxxxxl:clclc:::lodxxxxxdldoccdxo:;cl:,,oOddxllllllllllodxkkkkkkxddd\n \
OxkKK0000OOOOOOOOOOOOOOkkkkkkxxxxxkOOOOO0O0Okxxxdc;;;;;,,,,,,,,'''''''''.'............oKkl:'..''',::::;;cdxxxkkkkkkxdooolccododxOKkdddddodxxxxkkkkkkOOkkOOOkkkkkkkkkkkOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO000OOkxxxxxk00kxddddoddxxxkkkkkkkkkkxxxdooc:cl::::::clodddodoll:;:ll:;''''',lOddxollllllllloodxkxxxxxddd\n \
Ok0KKKOOO00O0XX0OOOOOOOkkkkkkkkkkxkOOOO0000Okxxxxo:;;;;,,,,,,,,'''''''''.............'dKkc:'.....,c;,'.'cxxxxkkkkkkkxdooolcldoood00dddddxxkkkkkkOOOOOOkOOkkkkkkkkkkkkkOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO000Okxxxddx00xddooodddxxxxkkkkkkkkkkxxl::c::ll::c:::cccllcccc::;;:::;,'...',cOxoxollllllllloddxkxxkkkddd\n \
0KKXKKKKKXKKKKKKKKKKKKKKK00000OkkkkO0OO0000Okxxxkdc;;;;,,,,,,,''''''''''.............'dKxl:'....'loc;;,:dxxxxkkkkkkkkxdooolcloloox0kddxxxxkkkOOOOOkOOOkOOkkkkkkkkkkkkkkO0OkkkOOOOOOOOOOOOOOOOOOOOO00000kxddddxO0xoooloddxxxxkkkkkkkkkkkkkxo:cllcclolc:::cccccc:::;;;;;;:;,'...',cOxoxolllllllllooxkkxkkkkxxd\n \
WWWWWMWWMMMWWWWMMMMMMMMMMMMMMMN0kkO00000000Okkkkkko:;;;;;,,,,,,'''''''''.............,xKxlc'.',,coxxdxxxddxxxxkkkkkkkkxdooollollooO0xddddxkkkkkkkO00kxxxxxxxkxxxxddxxxxOXOxxxxxdxxxxkkkkkkkO00OkkOOOO0OxxdolokOxollllodxxxkkkkkkkkkkkkkkkkdcodollodolc:::cccc::::;;:;;;;;,'...'':kxoxollllllllllodxxxkkkkkxx\n \
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMN0OO0000000000OkkOOOxl::;;;,,,,,''''''''.'.............,x0xoo,.,;;;;;;ckOxdxxxxxxkkkkkkkkkdoooollclok0xodooddddddxOOOkxxxxdxdOKkdddodxxxk0X0kxxxdddxdk0kdddddxkOkOkxddddddddddkkoclccccodxxxkkkkkkkkkkkkkkxkxl:llcccoxxoc::::::::::::::::::;,'',,,:kkoxdllllllllllodxxxxkkkkxx\n \
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWKKKKK000000OOOOO00OOdlcccc:::::::::::;;;;;;;;;;;;;;;;,:k0dll;,,,,,...'dxddxxxxxkkkkkkkkkxdoooolccldkxoxkxddxxxxxOKOxxxxxxxxx0KkxxdddxdkKNXX0xddddxxxOX0xxxxxxxxkXKkxxxxddddxdxOxlc:clcodddxxxkkkkkkkkkkkkkkxxxkkxxxO0OOkxdddddooooooollllllc:ldolok0kkdllllllllllldxxxxxkkkxx\n \
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWWWWWWWWNNNNNNWWWWWNNNNNNNXXXXXXXXKK0Okkxdoollllodxxk00dcoxxollc:,';dxdddxxxxkkkkkkkkxxolllc::clddddO0kdxxxxxxOKOxxxxxxxdxKKxxxddxxxxOXK0OxddddxxdOX0xxxxxxxxkK0xxxxxxxxOKkddxoc:clclooodxxxkkkkkkkkkkkkkkKMMMMMMMMMMMMMMMMWWWWWWWWWNNNNNNNNNKXNNWNNOolllllllllldxxddxxxkxx\n \
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWWNNNXXXKKKKKK0OocxKKK0KKKKK0kddddxxxxkkkkkkkxxdoc::;;looddddO0xddddddxO0kkkxdxxxdxOOxdxdddxxxxOOxxxxdddxxdkKOxxxxxxxdkK0xxxxxxxdkKOxxxdlccc::cclodxxxxkkkkkkkkkkkxKWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNXWMMMW0olollllllllodxddxxxkxd\n \
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWWNNXNNNNNNWWWMWWWWWWWXOxolkKK00K0Okkkxddddxxxxxkkkkkkxddoc:;,cxdoddddk0xdddddddxOOkxdddddddkkdddooddddkK0xxxdddoooodxxdddddxkO00kxxxxxxxdk0kdddxddl;,,;cloddxxxxxxkkkkkkkkx0WMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNXWMMMMKdooolllllllodddooodddo\n \
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWWWWWNNXK000OOxxxxkkkO00KK0OKXK0Okxxxxxkkkxxxxxoodddddxxxxxkkkkkxxxdol;';oxooodxddxdooodoook0xddddddxdxK0xdxddddddkKOxdddddooddO0kdddddddx00xddddddxxOOxddddoxx:.';cloddxxxxxxxxxxkkkkx0WMMMMMMMMMMMMMMMMMMMMMMMMMMWWMMMMMNXWMMMMKdooolllllcclooolllllll\n \
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWWWWWWWNNXXKK0OOOkkkxxxxxxxxxkkkkkkkxxxxk0XKOkkxxxkkkkxxxxddolloddddxxxxxkkkkxxxddol,':oxdoxxdldxdodddddxOkdoooooooox0OdddodddddkKOxxxddddxddOKkxxxxxxxxOKkddoooooddddkxdddxxc'':clooddxxxxxxxxxkkkkx0WMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNXWMMMMXxoooollllcclodolclllll\n \
MMMMMMMMMMMMMMMMMMMMMMWWWWWWWWWWWNNXXK00OOOkkkkxxxxxxxxkkkkkkkkkkkkkxxkkkOOOOO0K0Okkkxxddddddoodddddxddddxxxxxxkkkxxxxddol;,cloolooooxOxooooookOolooodddddOKkdxdddxdxxOKOdxddddddddOKkxxxxxxxxkKOxdddddoxOdodkkdxkdc,,:clooddxxxxxxxxxkkkkx0WMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNXWMMMMXxoooolllllccodoolllllo\n \
MMMMMMMMMWWWWWWWWWWNNNXXKK00OOOkkxxxxdddddxxxxkkkkxxxxxkkkxxxxxkkkkkkOOOOOOOkkxxdddoolllloooddxxxkkkxddddxxxxxxxkxxxxxddol,,ccloloolodxdoolllok0xddddddddx0KkdxdddxdddOKOddddddddddOKkdxdxddddx0OdodooodkOkdoddodddc',:clooddxxxxxxxxxxxxxx0WMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWXNMMMMXxooooollllcclddooooooo\n \
WWWWWNNNNXXKK00OOkkkxxxxddddddddxxxxxxxxxxxxxxxxxxxxxxxxkkOOOOOOkkkxxxxdddooollllllooodddxxxxxxxxxxxxdddddxxxxxxxxxxxxdolc,;::lxolooOkoloooddx00xdddddddox00ddddddddddOKkdddddddddd0Kxdddddoook0kooooolodxdlodddoooc',:clooddxxxxxxxxxxxxxx0WMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMWNWMMMMNkoooooolllcclooooddddd\n \
KK00OOOkxxxdddodddddxxxxxxxxxxxxxxxxxxxxxdxxdxxkkOOkkkkxxkkkxxddooollllclllllooodddxxxxxxxxxxxxxxxxkxdddddxxxxxxxxxxxddol:,,;lodddddOOdddddddkKOdddddddddx0OdoooodooddO0xdddddoooodO0dooodddddkKOxxxxxdoxxlc:cloxxoc,,:clooddxxxxxxxxxxxxxxOWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNOdodoooollccloooooodxx\n \
xxdxxxxxxxxxxxxxxxxxxxxxxxxxxxdddddxxxkkkkxxkkkkkkkxdddoooolllccccccllooodddddddddxxxxxxxxxxkkOOOOOOkoddddxxxxxxxxxxxdoll;,;ldoloook0xdddddddOKkdddddddddxKOdddooddddd0Kxdddddoodod00xddddddddkK0xxxxxxxO0xdolc::cc:,';:clodddxxxxxxxxxxxxxkKXXXXNNNNNNWWWMMMMMMMMMMMMWWMMMWWWMMMMMMMWOdddoooollcclooooodddx\n \
xxxxxxxxxxxxdxxxdddddddddddxxkkkOOOOkkkkxxddddooooollllccccclllloooddddddddddddddxxdddxxxkO0000OOkxxdoodddxxxxxxxxxxddolc;;::lollllxOdodddddd00xdddddddddkKOdddodddddd00xdxdddddxxx0KkdxddddddxK0xxxxxxxxOOxxxxdo:;'.';:clooddxxxxxxxxxxxxxdddxxxxxxkkkkOO00KXXNNNXKXNNNNWWWWMMMMMMMMWOdddoooollcclloooodxdd\n \
xxxddddddddddddddxxkkOOOOkkkkkkkxxdooooolllcccccc:::ccclllloooooooooooooooddddddxxkOOOOkkOOkxxxxxxxdoooddxxxxxxxxxxddoll:'';:odooookkdooddddx00ddddddddddOKkdddodddddxK0ddddddodddx0Kxddddddddx00xdddddddO0xxxdxOxl;..,:cloodddxxxxxxxxxxxddolloooooddddddxxkkkkOOkxkOO0KKNWWWMWWNXK0Okdddooooolccllooooxxdd\n \
xxxdddxxxkkOOOOOO0OOOOkkxxddddddddddddoooolllllllllooooddoooooooooooooddddddxkO0000OOkxxxxxxxxxxxxxdooddddxxxxxxxxxddolc;..,lxdooodOkooododoxKOddddddddddOKxodoodddddx0Oddddddddddx00xddddddddx00ddddddddO0xdxdxkd:;..,:cllodddxxxxxxxxxxxddl,',,,,,,,,,,,;:cloxkkkkkxddxxxkkOOOkxddoodddooooooocccooooodxdd\n \
OOOOOOOOkOOOkkxxdddddddddddddddddddddddddxxxxxddddddddoooooddddddddddxkOOOkkOOOkxxddxddxxxxxxxxxxxdooodddddddxxxxdddool:'.,cdxooooxOdoooooook0xoooooooood00dodooddddxOOkddddddodddd00doooddodod00ddddddddk0kdddxkd;...';:clodddxxxxxxxxxxxxdolcccllcclllcc::;,,;:loxkOkxdoooooooooooooddddoooooolccooooooddd\n \
0OOkkxxdddddddddddddddddddxxddddddddddddxdddddddddddddddddddddxxkO00K000Okxxxxxxxxxxxxxxxxxxxxxxxxdooddddddddxxxxdddolc;''clddooookkooooooook0dloooooooldOOooolododOKKKKOxdddddddox0Odooooooood0Oddddddddk0xddddkxl,..';:cloddddxxxxxxxxxxxdddoddddddxxxxxxxdoc:,',:ldkOkdoooooooooooooddooooooolccooodooddd\n \
ddddddddddddddddddddddddddddddddddddddddddddddddddddddddxkkOO00000Okxxddddddddddddxxxxxxxxxxxxxxxdoooodddddddxxxxdddolc;;;:coollllxxllllllllk0dlooooooold0OooolooooONXKKOdddddddddxKOddoooooood0OddddddddkOxddddkxo:...,:cloodddddxxxxxxxxxdddoddddddddxxxxxxxxxdc;'';ldOOxlllloooolllodoooooooolccooooodddd\n \
XXKKKKK0000OOOOOOOOOkkkkkxxxxxxdddddddddddoddodddxkOO00000Okkkxxxxxdddddddddddddxxxxxxxxxxxxxxxxxdoooodddddddxxxdddool:;odccoollllddllllllllkOoloooooooox0koooooooodxOOxdooooooddoxKOdddoooooox0kooooooooxOxododxl,....,;:lloddddddxxxxxxxxddddddddddddddxxxxxxxxxdl,',cdO0xlloooolllloooooooooolccooooddddd\n \
KKXXNNWWWMMMMMMMMMMMWWWWWWWNNNNNNNNXXXXXKKKKKKKKKKK00Okxxdddddxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxkkdoooooddddddxxxxdddolc::oocclolcccooccccclclkOolllloooolx0xooolloooooOOollllllloooxKkoooooooolx0dllllllolxkoooodd:...,:;;:clooddddddxxxxxxdddddoodddddddddxxxxxxxxxxoc,':d0Kxooooooolloddoooooollcclooddddod\n \
lloooddxxkkOOO00KKXNNNWWMMMMMMMMMMMMMMMWNNXXK0Okxddddddddddddddddddddxxxxxxxxxxxxxxxxxxxxxxkkkkxdooooodddddddxxxdddolc;:c::ccolcccooccccccclkkllllllllllkOdlllcccclclkxlllllllloook0xoooooooookOdllllllllddloloddl:'.,c;;:cloodddddddxxxxxxdddddoodooddoodxxxxxxxxxxxxo,,cd0Odoooooooooddooooooolcclooddoooo\n \
K00OOkkkxddollllllooddxxkkOOOOOOO00KXNNNXXXKK00000000OOOOOOOOOOOOkkkkkkkkxxxkxxxxxxxxxxxxxkxxxxxooooooddddddddddddoolc;;::ccclllccllccccccclkklllllllcclxkl::;;;;;;;:lc;,,,,,,,,;:oxoclllllllokOollllllcodolllodooxl';o:;:cloooddddddxxxxxxddddkxdxxdddoddxdxxxxxxxxxxkl':ok0kdO0Okkkxddddoooooolccloodooooo\n \
0000KKKKK000OOkkxxdoooddddoooollllloddxxkkOOO00KKXXNNNWWWWMMMMMMWWWWWWWWNNNNNNNNNNNNNNNNXXXXXXKkooooooodddddddddddoll:;cx0kc:cllccclcccccccokxcccc:::;,,:c,'.......,:;'.........,coc:;,,,;:::lkxlllllcclddllcll:;;cc';o:;:clloodddddddxxxxxdxdxO0xkOxdxxdxOOkxxxxxxxxxOx,;lx0Ox0WNK000kddddooooolccloooooooo\n \
ddddddddddddddddxkO0KXNNNNXXXKK00OOOkxxxddooooloooodddxxkkkOO000KKKXXNNNWWWWMMMMMMMMMMMMMMMMMMNkoooooooodddddddddoolc:oKWWKocclolcccccccccclxo:;;,,'''..;c,'''',',';l:''......';loooooc:,'.;;:c::ccccccldolc:::;;:lo:l0d::clloooodddddxxxddddddk0xxOkxxkxxkOkxxxxxxxxxkk:,lxOOxONWNKKKOxddddoooooc:clooooooo\n \
ddddddddddodxkOKXNWMMMMMMMMMMMMMMMMMMWWWNNXXKK00OOOkkxxddddooooooodddxxxkkkOO000KKKXXXNNNNWWWWKdoooooooooddddddddoolcc0WWWWOlclol:::::::::;;:;'',;,,,,,';o:,,,,,,,,;l:''....';ccclloooooool;'..'',;:::clllodollllloo;lkd:;:clooooddddddddddddddk0kk00kOX0kOKOxxxxxxxxxkk:,cdO0xOXNNNNNXkxxdddooooc:clooooooo\n \
ddddddddoodk0KKKXXNNNNNNWWWWWWWMMMMMMMMMMMMMMMMMMMMMMWWNNNXXXKKK000OOOkkkxxxxxxdddddxxxxkkkkOOxoloooooooodddddddooll:oXWWWXkc;;;;,'',;'''''''''':c;;,,'':ol;;,;;;;,:o:''.',;:::ccclloooox0Oo:'.....'',;;;;:llc:llcdkco0x:;:clloooddddddddddddddxOxxOOxkOkxxkxxxxxxxxxxxOl'cdk0kONMMMMMNOxxddddoooc:clooolllo\n \
dxkkkxxddddddddddxxxxxxxkkkkkOOOOOO000000000KKKKKXXXXXXXNNNNNWWWWWWWWWWWNNNNNXXKKK000OOOkkxxddollllloooooooodddooolc:lO00xc;'.',,,,,:l;',,,,,,,:oo;;;,'':do::;::::::l:,,,,;;;;:::cccllok0koolccc:::;;;cc;;;;,,:kdcxx:lko;;:clloooddddddddddddddxkdx00kk0Oxk0OxxxxxxxxxxKd,:ok0kkXMMMMMNOxxxdddoooc:cllllllll\n \
00OkxxddddddddxxxxddxxxxxxxddddddddddddddddddddddddddxxxxkO00KKKKKKKKKKKKXXXXXXXXXXXXXXKKKK0Oxolllllloooooooooooollc:::cc;,',;:;;:::ldc;:;;::::cdl;;;;;,:xd::::c::cllc:;::;;;;;::::ccokkdlcolccllllllodlc:cc,';oc;dd:lkd;,:cclloooodddddddddddddkxdkkxk00kkK0xxxxxxxxxxKO,;ox0OkXMMMMMNOxxxddooooc:cllllolll\n \
xdddddddddddddddxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxkkOO000000000000000000000000000000OOOOOOOxllllllllllloooooolllc:;:lolll::lc:::::cxoccccccccoko:::::;;ddc:::c::oxoooc:::;,;::::coxxdlc:cxdccllllloxdlllooc;cklcOkcoOo,,::clloooooddddddddddddxddk0kk00kkKKkxxxxxxxxx0O;,lxOOxKMMMMMNOxxxxdooooc::llllllll\n \
dddddddddddddddddddxddddddxxxxxxxxxxxxxxxxxxxxxxxkOO0000000000000000000000000000000000000000Odllllllllllllllllllllc;cdxolddl:cc:::cccdxlcccccccoko:cc::;;dxc::::::oxoxxc:c:,,::::lxkdlc:;;lkdccclllldkooolodc::l::xxcoKx;,;:cclloooooddddddddddx0Ox0Kkk00kkOOxdxxxxxxxd00:,ldOOx0WMMMMW0xxxddooolc;:cllllllo\n");

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
    struct elt* myname = name_list(); 
    print_list(myname);
    free_list(myname); 

    /*
    draw_me()
    */
    draw_me();
    printf("\nGot to 4");

}
