/** @file color.h
 *  @brief Provide support for colorful console ouput.
 *
 *  This file contains the necessary function support for colorful console text output.
 *  The usage is also simple. Before you output something, call function set_console_color.
 *  And remember to call unset_console_color after your output.
 *
 *  @author Li Jiaying
 *  @bug unset_console_color is set the console back to black background, white forground, no strong comparision
 *		instead of the previous setting.
 */
#ifndef _COLOR_H_
#define _COLOR_H_
#include <iostream>

/** @brief This enumeration contains all the colors predifined in project.
 *  Here we only introduce RED, YELLOW, GREEN, BLUE, WHITE 
 *  which is enough for our output.
 *  You can import more color if you want.
 */
enum Color {RED = 0, YELLOW, GREEN, BLUE, WHITE};

std::ostream& operator << (std::ostream& out, Color c);

/** @brief This function sets the given stream to the given color, YELLOW is default.
 *
 *  @param  out  The ostream to be changed, defines which stream you want to set
 *  @param  color The Color to set. YELLOW by default. 
 */
void setColor(std::ostream& out, int color = WHITE); 

#endif
