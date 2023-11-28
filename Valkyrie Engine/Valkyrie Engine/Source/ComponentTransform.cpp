#include "ComponentTransform.h"
#include "GameObject.h"

#include "../External/ImGUI/imgui.h"

ComponentTransform::ComponentTransform(GameObject* parent) : Component(parent)
{
	type = ComponentTypes::TRANSFORM;
	UpdateMatrix();

};

ComponentTransform::ComponentTransform(GameObject* parent, float3 position, float3 scale, Quat rotation) :
	Component(parent), world_scale(scale), world_rotation(rotation), world_position(position)
{

};

void ComponentTransform::Enable() {
	if (!this->active) {
		this->active = true;
		//ON ENABLE CODE
	}
}

void ComponentTransform::Disable() {
	if (this->active) {
		this->active = false;
		//ON DISABLE CODE
	}
}

void ComponentTransform::Update() {

}

inline void ComponentTransform::SetWorldRotation(Quat rotation)
{
	Quat parentWorldRotation = Quat::identity;

	if (_parent->parent != nullptr)
	{
		parentWorldRotation = _parent->parent->transform->world_rotation;
	}

	Quat parentWorldRotationInverse = parentWorldRotation;
	parentWorldRotationInverse.Inverse();

	Quat newLocalRotation = rotation.Mul(parentWorldRotation);
	SetRotation(newLocalRotation);

}

inline void ComponentTransform::SetWorldScale(float3 scale)
{
	float3 parentWorldScale = float3::one;

	if (_parent->parent != nullptr)
	{
		parentWorldScale = _parent->parent->transform->world_scale;
	}

	float3 newLocalScale = scale - parentWorldScale;
	SetScale(newLocalScale);

}

inline void ComponentTransform::SetWorldRotationEuler(float3 rotation)
{
	Quat quaternion = Quat::FromEulerXYZ(rotation.x, rotation.y, rotation.z);
	SetWorldRotation(quaternion);
}

inline void ComponentTransform::SetPosition(float3 position)
{
	this->new_position = position;
	UpdateMatrix();
	RecalculateTransformHierarchy();
}

inline void ComponentTransform::SetRotation(Quat rotation)
{
	this->new_rotation = rotation;
	this->new_rotation_euler = new_rotation.ToEulerXYX();
	UpdateMatrix();
	RecalculateTransformHierarchy();
}

inline void ComponentTransform::SetScale(float3 scale)
{
	this->new_scale = scale;
	UpdateMatrix();
	RecalculateTransformHierarchy();
}

inline void ComponentTransform::SetRotationEuler(float3 rotation)
{
	new_rotation_euler = rotation;
	new_rotation = Quat::FromEulerXYZ(rotation.x, rotation.y, rotation.z);
	UpdateMatrix();
	RecalculateTransformHierarchy();
}

float3 ComponentTransform::GetScale()
{
	return world_scale;
}

void ComponentTransform::UpdateMatrix() {

	transformMatrix = float4x4::FromTRS(new_position, new_rotation, new_scale);
}

void ComponentTransform::RecalculateTransformHierarchy()
{
	std::vector<ComponentTransform*> torecalculate;

	torecalculate.push_back(this);

	while (!torecalculate.empty())
	{
		ComponentTransform* recalculate = *torecalculate.begin();

		torecalculate.erase(torecalculate.begin());

		for (std::vector<GameObject*>::iterator dt = recalculate->_parent->children.begin(); dt != recalculate->_parent->children.end(); dt++)
		{
			torecalculate.push_back((*dt)->transform);
		}

		float4x4 parentWorldMatrix = float4x4::identity;

		if (recalculate->_parent->parent != nullptr)
		{
			parentWorldMatrix = recalculate->_parent->parent->transform->world_matrix;
		}
		recalculate->world_matrix = parentWorldMatrix * recalculate->transformMatrix;

		recalculate->world_matrix.Decompose(world_position, world_rotation, world_scale);
		this->world_rotation_euler = world_rotation.ToEulerXYZ();
	}
}

void ComponentTransform::OnEditor() {
	
	if (ImGui::CollapsingHeader("Component Transform"))
	{
		float3 new_world_position = new_position;
		float3 new_world_scale = new_scale;
		float3 euler_degree = new_rotation_euler * RADTODEG;

		bool pos_change = ImGui::DragFloat3("Position:", (float*)&new_world_position);
		bool scale_change = ImGui::DragFloat3("Scale:", (float*)&new_world_scale);
		bool rot_change = ImGui::DragFloat3("Rotation:", (float*)&euler_degree);
		
		if (pos_change)
		{
			SetPosition(new_world_position);
		}
		if (scale_change)
		{
			SetScale(new_world_scale);
		}

		if (rot_change)
		{
			euler_degree = euler_degree * DEGTORAD;

			SetRotationEuler(euler_degree);
		}
	}
}


