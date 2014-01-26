const int N = 1e7+9;
int p[N/5], pn;
bool notP[N];
bool getP(int n=N) {
    int i, j;
    for(i=2; i<n; ++i) {
        if(!notP[i]) p[pn++]=i;
        for(j=0; j<pn && i*p[j]<n; ++j) {
            notP[i*p[j]]=true;
            if(i%p[j]==0) break;
        }
    }
}
