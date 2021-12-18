#ifndef HEAP_H
#define HEAP_H
#include <vector>
#include <algorithm>
#include <functional>

template <typename T, typename Compare_type>
class heap
{
private:
    std::function<bool(T, T)> Compare = Compare_type();

    std::vector<T> &_arr;

    int parent(int index)
    {
        if (index == 0)
            return -1;
        return (index - 1) >> 1;
    }

    int left_child(int index)
    {
        return right_child(index) - 1;
    }

    int right_child(int index)
    {
        return (index + 1) << 1;
    }

    void make_heap(int index, int end)
    {
        int m = index;
        int left = left_child(index);
        if (left < end && Compare(_arr[m], _arr[left]))
            m = left;
        int right = right_child(index);
        if (right < end && Compare(_arr[m], _arr[right]))
            m = right;
        if (m != index)
        {
            std::swap(_arr[index], _arr[m]);
            make_heap(m, end);
        }
    }

public:
    heap(std::vector<T> &arr) : _arr(arr) {
        int n = _arr.size();
        if(n < 2) return;
        for(int i = n / 2 - 1; i >= 0; --i){
            make_heap(i, n);
        }
    }

    void push_heap(T val)
    {
        int index = _arr.size();
        _arr.push_back(val);
        while(index > 0){
            int par = parent(index);
            if(Compare(_arr[index], _arr[par])) break;
            std::swap(_arr[index], _arr[par]);
            index = par;
        }
    }

    T pop_heap()
    {
        int n = _arr.size();
        if(n > 0){
            std::swap(_arr.front(), _arr.back());
            make_heap(0, n - 1);
            T res = _arr.back();
            _arr.pop_back();
            return res;
        }
    }

    void heap_sort(){
        int n = _arr.size() - 1;
        while(n > 0){
            std::swap(_arr.front(), _arr[n]);
            make_heap(0, n);
            --n;
        }
    }
};

#endif // HEAP_H