/*************************
 * Muhammad Jamil Tokhi 
 * Student ID: xxxxxxxxx
 * Semester 1 - 2025
 * CMPE 180C - Juan Gomez 
 *************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

// Data structure to store five integers
typedef struct{
	int nums[5];
} five_numbers;

// Error handling helper function declaration
void error_message(int i, int error_number);

// Parse user input function declaration
int *parse_user_input(char *usr_arg);

// Helper function to parse the data stored in the .txt file declaration
five_numbers *parse_file(char *x, int *length);

// Compare function: checks data in user_input with data in file_data to find set membership
void compare(int *user_input, five_numbers *file_data, int length);


/************************
 *                      * 
 *    MAIN FUNCTION     *
 *                      *
 ************************/ 
int main(int argc, char *argv[]){

	// Initialize arrays to store user input and file data
	int *user_input;
	five_numbers *file_data;

	// RV (return value) initializations
	int strcmpRV;

	/******************************
	 * Handle command line input: *
	 ******************************/
	
	// Confirm argument count is correct. 
	if(argc != 5){
		error_message(1, errno);
		
	}

	// Check if first argument is -n
	strcmpRV = strcmp(argv[1], "-n");
	if(strcmpRV != 0){
		
		// If first argument is not -n, check if it is -f
		strcmpRV = strcmp(argv[1], "-f");

		// if first arg is not -n or -f, return error
		if(strcmpRV != 0){
			error_message(2, errno);
			
		} else{

			// Argument 1 is -f, so check if argument 3 is -n
			strcmpRV = strcmp(argv[3], "-n");
			if(strcmpRV != 0){
				// If not, return error.
				error_message(2, errno);
			}

			// First argument is -f and third argument is -n,
			// so begin parsing argument 2 as the file and argument 4 as the user input numbers

			/************
			*  PARSING  *
			*************/
			int file_data_length = -1;
			file_data = parse_file(argv[2], &file_data_length);
			user_input = parse_user_input(argv[4]);

			compare(user_input, file_data, file_data_length);

			free(file_data);
			free(user_input);		
		}

	} else{
		// First argument is -n so check if third argument is -f
			strcmpRV = strcmp(argv[3], "-f");
			if(strcmpRV != 0){
				// If not, return error.
				error_message(2, errno);
			}
		// First argument is -n and third argument is -f, 
		// so begin parsing argument 2 as user_input and argument 4 as file

		/************
		*  PARSING  *
		*************/	
		user_input = parse_user_input(argv[2]);
		int file_data_length = -1;
		file_data = parse_file(argv[4], &file_data_length);
		
		compare(user_input, file_data, file_data_length);

		free(user_input);
		free(file_data);
	}

	// end main, return 0 for success
	return 0;
}

void error_message(int i, int error_number){
	switch(i){
		case 1:
			fprintf(stderr, "Invalid argument count:\n");
			fprintf(stderr, "Program should have 4 arguments and be called in the following format:\n");
			fprintf(stderr, "number_checker -n num1,num2,num3,num4,num5 -f some_file.txt\n");
			break;
		case 2:
			fprintf(stderr, "Invalid argument(s):\n");
			fprintf(stderr, "NOTE: 1st and 3rd arguments must be either '-n' and '-f' OR '-f' and '-n' respectively.\n");
			fprintf(stderr, "Program should have 4 arguments and be called in the following format:\n");
			fprintf(stderr, "number_checker -n num1,num2,num3,num4,num5 -f some_file.txt\n");
			break;
		case 3:
			fprintf(stderr, "Invalid argument(s):\n");
			fprintf(stderr, "NOTE: following '-n' should be a list of 5 UNIQUE numbers separated by commas. For example, 1,2,3,4,5\n");
			fprintf(stderr, "Program should have 4 arguments and be called in the following format:\n");
			fprintf(stderr, "number_checker -n num1,num2,num3,num4,num5 -f some_file.txt\n");
			break;
		case 4:
			fprintf(stderr, "Error Parsing file:\n");
			fprintf(stderr, "ERROR CODE: %d, %s\n", error_number, strerror(error_number));
			fprintf(stderr, "Program should have 4 arguments and be called in the following format:\n");
			fprintf(stderr, "number_checker -n num1,num2,num3,num4,num5 -f some_file.txt\n");
			break;
		case 5:
			fprintf(stderr, "Error Parsing Input: invalid character passed.\n");
			break;
		default:
			fprintf(stderr, "UNKNOWN ERROR\n");
	}
	exit(EXIT_FAILURE);
}

/************************
 *                      *
 * PARSE INPUT FUNCTION	*
 *                      *
 ************************/
// Helper function to parse the numbers to check passed by user in command line
int *parse_user_input(char *usr_arg){
	//declare variables
	char *token, *endptr;
	int *return_array;
	int count = 0;
	int i = 0;
	int j = 0;

	//count # of commas in string
	for(i=0; i<strlen(usr_arg); i++){
		if(usr_arg[i] == ','){
			count++;
		}
	}
	// Return error if number of commas is not equal to 4
	if(count != 4){
		error_message(3, errno);
	}

	// Initialize return_array to size of 1 int
	i = 0;
	return_array = malloc(sizeof(int)*(i+1));

	// Tokenize usr_arg separated by comma	
	token = strtok(usr_arg, ",");
	
	// Convert to long and store in array
	errno = 0;
	return_array[i] = strtol(token, &endptr, 10);
	if(errno != 0){
		error_message(3, errno);
	} else if(return_array[i] < 0 || return_array[i] > 99){
		error_message(5, errno);
	} else if(*endptr != '\0'){
		error_message(5, errno);
	}
	// Iterate through usr_arg until all tokens are parsed
	while(token != NULL){
		i++;
		
		token = strtok(NULL, ",");
		if(token == NULL){
			break;
		}
		// Re-allocate memory in array to match size of number of tokens.
		return_array = realloc(return_array, sizeof(int)*(i+1));

		errno = 0;
		return_array[i] = strtol(token, &endptr, 10);
		if(errno != 0){
			error_message(3, errno);
		} else if(return_array[i] < 0 || return_array[i] > 99){
			error_message(5, errno);
		} else if(*endptr != '\0'){
			error_message(5, errno);
		}

		for(j=0;j<i; j++){
			if(return_array[i] == return_array[j]){
				error_message(3, errno);
			}
		}
	}

	// Return array should have 5 elements, otherwise return error.
	if(i != 5){
		error_message(3, errno);
	}

	return return_array;
}

/************************
 *                      *
 * PARSE FILE FUNCTION	*
 *                      *
 ************************/
// Helper function to parse the data stored in the .txt file
five_numbers *parse_file(char *x, int *length){

	five_numbers *return_array = malloc(sizeof(five_numbers));
	five_numbers current;
	char *token, *endptr;
	FILE *file_addr;
	struct stat fileStat; 
	int i = 0;
	int j = 0;
	errno = 0;
	
	// Open file in read mode
	file_addr = fopen(x, "r");
	if(file_addr == NULL && errno != 0){
		error_message(4, errno);
	}

	// Get stat and check for errors
	errno = 0;
	if(stat(x, &fileStat) == -1){
		error_message(4, errno);
	}

	// Create buffer the size of the file
	char *buffer = malloc(fileStat.st_size);
	
	// Parse file by newline until EOF
	errno = 0;
	while(fgets(buffer, fileStat.st_size+1, file_addr) != NULL){
	
		token = strtok(buffer, " ");

		if(token == NULL){
			break;
		}		
		// Convert to long and store in struct
		errno = 0;
		current.nums[0] = strtol(token, &endptr, 10);
		if(errno != 0){
			error_message(4, errno);
		}


		token = strtok(NULL, " ");
		if(token == NULL){
			break;
		}

		errno = 0;
		current.nums[1] = strtol(token, &endptr, 10);
		if(errno != 0){
			error_message(4, errno);
		}
		
		token = strtok(NULL, " ");
		if(token == NULL){
			break;
		}

		errno = 0;
		current.nums[2] = strtol(token, &endptr, 10);
		if(errno != 0){
			error_message(4, errno);
		}
		
		token = strtok(NULL, " ");
		if(token == NULL){
			break;
		}

		errno = 0;
		current.nums[3] = strtol(token, &endptr, 10);
		if(errno != 0){
			error_message(4, errno);
		}
		
		token = strtok(NULL, " ");
		if(token == NULL){
			break;
		}

		errno = 0;
		current.nums[4] = strtol(token, &endptr, 10);
		if(errno != 0){
			error_message(4, errno);
		}

		return_array[i] = current;
		i++;
		return_array = realloc(return_array, (sizeof(five_numbers))*(i+1));
	}
	if(errno != 0){
		fprintf(stderr, "%s",strerror(errno));
	}

	(*length) = i;
	free(buffer);
	fclose(file_addr);
	return return_array;
}

/****************************
 *                          *
 * Compare Values FUNCTION	*
 *                          *
 ****************************/
// Compare function: checks data in user_input with data in file_data to find set membership
void compare(int *user_input, five_numbers *file_data, int length){
	int match_count;
	struct output{
		int match[5][100];
		int count[5];
	};


	// Initialize output struct to -1 for the count
	struct output output_to_print;
	for (int i =0; i<5; i++){
		output_to_print.count[i] = -1;
	}
	
	// Line loop (row)
	for(int i=0; i<length; i++){
		
		match_count = 0;

		// User Input Index Loop
		for(int j=0; j<5; j++){

			//File Index Loop (column)
			for(int k=0; k<5; k++){
				if(user_input[j] == file_data[i].nums[k]){
					match_count++;
					break;
				}
			}
		}
	
		// Update output struct with the number of matches and what line they occur
		switch(match_count){
			case 0:
				break;
			case 1:
				output_to_print.count[0]++;
				output_to_print.match[0][output_to_print.count[0]] = i;
				break;
			case 2:
				output_to_print.count[1]++;
				output_to_print.match[1][output_to_print.count[1]] = i;
				break;
			case 3:
				output_to_print.count[2]++;
				output_to_print.match[2][output_to_print.count[2]] = i;
				break;
			case 4:
				output_to_print.count[3]++;
				output_to_print.match[3][output_to_print.count[3]] = i;
				break;
			case 5:
				output_to_print.count[4]++;
				output_to_print.match[4][output_to_print.count[4]] = i;
				break;
			default:
				break;
		}	
	}

	// Print to stdout
	for(int i=5; i>0; i--){
		if (output_to_print.count[i-1] > -1){
			int j = 0;
			fprintf(stdout, "%d (",i);
			for(j=0; j<output_to_print.count[i-1]; j++){
				fprintf(stdout, "%d,", output_to_print.match[i-1][j]);
			}
			fprintf(stdout, "%d", output_to_print.match[i-1][j]);
			fprintf(stdout, ")\n");
		}
	}
}