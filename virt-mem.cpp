#include<iostream>
using namespace std;

template<class cs>
unsigned int GetMemFunAddr(cs &funa)
{

	union
	{
		cs type;
		unsigned int addr;
	}ut;
	
	ut.type = funa;
	return ut.addr;
}

class ca
{
 public:
   ca();
	
   void avptr();
   
   virtual void fa();

   void callfa();

 private:
    int a,b;
};

class cs
{
 public:
	 cs();
	 virtual void fs();
 private:
	 int c;
};
			
cs::cs()
{
	unsigned int*pta = (unsigned int*)*(unsigned int*)this;
	
	cout<<"curr this addr:0x"<<hex<<(int)this<<endl;
	cout <<"cs vtable addr:0x"<<(int)pta<<endl;
	cout<<"cs vtable item:0x"<<*pta<<endl;
}

void cs::fs(){}

class cb:ca
{
  public:
					
	  cb();
	
	  virtual void fb();
	//
	//void fa();
	  void bvptr();

  private:
	  int ib;
};

class cc:ca,cs
{
   public:
	   void cvptr();
	   cc();
};


void cc::cvptr()
{
	cout<<"curr this addr:0x"<<hex<<(int)this<<endl;
	unsigned int*pta = (unsigned int*)*(unsigned int*)this;
	unsigned int*ptb = (unsigned int*)*((unsigned int*)this + 3);
	cout<<"vtable of ca:0x"<<hex<<(int)pta<<endl;

	cout<<"ca vtable item:0x"<<*pta<<endl;

	cout<<"cs vpt addr:0x"<<hex<<(int)((unsigned int*)this + 3)<<endl;
	cout<<"vtable of cs:0x"<<hex<<(int)ptb<<endl;
	cout<<"cs vtable item:0x"<<*ptb<<endl;
}



cc::cc()
{
}

void ca::fa()
{
  cout<<"ca vir fa()"<<endl;
}
void ca::callfa()
{
	unsigned int*pt = (unsigned int*)*(unsigned int*)this;
	cout<<"ca::callfa()"<<endl;
	void (*proc)(ca*);
	proc =(void(*)(ca*)) *pt;
	proc(this);
}

void cb::fb()
{
 cout<<"cb vir fb()"<<endl;
}

/*
void cb::fa()
{
	cout<<"cb::fa"<<endl;
}
*/

ca::ca()
{
	unsigned int*pt = (unsigned int*)*(unsigned int*)this;
	cout<<"curr this addr:0x"<<hex<<(int)this<<endl;
        cout<<"ca vtable addr:0x"<<hex<<(int)pt<<endl;
	cout<<"ca vtable item:0x"<<*pt<<endl;
}
void ca::avptr()
{
		
		union
		{
			void (ca::* type)();
			unsigned int addr;
		}ut;
		
		ut.type = &ca::fa;
		cout<<"ca virtual fa addr:0x"<<hex<<ut.addr<<endl;
}


cb::cb()
{
	unsigned int*pt = (unsigned int*)*(unsigned int*)this;
        cout<<"b vptr:0x"<<hex<<(int)pt<<endl;
	cout<<"b vtable item:0x"<<*pt<<endl;
}

void cb::bvptr()
{
	//cout<<"cb virtual fb() addr:0x"<<hex<<GetMemFunAddr(&cb::fb)<<endl;

	//cout<<"ca of cb virtual fa() addr:0x"<<hex<<GetMemFunAddr(&ca::fa)<<endl;
}

int run()
{
	cout<<"main()"<<endl;
        ca la;
	la.avptr();
	la.callfa();
  
	cb lb;
	cs lcs;

	cout<<"*********************************cc class************************"<<endl;
	cc c;
	c.cvptr();
  return 1;

	cout<<"local variable"<<endl;
	cb lcb;
	//lcb.avptr();
	lcb.bvptr();
  return 1;
}

class mutablecs
{
  public:
    mutablecs();
    void modify(int inc);
    void modify2 (int inc) const;
    void set_total_memory(int){}
    void set_free_memory(int){}
    void set_swap_memory(int){}

    int  add_from_total_memory(){return 3;}
    int  add_from_free_memory(){return 3;}
    int  add_from_swap_memory(){return 3;}
    
    int  add_to_total_memory(){return 3;}
    int  add_to_free_memory(){return 3;}
    int  add_to_swap_memory(){return 3;}

    int  total_memory(){return 2;}
    int  free_memory(){return 2;}
    int  swap_memory(){return 2;}
  private:
    mutable int si;
    mutablecs mb;
};

mutablecs::mutablecs()
{
  si = 0;
}
void mutablecs::modify(int inc)
{
  si += inc;
  cout<<"mutable modify,inc = "<<inc<<" si == "<<si<<endl;
}
void mutablecs::modify2(int inc) const
{
  si += inc;
  cout<<"mutable modify-2,inc = "<<inc<<" si == "<<si<<endl;
}

void runmutable()
{
  mutablecs cs;
#define callMod(num) cs.set_##num(mb.num()+this->num())
  callMod(total_memory);
  callMod(free_memory);
}
