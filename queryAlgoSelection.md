There is a trick to select which query algorithm shoul be used in a giver question

`invertible` means, the function whose inverse function exists. Such as for summation, subtraction is the inverse function. But for max or min, these
exists no inverse function.

||invertible|non-invertible|
|------|--------|-------|
|update not given(offline)|prefix sum | sparse table
|updates given(online)|fenwick tree|segment tree|
