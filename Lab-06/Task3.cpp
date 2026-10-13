#include <iostream>
#include <string>
using namespace std;
struct PrintRequest
{
    int id;
    int arrivalTime;
    int processingTime;
};
class CircularQueue
{
private:
    PrintRequest *data;
    int capacity;
    int minCapacity;
    int frontIndex;
    int rearIndex;
    int count;
public:
    CircularQueue(int cap)
    {
        capacity = cap;
        minCapacity = cap;
        data = new PrintRequest[capacity];
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }
    ~CircularQueue()
    {
        delete[] data;
    }
    bool isEmpty()
    {
        return count == 0;
    }
    bool isFull()
    {
        return count == capacity;
    }
    void resize(int newCapacity)
    {
        if (newCapacity < count)
        {
            cout << "Cannot resize: new capacity is smaller than number of requests" << endl;
            return;
        }
        PrintRequest *temp = new PrintRequest[newCapacity];
        for (int i = 0; i < count; i++)
        {
            temp[i] = data[(frontIndex + i) % capacity];
        }
        delete[] data;
        data = temp;
        cout << "Resized capacity from " << capacity << " to " << newCapacity << endl;
        capacity = newCapacity;
        frontIndex = 0;
        rearIndex = count - 1;
    }
    void enqueue(PrintRequest x)
    {
        if (isFull())
        {
            resize(capacity * 2);
        }
        rearIndex = (rearIndex + 1) % capacity;
        data[rearIndex] = x;
        count++;
    }
    PrintRequest dequeue()
    {
        PrintRequest x;
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            x.id = -1;
            x.arrivalTime = 0;
            x.processingTime = 0;
            return x;
        }
        x = data[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        count--;
        if (capacity > minCapacity && count <= capacity / 4)
        {
            resize(capacity / 2);
        }
        return x;
    }
    PrintRequest front()
    {
        PrintRequest x;
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            x.id = -1;
            x.arrivalTime = 0;
            x.processingTime = 0;
            return x;
        }
        return data[frontIndex];
    }
    void display()
    {
        cout << "Queue State -> Capacity: " << capacity << ", Size: " << count
             << ", Front Index: " << frontIndex << ", Rear Index: " << rearIndex << endl;
        cout << "Array: ";
        for (int i = 0; i < capacity; i++)
        {
            bool occupied = count > 0 && ((i - frontIndex + capacity) % capacity) < count;
            if (occupied)
            {
                cout << "[R" << data[i].id << "] ";
            }
            else
            {
                cout << "[ _ ] ";
            }
        }
        cout << endl;
        cout << "Order (front to rear): ";
        if (isEmpty())
        {
            cout << "empty";
        }
        for (int i = 0; i < count; i++)
        {
            PrintRequest r = data[(frontIndex + i) % capacity];
            cout << "R" << r.id << "(arr=" << r.arrivalTime << ", proc=" << r.processingTime << ") ";
        }
        cout << endl
             << endl;
    }
};
int main()
{
    CircularQueue queue(4);
    int arrival[10] = {0, 1, 2, 4, 5, 7, 8, 10, 11, 13};
    int processing[10] = {5, 3, 4, 2, 6, 1, 3, 2, 4, 2};
    string operations = "EEEEEDEEEEEDDDDDDDDD";
    int nextRequest = 0;
    int currentTime = 0;
    int totalWaiting = 0;
    int processed = 0;
    cout << "===== Print Server Request Handling System =====" << endl;
    cout << "Initial capacity: 4" << endl
         << endl;
    for (int i = 0; i < operations.length(); i++)
    {
        if (operations[i] == 'E')
        {
            PrintRequest r;
            r.id = nextRequest + 1;
            r.arrivalTime = arrival[nextRequest];
            r.processingTime = processing[nextRequest];
            nextRequest++;
            cout << "ENQUEUE request " << r.id << " (arrival " << r.arrivalTime
                 << ", processing " << r.processingTime << ")" << endl;
            queue.enqueue(r);
            queue.display();
        }
        else
        {
            PrintRequest r = queue.dequeue();
            if (r.id != -1)
            {
                int startTime = currentTime;
                if (r.arrivalTime > startTime)
                {
                    startTime = r.arrivalTime;
                }
                int waiting = startTime - r.arrivalTime;
                currentTime = startTime + r.processingTime;
                totalWaiting += waiting;
                processed++;
                cout << "DEQUEUE request " << r.id << " -> start time " << startTime
                     << ", waiting time " << waiting << ", finish time " << currentTime << endl;
            }
            queue.display();
        }
    }
    cout << "Total requests processed: " << processed << endl;
    cout << "Total waiting time: " << totalWaiting << endl;
    if (processed > 0)
    {
        cout << "Average waiting time: " << (double)totalWaiting / processed << endl;
    }
    return 0;
}