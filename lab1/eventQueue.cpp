//
//  eventQueue.cpp
//  lab1
//
//  Created by Ben Patient on 2/9/17.
//  Copyright © 2017 Ben Patient. All rights reserved.
//

#include "eventQueue.hpp"

/*class BinaryMinHeap {
 private:
 int *data;
 int heapSize;
 int arraySize;
 
 int getLeftChildIndex(int nodeIndex) {
 return 2 * nodeIndex + 1;
 }
 
 int getRightChildIndex(int nodeIndex) {
 return 2 * nodeIndex + 2;
 }
 
 int getParentIndex(int nodeIndex) {
 return (nodeIndex - 1) / 2;
 }
 
 public:
 BinaryMinHeap(int size) {
 data = new int[size];
 heapSize = 0;
 arraySize = size;
 }
 
 int getMinimum() {
 if (isEmpty())
 throw string("Heap is empty");
 else
 return data[0];
 }
 
 bool isEmpty() {
 return (heapSize == 0);
 }
 
 …
 
 ~BinaryMinHeap() {
 delete[] data;
 }
 };
 
 void insert(int data){
 int i = 0;
 
 if(!isFull()){
 // if queue is empty, insert the data
 
 if(itemCount == 0){
 intArray[itemCount++] = data;
 }else{
 // start from the right end of the queue
 for(i = itemCount - 1; i >= 0; i-- ){
 // if data is larger, shift existing item to right end
 if(data > intArray[i]){
 intArray[i+1] = intArray[i];
 }else{
 break;
 }
 }
 // insert the data
 intArray[i+1] = data;
 itemCount++;
 }
 }
 }*/