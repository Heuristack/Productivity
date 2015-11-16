/**
 * TITLE: Interrupted System Calls
 * AUTHOR: LiYing
 * DATE: 2010-5-14 16:23:33
 * NOTE: 'Slow system calls' could be interrupted
 */
/**
 * SLOW SYSTEM CALLS
 * 1.Reads that can block the caller forever if data isn't present with certain file types;
 * 2.Writes that can block the caller forever if the data can't be accepted immediately by these same file types;
 * 3.Opens that block until some condition occurs on certain file types;
 * 4.The pause function and the wait function;
 * 5.Certain ioctl operations;
 * 6.Some of the interprocess communication functions;
 */
/**
 * SIGNAL IMPLEMENTATIONS
 * signal
 * sigset
 * sigvec
 * sigaction
 */
/**
 * HANDLING STRATEGIES
 * AUTOMATIC RESTART OF INTERRUPTED SYSTEM CALLS (Y/N)
 * ABALITY TO BLOCK SIGNALS (Y/N)
 * SIGNAL HANDLERS REMAINS INSTALLED (Y/N)
 */

int main(){}/*main*/
