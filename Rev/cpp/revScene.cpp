#include "revScene.h"


void revScene::Load()
{
	revResourceManager& mgr = revResourceManager::Get();

	uint32 shaderResourceCount = static_cast<uint32>(shaderResources.size());
	uint32 textureResourceCount = static_cast<uint32>(textureResources.size());
	uint32 materialResourceCount = static_cast<uint32>(materialResources.size());
	uint32 modelResourceCount = static_cast<uint32>(modelResources.size());

	resources.reserve(shaderResourceCount + textureResourceCount + materialResourceCount + modelResourceCount);

	for (uint32 i = 0; i < shaderResourceCount; ++i) {
		revResource* r = mgr.Load<revShader>(shaderResources[i].c_str());
		resources.push_back(r);
	}

	for (uint32 i = 0; i < textureResourceCount; ++i) {
		revResource* r = mgr.Load<revTexture>(textureResources[i].c_str());
		resources.push_back(r);
	}

	for (uint32 i = 0; i < materialResourceCount; ++i) {
		revResource* r = mgr.Load<revShader>(materialResources[i].c_str());
		resources.push_back(r);
	}

	for (uint32 i = 0; i < modelResourceCount; ++i) {
		revResource* r = mgr.Load<revModel>(modelResources[i].c_str());
		resources.push_back(r);
	}

}

void revScene::Destroy()
{
	uint32 resourceCount = static_cast<uint32>(resources.size());
	for (uint32 i = 0; i < resourceCount; ++i) {
		resources[i]->Destroy();
	}
}