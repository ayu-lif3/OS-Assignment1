struct PCB{
    PCB *next;
    // All the other details of a process that a PCB contains
    .
    .
    .
    .
    .
}

struct Queue{

    ProcessControlBlock *front, *rear;

    Queue(){
        front = nullptr;
        rear = nullptr;
    }

    // Function that pushes a PCB at the rear end of the queue
    void push(int pID){
        ProcessControlBlock *pcb = new ProcessControlBlock();
        pcb->ID = pID;
        if(rear == nullptr){
            front = pcb;
            rear = pcb;
        }else{
            rear->next = pcb;
            rear = pcb;
        }
    }

    // Function that pops a PCB from the front end of the queue
    ProcessControlBlock *pop(){
        if(front == nullptr){
            return nullptr;
        }else{
            ProcessControlBlock *pcb = front;
            front = front->next;
            if(front == nullptr){
                rear = nullptr;
            }
            return pcb;
        }
    }

};


struct Semaphore{

    int semaphore = 1; // The actual value of the semaphore
    Semaphore(){
        semaphore = 1;
    }
    Semaphore(int s){
        semaphore = s;
    }

    // A queue to store the waiting processes
    Queue *FIFO = new Queue();

    // A function to implement the 'wait' functionality of a semaphore
    void wait(int pID){
        semaphore--;

        // If all resources are busy, push the process into the waiting queue and 'block' it
        if(semaphore < 0){
            FIFO->push(pID);
            ProcessControlBlock *pcb = FIFO->rear;
            block(pcb);
        }
    }

    // A function to implement the 'signal' functionality of a semaphore
    void signal(){
        semaphore++;

        // If there are any processes waiting for execution, pop from the waiting queue and wake the process up
        if(semaphore <= 0){
            ProcessControlBlock *pcb = FIFO->pop();
            wakeup(pcb);
        }
    }

};

