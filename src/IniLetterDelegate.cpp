#include "IniLetterDelegate.h"
#include "FileSystemModel.h"
#include "IDisplaySettings.h"
#include <QPainter>

IniLetterDelegate::IniLetterDelegate(int isDirectoryRole, const QSharedPointer<IDisplaySettings> settings, QObject* parent)
    : QStyledItemDelegate(parent)
    , isDirRole_(isDirectoryRole)
    , _settings(settings)
{
}

void IniLetterDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyle* style = option.widget->style();
    if (style)
        style->drawPrimitive(QStyle::PE_PanelItemViewItem, &option, painter, option.widget);

    bool isDir = index.data(isDirRole_).toBool();

    painter->save();
    QBrush iconBgBrush = QBrush(_settings->iconBgColor(isDir));
    QRect iconBg = QRect(option.rect.x(), option.rect.y(), option.rect.height(), option.rect.height());
    painter->fillRect(iconBg, iconBgBrush);
    QString line = index.data().toString();
    painter->setPen(_settings->iconFontColor());
    painter->drawText(iconBg, (Qt::AlignCenter | Qt::TextSingleLine), QString(line.front())); // default font used intentionally
    painter->setFont(_settings->font(isDir));
    painter->setPen(option.widget->palette().color(QPalette::Text));
    painter->translate(QPointF(option.rect.height(), 0));
    painter->drawText(option.rect, (option.displayAlignment | Qt::TextSingleLine), line);
    painter->restore();
}
