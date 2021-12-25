#include <iostream>
#include <vector>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
const int INF = INT_MAX;

pii minPair(pii a, pii b) {
    if (a.first == b.first) {
        return (a.second > b.second) ? b : a;
    } else {
        return (a.first > b.first) ? b : a;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, s;
    cin >> n >> s;
    int pow2 = 1 << n;
    vi w(n), prev(pow2);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }

    vector<pii> dp = vector<pii>(pow2, { INF, 0 });
    dp[0] = { 1, 0 };
    for (int x = 1; x < pow2; x++) {
        int ind = -1;
        pii minP = {INF, INF};
        for (int i = 0; i < n; i++) {
            if ((x & (1 << i)) > 0) {
                pii tmp = dp[x - (1 << i)];
                if (tmp.second + w[i] <= s) {
                    tmp = { tmp.first, tmp.second + w[i] };
                } else {
                    tmp = { tmp.first + 1, w[i] };
                }
                if (minPair(tmp, minP) == tmp) {
                    minP = tmp;
                    ind = x - (1 << i);
                }
            }
        }
        dp[x] = minP;
        prev[x] = ind;
    }

    int cnt = dp[pow2 - 1].first;
    cout << cnt << '\n';

    /*for (int i = 0; i < pow2; i++) {
        printf("%2d (%d,%3d) %2d\n", i, dp[i].first, dp[i].second, prev[i]);
    }*/

    int mask = pow2 - 1;
    int last = 0;
    int i = 0;
    int tmpW = 0;
    vvi bags(cnt);

    while (mask > 0) {
        if (w[i] + tmpW > s) {
            last++;
            tmpW = 0;
        }
        bags[last].push_back(i);
        tmpW += w[i++];
        mask = prev[mask];
    }

    for (vi& bag : bags) {
        cout << bag.size() << " ";
        for (int j : bag) {
            cout << j + 1 << " ";
        }
        cout << '\n';
    }

    return 0;
}
