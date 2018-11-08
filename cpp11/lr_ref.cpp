#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>

void test1()
{
	int i = 123;
    //int &intR = i;
}

void test2()
{
	int i = 123;
    int &intR = i;
}

void test3()
{
    int &&intRR = 456;
	int xx = intRR;
    printf("%d\n", xx);
}

void test3_2()
{
    int &&intRR = 456;
	intRR = 567;
	int xx = intRR;
}

class C1
{
    public:
        C1(int v)
        {
            std::cout << "C1()" << std::endl;
            m1 = v;
        }

        C1(const C1 &obj)
        {
            std::cout << "C1 &" << std::endl;
            m1 = obj.m1;
        }
        
        C1(C1 &&obj)
        {
            std::cout << "C1 &&" << std::endl;
            m1 = obj.m1;
        }

        C1 & operator = (const C1 &obj)
        {
            std::cout << "C1 =&" << std::endl;
            m1 = obj.m1;
        }

        C1 & operator = (C1 &&obj)
        {
            std::cout << "C1 &&=" << std::endl;
            m1 = obj.m1;
        }
    public:
        int m1;
};

C1 test5()
{
    std::cout << "test5() begin" << std::endl;

    C1 oc(456);

    std::cout << "test5() end" << std::endl;
    
    return oc;
}

std::vector<C1> test6()
{
    C1 oc(456);
    std::cout << "***" << std::endl;
    std::vector<C1> v;
    v.reserve(10);
    v.push_back(oc);
    std::cout << "***" << std::endl;
    v.push_back(oc);
    std::cout << "***" << std::endl;
    v.push_back(oc);
    std::cout << "***" << std::endl;

    std::cout << "test6()" << std::endl;
    
    return v;
}

C1 test7()
{
    C1 oc(789);
    C1 occ = oc;

    std::cout << "test7()" << std::endl;
    
    return occ;
}

C1 test8(int i)
{
    std::cout << "test8()" << std::endl;
    if (i % 100 == 12)
    {
        C1 oc(789);
        //C1 occ = oc;
        return oc;
    }
    else 
    {
        C1 oc(135);
        //C1 occ = oc;
        return oc;
    }
}

int main(int argc, char **argv)
{
    std::cout << "---------------" << std::endl;
    C1 oc1(123);
    C1 oc2(oc1);
    C1 oc3 = oc1;
    C1 oc4(std::move(oc1));

    std::cout << "---------------" << std::endl;
    C1 oc5 = test5();
    std::cout << oc5.m1 << std::endl;

    std::cout << "---------------" << std::endl;
    C1 oc6(test5());
    std::cout << oc6.m1 << std::endl;

    std::cout << "---------------" << std::endl;
    std::vector<C1> v = test6();
    //v = std::move(test6());
    std::cout << "------***-" << std::endl;
    for (auto &iter : v)
    {
        std::cout << iter.m1 << std::endl;
    }

    std::cout << "---------------" << std::endl;
    C1 oc7(1);
    oc7 = test7();
    std::cout << oc7.m1 << std::endl;

    std::cout << "---------------" << std::endl;
    //C1 oc8 = test8(atoi(argv[1]));
    //std::cout << oc8.m1 << std::endl;

    std::cout << "------***-" << std::endl;

    C1 oc8_1 = test8(110);
    //C1 oc8_1 = test5();
    std::cout << oc8_1.m1 << std::endl;


    std::cout << "---------------" << std::endl;

    test1();

	return 0;
}
