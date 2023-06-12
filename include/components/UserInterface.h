#pragma once
#ifndef RISE_USERINTERFACE_H
#define RISE_USERINTERFACE_H

#include <tkev3.h>

class UserInterface : public Entity {
public:
    using Entity::Entity;
    [[nodiscard]] const bool canHaveChildren() const final { return false; }
};

#endif // RISE_USERINTERFACE_H
