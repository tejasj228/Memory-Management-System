/*
All the main functions with respect to the MeMS are inplemented here
read the function discription for more details

NOTE: DO NOT CHANGE THE NAME OR SIGNATURE OF FUNCTIONS ALREADY PROVIDED
you are only allowed to implement the functions
you can also make additional helper functions a you wish

REFER DOCUMENTATION FOR MORE DETAILS ON FUNSTIONS AND THEIR FUNCTIONALITY
*/
// add other headers as required


//Author Tejas Jaiswal (CSD) 2022538, Pranshu Goel (CSSS)




/* In the following Program, We have taken some assumptions as all the facts about the program were not clear
   from the document provided */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h> // Include this for uintptr_t
#include <sys/mman.h>
#include <math.h>



#define PAGE_SIZE 4096



struct MAINMAINCHAIN
{
    int current;
    int t_size;
    uintptr_t addresss;
    void *start;
    void *end;
    struct MAINMAINCHAIN *next;
    struct MAINMAINCHAIN *pre;
    struct SUBSUBCHAIN *nxt;
    void *PH_ADD;
    int no;
};




int numb = 1;


struct SUBSUBCHAIN
{
    int data;
    int SZE;
    int GG;
    char GGWP;
    int IS__NOT__HOLE;
    void * PH_ADD;
    void *start;
    void *end;
    struct SUBSUBCHAIN *next;
    struct SUBSUBCHAIN *pre;
};
//Author Tejas Jaiswal (CSD) 2022538, Pranshu Goel (CSSS)


struct MAINMAINCHAIN *head;



size_t SUBxNODExSIZE = sizeof(struct SUBSUBCHAIN);
size_t MAINxNODExSIZE = sizeof(struct MAINMAINCHAIN);
void *START_VA;






int HEXA_TO_DECIMAL(const char *HEXA_STRING)
{
    // Check if the input string is empty or null
    if (HEXA_STRING == NULL || HEXA_STRING[0] == '\0')
    {
        return 0;
    }

    // Use strtol to convert the hexadecimal string to an integer
    // The base argument is set to 16 for hexadecimal conversion
    char *ENDDD__PTR;
    long decimalValue = strtol(HEXA_STRING, &ENDDD__PTR, 16);

    // Check for conversion errors
    if (*ENDDD__PTR != '\0')
    {
        fprintf(stderr, "Conversion error: Invalid hexadecimal string\n");
        return 0;
    }

    return (int)decimalValue;
}

/*
Use this macro where ever you need PAGE_SIZE.
As PAGESIZE can differ system to system we should have flexibility to modify this
macro to make the output of all system same and conduct a fair evaluation.
*/

/*
Initializes all the required parameters for the MeMS system. The main parameters to be initialized are:
1. the head of the free list i.e. the pointer that points to the head of the free list
2. the starting MeMS virtual address from which the heap in our MeMS virtual address space will start.
3. any other global variable that you want for the MeMS implementation can be initialized here.
Input Parameter: Nothing
Returns: Nothing
*/
void mems_init()
{
    head = mmap(NULL, MAINxNODExSIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    head->next = NULL;
    head->pre = NULL;
    START_VA = (void *)1000;
}


void SAMPLE()
{
    // Test Case
    char SAMPLE_;
    char SAMPLE__;
    char SAMPLE____;
    char SAMPLE______;
}

/*
This function will be called at the end of the MeMS system and its main job is to unmap the
allocated memory using the munmap system call.
Input Parameter: Nothing
Returns: Nothing
*/


//Author Tejas Jaiswal (CSD) 2022538, Pranshu Goel (CSSS)

void mems_finish()
{
    struct MAINMAINCHAIN *T__M__P = head->next;
    while (T__M__P->next != NULL)
    {
        T__M__P = T__M__P->next;
    }

    while (T__M__P != NULL)
    {
        struct SUBSUBCHAIN *subnode = T__M__P->nxt->next;
        struct SUBSUBCHAIN *pre;
        while (subnode != NULL)
        {
            pre = subnode->pre;
            munmap(pre->PH_ADD, SUBxNODExSIZE);
            subnode = subnode->next;
        }
        struct MAINMAINCHAIN * free_tmp = T__M__P;
        T__M__P = T__M__P->pre;
        munmap(free_tmp->PH_ADD,MAINxNODExSIZE + free_tmp->t_size);
    }
}

/*
Allocates memory of the specified size by reusing a segment from the free list if
a sufficiently large segment is available.

Else, uses the mmap system call to allocate more memory on the heap and updates
the free list accordingly.

Note that while mapping using mmap do not forget to reuse the unused space from mapping
by adding it to the free list.
Parameter: The size of the memory the user program wants
Returns: MeMS Virtual address (that is created by MeMS)
*/


//Author Tejas Jaiswal (CSD) 2022538, Pranshu Goel (CSSS)
void *mems_malloc(size_t size)
{

    // printf("size : %ld\n",size);
    size_t NODE__SIZEE = size;

    if (size % PAGE_SIZE != 0)
    {
        NODE__SIZEE = (size / PAGE_SIZE + 1) * PAGE_SIZE;
    }

    // printf("%ld\n",NODE__SIZEE);
    if (head->next == NULL)
    {
        // Allocate memory for the main chain and sub chain
        // Initialize and set up the structure
        // Add the main chain and sub chain to the free list
        // Update related values and return MeMS virtual address

        struct MAINMAINCHAIN *MAIN____NODE = mmap(NULL, MAINxNODExSIZE + (NODE__SIZEE), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        uintptr_t DECIMAL___ADDRESS = (uintptr_t)MAIN____NODE;
        MAIN____NODE->PH_ADD = (void *)MAIN____NODE;
        MAIN____NODE->addresss = DECIMAL___ADDRESS;
        MAIN____NODE->t_size = NODE__SIZEE;
        MAIN____NODE->start = START_VA;
        MAIN____NODE->end = NODE__SIZEE + START_VA - 1;
        MAIN____NODE->current = NODE__SIZEE - size;
        MAIN____NODE->next = NULL;
        MAIN____NODE->pre = NULL;

        // sub chain first node
        struct SUBSUBCHAIN *SUB____NODE = mmap(NULL, SUBxNODExSIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        SUB____NODE->IS__NOT__HOLE = 1;
        SUB____NODE->SZE = size;
        SUB____NODE->start = START_VA;
        SUB____NODE->PH_ADD = (void *) SUB____NODE;
        SUB____NODE->end = START_VA + size - 1;
        SUB____NODE->next = NULL;
        SUB____NODE->pre = NULL;

        MAIN____NODE->nxt = SUB____NODE;

        // adding hole
        struct SUBSUBCHAIN *HOLE_____NODE = mmap(NULL, SUBxNODExSIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        HOLE_____NODE->IS__NOT__HOLE = 0;
        HOLE_____NODE->SZE = MAIN____NODE->current;
        HOLE_____NODE->start = SUB____NODE->end + 1;
        HOLE_____NODE->PH_ADD = (void *) HOLE_____NODE;
        HOLE_____NODE->end = MAIN____NODE->end;
        HOLE_____NODE->next = NULL;
        HOLE_____NODE->pre = SUB____NODE;
        
        SUB____NODE->next = HOLE_____NODE;

        head->next = MAIN____NODE;

        MAIN____NODE->no = numb;
        numb++;

        return START_VA;
    }
    else
    {
        // Check if there is a sufficiently large segment in the free list
        // If not, allocate more memory using mmap
        // Update the free list and return MeMS virtual address
        struct MAINMAINCHAIN *PRE___NODE = head->next;
        struct MAINMAINCHAIN *temp = head->next->next;
       
        if (PRE___NODE->current >= size)
        {
            temp = PRE___NODE;
        }
        else
        {
            while (temp != NULL && temp->current < size)
            {
                PRE___NODE = PRE___NODE->next;
                temp = temp->next;
            }
        }

        if (temp == NULL)
        { // NO main nodes have memory more than the given size

            struct MAINMAINCHAIN *MAIN____NODE2 = mmap(NULL, MAINxNODExSIZE + (NODE__SIZEE), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
            uintptr_t DECIMAL___ADDRESS = (uintptr_t)MAIN____NODE2;
            MAIN____NODE2->addresss = DECIMAL___ADDRESS;
            MAIN____NODE2->t_size = NODE__SIZEE;
            MAIN____NODE2->start = PRE___NODE->end + 1;
            MAIN____NODE2->end = NODE__SIZEE + PRE___NODE->end;
            MAIN____NODE2->current = NODE__SIZEE - size;
            MAIN____NODE2->next = NULL;
            MAIN____NODE2->pre = PRE___NODE;
            MAIN____NODE2->PH_ADD = (void *)MAIN____NODE2;
            PRE___NODE->next = MAIN____NODE2;

            struct SUBSUBCHAIN *SUB____NODE = mmap(NULL, SUBxNODExSIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
            SUB____NODE->IS__NOT__HOLE = 1;
            SUB____NODE->PH_ADD = (void *) SUB____NODE;
    
            SUB____NODE->SZE = size;
            SUB____NODE->start = MAIN____NODE2->start;
            SUB____NODE->end = MAIN____NODE2->start + size - 1;
            SUB____NODE->next = NULL;
            SUB____NODE->pre = NULL;
            MAIN____NODE2->nxt = SUB____NODE;

            struct SUBSUBCHAIN *HOLE_____NODE = mmap(NULL, SUBxNODExSIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
            HOLE_____NODE->IS__NOT__HOLE = 0;
            HOLE_____NODE->PH_ADD = (void *) HOLE_____NODE;
            HOLE_____NODE->SZE = PAGE_SIZE - size;
            HOLE_____NODE->start = SUB____NODE->end + 1;
            HOLE_____NODE->end = SUB____NODE->end + 1 + PAGE_SIZE - size;
            HOLE_____NODE->next = NULL;
            HOLE_____NODE->pre = SUB____NODE;

            SUB____NODE->next = HOLE_____NODE;
            MAIN____NODE2->no = numb;
            numb++;
            void *T__M__P = SUB____NODE->start;
            return T__M__P;
        }
        else
        { // IF the main node of memory more than the size have been found

            struct SUBSUBCHAIN *SUB___TEMP = temp->nxt;
            // printf("hole size %d\n",SUB___TEMP->next->SZE);
            while (SUB___TEMP->IS__NOT__HOLE == 1)
            {
                SUB___TEMP = SUB___TEMP->next;
            }
            if (SUB___TEMP->IS__NOT__HOLE == 0)
            {
                SUB___TEMP->SZE = size;
                SUB___TEMP->IS__NOT__HOLE = 1;
                SUB___TEMP->start = SUB___TEMP->pre->end + 1;
                SUB___TEMP->end = SUB___TEMP->pre->end + +size;
                temp->current = temp->current - size; // reducing CURRENT size of the main node

                struct SUBSUBCHAIN *HOLE_____NODE = mmap(NULL, SUBxNODExSIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
                HOLE_____NODE->IS__NOT__HOLE = 0;
                HOLE_____NODE->PH_ADD = (void *) HOLE_____NODE;
                HOLE_____NODE->SZE = temp->current;
                HOLE_____NODE->start = SUB___TEMP->end + 1;
                HOLE_____NODE->end = temp->end;
                HOLE_____NODE->next = NULL;
                HOLE_____NODE->pre = SUB___TEMP;

                SUB___TEMP->next = HOLE_____NODE;

                void *T__M__P = (void *)SUB___TEMP->start;
                return T__M__P;
            }
        }
    }
}


void DECODE()
{
    // This function is for decoding purpose
}

void DECODE_2()
{
    // This function is for decoding purpose
}

/*
this function print the stats of the MeMS system like
1. How many pages are utilised by using the mems_malloc
2. how much memory is unused i.e. the memory that is in freelist and is not used.
3. It also prints details about each node in the main chain and each segment (PROCESS or HOLE) in the sub-chain.
Parameter: Nothing
Returns: Nothing but should print the necessary information on STDOUT
*/

//Author Tejas Jaiswal (CSD) 2022538, Pranshu Goel (CSSS)
void mems_print_stats()
{
    printf("----- MeMS SYSTEM STATS -----\n");
    int pages_used = 0, space_unused = 0, main_chain_length = 0, total_main_chain = 0;
    struct MAINMAINCHAIN *T__M__P = head->next;

    while (T__M__P != NULL)
    {
        pages_used += T__M__P->t_size / PAGE_SIZE;
        main_chain_length += 1;
        printf("MAIN[%ld:%ld]->", (uintptr_t)T__M__P->start, (uintptr_t)T__M__P->end);
        struct SUBSUBCHAIN *SUB___TEMP = T__M__P->nxt;
        while (SUB___TEMP != NULL)
        {
            if (SUB___TEMP->IS__NOT__HOLE == 1)
            {
                printf("P[%ld:%ld] <-> ", (uintptr_t)SUB___TEMP->start, (uintptr_t)SUB___TEMP->end);
            }
            else if (SUB___TEMP->IS__NOT__HOLE == 0)
            {
                printf("H[%ld:%ld] <-> ", (uintptr_t)SUB___TEMP->start, (uintptr_t)SUB___TEMP->end);
                space_unused += SUB___TEMP->SZE;
            }

            SUB___TEMP = SUB___TEMP->next;
        }

        printf("NULL\n");

        T__M__P = T__M__P->next;
    }

    printf("Pages Used: %d\n", pages_used);
    printf("Space Unused %d\n", space_unused);
    printf("Sub Chain Length Array : ");
    int arr[main_chain_length];
    int i = 0;
    T__M__P = head->next;
    while (T__M__P != NULL)
    {
        struct SUBSUBCHAIN *SUB___TEMP = T__M__P->nxt;
        int x = 0;
        while (SUB___TEMP != NULL)
        {
            x += 1;
            SUB___TEMP = SUB___TEMP->next;
        }
        arr[i] = x;
        i += 1;
        T__M__P = T__M__P->next;
    }
    printf("[ ");
    for (int j = 0; j < main_chain_length; j++)
    {
        printf("%d ,", arr[j]);
    }
    printf(" ]\n");

    printf("--------------------------------\n");
}

/*
Returns the MeMS physical address mapped to ptr ( ptr is MeMS virtual address).
Parameter: MeMS Virtual address (that is created by MeMS)
Returns: MeMS physical address mapped to the passed ptr (MeMS virtual address).
*/  
void *mems_get(void *v_ptr)         // considering the case for HOLE
{
    uintptr_t DECIMAL___ADDRESS = (uintptr_t)v_ptr;

    if(head != NULL){
        struct MAINMAINCHAIN * T__M__P = head->next;
        while (T__M__P!=NULL)
        {
            struct SUBSUBCHAIN * SUB___TEMP = T__M__P->nxt;
            while (SUB___TEMP != NULL)
            {
                if(DECIMAL___ADDRESS >= (uintptr_t) SUB___TEMP->start && DECIMAL___ADDRESS <= (uintptr_t) SUB___TEMP->end){
                    return SUB___TEMP->PH_ADD + (DECIMAL___ADDRESS - (uintptr_t) SUB___TEMP->start );
                }
                SUB___TEMP = SUB___TEMP->next;
            }
            T__M__P = T__M__P->next;
        }   
    }
    
    
}

/*
this function free up the memory pointed by our virtual_address and add it to the free list
Parameter: MeMS Virtual address (that is created by MeMS)
Returns: nothing
*/
void mems_free(void *v_ptr)
{

    struct MAINMAINCHAIN * T__M__P = head->next;
    int check = 1;
    while (T__M__P!=NULL && check != 0)
    {
        struct SUBSUBCHAIN * SUB___TEMP = T__M__P->nxt;
        
        while (SUB___TEMP!=NULL)
        {
            
            if((uintptr_t) SUB___TEMP->start == (uintptr_t) v_ptr && SUB___TEMP->IS__NOT__HOLE == 1){
                SUB___TEMP->IS__NOT__HOLE = 0;
                T__M__P->current += SUB___TEMP->SZE;
                
                check = 0;
                break;
            }
            SUB___TEMP = SUB___TEMP->next;
        }
        
        if(SUB___TEMP->pre != NULL && SUB___TEMP->pre->IS__NOT__HOLE == 0){

            struct SUBSUBCHAIN * NEW___S___NODE = mmap(NULL, SUBxNODExSIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
            NEW___S___NODE->IS__NOT__HOLE = 0;
            NEW___S___NODE->SZE = SUB___TEMP->SZE + SUB___TEMP->pre->SZE;
            NEW___S___NODE->PH_ADD = (void *) NEW___S___NODE;
            NEW___S___NODE->start = SUB___TEMP->pre->start;
            NEW___S___NODE->end = SUB___TEMP->end;
            NEW___S___NODE->next =SUB___TEMP->next;
            NEW___S___NODE->pre = SUB___TEMP->pre->pre;

            if(SUB___TEMP->pre->pre == NULL){
                T__M__P->nxt = NEW___S___NODE;
            }
            else{
                if(SUB___TEMP->next != NULL){
                    SUB___TEMP->next->pre= NEW___S___NODE;
                }
                if(SUB___TEMP->pre->pre != NULL){
                    SUB___TEMP->pre->pre->next = NEW___S___NODE;
                }
            }
            munmap(SUB___TEMP->pre->PH_ADD,SUBxNODExSIZE);
            munmap(SUB___TEMP->PH_ADD,SUBxNODExSIZE);
        }
        else if(SUB___TEMP->next != NULL && SUB___TEMP->next->IS__NOT__HOLE == 0){
            struct SUBSUBCHAIN * NEW___S___NODE = mmap(NULL, SUBxNODExSIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
            NEW___S___NODE->IS__NOT__HOLE = 0;
            NEW___S___NODE->SZE = SUB___TEMP->SZE + SUB___TEMP->next->SZE;
            NEW___S___NODE->PH_ADD = (void *) NEW___S___NODE;
            NEW___S___NODE->start = SUB___TEMP->start;
            NEW___S___NODE->end = SUB___TEMP->next->end;
            NEW___S___NODE->next =SUB___TEMP->next->next;
            NEW___S___NODE->pre = SUB___TEMP->pre;

            printf("%p\n",NEW___S___NODE->pre->start); 
            if(SUB___TEMP->pre == NULL){
                T__M__P->nxt = NEW___S___NODE;
            }
            else{
                if(SUB___TEMP->next->next != NULL){
                    SUB___TEMP->next->pre= NEW___S___NODE;
                }
                if(SUB___TEMP->pre != NULL){
                    SUB___TEMP->pre->next = NEW___S___NODE;
                }
     
            }
            munmap(SUB___TEMP->next->PH_ADD,SUBxNODExSIZE);
            munmap(SUB___TEMP->PH_ADD,SUBxNODExSIZE);
        }

        T__M__P = T__M__P->next;
    }
    

}
void TEST_()
{
    int TEST_A;
    int TEST_B;
    int TEST_C;
    int TEST_D;
    // test Case
}


//Author Tejas Jaiswal (CSD) 2022538, Pranshu Goel (CSSS)

