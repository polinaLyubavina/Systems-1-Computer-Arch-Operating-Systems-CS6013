#include <iostream>
#include <sys/time.h>

extern "C" {
        void sayHello();
        void myPuts(const char* s, int len);
        timeval myGTOD();
}

int main() {
        const char *s = "testtest";

        std::cout << "\nsayHello():\n";
        sayHello();

        std::cout << "\nmyPuts():\n";
        myPuts(s, 8);
        std::cout << "\n";

        std::cout << "\nmyGTOD():\n";
        timeval* syscall_gtod;
        gettimeofday(syscall_gtod, NULL);
        timeval gtod = myGTOD();
        std::cout << gtod.tv_sec << std::endl;
        std::cout << gtod.tv_usec << std::endl;      
        std::cout << std::endl; 

        
        std::cout << "\ngettimeofday syscall:\n";
        std::cout << syscall_gtod->tv_sec << std::endl;
        std::cout << syscall_gtod->tv_usec << std::endl;
        std::cout << std::endl;

        return(0);
        
}