
#include <stdio.h>
#include <stdlib.h>

void print_to_file(int n, double** aptr, int format_flag){
	char filename[50];
	
	char identifier[7]; // Size: 6 digits + 1 null terminator

        // Format n as a 6-character string with leading zeros
        sprintf(identifier, "%06d", n);
	if(format_flag == 1){

	
		sprintf(filename, "array-%s-asc.out", identifier);

        	FILE* file = fopen(filename, "w");

	        if(file == NULL){
        	        printf("Error opening file\n");
        	}
	        int i, j;

        	for(i = 0; i < n; i ++){
                	for(j = 0; j < n; j++){
                        	fprintf(file,"%.15f    ", aptr[i][j]);
               		 }
                	fprintf(file, "\n");
       		 }
		fclose(file);
	}
	else{
	

		sprintf(filename, "array-%s-bin.out", identifier);
	
		FILE* file = fopen(filename, "wb");
	
		if(file == NULL){
			printf("Error opening file\n");
		}
		
		size_t written = fwrite(aptr, sizeof(float), n * n, file);
		if(written != n * n){
			printf("Error writing the file \n");
		}
		fclose(file);
			
	}
	printf("contents written to the file name: %s\n", filename);
}         

int main(){
	
	FILE* input_file = fopen("input.in", "r");
    	if (input_file == NULL) {
        	printf("Error: Could not open file 'input.in'.\n");
        	return 1;
    	}
	int n;
    	// Read n and m from the file
       	if (fscanf(input_file, "%d", &n) != 1) {
                 printf("Error: Failed to read dimensions from the file.\n");
                 fclose(input_file);
                 return 1;
        }
     	fclose(input_file);
	
	// it can also be implemented using single block of code
	
       	printf("%d \n", n);
	double** ptr = (double**) malloc(n * sizeof(double*)); // dynamicaaly allocatng space for the pointers 
	if(ptr == NULL){
		printf("memory allocation is not successfull \n");
		return 1;
	}
	int i;
	int k, j;
	for(i = 0; i < n; i ++){
		*(ptr + i) = (double*) malloc(n * sizeof(double));// now allocate space for the doubles(size of 8 bytes)
		if(*(ptr + i) == NULL){
                	printf("Memory allocation is unsuccessful! \n");
	//if the present row doesnot allocate the space then we need to free the space of previously allocated space
			for(k = 0; k < i; k++){
				free(*(ptr + k));
			}
		
			free(ptr);
			return 1;
		}
		
	}
	// Initialize the matrix with A[i][j] = i + j
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
	       		ptr[i][j] = i + j + 2;
                }
	}

	int format_flag = 1;
	print_to_file(n, ptr, format_flag);
	
}

