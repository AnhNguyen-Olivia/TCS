#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// ANSI Color Codes
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_RESET "\033[0m"

// Global DFA configuration
int** arTrans = nullptr;
char* arEdgeVal = nullptr;
int* arFinalState = nullptr;
int m, n, q0, sizeF;

bool isValidDFA() {
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(arTrans[i][j] < 0 || arTrans[i][j] >= m) {
                cout << COLOR_RED << "\nInvalid transition from state " << i 
                     << " on symbol '" << arEdgeVal[j] << "'" << COLOR_RESET;
                return false;
            }
        }
    }
    return true;
}

void displayMenu() {
    cout << COLOR_BLUE << "\n\n========== DFA Simulator Menu ==========\n" << COLOR_RESET;
    cout << "1. Test a single string\n";
    cout << "2. Batch test multiple strings\n";
    cout << "3. Display transition table\n";
    cout << "4. Generate DFA visualization code\n";
    cout << "5. Step-by-step execution mode\n";
    cout << "6. Display DFA information\n";
    cout << "7. Exit\n";
    cout << COLOR_BLUE << "=======================================\n" << COLOR_RESET;
    cout << "Enter your choice: ";
}

bool validS(int currentState, const string& s, bool trace = false) {
    if(trace) cout << COLOR_YELLOW << "\n[TRACE] Starting state: q" << currentState << COLOR_RESET;
    
    for (char c : s) {
        int symbolIndex = -1;
        for (int i = 0; i < n; ++i) {
            if (arEdgeVal[i] == c) {
                symbolIndex = i;
                break;
            }
        }
        
        if (symbolIndex == -1) {
            if(trace) cout << COLOR_RED << "\n[TRACE] Invalid symbol '" << c << "'" << COLOR_RESET;
            return false;
        }

        int newState = arTrans[currentState][symbolIndex];
        if(trace) {
            cout << COLOR_YELLOW << "\n[TRACE] Reading '" << c 
                 << "' : q" << currentState << " -> q" << newState << COLOR_RESET;
        }
        currentState = newState;
    }

    bool accepted = false;
    for (int i = 0; i < sizeF; ++i) {
        if (arFinalState[i] == currentState) {
            accepted = true;
            break;
        }
    }
    
    if (trace) {
        cout << COLOR_YELLOW << "\n[TRACE] Final state: q" << currentState << " (" << COLOR_RESET;
        if (accepted) {
            cout << "Accept" << COLOR_GREEN;
        } else {
            cout << "Reject" << COLOR_RED;
        }
        cout << ")" << COLOR_RESET << endl;
    }
    
    return accepted;
}

void generateDFAdiagram() {
    cout << COLOR_GREEN << "\n// To visualize this DFA:\n";
    cout << "1. Copy the following code below\n";
    cout << "2. Go to https://dreampuf.github.io/GraphvizOnline/\n";
    cout << "3. Paste the code in the left panel and wait\n";
    cout << COLOR_RESET;

    cout << "digraph G {" << endl;
    cout << "  rankdir=LR;" << endl;
    cout << "  node [shape = point]; start;" << endl;
    cout << "  node [shape = doublecircle]; ";
    for(int i = 0; i < sizeF; i++) cout << "q" << arFinalState[i] << " ";
    cout << ";" << endl;
    cout << "  node [shape = circle];" << endl;
    cout << "  start -> q" << q0 << ";" << endl;
    
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            cout << "  q" << i << " -> q" << arTrans[i][j] 
                 << " [label=\"" << arEdgeVal[j] << "\"];" << endl;
        }
    }
    cout << "}" << endl;
}

void displayDFAInfo() {
    cout << COLOR_BLUE << "\n===== DFA Information =====" << COLOR_RESET;
    cout << "\nStates: q0 -> q" << m-1;
    cout << "\nAlphabet: ";
    for(int i = 0; i < n; i++) cout << arEdgeVal[i] << " ";
    cout << "\nStart state: q" << q0;
    cout << "\nFinal states: ";
    for(int i = 0; i < sizeF; i++) cout << "q" << arFinalState[i] << " ";
    cout << "\n" << COLOR_BLUE << "===========================" << COLOR_RESET << endl;
}

void setupDFA() {
    cout << COLOR_BLUE << "\n===== DFA Setup =====" << COLOR_RESET;
    cout << "\nNumber of states: ";
    cin >> m;
    cout << "Number of symbols: ";
    cin >> n;

    arTrans = new int*[m];
    for(int i = 0; i < m; ++i) arTrans[i] = new int[n];

    arEdgeVal = new char[n];
    cout << "Enter symbols (space separated): ";
    for(int i = 0; i < n; ++i) cin >> arEdgeVal[i];

    cout << "Start state (0-" << m-1 << "): ";
    cin >> q0;

    cout << "Number of final states: ";
    cin >> sizeF;
    arFinalState = new int[sizeF];
    cout << "Final states (space separated): ";
    for(int i = 0; i < sizeF; ++i) cin >> arFinalState[i];

    cout << "Transition table:\n";
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            cout << "δ(q" << i << ", " << arEdgeVal[j] << ") = ";
            cin >> arTrans[i][j];
        }
    }

    if(!isValidDFA()) {
        cout << COLOR_RED << "\nInvalid DFA configuration!" << COLOR_RESET;
        exit(1);
    }
}

int main() {
    cout << COLOR_GREEN << "============== DFA Simulator ==============" << COLOR_RESET;
    
    // Initial setup
    setupDFA();
    displayDFAInfo();

    int choice;
    string s, filename;
    
    do {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch(choice) {
            case 1: {
                cout << "Enter string to test: ";
                cin >> s;
                bool result = validS(q0, s);
                cout << "Result: " << (result ? COLOR_GREEN "Accepted" : COLOR_RED "Rejected") 
                     << COLOR_RESET << endl;
                break;
            }
            case 2: {
                cout << "Enter multiple strings (type 'exit' to stop):\n";
                while(true) {
                    cout << "> ";
                    cin >> s;
                    if(s == "exit") break;
                    bool result = validS(q0, s);
                    cout << "  " << (result ? COLOR_GREEN "Accepted " : COLOR_RED "Rejected ") 
                         << COLOR_RESET << s << endl;
                }
                break;
            }
            case 3: {
                cout << "\nTransition Table:\n";
                cout << left << setw(8) << "State";
                for(int j = 0; j < n; ++j) cout << setw(8) << arEdgeVal[j];
                cout << "\n----------------------------------\n";
                for(int i = 0; i < m; ++i) {
                    cout << setw(8) << i;
                    for(int j = 0; j < n; ++j) cout << setw(8) << arTrans[i][j];
                    cout << endl;
                }
                break;
            }
            case 4:
                generateDFAdiagram();
                break;
            case 5: {
                cout << "Enter string for step-by-step analysis: ";
                cin >> s;
                validS(q0, s, true);
                break;
            }
            case 6:
                displayDFAInfo();
                break;
            case 7:
                cout << COLOR_GREEN << "Exiting..." << COLOR_RESET << endl;
                break;
            default:
                cout << COLOR_RED << "Invalid choice!" << COLOR_RESET << endl;
        }
    } while(choice != 7);

    // Cleanup
    for(int i = 0; i < m; i++) delete[] arTrans[i];
    delete[] arTrans;
    delete[] arEdgeVal;
    delete[] arFinalState;

    return 0;
}