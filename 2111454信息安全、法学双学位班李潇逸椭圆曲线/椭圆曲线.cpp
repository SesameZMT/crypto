#include <iostream>

using namespace std;

long long exgcd(long long a,long long b,long long &x,long long &y)
{
	if(b==0)
	{
		x=1,y=0;
		return a;
	}
	long long ret=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return ret;
}

long long getInv(long long a,long long mod)
{
	long long x,y;
	long long d=exgcd(a,mod,x,y);
	return d==1 ? (x % mod + mod) % mod : -1;
}

class Point
{
public:
    Point() : x(0),y(0),isInfinity(false) {};
    Point(long long x,long long y) : x(x),y(y),isInfinity(false) {}; 
    long long x;
    long long y;
    bool isInfinity;
    Point operator=(Point point);
    bool operator==(Point point);
};
Point Point::operator=(Point point)
{
    this->x = point.x;
    this->y = point.y;
    this->isInfinity = point.isInfinity;
    return *this;
}
bool Point::operator==(Point point)
{
    return this->x == point.x && this->y == point.y;
}

class ecc
{
private:
    long long a;
    long long b;
    long long p;

public:
    ecc() : a(0),b(0),p(0) {};
    ecc(long long a,long long b,long long p) : a(a),b(b),p(p) {};
    Point Pointadd(Point point1,Point point2);
};
Point ecc::Pointadd(Point point1,Point point2)
{
    long long t;
    Point ans;
    if(point1.isInfinity)
    {
        return point2;
    }
    if(point1.operator==(point2))
    {
        long long t1 = getInv(2*point1.y,p);
        t = ((3 * (point1.x * point1.x) + a) * t1) % p; 
    }
    else
    {
        long long t2 = point2.x-point1.x;
        if(t2 == 0)
        {
            ans.isInfinity = true;
            return ans;
        }
        if(t2 < 0)
        {
            t2 += p;
        }
        long long t1 = getInv(t2,p);
        t = ((point2.y-point1.y) * t1) % p;
        if(t < 0)
        {
            t += p;
        }
    }

    ans.x = (t*t - point1.x - point2.x) % p;
    if(ans.x < 0)
    {
        ans.x += p;
    }
    ans.y = (t * (point1.x - ans.x) - point1.y) % p;
    if(ans.y < 0)
    {
        ans.y += p;
    }

    return ans;
}

int main()
{
    long long a,b,p,x,y,k;
    cin >> a >> b >> p;
    ecc e(a,b,p);
    cin >> x >> y >> k;
    Point point(x,y);
    Point ans;
    ans.operator=(point);

    for(int i = 1;i < k;i++)
    {
        ans.operator=(e.Pointadd(ans,point));
    }

    if(ans.isInfinity || k == 0)
    {
        cout << -1 << " " << -1;
    }
    else
    {
        if(ans.x < 0)
        {
            ans.x += p;
        }
        if(ans.y < 0)
        {
            ans.y += p;
        }
        cout << ans.x << " " << ans.y;
    }
}