#include<iostream>
#include<string>
using namespace std;

class TravelRoute
{
public:
  float travel_cost;
  TravelRoute()
  {
    travel_cost=0;
  }
  TravelRoute(float cost)
  {
    travel_cost=cost;
  }
};

class StarSystem
{
public:
  int system_id;
  string name;
  int num_planets;
  float x;
  float y;
  float z;
  bool is_habitable;
  int max_children;
  int child_count;
  StarSystem** children;
  TravelRoute* routes;

  StarSystem(int id,string n,int planets,float px,float py,float pz,bool habitable,int m)
  {
    system_id=id;
    name=n;
    num_planets=planets;
    x=px;
    y=py;
    z=pz;
    is_habitable=habitable;
    max_children=m;
    child_count=0;
    children=new StarSystem*[m];
    routes=new TravelRoute[m];
    for(int i=0;i<m;i++)
    {
      children[i]=NULL;
    }
  }

  ~StarSystem()
  {
    for(int i=0;i<child_count;i++)
    {
      delete children[i];
    }
    delete[] children;
    delete[] routes;
  }

  StarSystem(const StarSystem&)=delete;
  StarSystem& operator=(const StarSystem&)=delete;
};

class Galaxy
{
private:
  int M;
  StarSystem* root;

  int checkBalance(StarSystem* x,bool &balanced) const
  {
    if(x==NULL)
    {
      return 0;
    }
    int total=1;
    int smallest=0;
    int largest=0;
    for(int i=0;i<x->child_count;i++)
    {
      int size=checkBalance(x->children[i],balanced);
      total+=size;
      if(i==0)
      {
        smallest=size;
        largest=size;
      }
      else
      {
        if(size<smallest)
        {
          smallest=size;
        }
        if(size>largest)
        {
          largest=size;
        }
      }
    }
    if(largest-smallest>1)
    {
      balanced=false;
    }
    return total;
  }

  void printTree(StarSystem* x,int depth,float cost) const
  {
    if(x==NULL)
    {
      return;
    }
    for(int i=0;i<depth;i++)
    {
      cout<<"  ";
    }
    if(depth>0)
    {
      cout<<"-> ";
    }
    cout<<x->name<<" (ID "<<x->system_id<<", planets "<<x->num_planets<<", habitable "<<(x->is_habitable?"yes":"no")<<", coords ("<<x->x<<", "<<x->y<<", "<<x->z<<")";
    if(depth>0)
    {
      cout<<", route cost "<<cost;
    }
    cout<<")"<<endl;
    for(int i=0;i<x->child_count;i++)
    {
      printTree(x->children[i],depth+1,x->routes[i].travel_cost);
    }
  }

public:
  Galaxy(int m)
  {
    M=m;
    root=NULL;
  }

  Galaxy(int m,StarSystem* r)
  {
    M=m;
    root=r;
  }

  ~Galaxy()
  {
    delete root;
  }

  Galaxy(const Galaxy&)=delete;
  Galaxy& operator=(const Galaxy&)=delete;

  int getM() const
  {
    return M;
  }

  StarSystem* getRoot() const
  {
    return root;
  }

  bool setRoot(StarSystem* r)
  {
    if(root!=NULL)
    {
      return false;
    }
    root=r;
    return true;
  }

  bool addRoute(StarSystem* parent,StarSystem* child,float cost)
  {
    if(parent==NULL || child==NULL)
    {
      return false;
    }
    if(parent->child_count>=M || parent->child_count>=parent->max_children)
    {
      return false;
    }
    parent->children[parent->child_count]=child;
    parent->routes[parent->child_count]=TravelRoute(cost);
    parent->child_count++;
    return true;
  }

  bool is_balanced(StarSystem* x) const
  {
    bool balanced=true;
    checkBalance(x,balanced);
    return balanced;
  }

  int count_leaves(StarSystem* x) const
  {
    if(x==NULL)
    {
      return 0;
    }
    if(x->child_count==0)
    {
      return 1;
    }
    int total=0;
    for(int i=0;i<x->child_count;i++)
    {
      total+=count_leaves(x->children[i]);
    }
    return total;
  }

  void display() const
  {
    printTree(root,0,0);
  }
};

int main()
{
  int m=3;

  StarSystem* sol=new StarSystem(1,"Sol",8,0,0,0,true,m);
  StarSystem* alpha=new StarSystem(2,"AlphaCentauri",3,4.3,1.2,0.5,true,m);
  StarSystem* sirius=new StarSystem(3,"Sirius",2,8.6,-2.1,1.4,false,m);
  StarSystem* vega=new StarSystem(4,"Vega",5,25.0,3.3,-4.0,true,m);
  StarSystem* proxima=new StarSystem(5,"Proxima",1,4.2,1.0,0.4,true,m);
  StarSystem* barnard=new StarSystem(6,"Barnard",4,6.0,-1.5,2.2,false,m);
  StarSystem* sirius_b=new StarSystem(7,"SiriusB",0,8.7,-2.2,1.5,false,m);
  StarSystem* luyten=new StarSystem(8,"Luyten",2,12.4,5.1,-0.7,true,m);
  StarSystem* altair=new StarSystem(9,"Altair",3,16.7,-6.2,3.9,false,m);
  StarSystem* deneb=new StarSystem(10,"Deneb",6,30.2,7.7,2.8,true,m);

  Galaxy balancedGalaxy(m,sol);
  balancedGalaxy.addRoute(sol,alpha,4.3);
  balancedGalaxy.addRoute(sol,sirius,8.6);
  balancedGalaxy.addRoute(sol,vega,25.0);
  balancedGalaxy.addRoute(alpha,proxima,0.2);
  balancedGalaxy.addRoute(alpha,barnard,1.9);
  balancedGalaxy.addRoute(sirius,sirius_b,0.1);
  balancedGalaxy.addRoute(sirius,luyten,3.8);
  balancedGalaxy.addRoute(vega,altair,9.0);
  balancedGalaxy.addRoute(vega,deneb,5.5);

  cout<<"Galaxy 1 (M = "<<balancedGalaxy.getM()<<")"<<endl;
  balancedGalaxy.display();
  cout<<"Is balanced: "<<(balancedGalaxy.is_balanced(balancedGalaxy.getRoot())?"Yes":"No")<<endl;
  cout<<"Leaf count: "<<balancedGalaxy.count_leaves(balancedGalaxy.getRoot())<<endl;
  cout<<"Leaf count under AlphaCentauri: "<<balancedGalaxy.count_leaves(alpha)<<endl;
  cout<<endl;

  StarSystem* orion=new StarSystem(11,"Orion",7,50.0,10.0,5.0,true,m);
  StarSystem* rigel=new StarSystem(12,"Rigel",2,55.0,12.0,6.0,false,m);
  StarSystem* betel=new StarSystem(13,"Betelgeuse",0,60.0,-8.0,9.0,false,m);
  StarSystem* bellatrix=new StarSystem(14,"Bellatrix",3,62.0,4.0,1.0,true,m);
  StarSystem* saiph=new StarSystem(15,"Saiph",1,65.0,2.0,3.0,true,m);
  StarSystem* mintaka=new StarSystem(16,"Mintaka",4,68.0,1.0,7.0,false,m);

  Galaxy unbalancedGalaxy(m);
  unbalancedGalaxy.setRoot(orion);
  unbalancedGalaxy.addRoute(orion,rigel,6.2);
  unbalancedGalaxy.addRoute(orion,betel,7.7);
  unbalancedGalaxy.addRoute(rigel,bellatrix,2.4);
  unbalancedGalaxy.addRoute(bellatrix,saiph,1.1);
  unbalancedGalaxy.addRoute(saiph,mintaka,0.9);

  cout<<"Galaxy 2 (M = "<<unbalancedGalaxy.getM()<<")"<<endl;
  unbalancedGalaxy.display();
  cout<<"Is balanced: "<<(unbalancedGalaxy.is_balanced(unbalancedGalaxy.getRoot())?"Yes":"No")<<endl;
  cout<<"Leaf count: "<<unbalancedGalaxy.count_leaves(unbalancedGalaxy.getRoot())<<endl;
  cout<<"Is subtree at Bellatrix balanced: "<<(unbalancedGalaxy.is_balanced(bellatrix)?"Yes":"No")<<endl;
  cout<<"Leaf count under Rigel: "<<unbalancedGalaxy.count_leaves(rigel)<<endl;
  return 0;
}
