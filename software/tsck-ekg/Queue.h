#pragma once

namespace smm {
  template<typename T>
  class Queue {
  public:
    Queue(size_t maxSize) : maxSize(maxSize), frontIndex(0), backIndex(0), currentSize(0) {
      arr = (T*) malloc(sizeof(T) * maxSize);
    }
    
    void push(T element) {
      if (currentSize < maxSize) {
	arr[backIndex] = element;
	backIndex = (backIndex+1) % maxSize;
	currentSize += 1;
      }
    }

    void pop() {
      if (currentSize > 0) {
	currentSize -= 1;
	frontIndex = (frontIndex+1) % maxSize;
      }
    }

    T front() { return arr[frontIndex]; }
    
    size_t size() { return currentSize; }

    T * arr;
    unsigned int frontIndex, backIndex;
    size_t currentSize, maxSize;
  };
}
