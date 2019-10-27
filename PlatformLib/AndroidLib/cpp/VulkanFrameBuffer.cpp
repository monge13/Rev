#include "VulkanFrameBuffer.h"

#ifdef _USE_VULKAN

VulkanFrameBuffer::VulkanFrameBuffer() :
foramt(VK_FORMAT_A8B8G8R8_UINT_PACK32)
{
}

VulkanFrameBuffer::~VulkanFrameBuffer()
{
}

bool VulkanFrameBuffer::Create(const VulkanDeviceContext &deviceContext, const VulkanSwapChain &swapChain, const VulkanRenderInfo& renderInfo)
{
    foramt = swapChain.GetFormat();
    uint32 imageCount = 0;
    VkDevice device = deviceContext.GetDevice();
    VkSwapchainKHR  swapchain = swapChain.GetSwapChain();
    vkGetSwapchainImagesKHR(device, swapchain, &imageCount, nullptr);
    views.Resize(imageCount);
    vkGetSwapchainImagesKHR(device, swapchain, &imageCount, &images[0]);

    // create image view
    images.Resize(imageCount);
    for(uint i = 0; i < imageCount; ++i){
        VkImageViewCreateInfo viewCreateInfo = {
                .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
                .pNext = nullptr,
                .image = images[i],
                .viewType = VK_IMAGE_VIEW_TYPE_2D,
                .format = foramt,
                .components =
                        {
                            .r = VK_COMPONENT_SWIZZLE_R,
                            .g = VK_COMPONENT_SWIZZLE_G,
                            .b = VK_COMPONENT_SWIZZLE_B,
                            .a = VK_COMPONENT_SWIZZLE_A,
                        },
                .subresourceRange =
                        {
                            .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                            .baseMipLevel = 0,
                            .levelCount = 1,
                            .baseArrayLayer = 0,
                            .layerCount = 1
                        },
                .flags = 0,
        };
        VkResult result = vkCreateImageView(device, &viewCreateInfo, nullptr, &views[i]);
        if(result != VK_SUCCESS) return false;
    }

    // create framebuffer
    framebuffers.Resize(imageCount);
    for(int i = 0; i < imageCount; ++i){
        VkImageView  attachments[2] = {
                views[i],
                VK_NULL_HANDLE, // TODO: depth
        };
        VkExtent2D size = swapChain.GetDisplaySize();
        VkFramebufferCreateInfo framebufferCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
            .pNext = nullptr,
            .renderPass = renderInfo.GetRenderPass(),
            .layers = 1,
            .attachmentCount = 2, // if using depth set to 2
            .pAttachments = attachments,
            .width = size.width,
            .height = size.height,
        };

        VkResult result = vkCreateFramebuffer(device, &framebufferCreateInfo, nullptr, &framebuffers[i]);
        if(result != VK_SUCCESS) return false;
    }

    return true;
}

void VulkanFrameBuffer::Destroy(const VulkanDeviceContext& deviceContext)
{
    VkDevice device =  deviceContext.GetDevice();
    for(int i = 0; i < framebuffers.Count(); ++i){
        vkDestroyFramebuffer(device, framebuffers[i], nullptr);
        vkDestroyImageView(device, views[i], nullptr);
        vkDestroyImage(device, images[i], nullptr);
    }
}

#endif