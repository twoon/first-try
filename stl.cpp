#include<iostream>
#include<deque>
#include<vector>
#include<iterator>

namespace stldemons
{
  void nsproc()
  {  
    int i = 0;
    while(i < 20)
	    i++;
    
    std::cout<<i<<"--stldemons i value,yoyoyo"<<std::endl;

    return ; 
  }



  void badinsert()
  {
    std::deque<int> dq(1000,1480);
    std::copy(dq.begin(),dq.end(),std::ostream_iterator<int>(std::cout," "));
    std::deque<int>::iterator it = dq.begin()+dq.size()/2;
    for(;it != dq.end();++it)
	std::cout<<"it-"<<*it<<" ";
    it = dq.begin();
    for(int i = 0;i < 1000; i++)
    {
     // std::cout<<i<<"-th,iterator addr:0x"<<std::hex<<(long)it<<" ";
     std::cout<<i<<" "<<"pos: "<<it - dq.begin()<<" ";
     
     dq.insert(it,1);     
    }
  }

  int stlvar = 20;

}
