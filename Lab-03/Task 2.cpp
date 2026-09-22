#include <iostream>
#include <string>
using namespace std;
class StringPool {
public:
    string* stringPool;
    int currentSize;
    int maxSize;
    bool* isRemoved;
    StringPool() {
        maxSize = 5;
        currentSize = 0;
        stringPool = new string[maxSize];
        isRemoved = new bool[maxSize];
        for (int i = 0; i < maxSize; i++) {
            isRemoved[i] = false;
        }
    }
    void addString(string value) {
        if (currentSize < maxSize) {
            stringPool[currentSize] = value;
            isRemoved[currentSize] = false;
            currentSize++;
            cout << "Added: " << value << endl;
        } else {
            cout << "Pool is full, cannot add " << value << endl;
        }
    }
    void removeString(int index) {
        if (index >= 0 && index < currentSize) {
            cout << "Removed (without freeing): " << stringPool[index] << endl;
            isRemoved[index] = true;
         } else {
            cout << "Invalid index." << endl;
        }
    }
    void fixLeaks() {
        int fixedCount = 0;
        for (int i = 0; i < currentSize; i++) {
            if (isRemoved[i] && !stringPool[i].empty()) {
                cout << "Fixing leak at index " << i << " (was: " << stringPool[i] << ")" << endl;
                stringPool[i] = "";
                fixedCount++;
            }
        }
        cout << "Total leaks fixed: " << fixedCount << endl;
    }
    void displayStatus() {
        cout << "\n--- Pool Status ---" << endl;
        cout << "currentSize: " << currentSize << " / maxSize: " << maxSize << endl;
        for (int i = 0; i < currentSize; i++) {
            cout << i << ": ";
            if (isRemoved[i]) {
                if (stringPool[i].empty()) {
                    cout << "(removed, memory freed)";
                } else {
                    cout << "(removed, but LEAK -> " << stringPool[i] << ")";
                }
            } else {
                cout << stringPool[i];
            }
            cout << endl;
        }
        cout << "-------------------\n" << endl;
    }
    ~StringPool() {
        delete[] stringPool;
        delete[] isRemoved;
    }
};

int main() {
    StringPool pool;
    cout << "Pool created." << endl;
    cout << "maxSize: " << pool.maxSize << endl;
    cout << "currentSize: " << pool.currentSize << endl;
    cout << endl;
    pool.addString("apple");
    pool.addString("banana");
    pool.addString("cherry");
    pool.addString("date");
    pool.addString("elderberry");
    pool.displayStatus();
    pool.removeString(1);
    pool.removeString(3);
    pool.displayStatus();
    cout << "Detecting and fixing memory leaks..." << endl;
    pool.fixLeaks();
    pool.displayStatus();
    return 0;
}
