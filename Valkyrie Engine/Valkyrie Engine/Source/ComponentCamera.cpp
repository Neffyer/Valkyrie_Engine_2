#include "ComponentCamera.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "Color.h"

ComponentCamera::ComponentCamera(GameObject* parent) : Component(parent)
{
	type = ComponentTypes::CAMERA;

}

void ComponentCamera::Enable()
{

}

void ComponentCamera::Update()
{
	
}

void ComponentCamera::Disable()
{

}

void ComponentCamera::OnEditor()
{


	if (ImGui::CollapsingHeader("Component Camera"))
	{

		

	}

}
