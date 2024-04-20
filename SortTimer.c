#include<stdio.h>
#include<stdlib.h>
#include <sys/time.h>
#include <time.h>
#include<string.h>
long long BubbleSort(int *SortPtr,int nSort){
    	struct timeval start, end;
    	gettimeofday(&start,NULL);
    	int i,j,tmp;
	for(i = 0; i < nSort-1;i++){
		for(j = 0; j< nSort - i - 1;j++){
        		if(*(SortPtr+j) > *(SortPtr+j+1)){
                		tmp = *(SortPtr+j);
	                	*(SortPtr+j) = *(SortPtr+j+1);
	                	*(SortPtr+j+1) = tmp;
                	}       
        	}
	}
	gettimeofday(&end,NULL);
	long long elapsed_time = (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);
	return elapsed_time;
}
long long SelectionSort(int *SortPtr, int nSort){
	struct timeval start,end;
	gettimeofday(&start,NULL);
	int i,j,min,tmp;
	for(i = 0;i<nSort - 1;i++){
		min = i;
		for(j = i + 1;j < nSort;j++){
			if(*(SortPtr+j) < *(SortPtr+min)){
				min = j;
			}
		}
		tmp = *(SortPtr+i);
		*(SortPtr+i) = *(SortPtr+min);
		*(SortPtr+min) = tmp;
	}
	gettimeofday(&end, NULL);
	long long elapsed_time = (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);
	return elapsed_time;
}
long long InsertionSort(int *SortPtr, int nSort){
	struct timeval start,end;
	gettimeofday(&start,NULL);
	int i, key, j;
    	for (i = 1; i < nSort; i++){
        	key = *(SortPtr + i);
        	j = i - 1; 
		while (j >= 0 && *(SortPtr+j) > key) 
        	{
        		*(SortPtr + j + 1) = *(SortPtr + j);
        		j = j - 1;
        	}
		*(SortPtr + j + 1)= key;
    	}
	gettimeofday(&end, NULL);
        long long elapsed_time = (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);
	return elapsed_time;
}
void QuickSort(int *SortPtr, int low, int high) {
	if (low < high) {
		int pivot = *(SortPtr + ((low + high) / 2));
	        int i = low;
        	int j = high;
	        int tmp;
	        while (i <= j) {
        		while (*(SortPtr + i) < pivot) i++;
            		while (*(SortPtr + j) > pivot) j--;
	            	if (i <= j) {
	                	tmp = *(SortPtr + i);
        	        	*(SortPtr + i) = *(SortPtr + j);
                		*(SortPtr + j) = tmp;
                		i++;
	                	j--;
            	}
        }
        if (low < j) QuickSort(SortPtr, low, j);
        if (i < high) QuickSort(SortPtr, i, high);
    }
}
//Radix Sort
int getMax(int *SortPtr, int nSort) {
	int max = SortPtr[0];
  	for (int i = 1; i < nSort; i++){
    		if (SortPtr[i] > max){
      			max = SortPtr[i];
		}
	}
  	return max;
}
void countingSort(int *SortPtr, int nSort, int place) {
	int *output = malloc((nSort + 1) * sizeof(int));
	int max = getMax(SortPtr, nSort);
  	for (int i = 1; i < nSort; i++) {
    		if (((SortPtr[i] / place) % 10) > max){
      			max = SortPtr[i];
		}
  	}
  	int *count = malloc((max + 1) * sizeof(int));

  	for (int i = 0; i < max; ++i){
    		count[i] = 0;
	}
  	for (int i = 0; i < nSort; i++){
		    count[(SortPtr[i] / place) % 10]++;
	}
  	for (int i = 1; i < 10; i++){
    		count[i] += count[i - 1];
	}
  	for (int i = nSort - 1; i >= 0; i--) {
    		output[count[(SortPtr[i] / place) % 10] - 1] = SortPtr[i];
    		count[(SortPtr[i] / place) % 10]--;
  	}

	for (int i = 0; i < nSort; i++){
    		SortPtr[i] = output[i];
	}
	free(output);
	free(count);
}
void RadixSort(int *SortPtr, int nSort) {
	int max = getMax(SortPtr, nSort);
    	for (int place = 1; max / place > 0; place *= 10){
		countingSort(SortPtr, nSort, place);
	}
}
//Merge Sort
void Merge(int *SortPtr, int l, int m, int nSort){
	int i, j, k;
    	int n1 = m - l + 1;
    	int n2 = nSort - m;
    	int *L = malloc(n1 * sizeof(int));
	int *R = malloc(n2 * sizeof(int));
    	for (i = 0; i < n1; i++){
        	L[i] = SortPtr[l + i];
	}
    	for (j = 0; j < n2; j++){
		R[j] = SortPtr[m + 1 + j];
	}
	i = 0;
	j = 0;
	k = l;
    	while (i < n1 && j < n2){
        	if (L[i] <= R[j]) {
            		SortPtr[k] = L[i];
            		i++;
        	}
        	else{
            		SortPtr[k] = R[j];
            		j++;
        	}
        	k++;
	}
	while (i < n1){
        	SortPtr[k] = L[i];
	       	i++;
        	k++;
    	}
	while (j < n2){
		SortPtr[k] = R[j];
	        j++;
        	k++;
    	}
}
void MergeSort(int *SortPtr, int l, int nSort){
	if (l < nSort){
        	int m = l + (nSort - l) / 2;
	        MergeSort(SortPtr, l, m);
        	MergeSort(SortPtr, m + 1, nSort);
	        Merge(SortPtr, l, m, nSort);
    	}
}
int main(){
	int i, nSort, nRepeat,RangeMax;
	//[number of sorting algorithms]
	float TimeTaken[10];
	srand(time(NULL));
	printf("Enter the amount of elements to sort:");
	scanf("%d",&nSort);
	int *SortArray = malloc(nSort * sizeof(int));
	printf("Enter max element value:");
	scanf("%d",&RangeMax);
	printf("Enter the amount of times to repeat the test:");
	scanf("%d",&nRepeat);
	for(i = 0; i<nSort;i++){
		SortArray[i] = rand() % RangeMax+1;
	}
	long long add = 0;
	//Bubble Sort
	for(i = 0; i<nRepeat;i++){
		int *copy = malloc(nSort * sizeof(int));
		memcpy(copy, SortArray, nSort * sizeof(int));
		add += BubbleSort(copy,nSort);
		free(copy);
	}
	//Average time taken
	TimeTaken[0] = ((float)add/nRepeat)/1000000.0;
	printf("Average time taken for Bubble Sort:%fs\n",TimeTaken[0]);
	//Selection Sort
	add = 0;
	for(i = 0; i<nRepeat;i++){
		int *copy = malloc(nSort * sizeof(int));
		memcpy(copy, SortArray, nSort * sizeof(int));
		add += SelectionSort(copy,nSort);
		free(copy);
	}
	TimeTaken[1] = ((float)add/nRepeat)/1000000.0;
	printf("Average time taken for Selection Sort:%fs\n",TimeTaken[1]);
	//Insertion Sort
	add = 0;
	for(i = 0; i<nRepeat;i++){
                int *copy = malloc(nSort * sizeof(int));
                memcpy(copy, SortArray, nSort * sizeof(int));
                add += InsertionSort(copy,nSort);
                free(copy);
        }
	TimeTaken[2] = ((float)add/nRepeat)/1000000.0;
    	printf("Average time taken for Insertion Sort:%fs\n",TimeTaken[2]);
	//Quick Sort
	add = 0;
	for(i = 0; i<nRepeat;i++){
                int *copy = malloc(nSort * sizeof(int));
		struct timeval start, end;
                memcpy(copy, SortArray, nSort * sizeof(int));
		gettimeofday(&start,NULL);
                QuickSort(copy,0,nSort);
		gettimeofday(&end,NULL);
		long long elapsed_time = (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);
		add += elapsed_time;
                free(copy);
        }
        TimeTaken[3] = ((float)add/nRepeat)/1000000.0;
        printf("Average time taken for Quick Sort:%fs\n",TimeTaken[3]);
	//Radix Sort
	add = 0;
        for(i = 0; i<nRepeat;i++){
                int *copy = malloc(nSort * sizeof(int));
                struct timeval start, end;
                memcpy(copy, SortArray, nSort * sizeof(int));
                gettimeofday(&start,NULL);
                RadixSort(copy,nSort);
                gettimeofday(&end,NULL);
                long long elapsed_time = (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);
                add += elapsed_time;
                free(copy);
        }
        TimeTaken[4] = ((float)add/nRepeat)/1000000.0;
        printf("Average time taken for Radix Sort:%fs\n",TimeTaken[4]);
	//Merge Sort
        add = 0;
        for(i = 0; i<nRepeat;i++){
                int *copy = malloc(nSort * sizeof(int));
                struct timeval start, end;
                memcpy(copy, SortArray, nSort * sizeof(int));
                gettimeofday(&start,NULL);
                MergeSort(copy,0,nSort);
                gettimeofday(&end,NULL);
                long long elapsed_time = (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);
                add += elapsed_time;
                free(copy);
        }
        TimeTaken[5] = ((float)add/nRepeat)/1000000.0;
        printf("Average time taken for Merge Sort:%fs\n",TimeTaken[5]); 
}
