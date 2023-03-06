#include <bits/stdc++.h>
using namespace std;

//the blocked queue stores the process id of those processes which are blocked
queue<int> blocked_queue;
//the ready queue stores the process id of those processes which are run
queue<int> ready_queue;

void stuff(){
    //to initialise the ready queue with some dummy values
    ready_queue.push(1);
    ready_queue.push(2);
    ready_queue.push(3);
    ready_queue.push(4);
    ready_queue.push(5);
    ready_queue.push(6);
    ready_queue.push(7);
    ready_queue.push(8);
    ready_queue.push(9);
    ready_queue.push(10);
}

struct Semaphore{
    int val = 1;
    Semaphore(int n){
        val = n;
    }
};

void wakeUp(int pid){
    //to wake up the process with the process id pid
    ready_queue.push(pid);
}

void signal(Semaphore *s){
    //signal function, wakes up one process from the blocked queue
    s->val = s->val +1;
    if(s->val<=0){
        if(!blocked_queue.empty()){
            wakeUp(blocked_queue.pop());
        }
    }
}

void wait(Semaphore *s, int p){
    //puts processes in blocked queue depending on the value of semaphore
    s->val = s->val -1;
    if(s->val<0){
        blocked_queue.push(p);
    }
}

Semaphore* wrt = new Semaphore(1);
Semaphore* in = new Semaphore(1);
Semaphore* mx = new Semaphore(1);
int c = 0;

void reader(int p){
    wait(in, p);
    wait(mx, p);
    c++;
    if(c==1){
        wait(wrt, p);
    }
    signal(mx);
    signal(in);
    //critical section, i.e. the part where reading happens
    //read
    c--;
    if(c==0){
        signal(wrt);
    }
    signal(mx);
}

void starvefreereader(){
    do{
        int pid = 0;
        if(!ready_queue.empty()){
            pid = ready_queue.pop();
        }
        reader(pid);
    }while(true);
}

void writer(int p){
    wait(in, p);
    wait(wrt, p);
    //critical section, i.e the part where writing happens
    signal(wrt);
    signal(in);
}

void starvefreewriter(){
    do{
        int pid=0;
        if(!ready_queue.empty()){
            pid = ready_queue.pop();
        }
        writer(pid);
    }while(true);
}

