#include <iostream>

using namespace std;

// 扩展欧几里得算法求逆元
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
    long long x; // 输入点的横坐标
    long long y; // 输入点的纵坐标
    bool isInfinity; // 该点是否为无穷远点的标志位，初始设置为false
    Point operator=(Point point); // 重载赋值号
    bool operator==(Point point); // 重载等号
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
    // 椭圆曲线的属性
    long long a;
    long long b;
    long long p;

public:
    ecc() : a(0),b(0),p(0) {};
    ecc(long long a,long long b,long long p) : a(a),b(b),p(p) {};
    Point Pointadd(Point point1,Point point2); // 点加
};

/*
    因为题目要求的是倍加
    我这里point1代表的是每次倍加后的结果
    point2代表原始输入的点
*/
Point ecc::Pointadd(Point point1,Point point2)
{
    long long t; // 就是公式里的λ
    Point ans;
    // 当point1是无穷远点时，直接返回point2
    if(point1.isInfinity)
    {
        return point2;
    }
    // 当两点相同，使用此公式
    if(point1.operator==(point2))
    {
        long long t1 = getInv(2*point1.y,p); // 这里要求模逆
        t = ((3 * (point1.x * point1.x) + a) * t1) % p; 
    }
    // 当两点不同，使用此公式
    else
    {
        long long t2 = point2.x-point1.x;
        // 当两点横坐标相同，证明此时两点点加为无穷远点
        // 因此将ans的无穷远点标志位设置为真后直接返回
        // 不必担心重置为非无穷远点的问题
        // 因为在此之后若还要进行点加操作就会直接返回输入的点
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

    // 发现是无穷远点或k为0返回（-1，-1）
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