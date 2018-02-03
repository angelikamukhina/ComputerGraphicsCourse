#ifndef INC_3DSCENE_SHADERSLOADER_H
#define INC_3DSCENE_SHADERSLOADER_H

#include <GL/glew.h>

class ShadersLoader {
public:
    static GLuint LoadShaders(const char* vertex_file_path, const char * fragment_file_path);
};

#endif //INC_3DSCENE_SHADERSLOADER_H
