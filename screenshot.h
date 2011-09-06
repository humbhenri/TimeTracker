#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QObject>

class ScreenShot : public QObject
{
    Q_OBJECT
public:
    explicit ScreenShot(QObject *parent = 0);
    static void saveNewDesktopScreenshot(const QString & path);
signals:

public slots:

};

#endif // SCREENSHOT_H
