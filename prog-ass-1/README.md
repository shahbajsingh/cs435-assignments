_Problem Statement:_

Implement and compare the performance of various sorting algorithms based on their execution time. The sorting algorithms to be compared are:

* Insertion Sort
* Selection Sort (refer to problem 2.2-2)
* Merge Sort
* Bubble Sort (refer to section 2-2)
* Quick Sort

You can use recursive functions for the implementation.

_Input:_

* Type: Integers
* Test input sizes: n = 10, 100, 1000, 1M (1 million)
* Test input sequences:
* Increasing order
* Decreasing order
* Random order

_Submission Guidelines:_

1. Submission Format: Submit a zip file containing your source codes, a README
file with instructions, and a brief report on your findings.

2. Programming Language: Choose your preferred programming language (e.g.,
Python, C++, Java).

3. Code Clarity: Ensure that your code is well-documented providing clear
comments to enhance readability and easy to understand.

4. Execution Time Measurement: Include a mechanism to measure and report the
execution time of each sorting algorithm.

5. README File:

a. Provide clear instructions on how to compile and run your code from
terminal

b. Mention any external libraries or dependencies used.

c. Report bug (if any)

d. Briefly report on your findings about the algorithms

e. Any other information you might think is relevant.

6. Performance Analysis:

a. Include a brief report (preferably in README file) comparing the
performance of each sorting algorithm for different input sizes and
sequences.

7. Deadline: The submission deadline is Feb 10, 2024. Late submissions will incur
a penalty as follows:

a. You lose 50% of points for missing the deadline

b. You lose 100% of points if you submit after 3 or more days from the
deadline.

_Grading Criteria:_

* Correctness of sorting algorithms implementation
* Clarity and readability of code
* Accuracy and completeness of the performance analysis report
* Adherence to submission guidelines and deadlines

___

Shahbaj Singh
CS 435 Section 102
Professor Nahata

## <ins> Programming Assignment 01 </ins>

### Sorting Algorithm Performance Comparison

&nbsp;
&nbsp;

###### Running the Program

The majority of my implementation of the pertinent sorting algorithms– insertion sort, selection sort, merge sort, bubble sort, and quick sort– are written in an interactive python notebook with <code>.ipynb</code> file extension.

The implementation of these sorting algorithms is written in Python and the output of their test execution (on my system) is all displayed within the notebook, in the file [comparing_sorting_algorithms.ipynb](/prog-ass-1/comparing_sorting_algorithms.ipynb).

###### Bugs

Writing in Python, however, to an extent restricted my ability to thoroughly test each of these sorting algorithms; I ran into problems in testing these algorithms against arrays of sizes greater than 1M (1 million) in each and every case, and of arrays of sizes greater than 10 000 in the case of quick sort.

To work around this, I decided to rewrite the algorithms in C++.

###### Analysis
