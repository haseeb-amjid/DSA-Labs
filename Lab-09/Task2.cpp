#include<iostream>
#include<iomanip>
#include<string>
#include<cctype>
using namespace std;

class WordNode
{
public:
  string word;
  int frequency;
  WordNode* left;
  WordNode* right;
  WordNode(string w,int f)
  {
    word=w;
    frequency=f;
    left=NULL;
    right=NULL;
  }
};

class WordBST
{
private:
  WordNode* root;
  int uniqueWords;
  int totalWords;

  WordNode* insertWord(WordNode* r,const string &w)
  {
    if(r==NULL)
    {
      uniqueWords++;
      return new WordNode(w,1);
    }
    if(w<r->word)
    {
      r->left=insertWord(r->left,w);
    }
    else if(w>r->word)
    {
      r->right=insertWord(r->right,w);
    }
    else
    {
      r->frequency++;
    }
    return r;
  }

  WordNode* insertByFrequency(WordNode* r,const string &w,int f)
  {
    if(r==NULL)
    {
      return new WordNode(w,f);
    }
    if(f>r->frequency || (f==r->frequency && w<r->word))
    {
      r->left=insertByFrequency(r->left,w,f);
    }
    else
    {
      r->right=insertByFrequency(r->right,w,f);
    }
    return r;
  }

  void buildFrequencyTree(WordNode* r,WordNode* &frequencyRoot)
  {
    if(r==NULL)
    {
      return;
    }
    buildFrequencyTree(r->left,frequencyRoot);
    frequencyRoot=insertByFrequency(frequencyRoot,r->word,r->frequency);
    buildFrequencyTree(r->right,frequencyRoot);
  }

  void printInorder(WordNode* r)
  {
    if(r==NULL)
    {
      return;
    }
    printInorder(r->left);
    cout<<left<<setw(12)<<r->word<<r->frequency<<endl;
    printInorder(r->right);
  }

  int maxFrequency(WordNode* r)
  {
    if(r==NULL)
    {
      return 0;
    }
    int best=r->frequency;
    int leftBest=maxFrequency(r->left);
    int rightBest=maxFrequency(r->right);
    if(leftBest>best)
    {
      best=leftBest;
    }
    if(rightBest>best)
    {
      best=rightBest;
    }
    return best;
  }

  void printWordsWithFrequency(WordNode* r,int f)
  {
    if(r==NULL)
    {
      return;
    }
    printWordsWithFrequency(r->left,f);
    if(r->frequency==f)
    {
      cout<<left<<setw(12)<<r->word<<r->frequency<<endl;
    }
    printWordsWithFrequency(r->right,f);
  }

  void destroy(WordNode* r)
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
  WordBST()
  {
    root=NULL;
    uniqueWords=0;
    totalWords=0;
  }

  ~WordBST()
  {
    destroy(root);
  }

  void insert(string w)
  {
    for(int i=0;i<w.length();i++)
    {
      w[i]=tolower((unsigned char)w[i]);
    }
    totalWords++;
    root=insertWord(root,w);
  }

  void insertParagraph(const string &text)
  {
    string current="";
    for(int i=0;i<text.length();i++)
    {
      if(isalpha((unsigned char)text[i]))
      {
        current+=text[i];
      }
      else if(!current.empty())
      {
        insert(current);
        current="";
      }
    }
    if(!current.empty())
    {
      insert(current);
    }
  }

  void displayAlphabetical()
  {
    cout<<"Words in Alphabetical Order"<<endl;
    cout<<left<<setw(12)<<"Word"<<"Frequency"<<endl;
    printInorder(root);
  }

  void displayByFrequency()
  {
    WordNode* frequencyRoot=NULL;
    buildFrequencyTree(root,frequencyRoot);
    cout<<"Words by Frequency (Highest to Lowest)"<<endl;
    cout<<left<<setw(12)<<"Word"<<"Frequency"<<endl;
    printInorder(frequencyRoot);
    destroy(frequencyRoot);
  }

  void findMostFrequentWord()
  {
    int best=maxFrequency(root);
    cout<<"Most Frequent Word(s) (Frequency "<<best<<")"<<endl;
    printWordsWithFrequency(root,best);
  }

  void displaySummary()
  {
    cout<<"Total Unique Words: "<<uniqueWords<<endl;
    cout<<"Total Word Count: "<<totalWords<<endl;
  }
};

int main()
{
  string paragraph="The quick brown fox jumps over the lazy dog. The fox is quick and smart.";
  WordBST index;
  index.insertParagraph(paragraph);
  index.displayAlphabetical();
  cout<<endl;
  index.displayByFrequency();
  cout<<endl;
  index.findMostFrequentWord();
  cout<<endl;
  index.displaySummary();
  return 0;
}
