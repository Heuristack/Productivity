int magic_trace(char *filename, char *file, char *function, int line, char *format, ...);
int stack_trace(char *filename);
#define MT(...) magic_trace( "magic.trace", __FILE__, (char*)__FUNCTION__, __LINE__, __VA_ARGS__ )
#define ST() stack_trace("stack.trace")
