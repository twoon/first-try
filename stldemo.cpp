#include<vector>
#include<iterator>
#include<list>
#include<iostream>
#include<assert.h>
using namespace std;

namespace stldemons
{
  void nsproc();
  void badinsert();
}

char* names[] = 
{
  "md",
  "ms",
};

class WidgetBase
{
 public:
   virtual void say(){cout<<"base say"<<endl;}
};

class Widget:public WidgetBase
{
  public:
	  Widget();
	  void SetValue(int sa);
	  void print();
	  void say(){cout<<"widget say"<<endl;}
  private:
	  int sa;
};

Widget::Widget()
{
  sa = 23;
  cout<<"Widget Constructor~"<<endl;
}

void Widget::SetValue(int sa)
{
  this->sa = sa;
}

void Widget::print()
{ 
  cout<<"Widget:"<<sa<<endl;
}

char* GetName(int index)
{
 assert(index >= 0 && index < sizeof(names)/sizeof(names[0]));
 return names[index]; 
}

template<class Cont,class PtrMemFun> 
void apply(Cont &cs,PtrMemFun&pmf)
{
  //inform compiler that Cont::iterator is type,stop it from complaining.
  typename  Cont::iterator it = cs.begin();
  {
    ++it;
  }
}
int main()
{
  extern void runmutable();
  runmutable();
  return 1;

  stldemons::badinsert();

  vector<int> bs;
  vector<int> ls;

  apply(bs,ls);   
  

  ls.push_back(27);
  ls.push_back(28);
  ls.push_back(29);
  ls.push_back(30);

  copy(ls.begin(),ls.end(), ostream_iterator<int>(cout,"\n"));
  int lssize = ls.size();
  cout<<"vector ls size:"<<lssize<<endl;
  bs.reserve(lssize);

  copy(ls.begin(),ls.end(), bs.begin());

  //call apply() like normal function,or
  //like this,behave as a true 'template function'
  //apply<vector<int>,vector<int>  >(bs,ls); 



  for(vector<int>::iterator iter=bs.begin();iter!=bs.end();++iter)
  {
      cout<<*iter<<" ";
  }
  cout<<"bs size:"<<bs.size()<<endl;
  
  cout<<"erase ls"<<endl;
  for(vector<int>::iterator iter=ls.begin();iter!=ls.end();++iter)
  {
    if(*iter != 27)
      cout<<*iter<<" ";
    else
      ls.erase(iter);
  }
  cout<<endl;

  //int i = stldemons::stlvar;
  
  
  char*pstr = "abc-string";
  cout << "hex addr of static string:0x"<<hex<<(int)pstr<<endl;
  
  string str = pstr;

  cout<<"hex addr of string:0x"<<hex<<(int)(str.c_str())<<endl;
  
  return 1;
}


