extern puts

section .text                           ;this says that we're about to write code (as opposed to data)

global sayHello                         ;function declaration for sayHello
global  myPuts                          ;function declaration for myPuts
global  myGTOD                          ;function declaration for myGTOD

sayHello:
        mov     rdi, helloString        ;move helloString to rdi
        call    puts                    ;calls puts

        ret                             ;after printing returns void

myPuts:
        mov     rdx, rsi                ;move rsi (len), to rdx (where the count should be)
        mov     rsi, rdi                ;move rdi (*s) to rsi (where the string pointer should be) 
        mov     rdi, 1                  ;set rdi to 1 for printing to stdout
        mov     rax, 1                  ;set rax for sys_write

        syscall                         ;execute system call (sys_write)

        ret                             ;after printing return void

myGTOD:
        sub     rsp, 16                 ;make 16 bytes struct on the stack
        mov     rdi, rsp                ;move 16 byte struct to rdi (timeval) for syscall 96
        mov     rsi, 0                  ;put null pointer in the rsi (timezone) for syscall 96
        mov     rax, 96                 ;set rax for sys_gettimeofday
        syscall                         ;execute system call instruction (sys_gettimeofday)

        mov     rax, [rsp]              ;move tv_sec (seconds) from timeval struct
        mov     rdx, [rsp+8]            ;move tv_usec (microseconds) from timeval struct
        add     rsp, 16                 ;give back stack space  

        ret                             ;return tv_sec and tv_usec


section .rodata                         ;this is the read only data (hello is a constant) 
helloString: db "hello",0               ;hellostring is the name of our symbol
                                        ;db is the directive to put data in our object file
                                        ;the 0 is the null terminator that puts is expecting.  
                                        ;nasm does NOT null terminate our string automatically