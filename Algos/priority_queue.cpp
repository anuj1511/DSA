#include <iostream>
#include <vector>
using namespace std;

class PriorityQueue {
    // Declare the data members here
    vector<int> heap;

public:
    PriorityQueue() {
        // Implement the constructor here
        heap.clear();
    }

    inline int getLeftChild(int i) {
        return 2 * i + 1;
    }

    inline int getRightChild(int i) {
        return 2 * i + 2;
    }

    inline int getParent(int i) {
        return (i - 1) / 2;
    }

    /****** Implement all the public functions here *****/

    void insert(int element) {
        // Implement the insert() function here
        int size = heap.size();
        if (size == 0) {
            heap.push_back(element);
        } else {
            heap.push_back(element);
            size++;

            int child = size - 1;
            int parent = getParent(child);

            while (child != 0 && heap[parent] < heap[child]) {
                swap(heap[parent], heap[child]);
                child = parent;
                parent = getParent(child);
            }
        }
    }

    int getMax() {
        // Implement the getMax() function here
        if (heap.size() == 0) {
            return -1;
        }
        return heap[0];
    }

    int removeMax() {
        // Implement the removeMax() function here
        int size = heap.size();
        if (size == 0) {
            return -1;
        }

        int root = heap[0];
        if (size == 1) {
            heap.clear();
            return root;
        }

        swap(heap[0], heap[size - 1]);
        heap.pop_back();
        size--;

        int parent = 0;
        int leftChild = getLeftChild(parent);
        int rightChild = getRightChild(parent);
        int child;

        while (leftChild < size) {
            child = leftChild;
            if (rightChild < size) {
                if (heap[rightChild] > heap[leftChild]) {
                    child = rightChild;
                }
            }

            if (heap[child] > heap[parent]) {
                swap(heap[parent], heap[child]);
            } else {
                break;
            }
            parent = child;
            leftChild = getLeftChild(parent);
            rightChild = getRightChild(parent);
        }
        return root;
    }

    int getSize() {
        // Implement the getSize() function here
        return heap.size();
    }

    bool isEmpty() {
        // Implement the isEmpty() function here
        if (heap.size() == 0) {
            return true;
        }
        return false;
    }

    void print() {
        int size = heap.size();
        for (int i : heap) {
            cout << i << " ";
        } cout << endl;
    }

    //Heapify function to maintain heap property.
    void heapify(vector<int> heap, int n, int i) {
        int parent = i;
        int leftChild = getLeftChild(parent);
        int rightChild = getRightChild(parent);

        int largest = parent;

        if (leftChild < n && heap[leftChild] > heap[largest]) {
            largest = leftChild;
        }

        if (rightChild < n && heap[rightChild] >heap[largest]) {
            largest = rightChild;
        }

        if (largest != parent) {
            swap(heap[largest], heap[parent]);
            heapify(heap, n, largest);
        }
    }

    //Function to build a Heap from array.
    void buildHeap(vector<int> heap) {
        for (int i = getParent(heap.size()); i >= 0; i--) {
            heapify(heap, heap.size(), i);
        }
    }

    //Function to sort an array using Heap Sort.
    void heapSort() {
        buildHeap(heap);
    
        for (int i = heap.size() - 1; i >= 0; i--) {
            swap(heap[0], heap[i]);
            heapify(heap, i, 0);
        }
    }
};

int main() {
    PriorityQueue pq;
    int choice;
    cin >> choice;

    while (choice != -1) {
        switch (choice) {
        case 1:  // insert
            int element;
            cin >> element;
            pq.insert(element);
            break;
        case 2:  // getMax
            cout << pq.getMax() << "\n";
            break;
        case 3:  // removeMax
            cout << pq.removeMax() << "\n";
            break;
        case 4:  // size
            cout << pq.getSize() << "\n";
            break;
        case 5:  // isEmpty
            cout << (pq.isEmpty() ? "true\n" : "false\n");
            break;
        case 6:
            pq.print();
            break;
        default:
            return 0;
        }

        cin >> choice;
    }
}