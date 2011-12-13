/*

gcc -o vector_io_test ./vector_io_test.c ../src/serialize.c ../src/base64.c ../lib/libcgen.a -I../libcgeneric 

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"
#include "gen/error_macros.h"
#include "serialize.h"

const char* filepath = "vector_io_test.txt";


void intprint(const void* number) {
  printf("%u\n", *(unsigned int*)number);
}


int main(void) {
  fprintf(stderr, "Create a vector with the numbers 1 to 10\n");
  
  Vector* object;
  unsigned int x, y;
  memset(object, 0, sizeof(Vector));
  construct(Vector, object,sizeof(x),FREEOBJ);
  
  for (x = 0; x < 10; x++) {
    push_back(Vector,  object, &x, DYNAMIC);
  }
  
  fprintf(stderr, "Print content\n");
  
  set_print(Vector, object, intprint);
  print_all(Vector, object);
  
  
  
  fprintf(stderr, "Write the vector down!\n");
  FILE* f;
  
  
  /* you can change the coder the way you want to (may you've a list holding lists ... ) */
  Coder* coder = createBase64Coder();
  
  if(f = fopen(filepath, "w")) {
  	/* encode the vector as base64 in file vector_io_test.txt */
  	
  	if(encode(Vector, object, f, coder) != SUCCESS)
  		fprintf(stderr, "There was an error during encoding!\n");
  	fclose(f);
  }else
    fprintf(stderr, "Could not create or edit the file!\n");
  
  destruct(Vector, object);
  
  
  /*fprintf(stderr, "Read the vector from the file!\n");
  if(f = fopen(filepath, "r")) {
    object = decode(Vector, f, coder);
    
    if(object) {
    	 fprintf(stderr, "Print the content of the decoded data in a loop\n");
    	 
    	 VectorIter *ptr;
		 ptr = create(VectorIter,  object);
		 
		 head(VectorIter,ptr);
		 do {
		   intprint(retrieve(VectorIter, ptr));
	     }while (!next(VectorIter, ptr));
			  
		 destroy(VectorIter,ptr);
		 destruct(Vector,&object);
    }else
      fprintf(stderr, "There was an problem during the decoding\n");
    
  }else
    fprintf(stderr, "Could not read the file!\n");
  
  */
  /* you've to release it yourself */
  free(coder);
  
  return EXIT_SUCCESS;
}
