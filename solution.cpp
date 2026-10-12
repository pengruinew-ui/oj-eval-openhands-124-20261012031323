#include <bits/stdc++.h>
using namespace std;

int main() {
    int x, k, p;
    scanf("%d %d %d", &x, &k, &p);
    
    vector<int> available(x + 1, k);
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        scanf("%d %d %d", &u, &v, &n);
        
        if (u >= v) {
            printf("N\n");
            continue;
        }
        
        bool can_fulfill = true;
        for (int j = u; j < v; j++) {
            if (available[j] < n) {
                can_fulfill = false;
                break;
            }
        }
        
        if (can_fulfill) {
            printf("T\n");
            for (int j = u; j < v; j++) {
                available[j] -= n;
            }
        } else {
            printf("N\n");
        }
    }
    
    return 0;
}