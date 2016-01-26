/**
 * Subject: Memory-Layout
 * Author: LiYing
 */

/**
 * Memory-Layout Segments:
 * High Address(Ceiling)
 * Command-Line Arguments && Environment Variables
 * Stack (Grow from HA to LA): 1.Automatic Variables;2.Information each time a function is called;
 * ... ...
 * Heap  (Grow from LA to HA): 1.Dynamic memory allocation;
 * Uninitialized data(bss):1.e.g. int maxcount = 99 outside of any function;2Also called Data Segmemt
 * Initialized data: 1.Initialized to zero or null by the kernel;2Block Started by Symbol;3.e.g. long data[100]; outside any function;
 * Text: 1.Read Only;2.Sharable(for frequently executed programs);3.The machine instructions that the CPU executes.
 * Low Address(bottom)
 */
/**
 * STACK SEGMENT:
 * Each time a function is called, the address of where to return to and certain information about the caller's environment,
 * such as some of the machine registers, are saved on the stack. The newly called function then allocates room on the stack
 * for its automatic and temporary variables. This is how recursive functions in C can work. Each time a recursive function
 * calls itself, a new stack frame is used, so one set of variables doesn't interfere with the variables from another instance
 * of the function.
 */

int main(int argc, char *argv[]){
	printf("hello world\n");
	exit(0);
}/*main*/
