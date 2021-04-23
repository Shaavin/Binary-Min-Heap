#ifndef MYBINARYMINHEAP_HPP
#define MYBINARYMINHEAP_HPP

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

template <typename Comparable>
class myBinaryMinHeap
{
  public:
    explicit myBinaryMinHeap(int capacity = 100)
      : array(capacity), currentSize(0) { }
    explicit myBinaryMinHeap(const std::vector<Comparable> & items)
      : array(items.size() + 10), currentSize{items.size()}
    {
      for(int i = 0; i < items.size(); ++i)
        array[i + 1] = items[i];
      buildHeap();
    }

    bool isEmpty() const
    {
      return (currentSize == 0);
    }
    const Comparable & findMin() const
    {
      return array[1];
    }

    void insert(const Comparable & x)
    {
      if(currentSize == array.size() - 1)
        array.resize(array.size() * 2);

      // Percolate up:
      int hole = ++currentSize;
      Comparable copy = x;

      array[0] = std::move(copy);
      for( ; x < array[hole / 2]; hole /= 2)
        array[hole] = std::move(array[hole / 2]);
      array[hole] = std::move(array[0]);
    }
    void insert(Comparable && x)
    {
      if(currentSize == array.size() - 1)
        array.resize(array.size() * 2);

      // Percolate up:
      int hole = ++currentSize;

      array[0] = std::move(x);
      for( ; x < array[hole / 2]; hole /= 2)
        array[hole] = std::move(array[hole / 2]);
      array[hole] = std::move(array[0]);
    }
    void deleteMin()
    {
      if(isEmpty())
        std::cerr << "Cannot call deleteMin() on an empty min heap\n";
      array[1] = std::move(array[currentSize--]);
      percolateDown(1);
    }
    void deleteMin(Comparable & minItem)
    {
      if(isEmpty())
        std::cerr << "Cannot call deleteMin(Comparable &) on am empty min heap\n";
      minItem = std::move(array[1]);
      array[1] = std::move(array[currentSize--]);
      percolateDown(1);
    }
    void makeEmpty()
    {
      array.clear();
      array.resize(100);
      currentSize = 0;
    }

    void levelOrder(std::ofstream& out)
    {
      for(int i = 1; i <= currentSize; i++)
      {
        out << array[i] << '\n';
      }
    }

  private:
    int currentSize;                // num elements in the heap
    std::vector<Comparable> array;  // the heap array

    void buildHeap()
    {
      for(int i = currentSize / 2; i > 0; --i)
        percolateDown(i);
    }
    void percolateDown(int hole)
    {
      int child;
      Comparable tmp = std::move(array[hole]);
      for( ; hole * 2 <= currentSize; hole = child)
      {
        child = hole * 2;
        if(child != currentSize && array[child + 1] < array[child])
          ++child;
        if(array[child] < tmp)
          array[hole] = std::move(array[child]);
        else
          break;
      }
      array[hole] = std::move(tmp);
    }
};

#endif
