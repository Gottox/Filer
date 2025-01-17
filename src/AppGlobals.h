#ifndef GLOBALS_H
#define GLOBALS_H

#include <QColor>

class AppGlobals {
public:
    class Colors {
    public:
        static const QColor BackgroundColor;
        static const QColor TextColor;
    };

    static const int MaxItems;

    static const QString mediaPath;
    static const QString hardDiskName;

    static const QString desktopPicturePath;
};

#endif // GLOBALS_H
