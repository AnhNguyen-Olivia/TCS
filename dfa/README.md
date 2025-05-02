# DFA String Acceptance Checker

A C++ program that simulates a **Deterministic Finite Automaton (DFA)**. It allows users to define a DFA, test strings for acceptance, generate Graphviz visualizations, and more — all from the command line with colored output and a clear menu interface.

## 🛠 Features

- Single string and batch string testing
- Step-by-step execution with trace logs
- Transition table viewer
- Graphviz code generation for DFA visualization
- Detailed DFA setup and validation
- Color-coded terminal output (UNIX terminals)

## 🧪 How to Use

### 1. Compile

Make sure you have a C++ compiler like `g++`:

```bash
g++ dfa.cpp -o dfa
```

### 2. Run

```bash
./dfa
```

## 🧭 DFA Setup Flow

Follow the prompts:

1. **Enter number of states and symbols**  
   Example: `3` states, `2` symbols → inputs: `3`, `2`

2. **Enter symbols (e.g., a b)**  
   Example: `a b`

3. **Enter the start state index**  
   Example: `0`

4. **Enter number and list of final states**  
   Example: `1`, then `2`

5. **Enter transition table**  
   Input transitions in the format `δ(qi, a) = qj` for all states and symbols.

   Example for 3 states and 2 symbols:

   δ(q0, a) = 1
   δ(q0, b) = 0
   δ(q1, a) = 2
   δ(q1, b) = 1
   δ(q2, a) = 2
   δ(q2, b) = 2

## 📋 Menu Options

Once the DFA is set up:

========== DFA Simulator Menu ==========

1. Test a single string
2. Batch test multiple strings
3. Display transition table
4. Generate DFA visualization code
5. Step-by-step execution mode
6. Display DFA information
7. Exit

=======================================

## 🎯 Example Input & Output

**Sample DFA:** Accepts strings with even number of a's.

States: 0, 1
Symbols: a b
Start state: 0
Final states: 0

**Transition Table:**
δ(q0, a) = 1
δ(q0, b) = 0
δ(q1, a) = 0
δ(q1, b) = 1

**Test Input:**
abaa

**Output:**
Accepted

## 📈 DFA Graph Visualization

Option 4 outputs Graphviz code like:

```dot
digraph G {
  rankdir=LR;
  node [shape = point]; start;
  node [shape = doublecircle]; q0;
  node [shape = circle];
  start -> q0;
  q0 -> q1 [label="a"];
  q0 -> q0 [label="b"];
  ...
}
```

Use it on: [Graphviz Online](https://dreampuf.github.io/GraphvizOnline/)

---

## ⚠️ Notes & Tips

- Symbols not in the DFA's alphabet will be rejected.
- Invalid transitions (e.g., to non-existent states) are flagged immediately.
- Step-by-step trace shows detailed transition paths.
- Use a terminal that supports ANSI colors for best output.

🧠 **Tip**: Design your DFA on paper first to avoid confusion when inputting transitions.

## 📄 License

This project is for educational use. No license is currently applied.
