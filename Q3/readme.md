Question 3:Musical Mayhem

At the initial stage I have Created the following structs:-
1) performer:- consisting of performer's name, performer's instrument id and performer's arrival time in the event.
2) acous array:-It is an array(total number of accoustic stages) of struct acous(consisting of name,semaphore and a previous character which is initialised to character '0' at the beginning of the thread execution).
3) elec array:-It is an array(total number of electric stages) of struct ele(consisting of name,semaphore and a previous character which is initialised to character '0' at the beginning of the thread execution).
4) coordinators array:- It is an array( of total number of coordinators) of struct coordinator(consisting of a variable available denoting that a counter is available or not and a mutex lock,1 stands for available and 0 for non availabilty of the coordinator).
After taking the inputs, I am initialising the semaphores and the mutexes. After that I create a thread of all the performers which are directed to the function allott.

The Allott Function:-
In this function,My performers would have arrived after sleeping for a certain period of time and then will be ready to perform on any one of the stages. Now two cases arise:-
Case 1) Performer is a musician:-
In this case, I am checking which musician is allowed to perform in what type of stage i.e. Accoustic or electrical. After checking the required case, the performer is set on a loop which checks the availabililty of a particular type of stage. In the case of musicians and guitarists, since they can perform on both accoustic and electric stage, they are required to choose which stage do they want to perform(this is implemented by a random generator which generates either 1 or 2. 1 is for accoustic and 2 is for electrical). According to their priority
we search for a random stage. Now after they have performed, they are required to collect the t-shirts from the co-ordinators. For that the collectTshirt function handles the situation. After the musician has performed and has collected the tshirt my thread exits and a signal is sent to the semaphore of a particular stage idicating that the stage is now set free for the next performer to perform. 
Case 2) Performer is a singer:-
In this case, I am checking whether the singer chooses to perform solo or in pair(with a musician). Accordingly, we set the priority of the singer according to the random value(1 for pair , 2 for solo). According to their choice we search a stage and if the stage is free or occupied by a musician, the singer is sent to that stage to perform. After the singer's performance has finished, the thread exits.

Now if the performer in their repective threads do not get a stage available, then the loop is again repeated and the codition is again checked.
Suppose the waiting time of a performer exceeds t, then the performer exits the infinite loop and a message gets printed on the screen which says that the performer left because of impatience.
After all the threads have been executed, In the end I join all the threads and the process gets finished which is denoted by a message on the screen saying 'Finished'.
