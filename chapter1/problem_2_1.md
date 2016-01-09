* Show that insertion sort can sort the n/k sublists, each of length k, in O(nk) 
worst-case time.

- insertion sort T(k) = ak^2 + bk + c, we have n/k sublists, so result:
O(akn + bn + c/k) = O(nk)

* Show how to merge the sublists in O(nlg(n/k)) worst-case time.

- Suppose we a sublists of lenght k, so we have for each seq

T(k) = 2T(k/2) + ck if k > 1 or c if k = 1

- 






