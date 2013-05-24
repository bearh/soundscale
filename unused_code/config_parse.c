#include "defines.h"

/*
 * Odd file format.
 * I check everything
 */
int parse_conf(char *filename){
	int i;
	FILE *FILE_STREAM;
	char current_buffer[1024];
	// EXTERNS GO HERE
	extern bool sc_enable_output;
	// End of externs
	FILE_STREAM = fopen(filename,"r");
	if(FILE_STREAM == NULL){	
		// We will just use defaults then.
		return CONFIG_NON_EXISTANT;
	}
	fread(current_buffer,1024,1,FILE_STREAM);
	printf("%s",current_buffer);
	for(i=0;i<=;i++){
		if(){
		}
	}
	free(current_buffer);
	fclose(FILE_STREAM);
}
