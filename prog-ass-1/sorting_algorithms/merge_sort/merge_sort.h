#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <vector>

void merge(std::vector<int>& arr, int left, int mid, int right);
void merge_sort(std::vector<int>& arr, int left, int right);

#endif // MERGE_SORT_H