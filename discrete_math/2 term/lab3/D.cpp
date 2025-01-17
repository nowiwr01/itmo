#include <map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

/*
......................／＞　フ
.................... | _　 _l
..................／` ミ＿xノ
................/　　　　 |
............. / ヽ　　 ﾉ
.............│　　 |　|　|
..........／￣|　　 |　|　|
.......... | (￣ヽ＿_ヽ_)__)
...........＼二つ
*/

const int MAXN = 101;
const int MOD = 1000000007;
long long d[MAXN][MAXN][MAXN];

int n;
char symbol;
string current_string;
vector<pair<int, int>> graph[MAXN];

int main() {

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    freopen("nfc.in", "r", stdin);
    freopen("nfc.out", "w", stdout);

    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            for (int k = 0; k < MAXN; k++) {
                d[i][j][k] = 0;
            }
        }
    }

    cin >> n >> symbol;

    getline(cin, current_string);
    for (int i = 0; i < n; i++) {
        getline(cin, current_string);
        int from = current_string[0] - 'A';
        if (current_string[5] >= 'a' && current_string[5] <= 'z') {
            graph[from].emplace_back(current_string[5] - 'a', -1);
        }
        else {
            graph[from].emplace_back(current_string[5] - 'A', current_string[6] - 'A');
        }
    }

    getline(cin, current_string);

    // Алгоритм Кока-Янгера-Касами
    for (int i = 0; i < current_string.size(); i++) {
        for (int j = 0; j < 26; j++) {
            for (pair<int, int> current_map : graph[j]) {
                if (current_map.second == -1 && ((current_string[i] - 'a') == current_map.first)) {
                    d[j][i][i] += 1;
                }
            }
        }
    }

    for (int length = 2; length <= current_string.size(); length++) {
        for (int length2 = 0; length2 <= current_string.size() - length; length2++) {
            int current_length = length2 + length - 1;
            for (int k = length2; k < current_length; k++) {
                for (int i = 0; i < 26; i++) {
                    for (pair<int, int> current_map : graph[i]) {
                        if (current_map.second != -1) {
                            d[i][length2][current_length] = (d[i][length2][current_length] +
                                    d[current_map.first][length2][k] * d[current_map.second][k + 1][current_length]) % MOD;
                        }
                    }
                }
            }
        }
    }

    cout << d[symbol - 'A'][0][current_string.size() - 1] << endl;

    return 0;
}