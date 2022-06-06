#include "IniLetterDelegate.h"
#include "IDisplaySettings.h"
#include <cmath>

#include <QDebug>
#include <QFileSystemModel>
#include <QPainter>

IniLetterDelegate::IniLetterDelegate(QSharedPointer<IDisplaySettings> settings, QObject* parent)
    : QStyledItemDelegate(parent)
    , _settings(settings)
{
}

void IniLetterDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    static const QFileSystemModel* model = static_cast<const QFileSystemModel*>(index.model());
    bool isDir = model->isDir(index);

    painter->save();
    QBrush iconBgBrush = QBrush(_settings->iconBgColor(isDir));
    QRect iconBg = QRect(option.rect.x(), option.rect.y(), option.rect.height(), option.rect.height());
    painter->fillRect(iconBg, iconBgBrush);

    QString line = index.data().toString();
    painter->setPen(_settings->fontColorDefault());
    painter->drawText(iconBg, (Qt::AlignCenter | Qt::TextSingleLine), QString(line.front())); // default font used intentionally
    painter->setFont(_settings->font(isDir));
    painter->translate(QPointF(option.rect.height(), 0));
    painter->drawText(option.rect, (option.displayAlignment | Qt::TextSingleLine), line);
    painter->restore();
}

void IniLetterDelegate::setOrientation(Qt::Orientation orientation)
{
    QT_THROW("Not Available to set different orientation. Stay straight");
    //    _orientation = orientation;
}

Qt::Orientation IniLetterDelegate::orientation() const
{
    return Qt::Horizontal;
}
