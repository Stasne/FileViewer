#ifndef IDISPLAYSETTINGS_H
#define IDISPLAYSETTINGS_H
#include <QColor>
#include <QFont>
#include <QSize>

class IDisplaySettings {
public:
    IDisplaySettings() = default;
    virtual QFont fontDefault() const { return QFont(); }
    virtual QFont font(bool isDir) const
    {
        auto f = fontDefault();
        f.setBold(isDir);
        f.setItalic(not isDir);
        return f;
    }
    virtual QColor fontColorDefault() const { return Qt::white; }
    virtual QColor iconBgColor(bool isDir) const
    {
        static QColor fileBgColor(30, 180, 50);
        static QColor dirBgColor(50, 50, 180);
        return isDir ? dirBgColor : fileBgColor;
    }
};

#endif // IDISPLAYSETTINGS_H
