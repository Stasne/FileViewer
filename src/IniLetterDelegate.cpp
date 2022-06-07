#include "IniLetterDelegate.h"
#include "IDisplaySettings.h"
#include <QFileSystemModel>
#include <QPainter>
#include <QSortFilterProxyModel>

IniLetterDelegate::IniLetterDelegate(QSharedPointer<IDisplaySettings> settings, QObject* parent)
    : QStyledItemDelegate(parent)
    , _settings(settings)
{
}

void IniLetterDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QStyle* style = option.widget->style();
    if (style)
        style->drawPrimitive(QStyle::PE_PanelItemViewItem, &option, painter, option.widget);
    //####################### GAVNINA ############################
    /*
    // stupid workaround of model could be QSortFilterProxyModel... or else
    auto getModel = [&]() -> const QFileSystemModel* {
        if (not qobject_cast<const QFileSystemModel*>(index.model())) {
            Q_ASSERT(qobject_cast<const QSortFilterProxyModel*>(index.model()));
            auto proxy = qobject_cast<const QSortFilterProxyModel*>(index.model());
            return qobject_cast<QFileSystemModel*>(proxy->sourceModel());
        } else
            return qobject_cast<const QFileSystemModel*>(index.model());
        ;
    };
    const QFileSystemModel* model = getModel();
    //############################################################ */
    /*
    //TOZHE gavnina
        auto model = qobject_cast<const QFileSystemModel*>(qobject_cast<const QSortFilterProxyModel*>(index.model())->sourceModel());
        */
    // TODO:Works Only if index.model() is QFileSystemModel or derived...
    auto model = qobject_cast<const QFileSystemModel*>(index.model());
    bool isDir = model->isDir(index);

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

void IniLetterDelegate::setOrientation(Qt::Orientation orientation)
{
    QT_THROW("Not Available to set different orientation. Stay straight");
    //    _orientation = orientation;
}

Qt::Orientation IniLetterDelegate::orientation() const
{
    return Qt::Horizontal;
}
