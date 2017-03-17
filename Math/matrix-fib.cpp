// f[0]=0, f[1]=1, f[n]=f[n-2]+f[n-1]
#include<cstdio>
const int N = 2;
const int MOD = 10000;
int a[N][N], b[N][N], c[N][N];
void mul(int a[N][N], int b[N][N], int n)
{
    int i, j, k;
    for(i=0; i<n; ++i)
    {
        for(j=0; j<N; ++j)
        {
            c[i][j] = 0;
            for(k=0; k<N; ++k)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    for(i=0; i<n; ++i)
    {
        for(j=0; j<N; ++j)
        {
            a[i][j] = c[i][j] % MOD;
        }
    }
}
int main()
{
    int t, n, i, j;
    while(~scanf("%d", &n))
    {
        if(n == -1) break;
        a[0][0] = 0;
        a[0][1] = 1;
        b[0][0] = 0;
        b[0][1] = b[1][0] = b[1][1] = 1;
        while(n)
        {
            if(n&1) mul(a, b, 1);
            mul(b, b, 2);
            n >>= 1;
        }
        printf("%d\n", a[0][0]);
    }
    return 0;
}

