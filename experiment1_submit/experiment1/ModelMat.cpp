#include "ModelMat.h"

ModelMat::ModelMat()
{
    this->init();
}

glm::mat4 ModelMat::getComposite()
{
    return translate * glm::toMat4(rotate) * zoom;    
}

glm::mat4 ModelMat::getCompositeExceptZoom()
{
    return translate * glm::toMat4(rotate);
}

glm::quat ModelMat::getRotate()
{
    return this->rotate;
}

glm::mat4 ModelMat::getTranslate()
{
    return this->translate;
}

glm::mat4 ModelMat::getZoom()
{
    return this->zoom;
}

void ModelMat::setRotate(const glm::quat& _rotate)
{
    this->rotate = _rotate;
}

void ModelMat::setTranslate(const glm::mat4& _translate)
{
    this->translate = _translate;
}

void ModelMat::setZoom(const glm::mat4& _zoom)
{
    this->zoom = _zoom;
}

void ModelMat::init()
{
    this->translate = this->zoom = glm::mat4(1.0f);
    this->rotate = glm::quat(1, 0, 0, 0);
    this->translate = glm::translate(this->translate, glm::vec3(0.0f, 0.0f, 0.0f));
    this->zoom = glm::scale(this->zoom, glm::vec3(1.0f, 1.0f, 1.0f));
}
