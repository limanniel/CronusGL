#include "SceneNode.h"



SceneNode::SceneNode(Model* model)
{
	_Parent = nullptr;

	this->_Model = model;
	_Rotation = Rotation();
	_Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	_WorldTransformMatrix = glm::mat4(1.0f);
	_LocalTransformMatrix = glm::mat4(1.0f);
}


SceneNode::~SceneNode()
{
	Destroy();
}

void SceneNode::Update()
{
	_LocalTransformMatrix = ComputeLocalTransformMatrix();

	// Cumulate transformations 
	if (_Parent)
	{
		_WorldTransformMatrix = _Parent->_WorldTransformMatrix * _LocalTransformMatrix;
	}
	else
	{
		_WorldTransformMatrix = _LocalTransformMatrix;
	}

	// Loop through all Children/Siblings in PreOrder manner
	for (std::list<SceneNode*>::iterator i = _Child.begin(); i != _Child.end(); i++)
	{
		(*i)->Update();
	}
	for (std::list<SceneNode*>::iterator i = _Sibling.begin(); i != _Sibling.end(); i++)
	{
		(*i)->Update();
	}
}

void SceneNode::Render()
{
	for (std::list<SceneNode*>::iterator i = _Child.begin(); i != _Child.end(); i++)
	{
		(*i)->Render();
	}
	for (std::list<SceneNode*>::iterator i = _Sibling.begin(); i != _Sibling.end(); i++)
	{
		(*i)->Render();
	}
}

void SceneNode::Release()
{
	delete this;
}

void SceneNode::Destroy()
{
	for (std::list<SceneNode*>::iterator i = _Child.begin(); i != _Child.end(); i++)
	{
		(*i)->Release();
	}
	for (std::list<SceneNode*>::iterator i = _Sibling.begin(); i != _Sibling.end(); i++)
	{
		(*i)->Release();
	}
}

void SceneNode::AddChild(SceneNode* node)
{
	_Child.push_back(node);
	node->_Parent = this;
}

void SceneNode::AddSibling(SceneNode* node)
{
	_Sibling.push_back(node);
	node->_Parent = this->_Parent;
}

glm::mat4 SceneNode::ComputeLocalTransformMatrix()
{
	glm::mat4 tempMat = glm::translate(tempMat, _Position);
	tempMat = glm::rotate(tempMat, glm::radians(_Rotation.Angle), _Rotation.Axis);
	tempMat = glm::scale(tempMat, _Scale);
	return tempMat;
}
