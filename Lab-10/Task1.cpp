#include <iostream>
#include <list>
#include <queue>
using namespace std;
struct Container
{
    int id;
    int weight;
    Container* next;

    Container(int i, int w) : id(i), weight(w), next(NULL) {}
};
class ContainerList
{
public:
    Container* head;
    Container* tail;
    int totalWeight;

    ContainerList() : head(NULL), tail(NULL), totalWeight(0) {}

    ~ContainerList()
    {
        while (head != NULL)
        {
            Container* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void add(int id, int weight)
    {
        Container* node = new Container(id, weight);
        if (head == NULL)
        {
            head = node;
            tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }
        totalWeight += weight;
    }
};
struct Truck
{
    int number;
    int remaining;
    list<int> loaded;
};
bool loadContainers(Container* current, int remainingWeight, int remainingCapacity, list<Truck>& trucks)
{
    if (current == NULL)
    {
        return true;
    }
    if (remainingWeight > remainingCapacity)
    {
        return false;
    }
    for (list<Truck>::iterator it = trucks.begin(); it != trucks.end(); ++it)
    {
        if (current->weight > it->remaining)
        {
            continue;
        }
        it->remaining -= current->weight;
        it->loaded.push_back(current->id);
        if (loadContainers(current->next, remainingWeight - current->weight,
                           remainingCapacity - current->weight, trucks))
        {
            return true;
        }
        it->loaded.pop_back();
        it->remaining += current->weight;
    }
    return false;
}
int main()
{
    int n;
    int truckCount;
    int capacity;
    cout << "Enter number of containers: ";
    cin >> n;
    ContainerList containers;
    for (int i = 0; i < n; i++)
    {
        int id;
        int weight;
        cout << "Container " << i + 1 << " (id weight): ";
        cin >> id >> weight;
        containers.add(id, weight);
    }
    cout << "Enter number of trucks: ";
    cin >> truckCount;
    cout << "Enter capacity W of each truck: ";
    cin >> capacity;
    queue<int> truckQueue;
    for (int i = 0; i < truckCount; i++)
    {
        truckQueue.push(capacity);
    }
    list<Truck> trucks;
    int totalCapacity = 0;
    int number = 1;
    while (!truckQueue.empty())
    {
        Truck t;
        t.number = number++;
        t.remaining = truckQueue.front();
        totalCapacity += t.remaining;
        truckQueue.pop();
        trucks.push_back(t);
    }
    if (loadContainers(containers.head, containers.totalWeight, totalCapacity, trucks))
    {
        for (list<Truck>::iterator it = trucks.begin(); it != trucks.end(); ++it)
        {
            cout << "Truck " << it->number << ": ";
            if (it->loaded.empty())
            {
                cout << "empty";
            }
            for (list<int>::iterator c = it->loaded.begin(); c != it->loaded.end(); ++c)
            {
                cout << *c << " ";
            }
            cout << endl;
        }
    }
    else
    {
        cout << "Insufficient truck capacity." << endl;
    }
    return 0;
}