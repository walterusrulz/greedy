/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: walterus
 *
 * Created on March 16, 2019, 11:31 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define CAPACITY 4000//truck capacity, in KG
/*
 * Included function declarations:
 */
void mergeSort(unsigned long int *Arr, int start, int end);
void merge(unsigned long int *Arr, int start, int mid, int end);
int getPacketQuantity();               
void getPackets(unsigned long int *Arr, int size);
void arrayPrinter(unsigned long int *Arr, int size);
void greedyAlgo(unsigned long int *Arr, int size);
int isFeasable(int value, int *interLoad);
/*
 * Main (calls).
 */
int main(int argc, char** argv) {
    int sizeArr = getPacketQuantity();//how many packets?
    unsigned long int candidates[sizeArr];//Create array of candidates
    
    getPackets(candidates, sizeArr);
    arrayPrinter(candidates, sizeArr);//before ordering
    mergeSort(candidates,0, sizeArr-1);
    arrayPrinter(candidates, sizeArr);//after ordering
    sleep(2);
    greedyAlgo(candidates, sizeArr);
    return (EXIT_SUCCESS);
}

/*
 * Included function definitions:
 */
int isFeasable(int value, int *interLoad){
    int ans;
    
        if(*interLoad-value>=0){
           *interLoad-=value;
           ans=1;
        }else{
            ans=0;
        }
    return ans;
}

void greedyAlgo(unsigned long int *Arr, int size){
    int i;
    int totalLoad=0;//store weight of packets
    int totalPackets=0;//store number of packets
    int interLoad = CAPACITY;//temporal sum of capacity  
    printf("Capacity CHECKPOINT ->%d<-\n", interLoad);
    for(i=0; i<size; i++){
        if(isFeasable(Arr[i], &interLoad)==1){
            totalLoad += Arr[i];
            totalPackets ++;
        }else{
           break; 
        }
    }
    system("clear");
    printf("\n%d packets with total weight of %d, costing %d EUR to deliver.\n",
            totalPackets, totalLoad, totalPackets*10);
}

void getPackets(unsigned long int *Arr, int size){
    printf("Please introduce weight (KG, only integers), then hit Intro Until finished\n");
    int i;
    for(i=0;i<size;i++){
        int flag=0;
        do{
            system("clear");
            if(flag!=0){
                printf("Maximum weight CANNOT exceed %i!!!\n\n", CAPACITY);
            }
            printf("Weight of packet_%d, please:\n", i+1);//in order to begin at 1
            scanf("%lu", &Arr[i]);
            flag=1;
        }while(Arr[i]>CAPACITY);
    }
    system("clear"); 
    printf("Finished introducing weights!");
}

int getPacketQuantity(){
    int returnVar;
    printf("How many packets are we logging?\n");
    scanf("%i", &returnVar);
    system("clear"); 
    return returnVar;
}

void mergeSort(unsigned long int *Arr, int start, int end) {

	if(start < end) {
		int mid = (start + end) / 2;
		mergeSort(Arr, start, mid);
		mergeSort(Arr, mid+1, end);
		merge(Arr, start, mid, end);
	}
}

void merge(unsigned long int *Arr, int start, int mid, int end) {
	// create a temp array
	int temp[end - start + 1];
	// indexes for both intervals and temp arrays
	int i = start, j = mid+1, k = 0;

	// traverse both arrays and in each iteration add smaller of both elements in temp 
        //only unselected elements can apply for comparison, thus the different increments
        //depending on which array contributes with smaller element. Unpicked elements keep
        //participating till selected or cleared as leftovers.
	while(i <= mid && j <= end) {
		if(Arr[i] <= Arr[j]) {
			temp[k] = Arr[i];
			k += 1; i += 1;
		}
		else {
			temp[k] = Arr[j];
			k += 1; j += 1;
		}
	}
	// add elements left in the first interval 
	while(i <= mid) {
		temp[k] = Arr[i];
		k += 1; i += 1;
	}
	// add elements left in the second interval 
	while(j <= end) {
		temp[k] = Arr[j];
		k += 1; j += 1;
	}
	// copy temp to original interval
	for(i = start; i <= end; i += 1) {
		Arr[i] = temp[i - start];
	}
}

void arrayPrinter(unsigned long int *Arr, int size){
    int i;
    printf("\nArray is as follows:\n");
    for(i=0;i<size;i++){
        printf("%lu ", Arr[i]);
    }
}
