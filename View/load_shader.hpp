/*
 * load_shader.h
 *
 *  Created on: 21/apr/2013
 *      Author: lorenzo
 */

#ifndef LOAD_SHADER_H_
#define LOAD_SHADER_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <GL/glew.h>

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);


#endif /* LOAD_SHADER_H_ */
