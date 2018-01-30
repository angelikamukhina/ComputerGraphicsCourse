#ifndef INC_3DSCENE_TRANSFORMHANDLER_H
#define INC_3DSCENE_TRANSFORMHANDLER_H

#include <glm/detail/type_mat.hpp>

class TransformHandler {
public:
    static void computeMatricesFromInputs();
    static glm::mat4 getViewMatrix();
    static glm::mat4 getProjectionMatrix();
};


#endif //INC_3DSCENE_TRANSFORMHANDLER_H
