#ifndef VULKANWINDOW_H
#define VULKANWINDOW_H

#include <QObject>
#include <QVulkanWindow>
#include <QWindow>

class VulkanRenderer;

class VulkanWindow : public QVulkanWindow
{
    Q_OBJECT

public:
    QVulkanWindowRenderer *createRenderer() override;

    VulkanRenderer* getRenderer();

private:
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void wheelEvent(QWheelEvent *) override;

    VulkanRenderer* renderer;
    bool pressed = false;
    QPoint lastPos;
    float scale = 1.0f;

signals:
    void rendererHasBeenCreated();

};

#endif // VULKANWINDOW_H
