#include "PARCMLoaderScreen.h"
#include "SceneManager.h"
#include "ObjectScene.h"

PARCMLoaderScreen::PARCMLoaderScreen(std::string name) : AUIScreen(name)
{
}

void PARCMLoaderScreen::drawUI()
{
	ImGui::Begin("PARCM Scene Loader");
	
	ImGui::Columns(3);

	for (int i = 0; i < 5; i++)
	{
		std::string stringName = "Scene" + std::to_string(i + 1);
		ImGui::Text(stringName.c_str());
		ImGui::Spacing();
		if (ImGui::Button(("Load##" + std::to_string(i)).c_str(), ImVec2(100, 0)))
		{
			SceneManager::Instance()->loadSceneByIndex(i);
		}
		ImGui::SameLine();
		if (ImGui::Button(("Unload##" + std::to_string(i)).c_str(), ImVec2(100, 0)))
		{
			SceneManager::Instance()->unloadSceneByIndex(i);
		}
		ImGui::SameLine();
		if (ImGui::Button(("Toggle##" + std::to_string(i)).c_str(), ImVec2(100, 0)))
		{
			SceneManager::Instance()->toggleSceneByIndex(i);
		}
		ImGui::Spacing();
	}

	ImGui::Text("Load All Scenes");
	ImGui::Spacing();
	if (ImGui::Button("Load##5", ImVec2(100, 0)))
	{
		SceneManager::Instance()->loadAllScenes();
	}
	ImGui::SameLine();
	if (ImGui::Button("Unload##5", ImVec2(100, 0)))
	{
		SceneManager::Instance()->unloadAllScenes();
	}
	ImGui::SameLine();
	if (ImGui::Button("Toggle##5", ImVec2(100, 0)))
	{
		SceneManager::Instance()->toggleAllScenes();
	}
	ImGui::Spacing();



	ImGui::NextColumn();
	//loading bars here
	if (dynamic_cast<ObjectScene*>(SceneManager::Instance()->getSceneList()[0])->maxObjects != 0 && SceneManager::Instance()->getSceneList()[0] != NULL)
	{
		ImGui::Text("Scene 1 Loading");
		float progress = (float)dynamic_cast<ObjectScene*>(SceneManager::Instance()->getSceneList()[0])->countLoaded / (float)dynamic_cast<ObjectScene*>(SceneManager::Instance()->getSceneList()[0])->maxObjects;
		ImGui::ProgressBar(progress, ImVec2(200.0f, 0.0f));
		if (progress == 1)
			dynamic_cast<ObjectScene*>(SceneManager::Instance()->getSceneList()[0])->hasLoaded = true;
	}
	if (dynamic_cast<ObjectScene*>(SceneManager::Instance()->getSceneList()[1])->maxObjects != 0 && SceneManager::Instance()->getSceneList()[1] != NULL)
	{
		ImGui::Text("Scene 2 Loading");
		float progress = (float)dynamic_cast<ObjectScene*>(SceneManager::Instance()->getSceneList()[1])->countLoaded / (float)dynamic_cast<ObjectScene*>(SceneManager::Instance()->getSceneList()[1])->maxObjects;
		ImGui::ProgressBar(progress, ImVec2(200.0f, 0.0f));
		if (progress == 1)
			dynamic_cast<ObjectScene*>(SceneManager::Instance()->getSceneList()[1])->hasLoaded = true;
	}
	if (dynamic_cast<ObjectScene*>(SceneManager::Instance()->getSceneList()[2])->maxObjects != 0 && SceneManager::Instance()->getSceneList()[2] != NULL)
	{
		ImGui::Text("Scene 3 Loading");
		float progress = (float)dynamic_cast<ObjectScene*>(SceneManager::Instance()->getSceneList()[2])->countLoaded / (float)dynamic_cast<ObjectScene*>(SceneManager::Instance()->getSceneList()[2])->maxObjects;
		ImGui::ProgressBar(progress, ImVec2(200.0f, 0.0f));
		if (progress == 1)
			dynamic_cast<ObjectScene*>(SceneManager::Instance()->getSceneList()[2])->hasLoaded = true;
	}
	if (dynamic_cast<ObjectScene*>(SceneManager::Instance()->getSceneList()[3])->maxObjects != 0 && SceneManager::Instance()->getSceneList()[3] != NULL)
	{
		ImGui::Text("Scene 4 Loading");
		float progress = (float)dynamic_cast<ObjectScene*>(SceneManager::Instance()->getSceneList()[3])->countLoaded / (float)dynamic_cast<ObjectScene*>(SceneManager::Instance()->getSceneList()[3])->maxObjects;
		ImGui::ProgressBar(progress, ImVec2(200.0f, 0.0f));
		if (progress == 1)
			dynamic_cast<ObjectScene*>(SceneManager::Instance()->getSceneList()[3])->hasLoaded = true;
	}
	if (dynamic_cast<ObjectScene*>(SceneManager::Instance()->getSceneList()[4])->maxObjects != 0 && SceneManager::Instance()->getSceneList()[4] != NULL)
	{
		ImGui::Text("Scene 5 Loading");
		float progress = (float)dynamic_cast<ObjectScene*>(SceneManager::Instance()->getSceneList()[4])->countLoaded / (float)dynamic_cast<ObjectScene*>(SceneManager::Instance()->getSceneList()[4])->maxObjects;
		ImGui::ProgressBar(progress, ImVec2(200.0f, 0.0f));
		if (progress == 1)
			dynamic_cast<ObjectScene*>(SceneManager::Instance()->getSceneList()[4])->hasLoaded = true;
	}

	ImGui::NextColumn();
	//scene info here
	ImGui::Text("Current Loaded Scene: testname\n");
	ImGui::Text("Number of objects: testnum\n");

	
	ImGui::End();
}
