Question 2:Back to College
At the initial stage I have Created the following structs:-
1) pcomp:- consisting of pharmaceutical company's name, pharmaceutical company's waiting time(w),batches(r),probablity of curing(x) and number of vaccines in each batch prepared at a time(p).
2) vzone:- consisting of vaccination zone's name,number of vaccines left(k),number of slots,mutex and probablity of vaccine(whether it works) in percentage.
3) student:- consisting of student's name,whether he is vaccinated or not(isvaccinated) and number of tries (tries).

After the declaration of structs, I have created an array of structs. This will store the information of n pharmaceutical companies, m vaccination zones and o students.

After taking the inputs, I have created m threads of companies, n threads of vaccination zones and o threads of students and are redirected to func,func2,func3 respectively.

In func:-
Each phamaceutical company creates the vaccine batches within a stipulated amount of time, and their production stops when the vaccine batches have totally exhausted. 

In func2:-
Each struct vzone has a double pointer to s_cmp which contains the pointer to structs of all companies, through which iteratively the availability of batches is checked and the first company which has available batches is selected and one batch is taken from it.

In func3:-
The student Arrives at the college and gets ready to be vaccinated. Now in this process two cases may arise:- First being the case when the vaccine is successfully administered. In that case the student rejoins the college and the thread exists. Second case is when the vaccine fails to develop antibodies in the student, In that case, the student is again sent to a vaccination zone for vaccination.

Now after three tries, if the student still fails to develop antibodies he will be sent back home and the thread will exit then and there.

Now after all the threads have been executed, Simulation gets finished.