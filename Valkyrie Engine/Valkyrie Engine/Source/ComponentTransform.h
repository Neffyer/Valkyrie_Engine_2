#pragma once
#include "Component.h"
#include "../External/MathGeoLib/include/MathGeoLib.h"
#include "glmath.h"


class ComponentTransform : public Component {

public:
	void Enable() override;
	void Update() override;
	void Disable() override;
	void OnEditor() override;

	void inline SetWorldPosition(float3 position);
	void inline SetWorldRotation(Quat rotation);
	void inline SetWorldScale(float3 scale);
	void inline SetWorldRotationEuler(float3 rotation);

	void inline SetPosition(float3 position);
	void inline SetRotation(Quat rotation);
	void inline SetScale(float3 scale);
	void inline SetRotationEuler(float3 rotation);

	float3 inline GetPosition() const { return this->world_position; };
	Quat inline GetRotation() const { return this->world_rotation; };
	float3 inline GetScale() const { return this->world_scale; };
	float4x4 inline GetTransformMatrix() const { return this->world_matrix; };

	float3 GetScale();

	ComponentTransform(GameObject* parent);
	ComponentTransform(GameObject* parent, float3 position, float3 scale, Quat rotation);

private:
	void RecalculateTransformHierarchy();

public:
	void UpdateMatrix(); 

	float3 world_position{ 0.0f, 0.0f, 0.0f };
	Quat world_rotation = Quat::FromEulerXYZ(0.0f, 0.0f, 0.0f);
	float3 world_rotation_euler{ 0.0f, 0.0f, 0.0f };
	float3 world_scale{ 1.0f, 1.0f, 1.0f };
	float4x4 world_matrix = float4x4::identity;

	float3 new_position{ 0.0f, 0.0f, 0.0f };
	Quat new_rotation = Quat::FromEulerXYZ(0.0f, 0.0f, 0.0f);
	float3 new_rotation_euler{ 0.0f, 0.0f, 0.0f };
	float3 new_scale{1.0f, 1.0f, 1.0f};
	float4x4 transformMatrix = float4x4::identity;
};