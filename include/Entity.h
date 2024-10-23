#pragma once
#include <Components.h>
#include <memory>

class Entity {
public:
	std::shared_ptr<CTransform> cTransform;
	std::shared_ptr<CRecShape> cRecShape;
	std::shared_ptr<CCirShape> cCirShape;
	std::shared_ptr<CInput> cInput;

	Entity();
};