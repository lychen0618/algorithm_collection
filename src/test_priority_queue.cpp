#include <chapter06/priority_queue.hpp>
#include <iostream>
#include <cassert>
using chapter06::priority_queue;

#define EXPECT_EQUAL(a, b) \
    do                     \
    {                      \
        assert(a == b);      \
    } while (0);

//!Node:用于测试的类型
struct Node
{
    Node(int k) : key(k) {}
    double key; /*!< key存放数据 */
};

class QueueTest
{
public:
    typedef std::function<bool(std::shared_ptr<int>, std::shared_ptr<int>)> Int_Compare_Type;      /*当最小优先级队列存放的是int*数据时，相应的比较函数对象*/
    typedef std::function<int &(std::shared_ptr<int>)> Int_Get_Type;                               /*当最小优先级队列存放的是int*数据时，获取key的函数对象*/
    typedef std::function<bool(std::shared_ptr<Node>, std::shared_ptr<Node>)> Struct_Compare_Type; /*当最小优先级队列存放的是Node*数据时，相应的比较函数对象*/
    typedef std::function<double &(std::shared_ptr<Node>)> Struct_Get_Type;                        /*当最小优先级队列存放的是Node*数据时，获取key的函数对象*/
    typedef priority_queue<Node, double> Struct_PriorityQueue_Type;                                /*存放的是int*数据的最小优先级队列，其关键字就是int本身 */
    typedef priority_queue<int, int> Int_PriorityQueue_Type;                                       /*存放的是Node*数据的最小优先级队列，Node的关键字是double类型 */

    Int_Compare_Type int_compare = [](std::shared_ptr<int> first, std::shared_ptr<int> second)
    { return *first > *second; };
    Int_Get_Type int_get = [](std::shared_ptr<int> node) -> int & { return *node; };
    Struct_Compare_Type struct_compare = [](std::shared_ptr<Node> first, std::shared_ptr<Node> second)
    { return first->key < second->key; };
    Struct_Get_Type struct_get = [](std::shared_ptr<Node> node) -> double & { return node->key; };
    Struct_PriorityQueue_Type struct_priority = Struct_PriorityQueue_Type(struct_compare, struct_get);
    Int_PriorityQueue_Type int_priority = Int_PriorityQueue_Type(int_compare, int_get);
};

int main()
{
    QueueTest queue_test;
    for (int i = 0; i < 10; ++i)
    {
        queue_test.int_priority.insert(std::make_shared<int>(i));
        EXPECT_EQUAL(*(queue_test.int_priority.max()), i);
    }
    return 0;
}