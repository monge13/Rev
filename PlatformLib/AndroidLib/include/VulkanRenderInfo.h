#ifndef __VULKANRENDERINFO_H__
#define __VULKANRENDERINFO_H__

#ifdef _USE_VULKAN

#include "VulkanDeviceContext.h"
#include "VulkanSwapChain.h"
#include "VulkanShader.h"

class VulkanRenderInfo
{
public:
    bool Create(const VulkanDeviceContext& deviceContext, const VulkanSwapChain& swapChain);
    void Destroy(const VulkanDeviceContext& deviceContext);

    bool CreatePipeline(const VulkanDeviceContext& deviceContext, const VulkanSwapChain& swapChain, const VulkanShader& vertexShader, const VulkanShader& fragmentShader);

    const VkRenderPass& GetRenderPass() const { return renderPass; }
    const VkSemaphore& GetSemaphore() const { return semaphore; }
    const VkFence& GetFence() const { return fence; }
    const VkPipeline& GetPipeline() const { return pipeline; }
private:
    VkRenderPass renderPass;
    VkSemaphore  semaphore;
    VkFence fence;

    // pipeline
    VkPipelineLayout pipelineLayout;
    VkPipelineCache pipelineCache;
    VkPipeline  pipeline;

};

#endif
#endif
