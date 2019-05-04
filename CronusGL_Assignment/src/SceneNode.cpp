#include "SceneNode.h"



SceneNode::SceneNode(Model* model, glm::vec3 position, Rotation rotation, glm::vec3 scale)
{
	_Parent = nullptr;

	this->_Model = model;
	_Position = position;
	_Rotation = rotation;
	_Scale = scale;
	_WorldTransformMatrix = glm::mat4(1.0f);
	_LocalTransformMatrix = glm::mat4(1.0f);
	

	ComputeLocalTransformMatrix();
}


SceneNode::~SceneNode()
{
	Destroy();
}

void SceneNode::Update()
{

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

void SceneNode::ComputeLocalTransformMatrix()
{
	_LocalTransformMatrix = glm::translate(_LocalTransformMatrix, _Position);
	_LocalTransformMatrix = glm::rotate(_LocalTransformMatrix, glm::radians(_Rotation.Angle), _Rotation.Axis);
	_LocalTransformMatrix = glm::scale(_LocalTransformMatrix, _Scale);
}
