#include "Array.h"
#include <stdexcept>         // for std::out_of_bounds exception


//
// Array
//
template <typename T>
Array <T>::Array (void)
    : data_(new T[100]),
      cur_size_(50),
      max_size_(100)
{

}

//
// Array (size_t)
//
template <typename T>
Array <T>::Array (size_t length)
    : data_(new T[length*2]),
      cur_size_(length),
      max_size_(length*2)
{

}

//
// Array (size_t, char)
//
template <typename T>
Array <T>::Array (size_t length, T fill)
    : data_(new T[length*2]),
      cur_size_(length),
      max_size_(length*2)
{
    this->max_size_ = length*2;
    Array<T>::fill(fill);
}

//
// Array (const Array &)
//
template <typename T>
Array <T>::Array (const Array & array)
    : cur_size_(array.cur_size_),
      max_size_(array.max_size_)
{
    data_ = new T[max_size_];
    for(unsigned int x = 0; x < cur_size_; x++)
    {
        data_[x] = array.data_[x];
    }
}

//
// ~Array
//
template <typename T>
Array <T>::~Array (void)
{
    delete [] data_;
}

//
// operator =
//
template <typename T>
const Array <T> & Array <T>::operator = (const Array & rhs)
{
    //check for self assignment
    if(this == &rhs)
    {
        return *this;
    }
    if(this->cur_size_ < rhs.cur_size_)
    {
        size_t temp_length = rhs.cur_size_+cur_size_;
        T* temporary = new T[temp_length];

        T * swap = this->data_;
        this->data_ = temporary;
        temporary = swap;

        this->max_size_ = temp_length;
        delete [] temporary;
    }
    this->cur_size_ = rhs.cur_size_;
    for(unsigned int x = 0; x < this->cur_size_; x++)
    {
        data_[x] = rhs.data_[x];
    }
    return *this;
}

//
// operator []
//
template <typename T>
T & Array <T>::operator [] (size_t index)
{
    if(index >= cur_size_ || index <0)
    {
        throw std::out_of_range("Index is out of bounds");
    }
    return this->data_[index];
}

//
// operator []
//
template <typename T>
const T & Array <T>::operator [] (size_t index) const
{
    if(index >= cur_size_ || index <0)
    {
        throw std::out_of_range("Index is out of bounds");
    }
    return this->data_[index];
}

//
// get
//
template <typename T>
T Array <T>::get (size_t index) const
{
    if(index >= cur_size_ || index <0)
    {
        throw std::out_of_range("Index is out of bounds");
    }
    return data_[index];
}

//
// set
//
template <typename T>
void Array <T>::set (size_t index, T value)
{
    if(index >= cur_size_ || index <0)
    {
        throw std::out_of_range("Index is out of bounds");
    }
    else
    {
        data_[index] = value;
    }
}

//
// resize
//
template <typename T>
 void Array <T>::resize (size_t new_size)
{
    if (new_size <= cur_size_)
    {
        this->cur_size_ = new_size;
    }
    else if( new_size > cur_size_)
    {
        size_t temp_length = new_size+cur_size_;
        T* temporary = new T[temp_length];
        for(unsigned int x = 0; x < new_size; x++)
        {
            temporary[x] = data_[x];
        }
        T * swap = this->data_;
        this->data_ = temporary;
        temporary = swap;

        this->cur_size_ = new_size;
        this->max_size_ = temp_length;
        delete [] temporary;
    }
}

//
// find (char)
//
template  <typename T>
int Array <T>::find (T value) const
{
    try
    {
        return Array<T>::find(value,0);
    }
    catch(const std::out_of_range &)
    {
        //client wont be expecting this exception
    }
    return -1;
}

//
// find (char, size_t)
//
template <typename T>
int Array <T>::find (T val, size_t start) const
{
    if(start >= cur_size_)
    {
        throw std::out_of_range("Index is out of bounds");
    }
    else
    {
        for(; start < cur_size_; start++)
        {
            if(data_[start]== val)
            {
                return start;
            }
        }
    }
    return -1;
}

//
// operator ==
//
template <typename T>
bool Array <T>::operator == (const Array & rhs) const
{
    if(this->cur_size_ == rhs.cur_size_)
    {
        for(unsigned int x = 0; x <rhs.cur_size_;x++)
        {
            if(data_[x] != rhs.data_[x])
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }
    return true;
}

//
// operator !=
//
template <typename T>
bool Array <T>::operator != (const Array & rhs) const
{
    return !(*this == rhs);
}

//
// fill
//
template <typename T>
void Array <T>::fill (T value)
{
    unsigned int x = 0;
    while(x != cur_size_)
    {
        data_[x] = value;
        ++x;
    }
}
