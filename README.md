Starve free readers writers solution

Pseudocode:

Writer:
 
1 wait(in)
2 wait(mx)
3 c=c+1
4 if c==1, wait(wrt)
5 signal(mx)
6 signal(in)

Critical Section

7 wait(mx)
8 c=c-1
9 if c==0, signal(wrt)
10 signal(mx)

Reader:

1 wait(in)
2 wait(wrt)

Critical Section

3 signal(wrt)
4 signal(in)

Initial values:

Semaphores in, wrt and mx are initialised as 1.
Integer identifier c is initialised as 0.

Explanation of pseudocode:

Here, the semaphores wrt and mx are used to implement mutual exclusion of the reader and the writer. When control enters the reader’s critical section, then the value of semaphores is wrt=0, in=1, mx=1. So, the writer block is not run. And when the control enters the writer's critical section, the value of semaphores is wrt = 0, in = 0, mx = 0. So, the reader’s block is not run.

A more detailed account of the control flow, assuming we first enter the reader’s block can be described as follows:
1 in=0, this ensures that control would not go into the writer’s block
2 mx=0
3 c=1
4 Since c=1, wrt=0. This implies that now the control won’t be able to go into the critical section of the writer’s block, due to the wait command in line 2 of the writer's block. If c was not equal to 1, then the control would simply move onto line 5 as the writer’s block is already blocked so there’s no need to put it on hold again and again.
5 mx=1
6 in=1 this would let the control in writer’s block go to line 2, due to line 1 being wait(in)
7 mx=0, this would prevent the control to enter the reader’s block again
8 If c=0, then wrt=1 the control would flow to the writer’s block as wait(wrt) wouldn’t block the writer block’s critical section and the writer’s block would get executed. And if c is not equal to 0, then the reader’s block would be run again.
9 If c is not equal to 0, then mx = 1 and the reader block gets run again and so on.

Now, let’s assume the writer’s block gets executed first:
1 in=0, this would prevent the control from going into reader’s block
2 wrt=0
3 wrt=1
4 in=1, this would pass on the control to the reader’s block and the execution would follow the same pattern as specified above.

Here c is the number of readers currently reading the file. The semaphores wrt and mx are used to enforce mutual exclusion, whereas the semaphore in is used to ensure that the writer is not starved. It ensures that even if a writer comes in between a stream of readers, it would get a chance to run. The semaphore in provides an outer layer of prevention over the semaphores wrt and mx to provide starve free solution.
