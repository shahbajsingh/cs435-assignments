import random
import time

# LONGEST COMMON SUBSEQUENCE (LCS)

# A strand of DNA is a sequence of nucleotides, where each nucleotide is represented by a letter: A, C, G, or T
# One reason to compare two strands of DNA is to determine how 'similar' two strands are (e.g. to measure how closely related two organisms are)
# We can measure the similarity of strands S1 and S2 by finding a third strand S3 in which the bases in S3 appear in each of S1 and S2, in the same order,
# but not necessarily consecutively

# THE RECURSIVE APPROACH (TOP-DOWN)

# Let L(X, Y) be the length of the longest common subsequence of sequences X and Y, where X and Y are sequences of length m and n, respectively,
# that is, L(X, Y) = L(X[0...m-1], Y[0...n-1]); we employ the use of substructures X[0...m-2] and Y[0...n-2] to solve the problem of L(X, Y)

# Say we are comparing two sequences X and Y, where X = "ATATCG" and Y = "TACGAT", we can construct a recursion tree to find the longest common subsequence
#                                      L("ATATCG", "TACGAT")
#                                   /                        \
#               L("ATATC", "TACGAT")                          L("ATATCG", "TACGA")
#                   /             \                             /              \
#      L("ATAT", "TACGAT")   L("ATATC", "TACGA")      L("ATATC", "TACGA")    L("ATATCG", "TACG")

# The recursive approach is inefficient because it recomputes the same subproblems multiple times, leading to an exponential number of recursive calls;
# this could be improved by using dynamic programming to store the results of subproblems in a table, and then using these results to solve larger subproblems
# which would constitute the 'top-down' approach

# THE TABULAR APPROACH (BOTTOM-UP)

# The following procedure takes sequences X and Y as inputs, as well as their lengths, m and n, respectively, and returns the length of the longest common
# subsequence of X and Y; it stores the c[i,j] values in a table c[0:m, 0:n] and computes the entries in row-major order, i.e. the procedure fills 
# first row of c left-to-right, then the second row, and so on

# This approach also maintains the table b[1:m, 1:n] to help construct an optimal solution, where b[i,j] points to the table entry corresponding 
# to the optimal subproblem solution chosen when computing c[i,j]

# The procedure returns the tables b and c, where c[m,n] contains the length of an LCS of X and Y; the runtime of the procedure is Θ(mn), 
# as each table entry takes Θ(1) time to compute
'''
LCS_LENGTH(X, Y, m, n)

1. let b[1:m, 1:n] and c[0:m, 0:n] be new tables

2. for i = 1 to m
3.     c[i,0] = 0

4. for j = 0 to n
5.     c[0,j] = 0

6. for i = 1 to m
7.     for j = 1 to n
8.         if X[i] == Y[j]
9.             c[i,j] = c[i-1,j-1] + 1
10.            b[i,j] = "↖"

11.        else if c[i-1,j] >= c[i,j-1]
12.            c[i,j] = c[i-1,j]
13.            b[i,j] = "↑"

14.        else
15.            c[i,j] = c[i,j-1]
16.            b[i,j] = "←"

17. return b and c

PRINT_LCS(b, X, i, j)

1. if i == 0 or j == 0
2.     return # LCS is empty

3. if b[i,j] == "↖"
4.     PRINT_LCS(b, X, i-1, j-1)
5.     print X[i] # same as Y[j]

6. else if b[i,j] == "↑"
7.     PRINT_LCS(b, X, i-1, j)

8. else
9.     PRINT_LCS(b, X, i, j-1)
''' 

def longest_common_subsequence(X, Y, m, n):
    # let b[1:m, 1:n] and c[0:m, 0:n] be new tables
    b = [[0 for _ in range(n)] for _ in range(m)]
    c = [[0 for _ in range(n+1)] for _ in range(m+1)]

    # for i = 1 to m
    #     c[i,0] = 0
    for i in range(m+1):
        c[i][0] = 0

    # for j = 0 to n
    #     c[0,j] = 0
    for j in range(n+1):
        c[0][j] = 0

    # for i = 1 to m
    #     for j = 1 to n
    #         if X[i] == Y[j]
    #             c[i,j] = c[i-1,j-1] + 1
    #             b[i,j] = "↖"
    #         else if c[i-1,j] >= c[i,j-1]
    #             c[i,j] = c[i-1,j]
    #             b[i,j] = "↑"
    #         else
    #             c[i,j] = c[i,j-1]
    #             b[i,j] = "←"
        
    for i in range(1, m+1):
        for j in range(1, n+1):
            if X[i-1] == Y[j-1]:
                c[i][j] = c[i-1][j-1] + 1
                b[i-1][j-1] = "↖"
            elif c[i-1][j] >= c[i][j-1]:
                c[i][j] = c[i-1][j]
                b[i-1][j-1] = "↑"
            else:
                c[i][j] = c[i][j-1]
                b[i-1][j-1] = "←"

    # print_lcs(b, X, m, n)
    # print()
    return b, c

def print_lcs(b, X, i, j):
    # if i == 0 or j == 0
    #     return # LCS is empty
    if i == 0 or j == 0:
        return

    # if b[i,j] == "↖"
    #     PRINT_LCS(b, X, i-1, j-1)
    #     print X[i] # same as Y[j]
    if b[i-1][j-1] == "↖":
        print_lcs(b, X, i-1, j-1)
        print(X[i-1], end="")

    # else if b[i,j] == "↑"
    #     PRINT_LCS(b, X, i-1, j)
    elif b[i-1][j-1] == "↑":
        print_lcs(b, X, i-1, j)

    # else
    #     PRINT_LCS(b, X, i, j-1)
    else:
        print_lcs(b, X, i, j-1)

# Now that we have developed the LCS algorithm, we can improve on time complexity by eliminating the need for the b table, as 
# each c[i,j] entry depends on only three other c table entries: c[i-1,j-1], c[i-1,j], and c[i,j-1]; given the value of c[i,j], we can determine
# which of these three entries was used to compute c[i,j] in O(1) time without inspecting the b table
        
# We therefore reconstruct an LCS in O(m+n) time by using a procedure similar to PRINT_LCS, but without the b table
        
def longest_common_subsequence_optimized(X, Y, m, n):
    c = [[0 for _ in range(n+1)] for _ in range(m+1)]

    # fill c table
    for i in range(1, m+1):
        for j in range(1, n+1):
            if X[i-1] == Y[j-1]:
                c[i][j] = c[i-1][j-1] + 1
            elif c[i-1][j] >= c[i][j-1]:
                c[i][j] = c[i-1][j]
            else:
                c[i][j] = c[i][j-1]

    # reconstruct LCS
    lcs= ""
    i, j = m, n

    while i > 0 and j > 0:
        if X[i-1] == Y[j-1]:
            lcs = X[i-1] + lcs
            i -= 1
            j -= 1
        elif c[i-1][j] >= c[i][j-1]:
            i -= 1
        else:
            j -= 1

    # print(lcs)
    return c, lcs

def main():
    
    m = int(input("Enter the length of the first sequence: "))
    n = int(input("Enter the length of the second sequence: "))

    if m < 50 or n < 50:
        raise ValueError("ERROR: Length of sequences must be at least 50.")

    # random 50 char sequence of A, C, G, T
    seq1 = ''.join(random.choices("ACGT", k=m))
    seq2 = ''.join(random.choices("ACGT", k=n))
    
    print(f"Sequence 1: {seq1}\t\tlen: {len(seq1)}")
    print(f"Sequence 2: {seq2}\t\tlen: {len(seq2)}")
    print(f"Longest Common Subsequence: {longest_common_subsequence_optimized(seq1, seq2, len(seq1), len(seq2))[1]}\t\tlen: {len(longest_common_subsequence_optimized(seq1, seq2, len(seq1), len(seq2))[1])}")
    print()
    
    # time the LCS algorithms 10 times and print the average time
    total_time = 0
    for _ in range(10):
        start = time.time()
        longest_common_subsequence(seq1, seq2, len(seq1), len(seq2))
        end = time.time()
        total_time += end - start

    print('AVERAGE OF 10 RUNS')
    print(f"Average time for LCS: {total_time / 10:.10f} seconds")

    total_time = 0
    for _ in range(10):
        start = time.time()
        longest_common_subsequence_optimized(seq1, seq2, len(seq1), len(seq2))
        end = time.time()
        total_time += end - start

    print(f"Average time for optimized LCS: {total_time / 10:.10f} seconds")

    print()
    m = int(input("Enter the length of the first sequence: "))
    n = int(input("Enter the length of the second sequence: "))

    if m < 50 or n < 50:
        raise ValueError("ERROR: Length of sequences must be at least 50.")

    # random 50 char sequence of A, C, G, T
    seq1 = ''.join(random.choices("ACGT", k=m))
    seq2 = ''.join(random.choices("ACGT", k=n))

    print(f"Sequence 1: {seq1}\t\tlen: {len(seq1)}")
    print(f"Sequence 2: {seq2}\t\tlen: {len(seq2)}")
    print(f"Longest Common Subsequence: {longest_common_subsequence_optimized(seq1, seq2, len(seq1), len(seq2))[1]}\t\tlen: {len(longest_common_subsequence_optimized(seq1, seq2, len(seq1), len(seq2))[1])}")
    print()

    total_time = 0
    for _ in range(100):
        start = time.time()
        longest_common_subsequence(seq1, seq2, len(seq1), len(seq2))
        end = time.time()
        total_time += end - start

    print('\nAVERAGE OF 100 RUNS')
    print(f"Average time for LCS: {total_time / 100:.10f} seconds")

    total_time = 0
    for _ in range(100):
        start = time.time()
        longest_common_subsequence_optimized(seq1, seq2, len(seq1), len(seq2))
        end = time.time()
        total_time += end - start

    print(f"Average time for optimized LCS: {total_time / 100:.10f} seconds")

    print()
    m = int(input("Enter the length of the first sequence: "))
    n = int(input("Enter the length of the second sequence: "))

    if m < 50 or n < 50:
        raise ValueError("ERROR: Length of sequences must be at least 50.")

    # random 50 char sequence of A, C, G, T
    seq1 = ''.join(random.choices("ACGT", k=m))
    seq2 = ''.join(random.choices("ACGT", k=n))

    print(f"Sequence 1: {seq1}\t\tlen: {len(seq1)}")
    print(f"Sequence 2: {seq2}\t\tlen: {len(seq2)}")
    print(f"Longest Common Subsequence: {longest_common_subsequence_optimized(seq1, seq2, len(seq1), len(seq2))[1]}\t\tlen: {len(longest_common_subsequence_optimized(seq1, seq2, len(seq1), len(seq2))[1])}")
    print()

    total_time = 0
    for _ in range(1000):
        start = time.time()
        longest_common_subsequence(seq1, seq2, len(seq1), len(seq2))
        end = time.time()
        total_time += end - start

    print('\nAVERAGE OF 1000 RUNS')
    print(f"Average time for LCS: {total_time / 1000:.10f} seconds")

    total_time = 0
    for _ in range(1000):
        start = time.time()
        longest_common_subsequence_optimized(seq1, seq2, len(seq1), len(seq2))
        end = time.time()
        total_time += end - start

    print(f"Average time for optimized LCS: {total_time / 1000:.10f} seconds")


if __name__ == "__main__":
    main()