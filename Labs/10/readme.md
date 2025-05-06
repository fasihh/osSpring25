## Code Workout 1
### (a)
![image](https://github.com/user-attachments/assets/510fa167-0863-420c-80df-ee538136b406)
### (b)
In the original bounded buffer problem, the semaphores replace the indefinite waiting performed by the while loops to check for free slots (for producer) and not-free slots (for consumer).
<br>
When entering producer, the empty semaphore is decremented by `sem_wait()` and after writing to the buffer, full semaphore is incremented using `sem_post()`.
<br>
When entering consumer, the full semaphore is decremented by `sem_wait()` and after consuming the buffer value, empty semaphore is incremented using `sem_post()`.
### (c)
It prevents the threads from running without any delays. If not done, then both threads will try running back-to-back which might lead to less chances of other thread doing anything.
<br>
Besides, It's a better representation of real world scenarios as in them, there will mostly always be some delay after the critical section for data processing/handling.
## Code Workout 2
### (a)
![image](https://github.com/user-attachments/assets/a2fdcad4-c77f-40bb-a017-f5db5015beba)
### (b)
![image](https://github.com/user-attachments/assets/b6c0835e-65bd-4c82-a910-2520c4cd64d6)
### (c)
### (d)
#### (i)
This is ensured by the `readers_count` variable, as it checks if one reader is reading, then all other readers will keep on reading until the count reaches 0 again.
<br>
At that point, the `rw_mutex` is unlocked and the writers are given the chance to write again.
#### (ii)
This is ensured by the `rw_mutex` which decrements whenever a reader/writer gains access. This way, if a writer wants to gain access, the readers will pause under the `readers_count` if-condition,
and the writer will be able to write.
### (e)
