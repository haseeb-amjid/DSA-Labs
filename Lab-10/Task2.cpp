#include <iostream>
#include <list>
using namespace std;
struct Operation
{
    char type;
    int value;
};
void printStack(const list<Operation>& stack)
{
    if (stack.empty())
    {
        cout << "(no operations needed)" << endl;
        return;
    }
    for (list<Operation>::const_iterator it = stack.begin(); it != stack.end(); ++it)
    {
        cout << it->type << it->value << " ";
    }
    cout << endl;
}
bool applyOperation(const Operation& op, long long current, long long maxValue, long long& result)
{
    if (op.type == '+')
    {
        result = current + op.value;
    }
    else if (op.type == '-')
    {
        result = current - op.value;
    }
    else if (op.type == '*')
    {
        result = current * op.value;
    }
    else if (op.type == '/')
    {
        if (op.value == 0)
        {
            return false;
        }
        result = current / op.value;
    }
    else
    {
        return false;
    }
    return result >= 0 && result <= maxValue;
}
void synthesize(long long current, long long target, int budget, long long maxValue,
                const list<Operation>& allowed, list<Operation>& operationStack, int& count)
{
    if (current == target)
    {
        count++;
        cout << "Sequence " << count << ": ";
        printStack(operationStack);
    }
    if ((int)operationStack.size() >= budget)
    {
        return;
    }
    for (list<Operation>::const_iterator it = allowed.begin(); it != allowed.end(); ++it)
    {
        long long next;
        if (!applyOperation(*it, current, maxValue, next))
        {
            continue;
        }
        operationStack.push_back(*it);
        synthesize(next, target, budget, maxValue, allowed, operationStack, count);
        operationStack.pop_back();
    }
}
int main()
{
    long long start;
    long long target;
    long long maxValue;
    int budget;
    int opCount;
    cout << "Enter start state: ";
    cin >> start;
    cout << "Enter target state: ";
    cin >> target;
    cout << "Enter maximum operations K: ";
    cin >> budget;
    cout << "Enter overflow bound Mmax: ";
    cin >> maxValue;
    cout << "Enter number of allowed operations: ";
    cin >> opCount;
    list<Operation> allowed;
    for (int i = 0; i < opCount; i++)
        {
        Operation op;
        cout << "Operation " << i + 1 << " (symbol value, e.g. + 3): ";
        cin >> op.type >> op.value;
        allowed.push_back(op);
    }
    if (start < 0 || start > maxValue)
    {
        cout << "Start state is outside the allowed range." << endl;
        return 0;
    }
    list<Operation> operationStack;
    int count = 0;
    synthesize(start, target, budget, maxValue, allowed, operationStack, count);
    if (count == 0)
    {
        cout << "No valid sequence found." << endl;
    }
    return 0;
}