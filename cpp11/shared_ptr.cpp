#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <thread>


void thread1()
{
    std::cout << "thread1()" << std::endl;

    while (true)
    {
        sleep(1);
    }
}


void thread2(int n, std::string sName)
{
    std::cout << "thread2()" << std::endl;

    while (true)
    {
        ;//sleep(1);
    }
}

int main(int argc, char **argv)
{
    std::shared_ptr<int> sp1 = std::make_shared<int>(10);
    std::thread t1(thread1);
    std::thread t2(thread2, 1, "hi");

    t2.detach();
    t1.join();

    std::cout << "---------------" << std::endl;


	return 0;
}
