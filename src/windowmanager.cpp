#include "windowmanager.h"

#include <iostream>

#include "mainwindow.h"

WindowManager& WindowManager::getInstance()
{
    static WindowManager instance;
    return instance;
}

void WindowManager::setUp(
        MainWindow* w,
        ControlsWidget* c,
        VulkanRenderer* r,
        CodeEdit* e,
        OutputEdit* oe)
{
    mainWindow = w;
    controlsWidget = c;
    vulkanRenderer = r;
    codeEdit = e;
    outputEdit = oe;

    // TODO: Call this when renderer is fully initialized
    //setGpuLabel(vulkanRenderer->getGpuName());

    connect(controlsWidget, &ControlsWidget::imagePathHasChanged,
            this, &WindowManager::handleImagePathHasChanged);
    connect(codeEdit, &CodeEdit::requestErrorMessageUpdate,
            this, &WindowManager::handleRequestErrorMessageUpdate);
    connect(codeEdit, &CodeEdit::shaderCompiledSuccessfully,
            this, &WindowManager::handleShaderCompiled);
}

void WindowManager::setGpuLabel(const QString &s)
{
    controlsWidget->setGpuLabel(s);
}

void WindowManager::handleImagePathHasChanged(const QString& path)
{
    vulkanRenderer->updateImage(path);
}

void WindowManager::handleRequestErrorMessageUpdate(const std::string& msg)
{
    outputEdit->setErrorMsg(msg);
}

void WindowManager::handleShaderCompiled(const std::vector<unsigned int>& vec)
{
    std::cout << "Sending shader code to Vulkan" << std::endl;
    vulkanRenderer->updateShader(vec);
}
