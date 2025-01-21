#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int check_vector(int k, int n, double* result, double* vector){
	int i;
	double tol = 1.0e-6;
	double lambda;
	double factor = 0;
	double pre_factor;
	for(i = 0; i < n; i++){

		if(fabs(vector[i]) < tol){
			if(fabs(result[i]) > tol){
				printf("vec-%06d-%06d:Not an eigen vector\n", n, k);
				return 1;
			}
			else{
				continue;
			}
			
		}
		else{
			pre_factor = result[i]/vector[i];
		}

       		if(!factor){
			lambda = pre_factor;
			factor = 1;
		}
		else if(fabs(pre_factor - lambda) > tol){
			printf("vec-%06d-%06d:Not an eigen vector\n", n, k);
			return 0;
		}
		
	}
	if(factor){
		printf("Yes:%.2f \n", lambda);
	}
	        
}

double* get_vector(const char* vec_file_path, int index,int n){
	int i;
	//Read the vector from 'vec {nnnnnn} {vecnum}.in'
	FILE *vec_file = fopen(vec_file_path, "r");
	//double* vector = (double*) malloc(n * sizeof(double));
	double* vector = (double*) malloc(n * sizeof(double));
	
	if (vec_file == NULL) {
		printf("Error: Could not open '%s'\n", vec_file_path);                                                                            
      	}
	for (i = 0; i < n; i++) {
		if(fscanf(vec_file, "%lf,", vector + i) != 1){
			printf("Error in openinf file\n");
			fclose(vec_file);
		}
	}
	
	return vector;
}

int val_n(const char* filename){
	FILE* input_file = fopen(filename, "r");
        if(input_file == NULL){
                printf("File didnt opened \n");
                return 1;
        }
        int n;
        if(fscanf(input_file, "%d", &n) != 1){
                printf("File contains more than single argument\n");
                fclose(input_file);
                return 1;
        }
        fclose(input_file);
	return n;
}

int get_matrix(const char* mat_file_path, int n, double matrix[n][n]){
	FILE *mat_file = fopen(mat_file_path, "r");
	int i, j;
        if (mat_file == NULL) {
                printf("Error opening file\n");
                return 1;
        }
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
}
		
int main(){
	int n;
	// get size of the matrix
	n = val_n("input.in");

	// generate the file names 
	char mat_file_path[100], vec_file_path[100];
	snprintf(mat_file_path, sizeof(mat_file_path), "inputfiles/mat_%06d.in", n);
	
	// read matrix from input
	double matrix[n][n];
	get_matrix(mat_file_path, n, matrix);

	int i, j, k;
 
	// check for eigen vector and calculate Ax
	for(k = 1; k < 5; k++){
		snprintf(vec_file_path, sizeof(vec_file_path), "inputfiles/vec_%06d_%06d.in", n, k);

		double* vec = get_vector(vec_file_path, k, n);
	
		double result[n];

		for (i = 0;i < n ; i ++){
			result[i] = 0;
			for(j = 0; j < n; j++){
				result[i] += matrix[i][j] * vec[j];
			}
		}
		check_vector(k, n, result, vec);
		free(vec);
	}
	
}
