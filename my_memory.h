//Valentine Shidlovskiy
//CSCI - 335 - Home Project 1

#pragma once
#include <iostream>

template <typename T>
class my_unique_ptr
{
  public:
    my_unique_ptr<T>();
    my_unique_ptr<T>(T* nptr);
    my_unique_ptr<T>(my_unique_ptr &&); //Move constructor
    my_unique_ptr<T>(const my_unique_ptr &) = delete;  // copy constructor
    my_unique_ptr<T>& operator=(my_unique_ptr<T> &&); // move assignment operator
    my_unique_ptr<T>& operator=(const my_unique_ptr &) = delete;// copy assignment operator
    T& operator*();
    T* operator->();

    bool isNullptr();
    ~my_unique_ptr();
  private:
    T* p;
};


template <typename T>
class my_shared_ptr
{
  public:
    my_shared_ptr<T>();
    my_shared_ptr<T>(T* nptr);
    my_shared_ptr<T>(my_shared_ptr &&); //Move constructor
    my_shared_ptr<T>(const my_shared_ptr &);//Copy constructor
    my_shared_ptr<T>& operator=(my_shared_ptr &&); //Move assignement operator
    my_shared_ptr<T>& operator=(const my_shared_ptr &);//Copy assignment operator
    T& operator*();
    T* operator->();

    bool isNullptr();
    ~my_shared_ptr();
  private:
    T* p;
    int* count;
};

#include "my_memory.cpp"
