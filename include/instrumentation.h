/** @file instrumentation.h
 *  @brief Provide instrumentation function support for the framework.
 *
 *  @author Li Jiaying
 *  @bug No known bugs 
 */
#ifndef _INSTRUMENTATION_H_
#define _INSTRUMENTATION_H_
#include "config.h"
#include "states.h"
#include <stdarg.h>

/** \enum trace_type
 * @brief Contains all the FOUR trace typies here. Negative, Quesion, Positive and Counter_example
 *
 * Negative = -1 because we want to compatible with natural meaning and svm labels.
 *				 This also cause a problem to reassign states point in each test file which is ugly
 */
enum trace_type{ NEGATIVE = -1, QUESTION, POSITIVE, COUNTER_EXAMPLE };	/* trace_type */


int addStateInt(int first, ...);
int addStateDouble(double first, ...);

/// record furntions for each platform
#if WIN32  
	#define recordi(first, ...) addStateInt(first, ##__VA_ARGS__)
	#define recordd(first, ...) addStateDouble(first, ##__VA_ARGS__)
#elif (linux ||__MACH__) 
	#define recordi(first, args ...) addStateInt(first, ##args)
	#define recordd(first, args ...) addStateDouble(first, ##args)
#endif

/** @brief function jump list, DONOT use it unless you know what you are doing
 */
int mInt(int*);

/** @brief function jump list, DONOT use it unless you know what you are doing
 */
int mDouble(double*);


/** @brief This function should be called each time before executing loop
 *
 * @param void
 * @return void
 */
int beforeLoop();

/** @brief This function should be called each time after executing loop
 *
 * @param void
 * @return void
 */
int afterLoop(States *);

#endif
