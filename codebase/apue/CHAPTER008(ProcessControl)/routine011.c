/**
 * SUBJECT: Process Termination - changing user id and group id
 * AUTHOR: LiYing
 * TIME: 2009-10-23 10:56:17
 */
/**
 * PRIVILEGES
 * 1.based on user and group ids
 * 2.eg:being able to change the system's notion of the current date
 * 3.eg:access control (access to resources)
 * 4.eg:being able to read or write a particular file
 * 5.control access through changing userid and groupid
 */
/**
 * least-privilege model
 * use the least privilege necessary to accomplish any given task
 */
/**
 * THE THREE IDS IN TWO GROUP
 * (real, effective, saved set-) * (user, group)
 *  real user id  &&  real group id
 *  effective user id  &&  effective user id
 *  saved set-user-id  &&  saved set-user-id
 */
/**
 * FUNCTION PROTOTYPE
 * #include<unistd.h>
 * int setuid(uid_t uid);
 * int setgid(gid_t gid);
 * returns: zero if OK, minus one on error
 */
/**
 * FUNCTION PROTOTYPE
 * #include<unistd.h>
 * int setreuid(uid_t ruid, uid_t euid);
 * int setregid(uid_t rgid, uid_t egid);
 * returns: zero if OK, minus one on error
 */
/**
 * FUNCTION PROTOTYPE
 * #include<unistd.h>
 * int seteuid(uid_t uid);
 * int setegid(gid_t gid);
 * returns: zero if OK, minus one on error
 */
/**
 * RULES FOR WHO CAN CHANGE 'IDS'
 * CONDTIONS:
 * COND1:process has superuser privilege
 * COND2:uid is either real user id or saved set-user-id && !COND1
 * COND3:!COND1 && !COND2
 * RESULTS:
 * IFCOND1:set real user id, effective user id and saved set-user-id to uid
 * IFCOND2:only set effective user id; read user id and saved set-user-id not changed
 * IFCOND3:errno is set to EPERM, return 1
 * ASSUMING _POSIX_SAVED_IDS  is true
 */
/**
 * STATEMENTS ABOUT THE THREE USER IDS
 * 1.only superuser process can change the real user id;
 * 2.effective user id is set by exec functions only if the set-user-id bit is set for the program file;
 * 3.saved set-user-id is copied from effective user id by exec;
 */

