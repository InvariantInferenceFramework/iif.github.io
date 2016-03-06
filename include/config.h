/** @file config.h
 *  @brief Provide most configuration information for the whole project. 
 *
 *  This file contains most of the setting which are used to customize the project.
 *
 *  @author Li Jiaying
 *  @bug No known bugs. 
 */
#ifndef _CONFIG_H_
#define _CONFIG_H_


/**  @brief defines the number of paramenters by a given loop,\
 *		   This also is the number of parameters we need to record for processing.
 *		   This should be set in /CMakeLists.txt file
 *		   If it is not set correctly, you may come across a runtime error
 */
#define Nv 1 

 /*#define Cv(i) do {int return_num##i = 1;\
 for (int tempi = 0; tempi < i; i++) return_num##i *= (Nv + i);\
 for (int tempi = 0; tempi < i; i++) return_num##i /= (1 + i);\
 } while(0);
 #define Cv1to1 (Cv(1))
 #define Cv1to2 (Cv(1) + Cv(2))
 #define Cv1to3 (Cv(1) + Cv(2) + Cv(3))
 #define Cv1to4 (Cv(1) + Cv(2) + Cv(3) + Cv(4))
 */

#define Cv0 (1)
#define Cv1 (Nv)
#define Cv2 (Nv * (Nv + 1) / (1 * 2))
#define Cv3 (Nv * (Nv + 1) * (Nv + 2) / (1 * 2 * 3)) 
#define Cv4 (Nv * (Nv + 1) * (Nv + 2) * (Nv + 3) / (1 * 2 * 3 * 4))

#define Cv1to1 (Cv1)
#define Cv1to2 (Cv1 + Cv2)
#define Cv1to3 (Cv1 + Cv2 + Cv3) 
#define Cv1to4 (Cv1 + Cv2 + Cv3 + Cv4) 

#define Cv0to1 (Cv0 + Cv1)
#define Cv0to2 (Cv0 + Cv1 + Cv2)
#define Cv0to3 (Cv0 + Cv1 + Cv2 + Cv3) 
#define Cv0to4 (Cv0 + Cv1 + Cv2 + Cv3 + Cv4)

/*#define _Cv1to(n) Cv1to##n
#define Cv1to(n) _Cv1to(n)
*/



/** @brief is a integer, which defines precision as pow(10, -PRECISION)  
 *		   This should be set in /CMakeLists.txt file
 *		   You'd better set this value in a scope [1, 12] 
 */
#define PRECISION 3

/** @brief The pointer to test program, DO NOT assign directly
 *		   Call register_program to set its value
 */
extern int (*target_program) (int*);

/** @brief defines the initial max number items contains by states set. 
 *		   Better to be a number larger than 1000 
 */
const int Mitems = 10000000;

/** @brief defines max number of states contains in one executionn. 
 *		   Better to be a number larger than 128 
 */
const int MstatesIn1trace = 10240;

/** @brief defines the number of tests runs initially. Should be a positive integer.
 */
const int Nexe_init = 16 * Nv;

/** @brief defines the number of tests runs after the first time. Should be a positive integer.
 */
static int Nexe_after = 16 * Nv;

/** @brief defines the number of random tests runs each time, 
 *		   which is used to avoid bias caused by tests picking chioce. 
 *		   Should be a non-negative integer.
 */
const int Nexe_rand = 4 * Nv;

/** @brief defines the max number of iterations tried by machine learning algorithm, 
 *		   Should be a positive integer. Usually set between 8-128
 */
const int Miter = 512;

/** @brief This function register the test program to the framework.
 *
 *	@param func The function to be tested
 *		   It involves a small validation test on the given function.
 *  @param fun_name defines the function name, can be ignored, or set to NULL
 *  @return a boolean value false only when the given function is not valid.
 */
// legacy function, can be removed after all the test modification
bool register_program(int (*func)(int*), const char* func_name = 0);

/** @brief defines the timeout signal handler 
 */
// legacy function, can be removed after all the test modification
//void sig_alrm(int signo);

#endif
