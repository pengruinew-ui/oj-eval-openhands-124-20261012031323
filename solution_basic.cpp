#include <cstdio>
#include <algorithm>
using namespace std;

const int MAX_X = 1000005;

int main() {
    int x, k, p;
    scanf("%d %d %d", &x, &k, &p);
    
    int available[MAX_X];
    for (int i = 1; i < x; i++) {
        available[i] = k;
    }
    
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