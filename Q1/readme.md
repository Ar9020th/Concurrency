Question 1:Concurrent Merge Sort

Merge sort is implemented with two ways, recursive splitting and normal merge sort. Now if the value of method is 0 then it undergoes recursive splitting else it undergoes normal merge sort.
Two arrays are created, arr1 and arr
arr1 is normally allocated array on which normal merge sort is performed whereas arr is a shared memory segment 
Observation

For n < 1000, normal merge sort is faster than concurrent mergesort but significant improvement is observed for n nearing 1e4 and 1e5.

Sample outputs:

n=10
Normal Mergesort: 
Time Taken by Normal Mergesort is is 0.00000296 seconds
Mergesort by Recursive Splitting: 
Time Taken by Recursive splitting into child processes is 0.00038002 seconds
Ratio of Concurrent to Normal: 128.3

n=100
Normal Mergesort: 
Time Taken by Normal Mergesort is is 0.00001943 seconds
Mergesort by Recursive Splitting: 
Time Taken by Recursive splitting into child processes is 0.00319376 seconds
Ratio of Concurrent to Normal: 164.3

n=500
Normal Mergesort: 
Time Taken by Normal Mergesort is is 0.00002968 seconds
Mergesort by Recursive Splitting: 
Time Taken by Recursive splitting into child processes is 0.00804884 seconds
Ratio of Concurrent to Normal: 271.1

n=2000
Normal Mergesort: 
Time Taken by Normal Mergesort is is 0.00013637 seconds
Mergesort by Recursive Splitting: 
Time Taken by Recursive splitting into child processes is 0.02746730 seconds
Ratio of Concurrent to Normal: 201.4

n=10000
Normal Mergesort: 
Time Taken by Normal Mergesort is is 0.00072865 seconds
Mergesort by Recursive Splitting: 
Time Taken by Recursive splitting into child processes is 0.14841785 seconds
Ratio of Concurrent to Normal: 203.7

n=1e5
Normal Mergesort: 
Time Taken by Normal Mergesort is is 0.00970437 seconds
Mergesort by Recursive Splitting: 
Time Taken by Recursive splitting into child processes is 2.42705173 seconds
Ratio of Concurrent to Normal: 250.1