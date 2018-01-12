#ifndef CG_SHADERSLOADER_H
#define CG_SHADERSLOADER_H

#include <GL/glew.h>

class ShadersLoader {
public:
    static GLuint LoadShaders(const char* vertex_file_path, const char * fragment_file_path);
};


#endif //CG_SHADERSLOADER_H
