#pragma once
#include <vector>
#include <functional>
#include <memory>

namespace chapter06
{
    template <typename T, typename TKeyType>
    class priority_queue
    {
    public:
        typedef std::function<bool(std::shared_ptr<T>, std::shared_ptr<T>)> CompareType; /*一个可调用对象类型，该类型的对象可用于比较两个std::shared_ptr<T>的小于比较*/
        typedef std::function<TKeyType &(std::shared_ptr<T>)> GetKeyType;                /*一个可调用对象，该类型的对象可用于获取std::shared_ptr<T>的关键字，并修改该关键字（返回的是关键字的引用）*/
        priority_queue(CompareType compare, GetKeyType getKey) : _size(0), _compare(compare), _getKey(getKey) {}
        priority_queue(std::size_t reserve_size, CompareType compare, GetKeyType getKey) : _size(0), _compare(compare), _getKey(getKey)
        {
            _data.resize(reserve_size);
        }
        std::shared_ptr<T> max()
        {
            if (!_size)
                return std::shared_ptr<T>();
            return _data[0];
        }
        std::shared_ptr<T> extract_max()
        {
            if (!_size)
                return std::shared_ptr<T>();
            auto result = _data[0];
            _data[0] = _data[_size - 1];
            _size--;
            heapify(0);
            if (_size <= _data.size() / 4)
                _data.resize(_size * 2 + 2);
            return result;
        }
        int insert(std::shared_ptr<T> element)
        {
            if (!element)
                return -1;
            if (_size == _data.size())
                _data.resize(_size * 2 + 2);
            int index = _size;
            _size++;
            _data[index] = element;
            TKeyType &k = _getKey(element);
            TKeyType oldk = k;
            increase_key(index, oldk);
            return index;
        }
        void increase_key(std::size_t element_index, TKeyType new_key)
        {
            if (element_index >= _size)
                throw std::invalid_argument("increase_key error: element_index must less than _size!");
            if (new_key < _getKey(_data.at(element_index)))
                throw std::invalid_argument("increase_key error: new_key less _data.at(element_index)->key!");

            _getKey(_data.at(element_index)) = new_key;
            bool valid = true;
            while (element_index != 0)
            {
                auto pIndex = _parentIndex(element_index, valid);
                if (!valid)
                    break;
                if (_compare(_data.at(pIndex), _data.at(element_index)))
                    break;
                std::swap(_data.at(pIndex), _data.at(element_index));
                element_index = pIndex;
            }
        }
        bool is_empty()
        {
            return _size == 0;
        }
        int index_inqueue(std::shared_ptr<T> element)
        {
            if (!element)
                throw std::invalid_argument("is_inqueue error: element must not be nullptr!");
            for (size_t index = 0; index < _size; index++)
            {
                if (element == _data[index])
                    return index;
            }
            return -1;
        }
        void setupHeap()
        {
            if (_size <= 1)
                return;
            int index = (_size - 1) / 2;
            while (index >= 0)
            {
                heapify(index);
                index--;
            }
        }
        void heapify(std::size_t elementIndex)
        {
            if (elementIndex >= _size)
                return;
            auto minIndex = elementIndex;
            bool left_valid = true;
            bool right_valid = true;
            auto leftIndex = _lchildIndex(elementIndex, left_valid);
            auto rightIndex = _rchildIndex(elementIndex, right_valid);

            if (left_valid)
            {
                if (_compare(_data.at(leftIndex), _data.at(minIndex)))
                    minIndex = leftIndex;
            }
            if (right_valid)
            {
                if (_compare(_data.at(rightIndex), _data.at(minIndex)))
                    minIndex = rightIndex;
            }
            if (minIndex != elementIndex)
            {
                std::swap(_data.at(elementIndex), _data.at(minIndex));
                heapify(minIndex);
            }
        }

    protected:
        std::size_t _parentIndex(std::size_t elementIndex, bool &valid)
        {
            if (elementIndex >= _size)
            {
                valid = false; //无效结果
                return 0;
            }
            if (elementIndex == 0)
                return 0; //根节点的父节点是自己
            else
                return (elementIndex - 1) >> 1;
        }
        std::size_t _lchildIndex(std::size_t elementIndex, bool &valid)
        {
            if (_size < 2)
            {
                valid = false; //数组元素太少无效结果
                return 0;
            }
            if (elementIndex > ((_size - 2) >> 1))
            {
                valid = false; //超出范围，无效
                return 0;
            }
            return (elementIndex << 1) + 1;
        }
        std::size_t _rchildIndex(std::size_t elementIndex, bool &valid)
        {
            if (_size < 3)
            {
                valid = false; //数组元素太少无效结果
                return 0;
            }
            if (elementIndex > ((_size - 3) >> 1))
            {
                valid = false; //超出范围，无效
                return 0;
            }
            return (elementIndex << 1) + 2;
        }

    private:
        /*最大优先级队列的数据*/
        std::vector<std::shared_ptr<T>> _data;
        /*堆大小*/
        std::size_t _size;
        /*一个可调用对象，可用于比较两个std::shared_ptr<T>的小于比较*/
        CompareType _compare;
        /*一个可调用对象，可用于获取std::shared_ptr<T>的关键字，并修改该关键字（返回的是关键字的引用）*/
        GetKeyType _getKey;
    };
}