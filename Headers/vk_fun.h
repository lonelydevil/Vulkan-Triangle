#ifndef VK_FUN_H
#define VK_FUN_H

#include "std_c.h"
#include "ext.h"

VkInstance createInstance();
void deleteInstance(VkInstance *pInstance);

uint32_t getPhysicalDeviceNumber(VkInstance *pInstance);
VkPhysicalDevice *getPhysicalDevices(VkInstance *pInstance, uint32_t physicalDeviceNumber);
void deletePhysicalDevices(VkPhysicalDevice **ppPhysicalDevices);

uint32_t getBestPhysicalDeviceIndex(VkPhysicalDevice *pPhysicalDevices, uint32_t physicalDeviceNumber);
uint32_t getPhysicalDeviceTotalMemory(VkPhysicalDeviceMemoryProperties *pPhysicalDeviceMemoryProperties);

uint32_t getqueueFamilyNumber(VkPhysicalDevice *pPhysicalDevice);
VkQueueFamilyProperties *getQueueFamilyProperties(VkPhysicalDevice *pPhysicalDevice, uint32_t queueFamilyNumber);
void deleteQueueFamilyProperties(VkQueueFamilyProperties **ppQueueFamilyProperties);

VkDevice createDevice(VkPhysicalDevice *pPhysicalDevice, uint32_t queueFamilyNumber, VkQueueFamilyProperties *pQueueFamilyProperties);
void deleteDevice(VkDevice *pDevice);

uint32_t getBestGraphicsQueueFamilyindex(VkQueueFamilyProperties *pQueueFamilyProperties, uint32_t queueFamilyNumber);
uint32_t getGraphicsQueueMode(VkQueueFamilyProperties *pQueueFamilyProperties, uint32_t graphicsQueueFamilyindex);
VkQueue getDrawingQueue(VkDevice *pDevice, uint32_t graphicsQueueFamilyindex);
VkQueue getPresentingQueue(VkDevice *pDevice, uint32_t graphicsQueueFamilyindex, uint32_t graphicsQueueMode);

VkSurfaceKHR createSurface(GLFWwindow *pWindow, VkInstance *pInstance);
void deleteSurface(VkSurfaceKHR *pSurface, VkInstance *pInstance);
VkBool32 getSurfaceSupport(VkSurfaceKHR *pSurface, VkPhysicalDevice *pPhysicalDevice, uint32_t graphicsQueueFamilyindex);

VkSurfaceCapabilitiesKHR getSurfaceCapabilities(VkSurfaceKHR *pSurface, VkPhysicalDevice *pPhysicalDevice);
VkSurfaceFormatKHR getBestSurfaceFormat(VkSurfaceKHR *pSurface, VkPhysicalDevice *pPhysicalDevice);
VkPresentModeKHR getBestPresentMode(VkSurfaceKHR *pSurface, VkPhysicalDevice *pPhysicalDevice);
VkExtent2D getBestSwapchainExtent(VkSurfaceCapabilitiesKHR *pSurfaceCapabilities, GLFWwindow *window);

VkSwapchainKHR createSwapChain(VkDevice *pDevice, VkSurfaceKHR *pSurface, VkSurfaceCapabilitiesKHR *pSurfaceCapabilities, VkSurfaceFormatKHR *pSurfaceFormat, VkExtent2D *pSwapchainExtent, VkPresentModeKHR *pPresentMode, uint32_t imageArrayLayers, uint32_t graphicsQueueMode);
void deleteSwapchain(VkDevice *pDevice, VkSwapchainKHR *pSwapchain);

uint32_t getSwapchainImageNumber(VkDevice *pDevice, VkSwapchainKHR *pSwapchain);
VkImage *getSwapchainImages(VkDevice *pDevice, VkSwapchainKHR *pSwapchain, uint32_t swapchainImageNumber);
void deleteSwapchainImages(VkImage **ppImages);

VkImageView *createImageViews(VkDevice *pDevice, VkImage **ppImages, VkSurfaceFormatKHR *pFormat, uint32_t imageNumber, uint32_t imageArrayLayers);
void deleteImageViews(VkDevice *pDevice, VkImageView **ppImageViews, uint32_t imageViewNumber);

VkRenderPass createRenderPass(VkDevice *pDevice, VkSurfaceFormatKHR *pFormat);
void deleteRenderPass(VkDevice *pDevice, VkRenderPass *pRenderPass);
VkFramebuffer *createFramebuffers(VkDevice *pDevice, VkRenderPass *pRenderPass, VkExtent2D *pExtent, VkImageView **ppImageViews, uint32_t imageViewNumber);
void deleteFramebuffers(VkDevice *pDevice, VkFramebuffer **ppFramebuffers, uint32_t framebufferNumber);

char *getShaderCode(const char *fileName, uint32_t *pShaderSize);
void deleteShaderCode(char **ppShaderCode);
VkShaderModule createShaderModule(VkDevice *pDevice, char *pShaderCode, uint32_t shaderSize);
void deleteShaderModule(VkDevice *pDevice, VkShaderModule *pShaderModule);

VkPipelineLayout createPipelineLayout(VkDevice *pDevice);
void deletePipelineLayout(VkDevice *pDevice, VkPipelineLayout *pPipelineLayout);
VkPipelineShaderStageCreateInfo configureVertexShaderStageCreateInfo(VkShaderModule *pVertexShaderModule, const char *entryName);
VkPipelineShaderStageCreateInfo configureFragmentShaderStageCreateInfo(VkShaderModule *pFragmentShaderModule, const char *entryName);
VkPipelineVertexInputStateCreateInfo configureVertexInputStateCreateInfo();
VkPipelineInputAssemblyStateCreateInfo configureInputAssemblyStateCreateInfo();
VkViewport configureViewport(VkExtent2D *pExtent);
VkRect2D configureScissor(VkExtent2D *pExtent, uint32_t left, uint32_t right, uint32_t up, uint32_t down);
VkPipelineViewportStateCreateInfo configureViewportStateCreateInfo(VkViewport *pViewport, VkRect2D *pScissor);
VkPipelineRasterizationStateCreateInfo configureRasterizationStateCreateInfo();
VkPipelineMultisampleStateCreateInfo configureMultisampleStateCreateInfo();
VkPipelineColorBlendAttachmentState configureColorBlendAttachmentState();
VkPipelineColorBlendStateCreateInfo configureColorBlendStateCreateInfo(VkPipelineColorBlendAttachmentState *pColorBlendAttachmentState);
VkPipeline createGraphicsPipeline(VkDevice *pDevice, VkPipelineLayout *pPipelineLayout, VkShaderModule *pVertexShaderModule, VkShaderModule *pFragmentShaderModule, VkRenderPass *pRenderPass, VkExtent2D *pExtent);
void deleteGraphicsPipeline(VkDevice *pDevice, VkPipeline *pGraphicsPipeline);

VkCommandPool createCommandPool(VkDevice *pDevice, uint32_t queueFamilyIndex);
void deleteCommandPool(VkDevice *pDevice, VkCommandPool *pCommandPool);
VkCommandBuffer *createCommandBuffers(VkDevice *pDevice, VkCommandPool *pCommandPool, uint32_t commandBufferNumber);
void deleteCommandBuffers(VkDevice *pDevice, VkCommandBuffer **ppCommandBuffers, VkCommandPool *pCommandPool, uint32_t commandBufferNumber);
void recordCommandBuffers(VkCommandBuffer **ppCommandBuffers, VkRenderPass *pRenderPass, VkFramebuffer **ppFramebuffers, VkExtent2D *pExtent, VkPipeline *pPipeline, uint32_t commandBufferNumber);

VkSemaphore *createSemaphores(VkDevice *pDevice, uint32_t maxFrames);
void deleteSemaphores(VkDevice *pDevice, VkSemaphore **ppSemaphores, uint32_t maxFrames);
VkFence *createFences(VkDevice *pDevice, uint32_t maxFrames);
void deleteFences(VkDevice *pDevice, VkFence **ppFences, uint32_t maxFrames);
VkFence *createEmptyFences(uint32_t maxFrames);
void deleteEmptyFences(VkFence **ppFences);

void presentImage(VkDevice *pDevice, GLFWwindow *window, VkCommandBuffer *pCommandBuffers, VkFence *pFrontFences, VkFence *pBackFences, VkSemaphore *pWaitSemaphores, VkSemaphore *pSignalSemaphores, VkSwapchainKHR *pSwapchain, VkQueue *pDrawingQueue, VkQueue *pPresentingQueue, uint32_t maxFrames);

void testLoop(GLFWwindow *window);

#endif // VK_FUN_H
