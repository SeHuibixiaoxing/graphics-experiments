#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class ModelMat
{
public:
    ModelMat();

    glm::mat4 getComposite();
    glm::mat4 getCompositeExceptZoom();
    glm::quat getRotate();
    glm::mat4 getTranslate();
    glm::mat4 getZoom();
    void setRotate(const glm::quat& _rotate);
    void setTranslate(const glm::mat4& _translate);
    void setZoom(const glm::mat4& _zoom);
    void init();
private:
    glm::quat rotate;
    glm::mat4 translate;
    glm::mat4 zoom;
};

