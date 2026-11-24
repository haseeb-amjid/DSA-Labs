#include <iostream>
#include <list>
#include <queue>
using namespace std;
struct TreeNode
{
    int serviceID;
    int cost;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int id, int c) : serviceID(id), cost(c), left(NULL), right(NULL) {}
};
TreeNode* insertNode(TreeNode* root, int id, int cost)
{
    if (root == NULL)
    {
        return new TreeNode(id, cost);
    }
    if (cost < root->cost)
    {
        root->left = insertNode(root->left, id, cost);
    }
    else
    {
        root->right = insertNode(root->right, id, cost);
    }
    return root;
}
void destroyTree(TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }
    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
}
void printPath(const list<TreeNode*>& path)
{
    for (list<TreeNode*>::const_iterator it = path.begin(); it != path.end(); ++it)
    {
        if (it != path.begin())
        {
            cout << " -> ";
        }
        cout << (*it)->serviceID << "(" << (*it)->cost << ")";
    }
    cout << endl;
}
void findPaths(TreeNode* node, int target, int currentSum, list<TreeNode*>& path, int& count)
{
    if (node == NULL)
    {
        return;
    }
    path.push_back(node);
    currentSum += node->cost;
    if (currentSum == target)
    {
        count++;
        cout << "Path " << count << ": ";
        printPath(path);
    }
    if (currentSum <= target)
    {
        findPaths(node->left, target, currentSum, path, count);
        findPaths(node->right, target, currentSum, path, count);
    }
    path.pop_back();
}
void partA(TreeNode* root, int target)
{
    int count = 0;
    list<TreeNode*> path;
    queue<TreeNode*> level;
    if (root != NULL)
    {
        level.push(root);
    }
    while (!level.empty())
    {
        TreeNode* start = level.front();
        level.pop();
        findPaths(start, target, 0, path, count);
        if (start->left != NULL)
        {
            level.push(start->left);
        }
        if (start->right != NULL)
        {
            level.push(start->right);
        }
    }
    if (count == 0)
    {
        cout << "No downward path matches the budget." << endl;
    }
}
void inorder(TreeNode* node, list<TreeNode*>& sorted)
{
    if (node == NULL)
    {
        return;
    }
    inorder(node->left, sorted);
    sorted.push_back(node);
    inorder(node->right, sorted);
}
void findSubsets(list<TreeNode*>::iterator begin, list<TreeNode*>::iterator end,
                 int target, int currentSum, list<TreeNode*>& chosen, int& count)
{
    for (list<TreeNode*>::iterator it = begin; it != end; ++it)
    {
        if (currentSum + (*it)->cost > target)
        {
            break;
        }
        chosen.push_back(*it);

        if (currentSum + (*it)->cost == target)
        {
            count++;
            cout << "Subset " << count << ": ";
            printPath(chosen);
        }
        else
        {
            list<TreeNode*>::iterator next = it;
            ++next;
            findSubsets(next, end, target, currentSum + (*it)->cost, chosen, count);
        }
        chosen.pop_back();
    }
}
void partB(TreeNode* root, int target)
{
    list<TreeNode*> sorted;
    inorder(root, sorted);
    list<TreeNode*> chosen;
    int count = 0;
    findSubsets(sorted.begin(), sorted.end(), target, 0, chosen, count);
    if (count == 0)
    {
        cout << "No subset matches the budget." << endl;
    }
}
int main()
{
    int n;
    int budget;
    TreeNode* root = NULL;
    cout << "Enter number of microservices: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int id;
        int cost;
        cout << "Service " << i + 1 << " (serviceID monthlyCost): ";
        cin >> id >> cost;
        root = insertNode(root, id, cost);
    }
    cout << "Enter target budget B: ";
    cin >> budget;
    cout << endl << "Part A: Downward paths with sum " << budget << endl;
    partA(root, budget);
    cout << endl << "Part B: Subsets with sum " << budget << endl;
    partB(root, budget);
    destroyTree(root);
    return 0;
}