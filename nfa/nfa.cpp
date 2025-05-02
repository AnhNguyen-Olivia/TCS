#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

void find_lambda_closure(int q, int N, int M, int*** arTrans, int& nLC, int* &arLC) {
    bool* visited = new bool[N]();
    queue<int> q_queue;
    q_queue.push(q);
    visited[q] = true;
    arLC = new int[N];
    nLC = 0;
    arLC[nLC++] = q;

    while (!q_queue.empty()) {
        int current = q_queue.front();
        q_queue.pop();

        // M-1 is used to access lambda transitions (last column)
        int* transitions = arTrans[current][M-1];
        if (transitions != nullptr) {
            for (int i = 0; transitions[i] != -1; ++i) {
                int next_state = transitions[i];
                if (!visited[next_state]) {
                    visited[next_state] = true;
                    arLC[nLC++] = next_state;
                    q_queue.push(next_state);
                }
            }
        }
    }
    delete[] visited;
}

void move(int* states, int nStates, int a, int N, int*** arTrans, int* arEdgeVal, int sizeE, int* &arMoveA, int& nMove) {
    int j;
    for (j = 0; j < sizeE; ++j) {
        if (arEdgeVal[j] == a) break;
    }
    if (j >= sizeE) {
        arMoveA = nullptr;
        nMove = 0;
        return;
    }

    bool* added = new bool[N]();
    nMove = 0;
    arMoveA = new int[N];

    for (int i = 0; i < nStates; ++i) {
        int q = states[i];
        int* transitions = arTrans[q][j];
        if (transitions != nullptr) {
            for (int k = 0; transitions[k] != -1; ++k) {
                int next_state = transitions[k];
                if (!added[next_state]) {
                    added[next_state] = true;
                    arMoveA[nMove++] = next_state;
                }
            }
        }
    }

    delete[] added;
    if (nMove == 0) {
        delete[] arMoveA;
        arMoveA = nullptr;
    } else {
        int* temp = new int[nMove];
        memcpy(temp, arMoveA, nMove * sizeof(int));
        delete[] arMoveA;
        arMoveA = temp;
    }
}

void delta_star_q(int q, int a, int N, int M, int*** arTrans, int* arEdgeVal, int sizeE, int* &result, int& nResult) {
    int* S_lambda;
    int nS_lambda;
    find_lambda_closure(q, N, M, arTrans, nS_lambda, S_lambda);

    int* move_a;
    int nMove_a;
    move(S_lambda, nS_lambda, a, N, arTrans, arEdgeVal, sizeE, move_a, nMove_a);

    if (nMove_a == 0) {
        result = nullptr;
        nResult = 0;
        delete[] S_lambda;
        return;
    }

    bool* visited = new bool[N]();
    queue<int> q_queue;
    for (int i = 0; i < nMove_a; ++i) {
        if (!visited[move_a[i]]) {
            visited[move_a[i]] = true;
            q_queue.push(move_a[i]);
        }
    }

    result = new int[N];
    nResult = 0;

    while (!q_queue.empty()) {
        int current = q_queue.front();
        q_queue.pop();
        result[nResult++] = current;

        int* transitions = arTrans[current][M-1];
        if (transitions != nullptr) {
            for (int i = 0; transitions[i] != -1; ++i) {
                int next = transitions[i];
                if (!visited[next]) {
                    visited[next] = true;
                    q_queue.push(next);
                }
            }
        }
    }

    int* temp = new int[nResult];
    memcpy(temp, result, nResult * sizeof(int));
    delete[] result;
    result = temp;

    delete[] visited;
    delete[] S_lambda;
    delete[] move_a;
}

void delta_star_T(int* T, int nT, int a, int N, int M, int*** arTrans, int* arEdgeVal, int sizeE, int* &result, int& nResult) {
    bool* visited = new bool[N]();
    queue<int> q_queue;

    for (int i = 0; i < nT; ++i) {
        int q = T[i];
        if (!visited[q]) {
            int* lambda_closure;
            int n_lambda;
            find_lambda_closure(q, N, M, arTrans, n_lambda, lambda_closure);
            for (int j = 0; j < n_lambda; ++j) {
                int s = lambda_closure[j];
                if (!visited[s]) {
                    visited[s] = true;
                    q_queue.push(s);
                }
            }
            delete[] lambda_closure;
        }
    }

    int* T_lambda = new int[N];
    int nT_lambda = 0;
    memset(visited, 0, N * sizeof(bool));
    while (!q_queue.empty()) {
        int s = q_queue.front();
        q_queue.pop();
        if (!visited[s]) {
            visited[s] = true;
            T_lambda[nT_lambda++] = s;
            int* transitions = arTrans[s][M-1];
            if (transitions != nullptr) {
                for (int i = 0; transitions[i] != -1; ++i) {
                    int next = transitions[i];
                    if (!visited[next]) {
                        q_queue.push(next);
                    }
                }
            }
        }
    }

    int* move_a;
    int nMove_a;
    move(T_lambda, nT_lambda, a, N, arTrans, arEdgeVal, sizeE, move_a, nMove_a);

    if (nMove_a == 0) {
        result = nullptr;
        nResult = 0;
        delete[] T_lambda;
        delete[] visited;
        return;
    }

    memset(visited, 0, N * sizeof(bool));
    for (int i = 0; i < nMove_a; ++i) {
        if (!visited[move_a[i]]) {
            visited[move_a[i]] = true;
            q_queue.push(move_a[i]);
        }
    }

    result = new int[N];
    nResult = 0;

    while (!q_queue.empty()) {
        int current = q_queue.front();
        q_queue.pop();
        result[nResult++] = current;

        int* transitions = arTrans[current][M-1];
        if (transitions != nullptr) {
            for (int i = 0; transitions[i] != -1; ++i) {
                int next = transitions[i];
                if (!visited[next]) {
                    visited[next] = true;
                    q_queue.push(next);
                }
            }
        }
    }

    int* temp = new int[nResult];
    memcpy(temp, result, nResult * sizeof(int));
    delete[] result;
    result = temp;

    delete[] visited;
    delete[] T_lambda;
    delete[] move_a;
}

int main() {
    int N, M, sizeE;
    cout << "Enter number of states (N): ";
    cin >> N;
    cout << "Enter number of input symbols (including lambda): ";
    cin >> M;
    sizeE = M - 1; // Last column is for lambda

    if (M < 1) {
        cerr << "Error: At least 1 symbol (lambda) required!\n";
        return 1;
    }

    // Input edge values (symbols)
    int* arEdgeVal = new int[sizeE];
    cout << "Enter non-lambda symbols (e.g., a b), press Enter after each:\n";
    for (int i = 0; i < sizeE; ++i) {
        char inputChar;
        cout << "Symbol " << i + 1 << ": ";
        cin >> inputChar;
        arEdgeVal[i] = static_cast<int>(inputChar);
    }

    // Build transition table
    int*** arTrans = new int**[N];
    for (int i = 0; i < N; ++i) {
        arTrans[i] = new int*[M];
        cout << "\n--- State " << i << " ---\n";
        for (int j = 0; j < M; ++j) {
            if (j < sizeE) {
                cout << "  On symbol '" << (char)arEdgeVal[j] << "' (enter states space-separated, end with -1): ";
            } else {
                cout << "  On lambda (enter states space-separated, end with -1): ";
            }
            
            vector<int> transitions;
            int state;
            while (true) {
                cin >> state;
                if (state == -1) break;
                if (state < 0 || state >= N) {
                    cerr << "Invalid state! Valid states are 0-" << N-1 << ". Please re-enter:\n";
                    continue;
                }
                transitions.push_back(state);
            }
            transitions.push_back(-1);
            
            arTrans[i][j] = new int[transitions.size()];
            copy(transitions.begin(), transitions.end(), arTrans[i][j]);
        }
    }

    // Input query parameters with validation
    int q;
    do {
        cout << "\nEnter state q (0-" << N-1 << "): ";
        cin >> q;
    } while (q < 0 || q >= N);

    char aChar;
    bool validSymbol = false;
    int a;
    do {
        cout << "Enter symbol a (valid: ";
        for (int i = 0; i < sizeE; ++i) {
            cout << "'" << (char)arEdgeVal[i] << "' ";
        }
        cout << "): ";
        cin >> aChar;
        a = static_cast<int>(aChar);
        for (int i = 0; i < sizeE; ++i) {
            if (arEdgeVal[i] == a) {
                validSymbol = true;
                break;
            }
        }
        if (!validSymbol) {
            cerr << "Invalid symbol! Please try again.\n";
        }
    } while (!validSymbol);

    int nT;
    cout << "Enter size of set T: ";
    cin >> nT;
    int* T = new int[nT];
    cout << "Enter states in T (0-" << N-1 << " space-separated): ";
    for (int i = 0; i < nT; ++i) {
        do {
            cin >> T[i];
            if (T[i] < 0 || T[i] >= N) {
                cerr << "Invalid state! Enter again (0-" << N-1 << "): ";
            }
        } while (T[i] < 0 || T[i] >= N);
    }

    // Compute results
    int* result_q, *result_T;
    int nResult_q, nResult_T;
    delta_star_q(q, a, N, M, arTrans, arEdgeVal, sizeE, result_q, nResult_q);
    delta_star_T(T, nT, a, N, M, arTrans, arEdgeVal, sizeE, result_T, nResult_T);

    if (nResult_q > 0) sort(result_q, result_q + nResult_q);
    if (nResult_T > 0) sort(result_T, result_T + nResult_T);

    // Output results
    cout << "\ndelta*(q, a): ";
    if (nResult_q == 0) cout << "null sign";
    else for (int i = 0; i < nResult_q; ++i) cout << result_q[i] << " ";
    
    cout << "\ndelta*(T, a): ";
    if (nResult_T == 0) cout << "null sign";
    else for (int i = 0; i < nResult_T; ++i) cout << result_T[i] << " ";
    cout << endl;

    // Cleanup
    delete[] arEdgeVal;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) delete[] arTrans[i][j];
        delete[] arTrans[i];
    }
    delete[] arTrans;
    delete[] result_q;
    delete[] result_T;
    delete[] T;

    return 0;
}