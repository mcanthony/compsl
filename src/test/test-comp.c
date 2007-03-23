#include <stdio.h>
#include "../extern/vm.h"
#include "../extern/compart.h"
#include "../intern/compartment.h"
#include "../extern/compsl.h"
#include "../intern/vars.h"

// For DPRINTF
#include "../intern/debug.h"
#include "../compiler/node.h"

int goparse(const char* fn, compart *);

void addPrint(VM *vm); // add a printi(int) and printf(float) functions to the vm 

int main()
{
	printf("\nCompiler tests\n");
	const int NUM_FILES=6;
	
	const char * files[] = 
	{
		"src/test/base-structure.csl",
		"src/test/print-for-dbg.csl",
		"src/test/addition.csl",
		"src/test/functions.csl",
		"src/test/declarations.csl",
		"src/test/expressions.csl",
		"src/test/casting.csl",
		"src/test/flow-control.csl"
	};
	  
	  
	VM *veem = createVM();
	compart *com[NUM_FILES];
	addPrint(veem);
	
	for(int i=0;i<NUM_FILES;i++) {
	  int ret;
	  printf("Compiling: %s: ",files[i]);
		
	  com[i] = createComp(veem);
	  fflush(stdout);
	  ret = goparse(files[i], com[i]);
	  if(ret==0){
	    //DPRINTF("\t<%s>\n",com_prStats(com[i]));
	    printf("PASS\n");
	  } else {
	    printf("FAIL with exit code %i\n", ret);
	  }
	}
	
        puts("\nRunning a cubby - should print yes, no, Hello world");
	runCubbyhole(com[1], 0); 
	puts("\nRunning another cubby..");
	runCubbyhole(com[2], 0); 	
	puts("\nAnd another cubby..");
	runCubbyhole(com[3], 0); 	
	//TODO free com's
	
	destroyVM(veem);
	
	return 0;
}

intfloat compsl_printFloat(var *args) { printf("Value: %f\n", args[0].v.f); return (intfloat)0;}
intfloat compsl_printInt(var *args) { printf("Value: %i\n", args[0].v.i); return (intfloat)0;}	
intfloat compsl_printHello(var *args) { printf("Hello world\n"); return (intfloat)0;}	

void addPrint(VM *vm)
{
  if(!addFunc(vm, &compsl_printFloat, "printf", "float",false,true))
    puts("FAILED TO ADD printf");
  if(!addFunc(vm, &compsl_printInt, "printi", "int",false,true))
    puts("FAILED TO ADD printi");
  if(!addFunc(vm, &compsl_printHello, "helloWorld", "",false,true))
    puts("FAILED TO ADD helloWorld");
}
