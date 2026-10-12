#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class LazySegmentTree {
private:
    vector<int> tree;
    vector<int> lazy;
    int n;
    
    void build(int node, int start, int end, const vector<int>& arr) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(2 * node, start, mid, arr);
            build(2 * node + 1, mid + 1, end, arr);
            tree[node] = min(tree[2 * node], tree[2 * node + 1]);
        }
    }
    
    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node];
            if (start != end) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }
    
    void updateRange(int node, int start, int end, int l, int r, int val) {
        push(node, start, end);
        
        if (start > r || end < l) {
            return;
        }
        
        if (start >= l && end <= r) {
            lazy[node] += val;
            push(node, start, end);
            return;
        }
        
        int mid = (start + end) / 2;
        updateRange(2 * node, start, mid, l, r, val);
        updateRange(2 * node + 1, mid + 1, end, l, r, val);
        
        push(2 * node, start, mid);
        push(2 * node + 1, mid + 1, end);
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }
    
    int queryRange(int node, int start, int end, int l, int r) {
        if (start > r || end < l) {
            return INT_MAX;
        }
        
        push(node, start, end);
        
        if (start >= l && end <= r) {
            return tree[node];
        }
        
        int mid = (start + end) / 2;
        int left_min = queryRange(2 * node, start, mid, l, r);
        int right_min = queryRange(2 * node + 1, mid + 1, end, l, r);
        return min(left_min, right_min);
    }
    
public:
    LazySegmentTree(const vector<int>& arr) {
        n = arr.size() - 1; // 1-based indexing
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(1, 1, n, arr);
    }
    
    void updateRange(int l, int r, int val) {
        updateRange(1, 1, n, l, r, val);
    }
    
    int queryRange(int l, int r) {
        return queryRange(1, 1, n, l, r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int x, k, p;
    scanf("%d %d %d", &x, &k, &p);
    
    // Initialize available seats for each segment (1 to x-1)
    vector<int> available(x + 1, k);
    
    LazySegmentTree st(available);
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        scanf("%d %d %d", &u, &v, &n);
        
        // Check if all segments from u to v-1 have at least n available seats
        if (u >= v) {
            printf("N\n");
            continue;
        }
        
        int min_available = st.queryRange(u, v - 1);
        
        if (min_available >= n) {
            printf("T\n");
            // Update all segments from u to v-1 by subtracting n
            st.updateRange(u, v - 1, -n);
        } else {
            printf("N\n");
        }
    }
    
    return 0;
}