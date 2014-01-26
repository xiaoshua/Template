const int N = 1e7+9;
int p[N/5], pn;
bool notP[N];
bool getP() {
    int i, j;
    for(i=2; i<N; ++i) {
        if(!notP[i]) p[pn++]=i;
        for(j=0; j<pn && i*p[j]<N; ++j) {
            notP[i*p[j]]=true;
            if(i%p[j]==0) break;
        }
    }
}
