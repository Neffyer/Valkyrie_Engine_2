#ifndef MODULE_SCENE
#define MODULE_SCENE

#include "Module.h"
#include "Globals.h"
#include "GameObject.h"
#include <vector>


class ModuleScene : public Module
{
public:
	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();

	bool Init() override;
	update_status Update();
	bool CleanUp();

	GameObject* CreateGameObject(std::string name);
	std::vector<GameObject*> GetGameObjects();

public:
	std::vector<GameObject*> game_objects;
	GameObject* root_object = nullptr;
};






#endif //MODULE_IMPORTER
