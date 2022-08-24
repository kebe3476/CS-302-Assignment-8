/*
CS 302 Assignment 8

Name: Keith Beauvais, 5005338658, CS 302 Assignment 8
*/

struct stockType
{
    std::string name;
    int timesPurchased;
    double dividend;
    double price;
    bool operator < (const stockType &rhs){
        
        if(this->price < rhs.price){
            return true;
        }
        else if(this->price > rhs.price){
            return false;
        }
        else if(this->timesPurchased < rhs.timesPurchased){
            return true;
        }
        else if(this->timesPurchased > rhs.timesPurchased){
            return false;
        }
        else if(this->dividend < rhs.dividend){
            return true;
        }
        else if(this->dividend > rhs.dividend){
            return false;
        }
        else if(this->name[0] < rhs.name[0]){
            return true;
        }
        else if(this->name[0] > rhs.name[0]){
            return false;
        }

        return false;
    }
    
    bool operator > (const stockType &rhs){
        
        if(this->price > rhs.price){
            return true;
        }
        else if(this->price < rhs.price){
            return false;
        }
        else if(this->timesPurchased > rhs.timesPurchased){
            return true;
        }
        else if(this->timesPurchased < rhs.timesPurchased){
            return false;
        }
        else if(this->dividend > rhs.dividend){
            return true;
        }
        else if(this->dividend < rhs.dividend){
            return false;
        }
        else if(this->name[0] > rhs.name[0]){
            return true;
        }
        else if(this->name[0] < rhs.name[0]){
            return false;
        }

        return true;
    }

};

template <class Type>
class priorityQ
{
public:
    priorityQ(int = 10);
    priorityQ(std::vector<Type>);
    priorityQ(const priorityQ<Type> &);
    ~priorityQ();
    const priorityQ<Type> &operator=(const priorityQ<Type> &);
    void insert(Type);
    void deletePriority();
    Type getPriority() const;
    bool isEmpty() const;
    void bubbleUp(int);
    void bubbleDown(int);
    int getSize() const;
private:
    int capacity;
    int size;
    Type *heapArray;
};
/* 
priorityQ<Type>::priorityQ(int cap) - constructor that sets the capacity of the heap with cap,
allocates the heapArray with this capacity and sets the size variable

return value - n/a
*/
template <class Type>
priorityQ<Type>::priorityQ(int cap){
    size = 0;
    capacity = cap;
    heapArray = new Type[capacity];
    
}
/* 
priorityQ<Type>::priorityQ(vector<Type> v) - constructor that sets the capacity with v.size() +
1, sets the size with the same amount as capacity, assigns each element of the vector into the heapArray, 
and performs the steps that implements build heap

return value - n/a
*/
template <class Type>
priorityQ<Type>::priorityQ(std::vector<Type> v){
    capacity = v.size()+1;
    size = capacity;

    for(int i = 1; i < capacity; i++){
        heapArray[i] = v[i-1];
    }
}
/* 
priorityQ<Type>::priorityQ(const priorityQ<Type>& copy) - copy constructor

return value - n/a
*/
template <class Type>
priorityQ<Type>::priorityQ(const priorityQ<Type>& copy){
    capacity = copy.capacity;
    size = copy.size;
    heapArray = new Type[capacity];

    for(int i = 1; i< capacity+1; i++){
        heapArray[i] = copy.heapArray[i];
    }

}
/* 
priorityQ<Type>::~priorityQ() - destructor

return value - n/a
*/
template <class Type>
priorityQ<Type>::~priorityQ(){
    delete [] heapArray;
}
/* 
const priorityQ<Type>& priorityQ<Type>::operator=(const priorityQ<Type>& rhs) - assign-
ment operator

return value - n/a
*/
template <class Type>
const priorityQ<Type>& priorityQ<Type>::operator=(const priorityQ<Type>& rhs){
    
    delete [] heapArray;
    capacity = rhs.capacity;
    size = rhs.size;
    heapArray = new Type[capacity];

    for(int i = 1; i < capacity; i++){
        heapArray[i] = rhs.heapArray[i];
    }
    return (*this);
}
/* 
void priorityQ<Type>::insert(Type item) - assigns the item to the back of the heapArray (size
denotes the back of the heap array), increments size and then bubbles up the element (must double
the size of the heapArray if maxed out)

return value - n/a
*/
template <class Type>
void priorityQ<Type>::insert(Type item){
    size++;
    Type * temp;

    if(size ==  capacity){
        temp = heapArray;
        heapArray =new Type[capacity*2];

        for(int i = 1; i < capacity; i++){
            heapArray[i]=temp[i];
        }
        delete [] temp;
        capacity = capacity*2;
    }
    heapArray[size]= item;
    bubbleUp(size);
}
/* 
void priorityQ<Type>::deletePriority() - overwrites the root with the last element in the heap,
decrements the size by 1, and then bubbles down the element

return value - n/a
*/
template <class Type>
void priorityQ<Type>::deletePriority(){
    //int debug; 
    if(!isEmpty()){
        heapArray[1] = heapArray[size];
        size--;
        //debug = heapArray[1];
        bubbleDown(1);
    } 
}
/* 
Type priorityQ<Type>::getPriority() const - returns the root item

return value - n/a
*/
template <class Type>
Type priorityQ<Type>::getPriority() const{
    return heapArray[1];
}
/* 
bool priorityQ<Type>::isEmpty() const - returns true if the heap is empty and false

return value - n/a
*/
template <class Type>
bool priorityQ<Type>::isEmpty() const{
    if(size == 0){
        return true;
    }
    return false;
}
/* 
void priorityQ<Type>::bubbleUp(int index) - bubbles up the element at heapArray[index], com-
pares the item with its parent and swaps heapArray[index] with its parent if violates heap order,
continues this as long as the heap order is not maintained

return value - n/a
*/
template <class Type>
void priorityQ<Type>::bubbleUp(int index){
    Type parent;
    Type child = heapArray[index];

    if (heapArray[index / 2] > child ){
        parent = heapArray[index / 2];
        heapArray[index / 2] = child;
        heapArray[index] = parent;
        bubbleUp(index/2);
    }
    
    return;
}
/* 
void priorityQ<Type>::bubbleDown(int index) - bubbles down the element at heapArray[index]
with one of its children (larger or smaller child), swaps heapArray[index] with the left or right child
and continues this process as long as the array is not in heap order

return value - n/a
*/
template <class Type>
void priorityQ<Type>::bubbleDown(int index){
    int childIndex;

    if(index*2 > size){
        return;
    }

    if(heapArray[index] > heapArray[index * 2] || heapArray[index] > heapArray[(index * 2) + 1])
    {
        if (heapArray[index * 2] < heapArray[(index * 2) + 1]){
            childIndex = (index * 2);
        }
        
        else if (heapArray[index * 2] > heapArray[(index * 2) + 1]){
            childIndex = ((index * 2) + 1);
        }

        Type tempHolder = heapArray[index];
        heapArray[index] = heapArray[childIndex];
        heapArray[childIndex] = tempHolder;
        bubbleDown(childIndex);
        
    }
    return;
}
/* 
int priorityQ<Type>::getSize() const - returns the amount of elements in the heap array

return value - returns the amount of elements in the heap array
*/
template <class Type>
int priorityQ<Type>::getSize() const{
    
    return size;

}


