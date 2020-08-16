#ifndef __VULKANSAMPLERVIEW_H__
#define __VULKANSAMPLERVIEW_H__

#include "revGraphicsResource.h"
#include "VulkanDescriptorSet.h"
#include "VulkanSampler.h"

class VulkanSamplerView : public revGraphicsResource
{
public:
	VulkanSamplerView(){}
    virtual ~VulkanSamplerView(){}

    void Create(revDevice* device, const VulkanSampler& sampler, VulkanDescriptorSet::Chunk& chunk);
    virtual void Destroy();
private:
	VkDescriptorImageInfo descriptorImageInfo;
};



#endif

