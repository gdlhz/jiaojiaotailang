//2d

#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;
#define inc(i,a,b) for(int i=a;i<=b;i++)
#define dec(i,a,b) for(int i=a;i>=b;i--)
#define ll long long 
#define mst(a,b) memset(a,b,sizeof a)
#define pb push_back
#define db double
#define eps (1e-10)
#define equals(a,b) (fabs((a)-(b))<eps)
#define point Point 
#define segment Segment
#define line Line
class Point{
	public:
	db x,y;
	Point(db x=0,db y=0):x(x),y(y){}
	Point operator + (const Point &p) const {return Point(x+p.x,y+p.y);}
	Point operator - (const Point &p) const {return Point(x-p.x,y-p.y);}
	Point operator * (db k) { return Point(x*k,y*k);}
	Point operator / (db k) { return Point(x/k,y/k);}
	db abs(){ return sqrt(norm());}
	db norm(){ return x*x+y*y;}
	bool operator < (const Point &p) const{
		return x!=p.x? x<p.x:y<p.y;
	}

	bool operator == ( const Point &p) const{
		return fabs(x-p.x)<eps&&fabs(y-p.y) < eps;
	}
	void show(){
		printf("%.10f %.10f\n",x,y);
	}
	void get(){
		scanf("%lf%lf",&x,&y);
	}

};

typedef Point Vector;
inline db dot(Vector a,Vector b){

	return a.x*b.x+a.y*b.y;
}

inline db cross(Vector a,Vector b){
	return a.x*b.y-a.y*b.x;
}

inline db norm(Vector a){
	return a.x*a.x+a.y*a.y;
}

inline db abs(Vector a){
	return sqrt(norm(a));
}


struct Segment{
	Point p1,p2;
	void show(){ printf("%.5f %.5f %.5f %.5f\n",p1.x,p1.y,p2.x,p2.y);}

};

typedef Segment Line;

class Circle{
	public :
		Point c;
		db r;
	Circle(Point c=Point(),db r=0.0):c(c),r(r){}
};

typedef vector<Point> Polygon;

//投影
Point project(Segment s,Point p){
	Vector base=s.p2-s.p1;
	// t与base的比例
	double r=dot(p-s.p1,base)/norm(base);
	return s.p1+base*r;
}
//点关于直线的对称点
Point reflect(Segment s,Point p){
	return p+(project(s,p)-p)*2.0;
}

bool isOrthogonal(Vector a,Vector b){
	return equals(dot(a,b),0.0);
}

bool isOrthogonal(Point a1,Point a2,Point b1,Point b2){
	return isOrthogonal(a1-a2,b1-b2);
}

bool isOrthogonal(Segment s1,Segment s2){
	return equals(dot(s1.p2-s1.p1,s2.p2-s2.p1),0.0);
}

bool isParallel(Vector a,Vector b){
	return equals(cross(a,b),0.0);
}

bool isParallel(point a1,point a2,point b1,point b2){
	return isParallel(a1-a2,b1-b2);
}

bool isParallel(Segment s1,Segment s2){
	return isParallel(cross(s1.p2-s1.p1,s2.p2-s2.p1),0.0);
}

static const int COUNTER_CLOCKWISE=1; //逆时针
static const int CLOCKWISE=-1; //顺时针
static const int ONLINE_BACK=2; //反向
static const int ONLINE_FRONT=-2; //同向
static const int ON_SEGMENT=0; // 在线段上 指p0p2在p0p1上
int ccw(point p0,point p1,point p2){
	Vector a=p1-p0;
	Vector b=p2-p0;
	if(cross(a,b)>eps) return COUNTER_CLOCKWISE;
	if(cross(a,b)<-eps) return CLOCKWISE;
	if(dot(a,b) < -eps) return ONLINE_BACK;
	if(a.norm()<b.norm()) return ONLINE_FRONT;
	return ON_SEGMENT;
}


bool intersect(Point p1,point p2,point p3,point p4){
	int st1=ccw(p1,p2,p3)*ccw(p1,p2,p4);
	int st2=ccw(p3,p4,p1)*ccw(p3,p4,p2);
	return st1<=0&&st2<=0;
}

bool intersect(segment s1,segment s2){
	return intersect(s1.p1,s1.p2,s2.p1,s2.p2);
}

Point getCrossPoint(point p1,point p2,point p3,point p4){
	Vector base=p4-p3;
	db d1=abs(cross(base,p1-p3));
	db d2=abs(cross(base,p2-p3));
	db t=d1/(d1+d2);
	return p1+(p2-p1)*t;
}

Point getCrossPoint(segment s1,segment s2){
	return getCrossPoint(s1.p1,s1.p2,s2.p1,s2.p2);
}


db getDistance(point a,point b){
	cout<<"getDistance\n";
	a.show();
	b.show();
	return abs(a-b);
}

db getDistanceLP(line l,point p){
	return abs(cross(l.p2-l.p1,p-l.p1)/abs(l.p2-l.p1));
}

db getDistance(segment s,point p){
	if(dot(s.p2-s.p1,p-s.p1)<0.0) return abs(p-s.p1);
	if(dot(s.p1-s.p2,p-s.p2)<0.0) return abs(p-s.p2);
	return getDistanceLP(s,p);
}


db getDistance(segment s1,segment s2){
	if(intersect(s1,s2)) return 0.0;
	return min(min(getDistance(s1,s2.p1),getDistance(s1,s2.p2)),
			min(getDistance(s2,s1.p1),getDistance(s2,s1.p2)));
}

	


int T;
point p0,p1,p2,p3,p4;
int q;
segment a,b;

int main(){
	scanf("%d",&T);
	while(T--){
		a.p1.get();
		a.p2.get();
		b.p1.get();
		b.p2.get();
	//	a.show();
	//	b.show();

		db ans=getDistance(a,b);
		db v1=getDistance(a,b.p1);
		db v2=getDistance(a,b.p2);
		db v3=getDistance(b,a.p1);
		db v4=getDistance(b,a.p2);

		printf("%.10f\n",ans);
	}
	return 0;
}

