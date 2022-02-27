 #include <iostream>
 #include <thread>
 #include <string>
 #include <atomic>
 #include <vector>
 #include <sstream>
 #include <fmt/format.h>

std::atomic_flag flag = ATOMIC_FLAG_INIT;
static int p=20;
void function(int x, int y)
{
    //try to acquire lock
     while(flag.test_and_set())
     {}
     //critical section 
     p=p+x;
     fmt::print("Thread : {} incremented p by {} . P = {} \n", y, x, p);
     //release lock
     flag.clear();
     return ;
}

int main()
{
    std::vector<std::thread> threads;
    for(int i=0; i<10 ;i++)
    {
        threads.push_back(std::thread(function,i*3,i));
    }
    for(int i=0;i<10;i++)
    {
        threads.at(i).join();
    }



    return 0;
}