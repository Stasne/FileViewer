#ifndef INITIALLETTERDELEGATE_H
#define INITIALLETTERDELEGATE_H
#include <QItemDelegate>
#include <QStyledItemDelegate>
class IDisplaySettings;
class IniLetterDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    enum class EntryType {
        FILE = 0,
        DIR = 1,
    };
    IniLetterDelegate(QSharedPointer<IDisplaySettings>, QObject* parent = nullptr);
    ~IniLetterDelegate() = default;
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setOrientation(Qt::Orientation orientation);
    Qt::Orientation orientation() const;

protected:
    Qt::Orientation _orientation = Qt::Orientation::Horizontal;

private:
    QSharedPointer<IDisplaySettings> _settings;
};

#endif // INITIALLETTERDELEGATE_H
