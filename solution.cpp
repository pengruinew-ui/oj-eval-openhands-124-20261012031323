#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class SegmentTree {
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
    
    void update(int node, int start, int end, int l, int r, int val) {
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
        update(2 * node, start, mid, l, r, val);
        update(2 * node + 1, mid + 1, end, l, r, val);
        
        push(2 * node, start, mid);
        push(2 * node + 1, mid + 1, end);
        tree[node] = min(tree[2 * node], tree[2 * node + 1]);
    }
    
    int query(int node, int start, int end, int l, int r) {
        if (start > r || end < l) {
            return INT_MAX;
        }
        
        push(node, start, end);
        
        if (start >= l && end <= r) {
            return tree[node];
        }
        
        int mid = (start + end) / 2;
        int left_min = query(2 * node, start, mid, l, r);
        int right_min = query(2 * node + 1, mid + 1, end, l, r);
        return min(left_min, right_min);
    }
    
public:
    SegmentTree(int size, int initial_value) {
        n = size;
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        vector<int> arr(n + 1, initial_value);
        build(1, 1, n, arr);
    }
    
    void update_range(int l, int r, int val) {
        if (l <= r) {
            update(1, 1, n, l, r, val);
        }
    }
    
    int query_min(int l, int r) {
        if (l <= r) {
            return query(1, 1, n, l, r);
        }
        return INT_MAX;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int x, k, p;
    if (scanf("%d %d %d", &x, &k, &p) != 3) return 0;
    
    SegmentTree st(x - 1, k);
    
    for (int i = 0; i < p; i++) {
        int u, v, n;
        if (scanf("%d %d %d", &u, &v, &n) != 3) break;
        
        if (u >= v || u < 1 || v > x) {
            printf("N\n");
            continue;
        }
        
        int min_available = st.query_min(u, v - 1);
        
        if (min_available >= n) {
            printf("T\n");
            st.update_range(u, v - 1, -n);
        } else {
            printf("N\n");
        }
    }
    
    return 0;
}