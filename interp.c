/* interp.c
 * Robert Allen
 * CPSC 275
 * 12/9/2020
 */

#include <stdio.h>
#include <string.h>
#define OUTBOUNDS 128
#define OUTBOUNDSNEG -129
#define MEM 8
#define REG 4
#define FLAG 3 
#define INSTRUCTION 7
#define MAXLOCATIONS 15

void write(int location[], int n);
void read(int location1[], int data, char arg[]);
void move(int location1[], int location2[], char arg1[], char arg2[]);
void prints(int array1[], int array2[], int array3[]);
void arithmetic(int location1[], int location2[], int location3[], char arg1[], char arg2[], char operation[]);

void main() {
	int m0 = OUTBOUNDS, m1 = OUTBOUNDS, m2 = OUTBOUNDS, m3 = OUTBOUNDS, m4 = OUTBOUNDS, m5 = OUTBOUNDS, m6 = OUTBOUNDS, m7 = OUTBOUNDS;
	int r0 = OUTBOUNDS, r1 = OUTBOUNDS, r2 = OUTBOUNDS, r3 = OUTBOUNDS;
	int zf = 0, sf = 0, of = 0;
	int memory[MEM] = {m0, m1, m2, m3, m4, m5, m6, m7};
	int registers[REG] = {r0, r1, r2, r3};
	int flags[FLAG] = {zf, sf, of};
	int data;
	int index;
	int index2;
	char instruct[INSTRUCTION];
	char arg1[FLAG];
	char arg2[FLAG];
	int i, j, k, m;
	printf("SMS$> ");
	scanf("%s", instruct);
	for (i = 0; i < INSTRUCTION; i++) {
		instruct[i] = tolower(instruct[i]);
	}
	while (strcmp(instruct, "quit") != 0) {
		if (strcmp(instruct, "write") == 0 || strcmp(instruct, "prints") == 0) {
			if (instruct[0] == 'w') {
				scanf("%s", arg1);
				index = (arg1[1] - '0');
				for (j = 0; j < FLAG; j++) {
					arg1[j] = tolower(arg1[j]);
				}
				if (arg1[2] == ',') {
					printf("???\n");
				}
				else if (arg1[0] == 'm') {
					write(memory, index);
				}
				else if (arg1[0] == 'r') {
					write(registers, index);
				}
				else if (arg1[0] == 'z' || arg1[0] == 's' || arg1[0] == 'o') {
					if (arg1[0] == 'z') {
						write(flags, 0);
					}
					else if (arg1[0] == 's') {
						write(flags, 1);
					}
					else {
						write(flags, 2);
					}
				}
				else {
					printf("???\n");
				}
			}
			else {
				prints(memory, registers, flags);
			}
		}
		else if (strcmp(instruct, "read") == 0) {
			scanf("%d", &data);
			scanf("%s", arg2);
			if (strcmp(arg2, ",") != 0) {
				printf("???\n");
			}
			else {
				scanf("%s", arg2);
				for (k = 0; k < FLAG; k++) {
					arg2[k] = tolower(arg2[k]);
				}
				if (data >= OUTBOUNDS || data <= OUTBOUNDSNEG ) {
					printf("???\n");
					flags[2] = 1;
					read(memory, OUTBOUNDS, arg2);
				}
				else {
					if (arg2[0] == 'm') {
						read(memory, data, arg2);
					}
					else if (arg2[0] == 'r') {
						read(registers, data, arg2);
					}
				}
			}
		}
		else if (strcmp(instruct, "add") == 0 || strcmp(instruct, "sub") == 0 || strcmp(instruct, "mult") == 0 || strcmp(instruct, "div") == 0 || strcmp(instruct, "mod") == 0 || strcmp(instruct, "div") == 0 || strcmp(instruct, "move") == 0) {
			scanf("%s", arg1);
			scanf("%s", arg2);
			for (m = 0; m < FLAG; m++) {
				arg1[m] = tolower(arg1[m]);
				arg2[m] = tolower(arg2[m]);
			}
			index2 = (arg2[1] - '0');
			if ((arg1[0] == 'm') && (arg2[0] == 'm')) {
				printf("???\n");
			}
			else if (strcmp(instruct, "move") == 0) {
				move(memory, registers, arg1, arg2);
			}
			else {
				arithmetic(memory, registers, flags, arg1, arg2, instruct);
			}
		}
		else {
			printf("???\n");
		}
		printf("SMS$> ");
		scanf("%s", instruct);
	}
}

void write(int location[], int n) {
	int value = location[n];
	if (value == OUTBOUNDS) {
		printf("?\n");
	}
	else {
		printf("%d\n", value);
	}
}

void read(int location1[], int data, char arg[]) {
	location1[arg[1] - '0'] = data;
}

void move(int location1[], int location2[], char arg1[], char arg2[]) {
	if (arg1[2] != ',') {
		printf("???\n");
	}
	else {
		if (arg1[0] == 'r') {
			if (arg2[0] == 'r') {
				location2[arg2[1] - '0'] = location2[arg1[1] - '0'];
			}
			else {
				location1[arg2[1] - '0'] = location2[arg1[1] - '0'];	
			}
		}
		else {
			location2[arg2[1] - '0'] = location1[arg1[1] - '0'];
		}
	}
}

void prints(int array1[], int array2[], int array3[]){
	int i, j, k, p;
	for (j = 0; j < REG; j++) {
		if (array2[j] == OUTBOUNDS) {
			printf("?\t");
		}
		else {
			printf("%d\t", array2[j]);
		}
	}
	for (i = 0; i < MEM; i++) {
		if (array1[i] == OUTBOUNDS) {
			printf("?\t");
		}
		else {
			printf("%d\t", array1[i]);
		}
	}
	for (k = 0; k < FLAG; k++) {
		printf("%d\t", array3[k]);
	}
	printf("\n");
	for (p = 0; p < MAXLOCATIONS; p++) {
		printf("--\t");
	}
	printf("\n");
	printf("R0\tR1\tR2\tR3\tM0\tM1\tM2\tM3\tM4\tM5\tM6\tM7\tZF\tSF\tOF\n");
}

void arithmetic(int location1[], int location2[], int location3[], char arg1[], char arg2[], char operation[]) {
	int result;
	if (arg1[2] != ',') {
		printf("???\n");
		return;
	}
	if (arg1[0] == 'r') {
		if (location2[arg1[1] - '0'] <= OUTBOUNDSNEG || location2[arg1[1] - '0'] >= OUTBOUNDS) {
			result = OUTBOUNDS;
		}
		else if (arg2[0] == 'r') {
			if (location2[arg2[1] - '0'] <= OUTBOUNDSNEG || location2[arg2[1] - '0'] >= OUTBOUNDS) {
				result = OUTBOUNDS;
			}
			else {
				if (operation[0] == 'a') {
					result = location2[arg1[1] - '0'] + location2[arg2[1] - '0'];
				}
				else if (operation[0] == 's') {
					result = location2[arg2[1] - '0'] - location2[arg1[1] - '0'];
				}
				else if (operation[0] == 'd') {
					result = location2[arg1[1] - '0'] / location2[arg2[1] - '0'];
				}
				else if (operation[0] == 'm') {
					if (operation[1] == 'u') {
						result = location2[arg1[1] - '0'] * location2[arg2[1] - '0'];
					}
					else {
						result = location2[arg1[1] - '0'] % location2[arg2[1] - '0'];
					}
				}
			}
		}
		else {
			if (location1[arg2[1] - '0'] <= OUTBOUNDSNEG || location1[arg2[1] - '0'] >= OUTBOUNDS) {
				result = OUTBOUNDS;
			}
			else {
				if (operation[0] == 'a') {
					result = location2[arg1[1] - '0'] + location1[arg2[1] - '0'];
				}
				else if (operation[0] == 's') {
					result = location1[arg2[1] - '0'] - location2[arg1[1] - '0'];
				}
				else if (operation[0] == 'd') {
					result = location2[arg1[1] - '0'] / location1[arg2[1] - '0'];
				}
				else if (operation[0] == 'm') {
					if (operation[1] == 'u') {
						result = location2[arg1[1] - '0'] * location1[arg2[1] - '0'];
					}
					else {
						result = location2[arg1[1] - '0'] % location1[arg2[1] - '0']; 
					}
				}
			}
		}
	}
	else if (arg1[0] == 'm') {
		if (location1[arg1[1] - '0'] <= OUTBOUNDSNEG || location1[arg1[1] - '0'] >= OUTBOUNDS) {
			result = OUTBOUNDS;
		}
		else if (location2[arg2[1] - '0'] <= OUTBOUNDSNEG || location2[arg2[1] - '0'] >= OUTBOUNDS) {
			result = OUTBOUNDS;
		}
		else {
			if (operation[0] == 'a') {
				result = location1[arg1[1] - '0'] + location2[arg2[1] - '0'];
			}
			else if (operation[0] == 's') {
				result = location2[arg2[1] - '0'] - location1[arg1[1] - '0'];
			}
			else if (operation[0] == 'd') {
				result = location1[arg1[1] - '0'] / location2[arg2[1] - '0'];
			}
			else if (operation[0] == 'm') {
				if (operation[1] == 'u') {
					result = location1[arg1[1] - '0'] * location2[arg2[1] - '0'];
				}
				else {
					result = location1[arg1[1] - '0'] % location2[arg2[1] - '0'];
				}
			}
		}
	}
	if ((arg1[0] != 'm' && arg1[0] != 'r' ) || (arg2[0] != 'm' && arg2[0] != 'r')) {
		printf("???\n");
	}
	else if (result <= OUTBOUNDSNEG || result >= OUTBOUNDS) {
		location2[0] = OUTBOUNDS;
		location3[2] = 1;
		location3[0] = 0;
		location3[1] = 0;
		read(location2, OUTBOUNDS, "r0");
	}
	else {
		location2[0] = result;
		if (result == 0) {
			location3[0] = 1;
			location3[1] = 0;
			location3[2] = 0;
		}
		else if (result < 0) {
			location3[1] = 1;
			location3[0] = 0;
			location3[2] = 0;
		}
		else if (result > 0) {
			location3[0] = 0;
			location3[1] = 0;
			location3[2] = 0;
		}
	}
}
