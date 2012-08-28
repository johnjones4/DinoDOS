#define MAIN
#include "proc.h"

/*
 * This function initializes all of the global variables and structures defined 
 * above. All entries in the memory map should be marked as FREE. All of the 
 * PCBs in the pcbPool should have the first character of their names set to 
 * null, their state set to DEFUNCT and their segment and stack pointers set to 
 * 0x0000. The PCB for the idle process should be initialized with the name 
 * IDLE, the state READY, and both the segment and stack pointers set to 0x0000.  
 * running should refer to the PCB for the idle process and the ready queue
 * should be empty.
 */  
void initializeProcStructures()
{
	int i;
	//set the memoryMap to FREE and initialize all PCBs in the pool
	for(i=0; i<8; i++) {
		//memory map
		memoryMap[i] = FREE;
		//pcb
		pcbPool[i].name[0] = NULL;
		pcbPool[i].state = DEFUNCT;
		pcbPool[i].segment = 0x0000;
		pcbPool[i].stackPointer = 0x0000;
		//initialize the sleep counter and priority
		pcbPool[i].sleepCount = 0;
		pcbPool[i].priority = 0;
	}
	//initially we are waiting for nothing to finish (full multiprogramming)
	wait_segment = 0;
	//setup the idle process' name
	idleProc.name[0] = 'I';
	idleProc.name[1] = 'D';
	idleProc.name[2] = 'L';
	idleProc.name[3] = 'E';
	idleProc.name[4] =  NULL;
	//initialize the idle process
	idleProc.state = READY;
	idleProc.segment = 0x0000;
	idleProc.stackPointer = 0x0000;
	idleProc.sleepCount = 0;
	idleProc.priority = 0;
	
	//point running to the idle process
	running = &idleProc;
	
	//initialize the ready head and tail pointers
	readyHead = NULL;
	readyTail = NULL;
}

/*
 * Returns the index of the first free memory segment or -1 if all of the memory
 * segments are used.
 */
int getFreeMemorySegment()
{
	int i;
	//look for a free spot
	for(i=0; i<8; i++) {
		if(memoryMap[i] == FREE) {
			//set this as used
			memoryMap[i] = USED;
			//convert to memory segment
			return (i*0x1000)+0x2000;
		}
	}
	//never found a free segment
	return NO_FREE_SEGMENTS;
}

/*
 * Release the indicated memory segment.
 */
void releaseMemorySegment(int seg)
{
	//convert back to an index
	int index = (seg - 0x2000) / 0x1000;
	memoryMap[index] = FREE;
}

/*
 * Return a pointer to an available PCB from the PCB pool.  All of the available 
 * PCBs should be marked as DEFUNCT.  Return NULL if there are no PCBs 
 * available.
 */
struct PCB *getFreePCB()
{
	int i;
	//look for a free spot (DEFUNCT)
	for(i=0; i<8; i++) {
		if(pcbPool[i].state == DEFUNCT) {
			//return a pointer to it
			return &pcbPool[i];
		}
	}
	//never found a DEFUNCT pcb
	return NULL;
}

/*
 * Release the provided PCB by setting its state to DEFUNCT, setting its next 
 * and prev pointers to NULL and setting the first character of its name to 
 * 0x00.
 */
void releasePCB(struct PCB *pcb)
{
	//set its state
	pcb->state = DEFUNCT;
	//reset its next and previous pointers
	pcb->next = NULL;
	pcb->prev = NULL;
	//'clear' its name
	pcb->name[0] = 0x00;
	//reset its sleep and priorities
	pcb->sleepCount = 0;
	pcb->priority = 0;
}

/*
 * Add the provided PCB to the tail of the ready queue. This will be based on
 * the priority of 'pcb'.
 */
void addToReady(struct PCB *pcb)
{
	//if the head is NULL, set both to pcb
	if (readyHead == NULL) {
		readyHead = pcb;
		readyTail = pcb;
	} else {
		//find where to place the PCB
		struct PCB *cur = readyHead;
		while(cur != NULL && pcb->priority <= cur->priority) {
			cur = cur->next;
		}
		//find what broke the loop and place the PCB
		if(cur == NULL) {
			//place at the end of the queue
			//set the prev and next pointers
			pcb->prev = readyTail;
			readyTail->next = pcb;
			//add to the end
			readyTail = pcb;
			readyTail->next = NULL;
		} else if(cur == readyHead) {
			//place it at the start
			pcb->next = readyHead;
			pcb->prev = NULL;
			readyHead->prev = pcb;
			readyHead = pcb;
		} else {
			//insert into its place
			pcb->next = cur;
			pcb->prev = cur->prev;
			pcb->prev->next = pcb;
			cur->prev = pcb;
		}

	}
}

/*
 * Remove the PCB at the head of the ready queue and return a pointer to it.
 */
struct PCB *removeFromReady()
{
	//check to make sure it is not empty or its not the same as the tail
	if (readyHead == NULL) {
		return NULL;
	} else {
		//what is to be returned
		struct PCB *tmp = readyHead;
		//set the head to what was next (if there is a next)
		if(readyHead->next != NULL) {
			readyHead = tmp->next;
			//clear the pointer to prev
			readyHead->prev = NULL;
		} else {
			//set readyHead and readyTail to null (list is empty)
			readyHead = NULL;
			readyTail = NULL;
		}
		//clear the pointers to next and prev
		tmp->prev = NULL;
		tmp->next = NULL;
		return tmp;
	}
}

/*
 * Get the highest priority out of all PCBs not including the shell.
 */
int highestCurPriority()
{
	int i,max = 0; //the shell should to 0, so this is a valid start
	for(i=0; i<8; i++) {
		if(&pcbPool[i] != shellPtr && pcbPool[i].priority > max) {
			max = pcbPool[i].priority;
		}
	}
	return max;
}
