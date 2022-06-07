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
    virtual QColor iconFontColor() const { return Qt::white; }
    virtual const QColor& iconBgColor(bool isDir) const
    {
        static const QColor fileBgColor(30, 180, 50);
        static const QColor dirBgColor(50, 50, 180);
        return isDir ? dirBgColor : fileBgColor;
    }
};

#endif // IDISPLAYSETTINGS_H
