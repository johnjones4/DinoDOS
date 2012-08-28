/*
 *  testproc.c
 *  
 *
 *  Created by Grant Braught on 4/1/10.
 *  Copyright 2010 Dickinson College. All rights reserved.
 *
 */

#define MAIN

#include "stdio.h"
#include "assert.h"
#include <string.h>
#include "proc.h"

void testInit() {	
	initializeProcStructures();
	
	assert(running == &idleProc);
	assert(readyHead == NULL);
	assert(readyTail == NULL);
	int i=0;
	for (i=0; i<8; i++) {
		assert(memoryMap[i] == FREE);
		assert(pcbPool[i].name[0] == 0x00);
		assert(pcbPool[i].state == DEFUNCT);
		assert(pcbPool[i].segment == 0x00);
		assert(pcbPool[i].stackPointer == 0x00);
		assert(pcbPool[i].sleepCount == 0);
		assert(pcbPool[i].priority == 0);
	}
	
	assert(strcmp(idleProc.name, "IDLE\0") == 0);
	assert(idleProc.segment == 0x0000);
	assert(idleProc.stackPointer == 0x0000); 
	assert(idleProc.sleepCount == 0);
	assert(idleProc.priority == 0);
}

void testGetFreeMemorySegment()
{
	//reset
	initializeProcStructures();

	//set each as used and check next as we go
	int i, seg = 0x2000;
	for(i=0; i<8; i++) {
		//check our first free segment
		assert(getFreeMemorySegment() == seg);
		//increment our segment
		seg += 0x1000;
	}
	//all should be USED now
	assert(getFreeMemorySegment() == NO_FREE_SEGMENTS);
}

void testReleaseMemorySegment()
{
	//reset
	initializeProcStructures();

	//set all to used
	int i;
	for(i=0; i<8; i++) {
		memoryMap[i] = USED;
	}

	//assert all are used
	assert(getFreeMemorySegment() == NO_FREE_SEGMENTS);

	//go backwards releasing them
	int seg = 0x9000;
	for(i=7; i >= 0; i--) {
		//release it
		releaseMemorySegment(seg);
		//check that it is FREE
		assert(memoryMap[i] == FREE);
		//make sure it comes back as free
		assert(getFreeMemorySegment() == seg);
		//update segment
		seg -= 0x1000;
	}
}

void testGetFreePCB()
{
	//reset
	initializeProcStructures();

	//go through one by one marking as defunct as we go
	int i;
	for(i=0; i<8; i++) {
		//check that pcb 'i' was returned
		assert(getFreePCB() == &pcbPool[i]);
		//mark it as anything but DEFUNCT
		pcbPool[i].state = RUNNING;
	}
	//all should be RUNNING now
	assert(getFreePCB() == NULL);
}

void testReleasePCB()
{
	//reset
	initializeProcStructures();
	
	//set each PCB's name, state, and prev/next pointers to non-defualt
	int i;
	for(i=0; i<8; i++) {
		//mark it as anything but DEFUNCT
		pcbPool[i].state = RUNNING;
		//give it a name (no need to null terminate for test)
		pcbPool[i].name[0] = 'r';
		//set its pointers to itself
		pcbPool[i].next = &pcbPool[i];
		pcbPool[i].prev = &pcbPool[i];
	}
	//all should be RUNNING now
	assert(getFreePCB() == NULL);

	//go backwards freeing them and checking them
	for(i=7; i >= 0; i--) {
		//release it
		releasePCB(&pcbPool[i]);
		//check that it is DEFUNCT
		assert(pcbPool[i].state == DEFUNCT);
		//check its name
		assert(pcbPool[i].name[i] == '\0');
		//check its next/prev pointers
		assert(pcbPool[i].next == NULL);
		assert(pcbPool[i].prev == NULL);
		//make sure it comes back as free now
		assert(getFreePCB() == &pcbPool[i]);
	}
}

void testAddToReady()
{
	//reset
	initializeProcStructures();

	//add each to the ready queue
	int i,j;
	for(i=0; i<8; i++) {
		//add to the tail
		addToReady(&pcbPool[i]);
		//check that it is at the tail
		assert(readyTail == &pcbPool[i]);
		//check prev/next pointers
		if (i == 0) {
			//should be null for 0
			assert(readyTail->next == NULL);
			assert(readyTail->prev == NULL);
		} else {
			//prev should be i-1 in the pool
			assert(readyTail->prev == &pcbPool[i-1]);
			//next should always be null
			assert(readyTail->next == NULL);
		}
		//check that we can iterate through the queue
		struct PCB *tmp = readyHead; //start at the head
		for(j=0; j<i; j++) {
			assert(tmp == &pcbPool[j]);
			//go to the next
			tmp = tmp->next;
		}
		
		//should be at the end now
		assert(tmp == &pcbPool[j]);
	}
}

void testRemoveFromReady()
{
	//reset
	initializeProcStructures();

	//empty queue should return null
	assert(removeFromReady() == NULL);
	
	int i;
	//add all to ready
	for(i=0; i<8; i++) {
		addToReady(&pcbPool[i]);
	}

	//now pull each head off the queue
	for(i=0; i<8; i++) {
		assert(removeFromReady() == &pcbPool[i]);
		//check that the head now points to what was next
		if(i != 7) {
			assert(readyHead == &pcbPool[i+1]);
		} else {	
			//should be empty again
			assert(readyHead == NULL);
			assert(readyTail == NULL);
			assert(removeFromReady() == NULL);
		}
	}
}

void testRemoveFromReadyPriority()
{
	//reset
	initializeProcStructures();

	//empty queue should return null
	assert(removeFromReady() == NULL);
	
	int i;
	//add all to ready in a different order
	pcbPool[0].priority = 100;
	assert(highestCurPriority() == 100);
	pcbPool[1].priority = 12;
	assert(highestCurPriority() == 100);
	pcbPool[2].priority = 0;
	assert(highestCurPriority() == 100);
	pcbPool[3].priority = 0;
	assert(highestCurPriority() == 100);
	pcbPool[4].priority = -1;
	assert(highestCurPriority() == 100);
	pcbPool[5].priority = -256;
	assert(highestCurPriority() == 100);
	pcbPool[6].priority = 200;
	assert(highestCurPriority() == 200);
	pcbPool[7].priority = 0;
	assert(highestCurPriority() == 200);
	//add all to ready
	for(i=0; i<8; i++) {
		addToReady(&pcbPool[i]);
	}

	//now pull each head off the queue
	assert(removeFromReady() == &pcbPool[6]);
	assert(removeFromReady() == &pcbPool[0]);
	assert(removeFromReady() == &pcbPool[1]);
	assert(removeFromReady() == &pcbPool[2]);
	assert(removeFromReady() == &pcbPool[3]);
	assert(removeFromReady() == &pcbPool[7]);
	assert(removeFromReady() == &pcbPool[4]);
	assert(removeFromReady() == &pcbPool[5]);
	assert(removeFromReady() == NULL);
}

int main() {
	printf("Testing initializeProcStructures\n");
	testInit();
	printf("Testing getFreeMemorySegment\n");
	testGetFreeMemorySegment();
	printf("Testing releaseMemorySegment\n");
 	testReleaseMemorySegment();
	printf("Testing getFreePCB\n");
	testGetFreePCB();
	printf("Testing releasePCB\n");
	testReleasePCB();
	printf("Testing addToReady\n");
	testAddToReady();
	printf("Testing removeFromReady\n");
	testRemoveFromReady();
	printf("Testing removeFromReady with priority\n");
	testRemoveFromReadyPriority();
	printf("done\n");	
}
