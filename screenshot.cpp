#include "screenshot.h"
#include <QPixmap>
#include <QApplication>
#include <QDesktopWidget>

ScreenShot::ScreenShot(QObject *parent) :
    QObject(parent)
{
}

// Take a desktop screenshot and save it in path
void ScreenShot::saveNewDesktopScreenshot(const QString &path)
{
    QPixmap shot = QPixmap::grabWindow(QApplication::desktop()->winId());
    shot = shot.scaled(640, 480, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    shot.save(path, "png");
}
