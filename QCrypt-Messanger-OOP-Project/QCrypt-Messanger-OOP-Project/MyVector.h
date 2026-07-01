#ifndef MYVECTOR_H
#define MYVECTOR_H

template <typename T>
class MyVector
{
private:
    T* arr;
    int sz;
    int cap;

    void resize()
    {
        int newCap;
        if (cap == 0)
        {
            newCap = 4;
        }
        else
        {
            newCap = cap * 2;
        }
        T* newArr = new T[newCap];
        for (int i = 0; i < sz; ++i)
        {
            newArr[i] = arr[i];
        }

        delete[] arr;
        arr = newArr;
        cap = newCap;
    }

public:
    MyVector() :arr(nullptr), sz(0), cap(0)
    {

    }

    MyVector(const MyVector<T>& other) :arr(nullptr), sz(0), cap(0)
    {
        for (int i = 0; i < other.sz; ++i)
        {
            push_back(other.arr[i]);
        }
    }

    ~MyVector()
    {
        delete[] arr;
    }

    MyVector<T>& operator=(const MyVector<T>& other)
    {
        if (this != &other)
        {
            delete[] arr;
            arr = nullptr;
            sz = 0;
            cap = 0;
            for (int i = 0; i < other.sz; ++i)
            {
                push_back(other.arr[i]);
            }
        }
        return *this;
    }

    void push_back(const T& val)
    {
        if (sz == cap)
        {
            resize();
        }
        arr[sz++] = val;
    }

    T& operator[](int index)
    {
        return arr[index];
    }

    const T& operator[](int index) const
    {
        return arr[index];
    }

    int size() const
    {
        return sz;
    }

    void clear()
    {
        sz = 0;
    }

    bool empty() const
    {
        return sz == 0;
    }
};

#endif
