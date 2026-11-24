#include<iostream>
using namespace std;

class Node
{
public:
  int key;
  Node* left;
  Node* right;
  Node* parent;
  Node(int k)
  {
    key=k;
    left=NULL;
    right=NULL;
    parent=NULL;
  }
};

class BST
{
private:
  Node* root;

  Node* insertNode(Node* r,Node* p,int k)
  {
    if(r==NULL)
    {
      Node* n=new Node(k);
      n->parent=p;
      return n;
    }
    if(k<r->key)
    {
      r->left=insertNode(r->left,r,k);
    }
    else if(k>r->key)
    {
      r->right=insertNode(r->right,r,k);
    }
    return r;
  }

  void inorder(Node* r)
  {
    if(r==NULL)
    {
      return;
    }
    inorder(r->left);
    cout<<r->key<<" ";
    inorder(r->right);
  }

  Node* minNode(Node* r)
  {
    while(r!=NULL && r->left!=NULL)
    {
      r=r->left;
    }
    return r;
  }

  Node* maxNode(Node* r)
  {
    while(r!=NULL && r->right!=NULL)
    {
      r=r->right;
    }
    return r;
  }

  Node* nextNode(Node* n)
  {
    if(n->right!=NULL)
    {
      return minNode(n->right);
    }
    Node* p=n->parent;
    while(p!=NULL && n==p->right)
    {
      n=p;
      p=p->parent;
    }
    return p;
  }

  void rangeRecursive(Node* r,int low,int high,int &comparisons)
  {
    if(r==NULL)
    {
      return;
    }
    comparisons++;
    if(r->key<low)
    {
      rangeRecursive(r->right,low,high,comparisons);
      return;
    }
    comparisons++;
    if(r->key>high)
    {
      rangeRecursive(r->left,low,high,comparisons);
      return;
    }
    rangeRecursive(r->left,low,high,comparisons);
    cout<<r->key<<" ";
    rangeRecursive(r->right,low,high,comparisons);
  }

  void destroy(Node* r)
  {
    if(r==NULL)
    {
      return;
    }
    destroy(r->left);
    destroy(r->right);
    delete r;
  }

public:
  BST()
  {
    root=NULL;
  }

  ~BST()
  {
    destroy(root);
  }

  void insert(int k)
  {
    root=insertNode(root,NULL,k);
  }

  void displayInorder()
  {
    cout<<"Inorder Traversal: ";
    inorder(root);
    cout<<endl;
  }

  void findPredecessorSuccessor(int key)
  {
    Node* predecessor=NULL;
    Node* successor=NULL;
    Node* current=root;
    while(current!=NULL)
    {
      if(key<current->key)
      {
        successor=current;
        current=current->left;
      }
      else if(key>current->key)
      {
        predecessor=current;
        current=current->right;
      }
      else
      {
        if(current->left!=NULL)
        {
          predecessor=maxNode(current->left);
        }
        if(current->right!=NULL)
        {
          successor=minNode(current->right);
        }
        break;
      }
    }
    cout<<"Key: "<<key<<endl;
    if(predecessor!=NULL)
    {
      cout<<"Inorder Predecessor: "<<predecessor->key<<endl;
    }
    else
    {
      cout<<"Inorder Predecessor: None"<<endl;
    }
    if(successor!=NULL)
    {
      cout<<"Inorder Successor: "<<successor->key<<endl;
    }
    else
    {
      cout<<"Inorder Successor: None"<<endl;
    }
  }

  int rangeQueryRecursive(int low,int high)
  {
    int comparisons=0;
    cout<<"Recursive Range Query ["<<low<<", "<<high<<"]: ";
    rangeRecursive(root,low,high,comparisons);
    cout<<endl;
    cout<<"Comparisons (Recursive): "<<comparisons<<endl;
    return comparisons;
  }

  int rangeQueryIterative(int low,int high)
  {
    int comparisons=0;
    Node* current=root;
    Node* start=NULL;
    while(current!=NULL)
    {
      comparisons++;
      if(current->key<low)
      {
        current=current->right;
      }
      else
      {
        start=current;
        current=current->left;
      }
    }
    cout<<"Iterative Range Query ["<<low<<", "<<high<<"]: ";
    while(start!=NULL)
    {
      comparisons++;
      if(start->key>high)
      {
        break;
      }
      cout<<start->key<<" ";
      start=nextNode(start);
    }
    cout<<endl;
    cout<<"Comparisons (Iterative): "<<comparisons<<endl;
    return comparisons;
  }
};

int main()
{
  int values[]={50,30,70,20,40,60,80,35,45,65,85};
  int size=sizeof(values)/sizeof(values[0]);
  BST tree;
  for(int i=0;i<size;i++)
  {
    tree.insert(values[i]);
  }
  tree.displayInorder();
  cout<<endl;
  tree.findPredecessorSuccessor(40);
  cout<<endl;
  int recursiveCount=tree.rangeQueryRecursive(30,70);
  cout<<endl;
  int iterativeCount=tree.rangeQueryIterative(30,70);
  cout<<endl;
  cout<<"Comparative Analysis"<<endl;
  cout<<"Recursive comparisons: "<<recursiveCount<<endl;
  cout<<"Iterative comparisons: "<<iterativeCount<<endl;
  if(recursiveCount>iterativeCount)
  {
    cout<<"Iterative version made "<<recursiveCount-iterativeCount<<" fewer comparisons"<<endl;
  }
  else if(iterativeCount>recursiveCount)
  {
    cout<<"Recursive version made "<<iterativeCount-recursiveCount<<" fewer comparisons"<<endl;
  }
  else
  {
    cout<<"Both versions made the same number of comparisons"<<endl;
  }
  return 0;
}
