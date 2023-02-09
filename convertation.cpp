#include <bits/stdc++.h>

#define st string
#define pb push_back
#define no cout << "NO" << endl;
#define yes cout << "YES" << endl;
#define vec vector
#define len length()
#define all(a) a.begin(), a.end()
#define ff first
#define ss second
#define int long long

using namespace std;
using vl = vec<int>;
using vi = vec<int>;
using vvi = vec<vi>;
using pi = pair<int, int>;
using vpi = vec<pi>;
using vvvi = vec<vvi>;
using vvpi = vec<vec<pi>>;
using vvvpi = vec<vvpi>;
using vvvvi = vec<vvvi>;
using vppi = vec<pair<pair<int, int>, pair<int, int>>>;

int check(char x) {
    if (x >= '0' && x <= '9') {
        return 1;
    }
    if (x >= 'a' && x <= 'z') {
        return 1;
    }
    if (x >= 'A' && x <= 'Z') {
        return 1;
    }
    return 0;
}

const int P = 1000;

struct Node {
    int l = 0, r = 0;
    st op;
    int x = 0;
};

vec<Node> t;
int c = 0;

// [l,r)
int calcinf(vec<st> &a, int l, int r, map<st, int> &prio) {
    //cout << l << " " << r << endl;
    if (r <= l) {
        return 0;
    }
    int n = a.size();
    vpi pri;
    int b = 0;
    for (int i = l; i < r; i++) {
        if (a[i] == "(") {
            b++;
        }
        if (a[i] == ")") {
            b--;
        }
        if (prio.find(a[i]) != prio.end()) {
            pri.pb({b * P + prio[a[i]], -i});
        }
    }
    sort(all(pri));
    for (auto u : pri) {
        st nw = a[-u.ss];
        if (prio.find(nw) != prio.end()) {
            //cout << nw << endl;
            Node x;
            x.op = nw;
            c++;
            t.pb(x);
            int id = c;
            int ll = calcinf(a, l, -u.ss, prio);
            int rl = calcinf(a, -u.ss + 1, r, prio);
            t[id].l = ll;
            t[id].r = rl;
            return id;
        }
    }
    for (int i = l; i < r; i++) {
        st nw = a[i];
        if (nw != "(" && nw != ")") {
            Node x;
            x.op = nw;
            t.pb(x);
            c++;
            return c;
        }
    }
    return 0;
}

int gl = 0;

//int calcpref(vec<st> &a, int x) {
//    if (x >= a.size()) {
//        return 0;
//    }
//    Node nd;
//    nd.op = a[x];
//    t.pb(nd);
//    c++;
//    int id = c;
//    if (a[x] != "+" && a[x] != "-" && a[x] != "*" && a[x] != "/") {
//        gl++;
//        return id;
//    }
//    gl++;
//    int l = calcpref(a, gl);
//    gl++;
//    int r = calcpref(a, gl);
//    t[id].l = l;
//    t[id].r = r;
//    return id;
//}

int find(int v, st &s, int x) {
    if (v == 0) return 0;
    int ok = 0;
    ok |= find(t[v].l, s, x);
    if (!ok) {
        ok |= find(t[v].r, s, x);
    }
    if (!ok) {
        if (t[v].op == "+" || t[v].op == "-" || t[v].op == "*" || t[v].op == "/") {
            if (!t[v].l) {
                t[v].l = x;
                return 1;
            }
            if (!t[v].r) {
                t[v].r = x;
                return 1;
            }
        }
    }
    return (ok ? 1 : 0);
}

void calcpref(vec<st> &a, int x) {
    Node nd;
    nd.op = a[x];
    t.pb(nd);
    c++;
    if (c == 1) {
        return;
    }
    find(1, a[x], c);
}

int find2(int v, st &s, int x) {
//    if (x == 6) {
//        cout << v << endl;
//    }

    if (v == 0) return 0;

    int ok = 0;
    ok |= find2(t[v].r, s, x);

    if (!ok) {
        if (t[v].op == "+" || t[v].op == "-" || t[v].op == "*" || t[v].op == "/") {
            if (!t[v].r) {
                t[v].r = x;
                return 1;
            }
        }
    }

    if (!ok) {
        ok |= find2(t[v].l, s, x);
    }

    if (!ok) {
        if (t[v].op == "+" || t[v].op == "-" || t[v].op == "*" || t[v].op == "/") {
            if (!t[v].l) {
                t[v].l = x;
                return 1;
            }
        }
    }

    return (ok ? 1 : 0);
}

void calcpost(vec<st> &a, int x) {
    Node nd;
    nd.op = a[x];
    t.pb(nd);
    c++;
    if (c == 1) {
        return;
    }
    find2(1, a[x], c);
}

void printpost(int v) {
    if (v == 0) return;
    printpost(t[v].l);
    printpost(t[v].r);
    cout << t[v].op << " ";
}

void printpref(int v) {
    if (v == 0) return;
    cout << t[v].op << " ";
    printpref(t[v].l);
    printpref(t[v].r);
}

st printinf(int v) {
    if (v == 0) return "";
    st s1 = printinf(t[v].l);
    st s2 = printinf(t[v].r);
    st s3;
    st x = t[v].op;
    if (x != "+" && x != "-" && x != "*" && x != "/") {
        s3 += x;
        return s3;
    }
    x = t[t[v].l].op;
    if (x != "+" && x != "-" && x != "*" && x != "/") {
        s3 += x;
    }
    else {
        s3 += '(';
        s3 += s1;
        s3 += ')';
    }
    s3 += t[v].op;
    x = t[t[v].r].op;
    if (x != "+" && x != "-" && x != "*" && x != "/") {
        s3 += x;
    }
    else {
        s3 += '(';
        s3 += s2;
        s3 += ')';
    }
    return s3;
}

void infix() {
    t.resize(1);
    map<st, int> prio;
    prio["+"] = 1;
    prio["-"] = 1;
    prio["*"] = 2;
    prio["/"] = 2;
    st s;
    getline(cin, s);
    getline(cin, s);
    int n = s.size();
    st nw;
    vec<st> ans;
    for (int i = 0; i < n; i++) {
        if (s[i] == ' ') {
            continue;
        }
        if (check(s[i])) {
            nw += s[i];
        }
        else {
            if (nw.size()) {
                ans.pb(nw);
                nw = "";
            }
            st s1;
            s1 += s[i];
            ans.pb(s1);
        }
    }
    if (nw.size()) {
        ans.pb(nw);
    }
    calcinf(ans, 0, ans.size(), prio);
    if (c) {
        cout << "Postfix: ";
        printpost(1);
        cout << endl;
        cout << "Prefix: ";
        printpref(1);
    }
}

void prefix() {
    t.resize(1);
    map<st, int> prio;
    prio["+"] = 1;
    prio["-"] = 1;
    prio["*"] = 2;
    prio["/"] = 2;
    vec<st> ans;
    cout << "Enter count of operations:" << endl;
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        st s; cin >> s;
        ans.pb(s);
    }

    for (int i = 0; i < ans.size(); i++) {
        calcpref(ans, i);
    }
    if (c) {
        cout << "Postfix: ";
        printpost(1);
        cout << endl;
        cout << "Infix: ";
        cout << printinf(1);
    }
}

void postfix() {
    t.resize(1);
    map<st, int> prio;
    prio["+"] = 1;
    prio["-"] = 1;
    prio["*"] = 2;
    prio["/"] = 2;
    vec<st> ans;
    cout << "Enter count of operations:" << endl;
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        st s; cin >> s;
        ans.pb(s);
    }

    for (int i = ans.size() - 1; i >= 0; i--) {
        calcpost(ans, i);
    }

//    for (int i = 0; i <= c; i++) {
//        cout << i << " " << t[i].op << " " << t[i].l << " " << t[i].r << endl;
//    }

    if (c) {
        cout << "Prefix: ";
        printpref(1);
        cout << endl;
        cout << "Infix: ";
        cout << printinf(1);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    //freopen("input.csv", "r", stdin);
    //freopen("output.csv", "w", stdout);
    /*int tt; cin >> tt;
    while (tt--) {
        solve();
    }*/
    st s; cin >> s;
    if (s == "infix") {
        infix();
    }
    else if (s == "prefix") {
        prefix();
    }
    else {
        postfix();
    }
}