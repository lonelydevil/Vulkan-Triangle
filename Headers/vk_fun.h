/**
 * @file vk_fun.h
 * @brief This file contains the API for interacting with Vulkan API in our application
 * @authors lonelydevil nakira974
 * @date 24/02/2024
 */
#ifndef VK_FUN_H
#define VK_FUN_H

#include "std_c.h"
#include "ext.h"

/**
 * @brief Create a Vulkan instance to link current application with API
 * @param app_name Application name
 * @param app_version Application version
 * @param engine_name Engine name
 * @param engine_version Engine version
 * @return The new VkInstance from the API
 */
VkInstance createInstance(const char * app_name,uint32_t app_version, const char * engine_name, uint32_t engine_version);

/**
 * @brief Delete a linked Vulkan instance from the API
 * @param pInstance The Vulkan instance to be removed
 */
void deleteInstance(VkInstance *pInstance);

/**
 * @brief Fetch the current count of physical devices
 * @param pInstance Application Vulkan instance
 * @return The physical devices list
 */
uint32_t getPhysicalDeviceNumber(VkInstance *pInstance);

/**
 * @brief Fetch Vulkan compatible physical devices in
 * @param pInstance Application Vulkan instance
 * @param physicalDeviceNumber Physical devices list
 * @return Vulkan compatible physical devices list
 */
VkPhysicalDevice *getPhysicalDevices(VkInstance *pInstance, uint32_t physicalDeviceNumber);

/**
 * @brief Remove a VkPhysicalDevice struct instance
 * @param ppPhysicalDevices Vulkan compatible physical devices list to be removed
 */
void deletePhysicalDevices(VkPhysicalDevice **ppPhysicalDevices);

/**
 * @brief Choose the best physical device
 * @param pPhysicalDevices Vulkan compatible physical devices list
 * @param physicalDeviceNumber The physical devices list
 * @return Index of the best physical device
 */
uint32_t getBestPhysicalDeviceIndex(VkPhysicalDevice *pPhysicalDevices, uint32_t physicalDeviceNumber);

/**
 * @brief Fetch the total amount of memory for a given physical device
 * @param pPhysicalDeviceMemoryProperties Physical device memory properties
 * @return Amount of memory available for the given device
 */
uint32_t getPhysicalDeviceTotalMemory(VkPhysicalDeviceMemoryProperties *pPhysicalDeviceMemoryProperties);

/**
 * @brief Fetch the list of supported queues family for a given physical device
 * @param pPhysicalDevice The physical device to get queues family on
 * @return The list of supported queues family for the given device
 */
uint32_t getQueueFamilyNumber(VkPhysicalDevice *pPhysicalDevice);

/**
 * @brief Fetch the queue family properties for a given device and a given queue family
 * @param pPhysicalDevice The physical device to inspect queue family details
 * @param queueFamilyNumber The queue family to inspect details on
 * @return The details of the given queue family for the given device
 */
VkQueueFamilyProperties *getQueueFamilyProperties(VkPhysicalDevice *pPhysicalDevice, uint32_t queueFamilyNumber);

/**
 * @brief Delete a queue family properties array
 * @param ppQueueFamilyProperties The queue family properties to be destroyed
 */
void deleteQueueFamilyProperties(VkQueueFamilyProperties **ppQueueFamilyProperties);

/**
 * @brief Create a logical device
 * @param pPhysicalDevice Target physical device
 * @param queueFamilyNumber Chosen queue family
 * @param pQueueFamilyProperties Queue family properties for the given device and the chosen queue family
 * @return
 */
VkDevice createDevice(VkPhysicalDevice *pPhysicalDevice, uint32_t queueFamilyNumber, VkQueueFamilyProperties *pQueueFamilyProperties);

/**
 * @brief Destroy a logical device
 * @param pDevice The logical device to be destroyed
 */
void deleteDevice(VkDevice *pDevice);

/**
 * @brief Fetch the best graphics queue family for a given queue family
 * @param pQueueFamilyProperties Queue family properties for a given device and given family queue
 * @param queueFamilyNumber The queue family index
 * @return The chosen graphics family index
 */
uint32_t getBestGraphicsQueueFamilyindex(VkQueueFamilyProperties *pQueueFamilyProperties, uint32_t queueFamilyNumber);

/**
 * @brief Fetch the list of graphics queue mode for a given queue family
 * @param pQueueFamilyProperties Queue family properties for a given device and given family queue
 * @param graphicsQueueFamilyindex Chosen graphics family index for a given queue family
 * @return
 */
uint32_t getGraphicsQueueMode(VkQueueFamilyProperties *pQueueFamilyProperties, uint32_t graphicsQueueFamilyindex);

/**
 * @brief Allocate a queue for drawing operations
 * @param pDevice The target logical device where to allocate the queue
 * @param graphicsQueueFamilyindex Chosen queue family index
 * @return The application drawing queue
 */
VkQueue getDrawingQueue(VkDevice *pDevice, uint32_t graphicsQueueFamilyindex);

/**
 * @brief Allocate a queue for presenation operations
 * @param pDevice The target logical device where to allocate the queue
 * @param graphicsQueueFamilyindex Chosen queue family index
 * @param graphicsQueueMode Chosen graphics queue mode
 * @return The application presentation queue
 */
VkQueue getPresentingQueue(VkDevice *pDevice, uint32_t graphicsQueueFamilyindex, uint32_t graphicsQueueMode);

/**
 * @brief Create a Vulkan surface for a given GLFW window
 * @param pWindow The window to bet set in the Vulkan surface
 * @param pInstance Application Vulkan instance
 * @return The created Vulkan surface
 */
VkSurfaceKHR createSurface(GLFWwindow *pWindow, VkInstance *pInstance);

/**
 * @brief Destroy a Vulkan surface with its associated window
 * @param pSurface The Vulkan surface to be removed
 * @param pInstance Application Vulkan instance
 */
void deleteSurface(VkSurfaceKHR *pSurface, VkInstance *pInstance);

/**
 * @brief Fetch if the current platform does support Vulkan surface
 * @param pSurface The target surface to check if it's supported or not
 * @param pPhysicalDevice Physical device to lookup on
 * @param graphicsQueueFamilyindex Chosen queue family index
 * @return True if the physical device and the chosen family queue are supporting Vulkan surface, otherwise false
 */
VkBool32 getSurfaceSupport(VkSurfaceKHR *pSurface, VkPhysicalDevice *pPhysicalDevice, uint32_t graphicsQueueFamilyindex);

/**
 * @brief Fetch the current Vulkan surface capabilities (minimum length, supported colors...)
 * @param pSurface Target surface to get capabilities
 * @param pPhysicalDevice Target physical device where the surface is allocated
 * @return Current surface capabilities for the given physical device
 */
VkSurfaceCapabilitiesKHR getSurfaceCapabilities(VkSurfaceKHR *pSurface, VkPhysicalDevice *pPhysicalDevice);

/**
 * @brief Fetch the best surface format for rendering on a given surface
 * @param pSurface Target surface to get the best format on
 * @param pPhysicalDevice  Target physical device where the surface is allocated
 * @return The best surface format for the given surface
 */
VkSurfaceFormatKHR getBestSurfaceFormat(VkSurfaceKHR *pSurface, VkPhysicalDevice *pPhysicalDevice);

/**
 * @brief Fetch the best presentation mode for rendering on a given surface
 * @param pSurface Target surface to get the best presentation mode on
 * @param pPhysicalDevice Target physical device where is allocated the surface
 * @return The best present mode for the given surface
 */
VkPresentModeKHR getBestPresentMode(VkSurfaceKHR *pSurface, VkPhysicalDevice *pPhysicalDevice);

/**
 * @brief Fetch the best swapchain extent for a given surface capabilities and window
 * @param pSurfaceCapabilities Capabilities of the surface for the given window
 * @param window Target window of the swap chain
 * @return  The best swap chain extention for the given surface and window
 */
VkExtent2D getBestSwapchainExtent(VkSurfaceCapabilitiesKHR *pSurfaceCapabilities, GLFWwindow *window);

/**
 * @brief Create a swapchain with the specified parameters
 * @param pDevice Target logical device
 * @param pSurface Target surface
 * @param pSurfaceCapabilities - Target surface capabilities
 * @param pSurfaceFormat Target surface best format
 * @param pSwapchainExtent Chosen swap chain extensions for the given capabilities
 * @param pPresentMode Chosen surface presentation mode
 * @param imageArrayLayers Number of image array layers
 * @param graphicsQueueMode Chosen graphics queue mode for the given queue family
 * @return The created swap chain object
 */
VkSwapchainKHR createSwapChain(VkDevice *pDevice, VkSurfaceKHR *pSurface, VkSurfaceCapabilitiesKHR *pSurfaceCapabilities, VkSurfaceFormatKHR *pSurfaceFormat, VkExtent2D *pSwapchainExtent, VkPresentModeKHR *pPresentMode, uint32_t imageArrayLayers, uint32_t graphicsQueueMode);

/**
 * @brief Destroy the given swap chain
 * @param pDevice Target logical device
 * @param pSwapchain Target swap chain
 */
void deleteSwapchain(VkDevice *pDevice, VkSwapchainKHR *pSwapchain);

/**
 * @brief Fetch the number of images in a given swapchain
 * @param pDevice Target logical device
 * @param pSwapchain Target swap chain
 * @return The number current of images in the swapchain
 */
uint32_t getSwapchainImageNumber(VkDevice *pDevice, VkSwapchainKHR *pSwapchain);

/**
 * @brief Fetch an array of images in a given swapchain
 * @param pDevice Target logical device
 * @param pSwapchain Target swap chain
 * @param swapchainImageNumber Number of images in the swap chain
 * @return Pointer to the array of images in the swap chain
 */
VkImage *getSwapchainImages(VkDevice *pDevice, VkSwapchainKHR *pSwapchain, uint32_t swapchainImageNumber);

/**
 * @brief Delete the array of images in a given swap chain
 * @param ppImages Pointer to the pointer of the array of images
 */
void deleteSwapchainImages(VkImage **ppImages);

/**
 * @brief Create an array of image views for a given set of images
 * @param pDevice Target logical device
 * @param ppImages Pointer to the pointer of the array of images
 * @param pFormat Chosen surface format
 * @param imageNumber Number of images in the given array
 * @param imageArrayLayers Number of array layers for each image
 * @return Pointer to the array of image views
 */
VkImageView *createImageViews(VkDevice *pDevice, VkImage **ppImages, VkSurfaceFormatKHR *pFormat, uint32_t imageNumber, uint32_t imageArrayLayers);

/**
 * @brief Destroy an array of images view
 * @param pDevice Target logical device
 * @param ppImageViews Pointer to the pointer of the array of image view
 * @param imageViewNumber Number of image views in the given array
 */
void deleteImageViews(VkDevice *pDevice, VkImageView **ppImageViews, uint32_t imageViewNumber);

/**
 * @brief Create a Vulkan render pass.
 * @param pDevice Target logical device
 * @param pFormat Chosen surface format
 * @return The created render pass
 */
VkRenderPass createRenderPass(VkDevice *pDevice, VkSurfaceFormatKHR *pFormat);

/**
 * @brief Destroy a Vulkan render pass.
 * @param pDevice Target logical device
 * @param pRenderPass Render pass to be destroyed
 */
void deleteRenderPass(VkDevice *pDevice, VkRenderPass *pRenderPass);

/**
 * @brief Create Vulkan framebuffers for rendering.
 * @param pDevice Target logical device
 * @param pRenderPass Target render pass
 * @param pExtent Frame buffers extensions
 * @param ppImageViews Pointer to an array of image views
 * @param imageViewNumber Number of image views in the given array
 * @return Pointer to the created framebuffers
 */
VkFramebuffer *createFramebuffers(VkDevice *pDevice, VkRenderPass *pRenderPass, VkExtent2D *pExtent, VkImageView **ppImageViews, uint32_t imageViewNumber);

/**
 * @brief Delete Vulkan framebuffers.
 * @param pDevice - Pointer to the Vulkan device
 * @param ppFramebuffers - Pointer to an array of framebuffers
 * @param framebufferNumber - Number of framebuffers
 */
void deleteFramebuffers(VkDevice *pDevice, VkFramebuffer **ppFramebuffers, uint32_t framebufferNumber);

/**
 * @brief Retrieve the shader code from a file.
 * @param fileName The name of the file containing the shader code
 * @param pShaderSize Pointer to the size of the shader code
 * @return Pointer to the retrieved shader code
 */
char *getShaderCode(const char *fileName, uint32_t *pShaderSize);

/**
 * @biref Delete the shader code.
 * @param ppShaderCode Pointer to the shader code
 */
void deleteShaderCode(char **ppShaderCode);

/**
 * Create a Vulkan shader module from the shader code.
 *
 * @param pDevice Target logical device
 * @param pShaderCode Pointer to the shader code
 * @param shaderSize Size of the shader code
 * @return The created shader module
 */
VkShaderModule createShaderModule(VkDevice *pDevice, char *pShaderCode, uint32_t shaderSize);

/**
 * @brief Destroy a Vulkan shader module
 * @param pDevice Target logical device
 * @param pShaderModule Pointer to the shader module to be destroyed
 */
void deleteShaderModule(VkDevice *pDevice, VkShaderModule *pShaderModule);

/**
 * @brief Create a Vulkan pipeline layout.
 * @param pDevice Target logical device
 * @see A pipeline layout defines the interface between the shader stages and the pipeline resources. It specifies the layout of the descriptor sets and the push constant ranges used by the shaders.
 * @return The created pipeline layout
 */
VkPipelineLayout createPipelineLayout(VkDevice *pDevice);

/**
 * @brief Delete a Vulkan pipeline layout.
 * @param pDevice Target logical device
 * @param pPipelineLayout Pointer to the pipeline layout to be deleted
 */
void deletePipelineLayout(VkDevice *pDevice, VkPipelineLayout *pPipelineLayout);

/**
 * @brief Configure the vertex shader stage create info for a Vulkan pipeline.
 * @param pVertexShaderModule Pointer to the vertex shader module
 * @param entryName Name of the entry point function in the vertex shader
 * @return The configured shader stage create info
 * @see Set up the necessary information for the vertex shader stage, such as the shader module and the entry point function, which will be used during the pipeline creation process
 */
VkPipelineShaderStageCreateInfo configureVertexShaderStageCreateInfo(VkShaderModule *pVertexShaderModule, const char *entryName);

/**
 * @brief Configure the fragment shader stage create info for a Vulkan pipeline.
 * @param pFragmentShaderModule Pointer to the fragment shader module
 * @param entryName Name of the entry point function in the fragment shader
 * @return The configured shader stage create info
 * @see set up the necessary information for the fragment shader stage, such as the shader module and the entry point function, which will be used during the pipeline creation process
 */
VkPipelineShaderStageCreateInfo configureFragmentShaderStageCreateInfo(VkShaderModule *pFragmentShaderModule, const char *entryName);

/**
 * @brief Configure the vertex input state create info for a Vulkan pipeline.
 * @return The configured vertex input state create info
 * @see Set up the necessary information for the vertex input state, such as the vertex attribute descriptions and bindings, which will be used during the pipeline creation process
 * */
VkPipelineVertexInputStateCreateInfo configureVertexInputStateCreateInfo();

/**
 * @brief Configure the input assembly state create info for a Vulkan pipeline.
 * @return The configured input assembly state create info
 * @see Set up the necessary information for the input assembly state, such as the primitive topology and whether primitive restart is enabled, which will be used during the pipeline creation process
 */
VkPipelineInputAssemblyStateCreateInfo configureInputAssemblyStateCreateInfo();

/**
 * @brief Configure the viewport for a Vulkan pipeline.
 * @param pExtent Pointer to the extent of the viewport
 * @return The configured viewport
 * @see Set up the necessary information for the viewport, such as the extent of the viewport, which specifies the width and height of the viewport in pixels
 */
VkViewport configureViewport(VkExtent2D *pExtent);

/**
 * @brief Configure the scissor for a Vulkan pipeline.
 * @param pExtent Pointer to the extension of the scissor
 * @param left The left boundary of the scissor rectangle
 * @param right The right boundary of the scissor rectangle
 * @param up The upper boundary of the scissor rectangle
 * @param down The lower boundary of the scissor rectangle
 * @return The configured scissor rectangle
 * @see Scissor is used to define a rectangular region of the framebuffer where pixels can be modified
 */
VkRect2D configureScissor(VkExtent2D *pExtent, uint32_t left, uint32_t right, uint32_t up, uint32_t down);

/**
 * @biref Configure the viewport state create info for a Vulkan pipeline.
 * @param pViewport Pointer to the viewport
 * @param pScissor Pointer to the scissor
 * @return The configured viewport state create info
 * @see The viewport state create info specifies the viewport and scissor for the pipeline
 */
VkPipelineViewportStateCreateInfo configureViewportStateCreateInfo(VkViewport *pViewport, VkRect2D *pScissor);

/**
 * @brief Configure the rasterization state create info for a Vulkan pipeline.
 * @return The configured rasterization state create info
 * @see The rasterization state create info specifies how primitives are rasterized and processed for the pipeline
 */
VkPipelineRasterizationStateCreateInfo configureRasterizationStateCreateInfo();

/**
 * @brief Configure the multisample state create info for a Vulkan pipeline.
 * @return  The configured multisample state create info
 * @see The multisample state create info specifies how multiple samples are used for each pixel in the pipeline
 */
VkPipelineMultisampleStateCreateInfo configureMultisampleStateCreateInfo();

/**
 * @brief Configure the color blend attachment state for a Vulkan pipeline.
 * @return The configured color blend attachment state
 * @see The color blend attachment state specifies how the color blending is performed for each attachment in the pipeline
 */
VkPipelineColorBlendAttachmentState configureColorBlendAttachmentState();

/**
 * @brief Configure the color blend state create info for a Vulkan pipeline.
 * @param pColorBlendAttachmentState Pointer to the color blend attachment state
 * @return The configured color blend state create info
 * @see The color blend state create info specifies how the color blending is performed for all attachments in the pipeline
 */
VkPipelineColorBlendStateCreateInfo configureColorBlendStateCreateInfo(VkPipelineColorBlendAttachmentState *pColorBlendAttachmentState);

/**
 * @brief Create a graphics pipeline for rendering in Vulkan.
 * @param pDevice Target logical device
 * @param pPipelineLayout Pointer to the pipeline layout
 * @param pVertexShaderModule Pointer to the vertex shader module
 * @param pFragmentShaderModule Pointer to the fragment shader module
 * @param pRenderPass Pointer to the render pass
 * @param pExtent Pointer to the extension of the rendering area
 * @return The created graphics pipeline
 * @see Create a graphics pipeline that defines the entire rendering process, including the shaders, vertex input, rasterization, and more
 */
VkPipeline createGraphicsPipeline(VkDevice *pDevice, VkPipelineLayout *pPipelineLayout, VkShaderModule *pVertexShaderModule, VkShaderModule *pFragmentShaderModule, VkRenderPass *pRenderPass, VkExtent2D *pExtent);

/**
 * @brief Destroy a graphics pipeline in Vulkan.
 * @param pDevice Target logical device
 * @param pGraphicsPipeline Pointer to the graphics pipeline to be deleted
 */
void deleteGraphicsPipeline(VkDevice *pDevice, VkPipeline *pGraphicsPipeline);

/**
 * @brief Creates a Vulkan command pool for a given queue family.
 * @param pDevice Target logical device
 * @param queueFamilyIndex Index of the queue family
 * @return The created command pool
 */
VkCommandPool createCommandPool(VkDevice *pDevice, uint32_t queueFamilyIndex);

/**
 * @brief Deletes a Vulkan command pool.
 * @param pDevice Target logical device
 * @param pCommandPool Pointer to the command pool to be removed
 */
void deleteCommandPool(VkDevice *pDevice, VkCommandPool *pCommandPool);

/**
 * @brief Creates multiple Vulkan command buffers.
 * @param pDevice Target logical device
 * @param pCommandPool Pointer to the command pool
 * @param commandBufferNumber Number of command buffers to create
 * @return Pointer to the created command buffers
 */
VkCommandBuffer *createCommandBuffers(VkDevice *pDevice, VkCommandPool *pCommandPool, uint32_t commandBufferNumber);

/**
 * @brief Deletes multiple Vulkan command buffers.
 * @param pDevice Target logical device
 * @param ppCommandBuffers Pointer to an array of command buffer pointers
 * @param pCommandPool Pointer to the command pool
 * @param commandBufferNumber Number of command buffers to delete
 */
void deleteCommandBuffers(VkDevice *pDevice, VkCommandBuffer **ppCommandBuffers, VkCommandPool *pCommandPool, uint32_t commandBufferNumber);

/**
 * @brief Records commands into multiple Vulkan command buffers.
 * @param ppCommandBuffers Pointer to an array of command buffer pointers
 * @param pRenderPass Pointer to the render pass
 * @param ppFramebuffers Pointer to an array of framebuffer pointers
 * @param pExtent Pointer to the extent of the framebuffer
 * @param pPipeline Pointer to the graphics pipeline
 * @param commandBufferNumber Number of command buffers to record
 */
void recordCommandBuffers(VkCommandBuffer **ppCommandBuffers, VkRenderPass *pRenderPass, VkFramebuffer **ppFramebuffers, VkExtent2D *pExtent, VkPipeline *pPipeline, uint32_t commandBufferNumber);

/**
 * @brief Create an array of semaphores for synchronization between frames
 * @param pDevice Target logical device
 * @param maxFrames Maximum number of frames to be synchronized
 * @return Pointer to the array of semaphores
 */
VkSemaphore *createSemaphores(VkDevice *pDevice, uint32_t maxFrames);

/**
 * @brief Delete an array of semaphores
 * @param pDevice Target logical device
 * @param ppSemaphores Pointer to the pointer of the array of semaphores
 * @param maxFrames Maximum number of frames that were synchronized
 */
void deleteSemaphores(VkDevice *pDevice, VkSemaphore **ppSemaphores, uint32_t maxFrames);

/**
 * @brief Create an array of fences for synchronization between frames
 * @param pDevice Pointer to the Vulkan device object
 * @param maxFrames Maximum number of frames to be synchronized
 * @return Pointer to the array of fences
 */
VkFence *createFences(VkDevice *pDevice, uint32_t maxFrames);

/**
 * @brief Delete an array of fences
 * @param pDevice Target logical device
 * @param ppFences Pointer to the pointer of the array of fences
 * @param maxFrames Maximum number of frames that were synchronized
 */
void deleteFences(VkDevice *pDevice, VkFence **ppFences, uint32_t maxFrames);

/**
 * @brief Create an array of empty fences for synchronization between frames
 * @param maxFrames Maximum number of frames to be synchronized
 * @return Pointer to the array of fences
 */
VkFence *createEmptyFences(uint32_t maxFrames);

/**
 * @brief Delete an array of empty fences
 * @param ppFences Pointer to the pointer of the array of fences
 */
void deleteEmptyFences(VkFence **ppFences);

/**
 * @brief Main program loop
 * @param pDevice Target logical device
 * @param window Target window
 * @param pCommandBuffers Target command buffers
 * @param pFrontFences Target presentation fences
 * @param pBackFences Target drawing fences
 * @param pWaitSemaphores  Target wait semaphores for a given number of frames
 * @param pSignalSemaphores Target signal semaphores for a given number of frames
 * @param pSwapchain Target swap chain
 * @param pDrawingQueue Target drawing queue
 * @param pPresentingQueue Target presentation queue
 * @param maxFrames Maximum number of frames to be synchronized
 */
void presentImage(VkDevice *pDevice, GLFWwindow *window, VkCommandBuffer *pCommandBuffers, VkFence *pFrontFences, VkFence *pBackFences, VkSemaphore *pWaitSemaphores, VkSemaphore *pSignalSemaphores, VkSwapchainKHR *pSwapchain, VkQueue *pDrawingQueue, VkQueue *pPresentingQueue, uint32_t maxFrames);

void testLoop(GLFWwindow *window);

#endif // VK_FUN_H
