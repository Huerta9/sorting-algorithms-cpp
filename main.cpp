#include <iostream>
#include <vector>
using namespace std;

// ordenaIntercambio
void ordenaIntercambio(vector<int>& v, long long& comps) {
    int n = (int)v.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            comps++;
            if (v[j] < v[i]) {
                swap(v[i], v[j]);
            }
        }
    }
}

// ordenaBurbuja
void ordenaBurbuja(vector<int>& v, long long& comps) {
    int n = (int)v.size();
    bool huboIntercambio = true;
    for (int i = 0; i < n - 1 && huboIntercambio; i++) {
        huboIntercambio = false;
        for (int j = 0; j < n - 1 - i; j++) {
            comps++;
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
                huboIntercambio = true;
            }
        }
    }
}

// merge (auxiliar de ordenaMerge)
void merge(vector<int>& v, int l, int m, int r, long long& comps) {
    vector<int> tmp;
    tmp.reserve(r - l + 1);
    int i = l, j = m + 1;

    while (i <= m && j <= r) {
        comps++;
        if (v[i] <= v[j]) {
            tmp.push_back(v[i++]);
        } else {
            tmp.push_back(v[j++]);
        }
    }
    while (i <= m) {
        comps++;
        tmp.push_back(v[i++]);
    }
    while (j <= r) {
        comps++;
        tmp.push_back(v[j++]);
    }

    for (int k = 0; k < (int)tmp.size(); k++) {
        v[l + k] = tmp[k];
    }
}

// mergeSortRec (auxiliar de ordenaMerge)
void mergeSortRec(vector<int>& v, int l, int r, long long& comps) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSortRec(v, l, m, comps);
    mergeSortRec(v, m + 1, r, comps);
    merge(v, l, m, r, comps);
}

// ordenaMerge
void ordenaMerge(vector<int>& v, long long& comps) {
    if (v.empty()) return;
    mergeSortRec(v, 0, (int)v.size() - 1, comps);
}

// busqSecuencial
int busqSecuencial(const vector<int>& v, int dato, long long& comps) {
    int n = (int)v.size();
    for (int i = 0; i < n; i++) {
        comps++;
        if (v[i] == dato) {
            return i;
        }
    }
    return -1;
}

// busqBinaria
int busqBinaria(const vector<int>& v, int dato, long long& comps) {
    int low = 0, high = (int)v.size() - 1;
    while (low <= high) {
        comps++;
        int mid = low + (high - low) / 2;
        if (v[mid] == dato) {
            return mid;
        } else if (v[mid] < dato) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

// main
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> original(n);
    for (int i = 0; i < n; i++) {
        cin >> original[i];
    }

    int b;
    cin >> b;

    vector<int> busquedas(b);
    for (int i = 0; i < b; i++) {
        cin >> busquedas[i];
    }

    vector<int> vIntercambio = original;
    vector<int> vBurbuja = original;
    vector<int> vMerge = original;

    long long compIntercambio = 0, compBurbuja = 0, compMerge = 0;

    ordenaIntercambio(vIntercambio, compIntercambio);
    ordenaBurbuja(vBurbuja, compBurbuja);
    ordenaMerge(vMerge, compMerge);

    const vector<int>& ordenado = vMerge;

    cout << compIntercambio << " " << compBurbuja << " " << compMerge << "\n";

    for (int i = 0; i < b; i++) {
        int dato = busquedas[i];

        long long compSec = 0, compBin = 0;
        int posSec = busqSecuencial(original, dato, compSec);
        int posBin = busqBinaria(ordenado, dato, compBin);

        cout << posSec << " " << compSec << " " << posBin << " " << compBin << "\n";
    }

    return 0;
}