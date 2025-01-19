#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int check_vector(int n, double* result, double* vector){
	int i;
	double tol = 1e-300;
	double lambda;
	double factor = 0;
	for(i = 0; i < n; i++){
		if(fabs(vector[i]) < tol){
			if(fabs(result[i]) > tol){
				printf("This is not the eigen vector\e");
				return 1;
			}
			continue;
		}

		double pre_factor = result[i]/vector[i];
       		if(!factor){
			lambda = pre_factor;
			factor = 1;
		}
		if(pre_factor != lambda){
			printf("This is not the eigen value\n");
			return 0;
		}
	}
	if(factor){
		printf("The eigen value is %.2f \n", lambda);
	}
	        
}

double* get_vector(int index,int n){
	char vec_file_path[100];
	int i;
	snprintf(vec_file_path, sizeof(vec_file_path), "inputfiles/vec_%06d_%06d.in", n, index);
	//Read the vector from 'vec {nnnnnn} {vecnum}.in'
	FILE *vec_file = fopen(vec_file_path, "r");
	//double* vector = (double*) malloc(n * sizeof(double));
	double* vector = (double*) malloc(n * sizeof(double));
	printf("%s \n", vec_file_path);
	if (vec_file == NULL) {
		printf("Error: Could not open '%s'\n", vec_file_path);                                                                            
      	}
	for (i = 0; i < n; i++) {
		if(fscanf(vec_file, "%lf,", vector + i) != 1){
			printf("Error in openinf file\n");
			fclose(vec_file);
		}
	}
	
	printf("%p\n", vector);
	return vector;
}
		
int main(){
	FILE* input_file = fopen("input.in", "r");
	if(input_file == NULL){
		printf("File didnt opened \n");
		return 1;
	}
	int n, i, j;
	if(fscanf(input_file, "%d", &n) != 1){
		printf("File contains more than single argument\n");
		fclose(input_file);
		return 1;	
	}	
	fclose(input_file);
	printf("value of matrix is: %d\n", n);


	// generate the file names 
	char mat_file_path[100], vec_file_path[100];
	snprintf(mat_file_path, sizeof(mat_file_path), "inputfiles/mat_%06d.in", n);
	//snprintf(vec_file_path, sizeof(vec_file_path), "inputfiles/vec_%06d_%06d.in", n, 2);

	double matrix[n][n];
	
    	FILE *mat_file = fopen(mat_file_path, "r");
    	if (mat_file == NULL) {
        	printf("Error opening file\n");
        	return 1;
    	}

    // Reading the matrix from the file
        for (i = 0; i < n; i++) {
        	for (j = 0; j < n; j++) {
                	if(fscanf(mat_file, "%lf,", &matrix[i][j]) != 1){
				printf("Failed to read accorded at line no.:%d\n", i);
				fclose(mat_file);
				free(matrix);
				return 1;
			}
                }
        }
        fclose(mat_file);

	//Read the vector from 'vec {nnnnnn} {vecnum}.in'
    	//FILE *vec_file = fopen(vec_file_path, "r");
	//double* vector = (double*) malloc(n * sizeof(double));
	//
	//double vector[n];
	//printf("%s \n", vec_file_path);
	//if (vec_file == NULL) {
        ///	printf("Error: Could not open '%s'\n", vec_file_path);
       	//	return 1;
    //	}
    //	for (i = 0; i < n; i++) {
      //         if(fscanf(vec_file, "%lf,", vector + i) != 1){
	//		printf("Failed to read the values at index %d\n", i);
	//		fclose(vec_file);
	//		free(vector);
	//		return 1;
	//	}

    //	}
    //	fclose(vec_file);

//	for(i = 0; i < n ; i++){
//		printf("%e \n", *(vector + i));
//	}
//	free(vector);

	// get vector
	 
	double* vec = get_vector(1, n);
	
	
	// do the matrix multiplication
	double result[n];

	for (i = 0;i < n ; i ++){
		for(j = 0; j < n; j++){
			result[i] += matrix[i][j] * vec[j];
		}
	}
	check_vector(n, result, vec);
	free(vec);	
}
