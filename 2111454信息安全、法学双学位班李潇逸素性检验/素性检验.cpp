#include <iostream>
using namespace std;
long long mod_mul(long long a, long long b, long long n)//快速乘法
{
	long long result = 0;
	while (b > 0)
	{
		if (b & 1)//判断是否为偶数
			result = (result + a) % n;
		a = (a + a) % n;
		b = b >> 1;//除二操作
	}
	return result;
}
long long mod_exp(long long a, long long b, long long n)//快速幂
{
	long long result = 1;
	while (b > 0)
	{
		if ((b & 1) > 0)
			result = mod_mul(result, a, n);
		a = mod_mul(a, a, n);
		b = b >> 1;//除二操作
	}
	return result;
}
bool isprime(long long n)
{
	int k = 0;
	long long p = n - 1;
	while ((p & 1) == 0)//判断是否为奇数
	{
		p = p >> 1;//除二操作
		k++;
	}
	for (int i = 0; i < 6; i++)
	{
		long long a = rand() % (n - 1 - 1 + 1) + 1;
		long long b = mod_exp(a, p, n);
		bool flag = false;
		if (b == 1)
			continue;
		for (int j = 0; j < k; j++)
			if ((b + 1) % n == 0)
			{
				flag = true;
				break;
			}
			else
				b = (b * b) % n;
		if (flag)
			continue;
		return false;
	}
	return true;
}
int main()
{
	long long N;
	cin >> N;
    if (N == 0 || N == 1)
    {
        cout <<"No";
    }
    else
    {
        if (isprime(N))
        {
            cout <<"Yes";
        }
        else
        {
            cout <<"No";
        }
    }
}