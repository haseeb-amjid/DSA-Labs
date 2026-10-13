#include <iostream>
using namespace std;
const int MAX = 100;
class WaitingRoom
{
private:
    int queue[MAX];
    int frontIndex;
    int rearIndex;
    int count;
    int nextId;
public:
    WaitingRoom()
    {
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
        nextId = 1;
    }
    void RegisterPatient()
    {
        if (count == MAX)
        {
            cout << "Waiting room is full, cannot register more patients" << endl;
            return;
        }
        rearIndex = (rearIndex + 1) % MAX;
        queue[rearIndex] = nextId;
        count++;
        cout << "Patient registered with ID " << nextId << endl;
        nextId++;
    }
    void ServePatient()
    {
        if (count == 0)
        {
            cout << "No patients are waiting" << endl;
            return;
        }
        int id = queue[frontIndex];
        frontIndex = (frontIndex + 1) % MAX;
        count--;
        cout << "Now serving patient with ID " << id << endl;
    }
    void CancelAll()
    {
        if (count == 0)
        {
            cout << "No appointments to cancel" << endl;
            return;
        }
        cout << count << " appointment(s) cancelled" << endl;
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }
    bool CanDoctorGoHome()
    {
        return count == 0;
    }
    void ShowAllPatient()
    {
        if (count == 0)
        {
            cout << "No patients are waiting" << endl;
            return;
        }
        int temp[MAX];
        for (int i = 0; i < count; i++)
        {
            temp[i] = queue[(frontIndex + i) % MAX];
        }

        for (int i = 1; i < count; i++)
        {
            int key = temp[i];
            int j = i - 1;
            while (j >= 0 && temp[j] > key)
            {
                temp[j + 1] = temp[j];
                j--;
            }
            temp[j + 1] = key;
        }
        cout << "Waiting patients (sorted): ";
        for (int i = 0; i < count; i++)
        {
            cout << temp[i] << " ";
        }
        cout << endl;
    }
};
int main()
{
    WaitingRoom room;
    int choice;
    do
    {
        cout << "\n===== Emergency Ward Waiting Room =====" << endl;
        cout << "1. Register patient" << endl;
        cout << "2. Serve patient" << endl;
        cout << "3. Cancel all appointments" << endl;
        cout << "4. Can doctor go home?" << endl;
        cout << "5. Show all waiting patients" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        if (!(cin >> choice))
        {
            break;
        }
        switch (choice)
        {
        case 1:
            room.RegisterPatient();
            break;
        case 2:
            room.ServePatient();
            break;
        case 3:
            room.CancelAll();
            break;
        case 4:
            if (room.CanDoctorGoHome())
            {
                cout << "Yes, no one is waiting. Doctor can go home" << endl;
            }
            else
            {
                cout << "No, patients are still waiting" << endl;
            }
            break;
        case 5:
            room.ShowAllPatient();
            break;
        case 0:
            cout << "Exiting program" << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 0);
    return 0;
}