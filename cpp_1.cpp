// cpp_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

class shape{
public:
	shape(int xx,int yy):x(xx),y(yy),next(0){}
	virtual ~shape(){std::cout <<"dbg:shape destroyed"<<std::endl;}

	virtual void Draw(){ GetType();PrintPos();PrintSpecifics();}
	virtual void Scale(int factor)=0;
	virtual void Move(int xo, int yo){x+=xo;y+=yo;}

protected:
	virtual void PrintPos(){ std::cout << "x = " << x << " , y = " << y ;}
	virtual void PrintSpecifics() = 0;

	int x,y;
	virtual void GetType() = 0;

public: // just for simplicity
	class shape *next;
};

// holds shapes, duh...
class shape_container{
public:
	class shape *shapes;

	typedef void (shape_container::*ft )(shape *);
	
	shape_container():shapes(0){}
	~shape_container(){
		class shape *t = shapes;		
		class shape *t1;		
		while(t) {
			t1 = t;
			t = t->next;			
			delete t1;
		}
	};

	void Add(shape *s){
		class shape *t = shapes;
		if(!t) {shapes = s; return;}
		while(t->next) t = t->next;
		t->next = s;
	}
	void DrawAll(void){
		class shape *t = shapes;		
		while(t) {
			t->Draw();
			t = t->next;			
		}
	}
	void MoveAll(int x,int y){
		class shape *t = shapes;		
		while(t) {
			t->Move(x,y);
			t = t->next;			
		}
	}
	void ScaleAll(int fact){
		class shape *t = shapes;		
		while(t) {
			t->Scale(fact);
			t = t->next;			
		}
	}

};


class ellipse : public shape{
public:
	ellipse(int xx,int yy, int rr1, int rr2):shape(xx,yy),r1(rr1),r2(rr2){}
	virtual ~ellipse(){std::cout <<"dbg:ellipse destroyed"<<std::endl;}
	virtual void Scale(int factor){ r1 *=factor;r2 *=factor;}	

protected:
	int r1,r2;
	virtual void PrintSpecifics(){std::cout << " , r1 = " << r1 << " , r2 = " << r2<< std::endl;}
	virtual void GetType(){std::cout << "ellipse: ";}
};

class circle : public ellipse{
public:
	circle(int xx,int yy, int rr1):ellipse(xx,yy,rr1,rr1){}
	virtual ~circle(){std::cout <<"dbg:circle destroyed"<<std::endl;}		
private:
	virtual void PrintSpecifics(){std::cout << " , r = " << r1 << std::endl;}
	virtual void GetType(){std::cout << "circle: ";}	
};

class rectangle : public shape{
public:
	rectangle(int xx,int yy, int ww, int hh):shape(xx,yy),w(ww),h(hh){}
	virtual ~rectangle(){std::cout <<"dbg:rectangle destroyed"<<std::endl;}
	virtual void Scale(int factor){ w *=factor;h *=factor;}	

protected:
	int w,h;
	virtual void PrintSpecifics(){std::cout << " , w = " << w << " , h = " << h << std::endl;}
	virtual void GetType(){std::cout << "rectangle: ";}
};

class square : public rectangle{
public:
	square(int xx,int yy, int size):rectangle(xx,yy,size,size){}
	virtual ~square(){std::cout <<"dbg:square destroyed"<<std::endl;}
	virtual void Scale(int factor){ std::cout <<"dbg:"; GetType();std::cout<<"is unscalable" <<std::endl;}	
	
protected:	
	virtual void PrintSpecifics(){std::cout << " , w = " << w << " , h = " << h << std::endl;}
	virtual void GetType(){std::cout << "square: ";}
};

class triangle : public square{
public:
	triangle(int xx,int yy, int size):square(xx,yy,size){}
	virtual ~triangle(){std::cout <<"dbg:triangle destroyed"<<std::endl;}
	virtual void Scale(int factor){ w *=factor;h *=factor;}	

	virtual void Move(int xo, int yo){std::cout <<"dbg:"; GetType();std::cout<<"is unmovable" <<std::endl;}

protected:		
	virtual void GetType(){std::cout << "triangle: ";}
};


int _tmain(int argc, _TCHAR* argv[])
{
	shape_container *p = new shape_container();
	
	p->Add( new ellipse(10,10,10,20));
	p->Add(new circle(20,20,30));
	p->Add(new rectangle(30,40,10,20));
	p->Add(new square(40,10,30));
	p->Add(new triangle(40,10,30));

	std::cout <<"all elements original settings"<<std::endl <<std::endl;
	p->DrawAll();

	std::cout <<std::endl<<"move all elements to the right and down by (5,7)"<<std::endl;
	p->MoveAll(5,7);	
	p->DrawAll();

	std::cout <<std::endl<<"scale all elements by 2"<<std::endl;
	p->ScaleAll(2);
	p->DrawAll();

	std::cout <<std::endl<<"destroying all elements"<<std::endl;
	delete p;	

	return 0;
}

