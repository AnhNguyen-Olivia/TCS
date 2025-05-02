# User Guide: Lambda Closure & Transition Computation in NFAs

This program allows users to work with **non-deterministic finite automata (NFA)** with **lambda (ε) transitions**. It computes:

- The **lambda-closure** of a single state.
- The **delta\*(q, a)**: reachable states from a single state `q` via symbol `a` including lambda transitions.
- The **delta\*(T, a)**: reachable states from a set `T` via symbol `a`.

## 🛠 Requirements

- C++ Compiler (e.g., g++, clang++)
- Basic understanding of NFAs and lambda transitions

## 📂 Program Structure

### 1. **Input Parameters**

- **N**: Number of states.
- **M**: Number of symbols including lambda.
- **Symbols**: All symbols except lambda (lambda is assumed to be the last column).
- **Transition Table**: For each state and each symbol (including lambda), specify the next possible states.
- **q**: A specific state for `delta*(q, a)` query.
- **a**: The input symbol.
- **T**: A set of states for `delta*(T, a)` query.

### 2. **Key Functions**

#### ✅ `find_lambda_closure(int q, ...)`

Finds the lambda closure of a state `q` (i.e., all states reachable from `q` by following only lambda transitions).

#### ✅ `move(int* states, int nStates, int a, ...)`

Returns the set of states reachable by symbol `a` from a given set of states.

#### ✅ `delta_star_q(...)`

Computes the full transition of `q` by symbol `a` including lambda closures before and after the move.

#### ✅ `delta_star_T(...)`

Same as `delta_star_q`, but works on a set of states `T`.

### 3. **Output**

After processing:

- **`delta*(q, a)`** — Displays all states reachable from `q` by symbol `a` (with lambda transitions).
- **`delta*(T, a)`** — Displays all states reachable from a set of states `T` by symbol `a` (with lambda transitions).

If no states are reachable, it prints `null sign`.

## 💻 How to Use

### 🧾 Sample Input

``` terminal
Enter number of states (N): 3
Enter number of input symbols (including lambda): 2
Enter non-lambda symbols (e.g., a b), press Enter after each:
Symbol 1: a

--- State 0 ---
  On symbol 'a': 1 -1
  On lambda: 2 -1

--- State 1 ---
  On symbol 'a': -1
  On lambda: -1

--- State 2 ---
  On symbol 'a': 0 -1
  On lambda: -1

Enter state q (0-2): 0
Enter symbol a (valid: 'a'): a
Enter size of set T: 2
Enter states in T (0-2 space-separated): 0 1
```

### 🖨 Output

``` terminal
delta*(q, a): 0 1 2
delta*(T, a): 0 1 2
```

## 🧼 Memory Management

All dynamically allocated arrays are deallocated at the end of the program to prevent memory leaks.

## 📌 Notes

- Symbols are stored as ASCII integers.
- Lambda is always the last input symbol column (M-1).
- Input validation is provided for state indices and symbol correctness.
- Supports up to N states and M input symbols including lambda.

## 📎 Compilation

```bash
g++ -o lambda_closure lambda_closure.cpp
./lambda_closure
```

Replace `lambda_closure.cpp` with your file name if different.

## 🧠 Concepts Used

- Lambda (ε) closures in NFAs
- BFS for reachable state discovery
- State transitions by input symbols
- Memory management in C++
