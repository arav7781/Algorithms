# Algorithms

Implementations from the Stanford Algorithms specialization (divide and conquer, graph search), mostly in C.

| Topic | Files |
| --- | --- |
| Divide and conquer | `Karatsuba algorithm.c`, `LargeNOMULTIPLICATION.py`, `StrassensALGO.c`, `MatrixMulUSINGrecur.c`, `ClosestPair.c` |
| Counting inversions | `InversionCountUDINGFILE.c`, `findINVERSIONSDIV&CON.cpp` |
| Quicksort pivots | first, last and median-of-three element as pivot |
| Selection | randomized selection, deterministic (median of medians) selection, `LOGtournamentprob.c` |
| Graphs | Karger's randomized min cut (C and C++) |
| Dynamic programming | sequence alignment (DNA), brute-force longest substring for comparison |

`nb/` holds a notebook fine-tuning Qwen2.5-3B with GRPO.

Build: `gcc file.c -o out && ./out` (C++: `g++`).
