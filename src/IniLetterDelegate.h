#ifndef INITIALLETTERDELEGATE_H
#define INITIALLETTERDELEGATE_H

#include <QStyledItemDelegate>

class IDisplaySettings;
///
/// \brief The IniLetterDelegate class
/// Делегат отобажения "Буквицы" имени файла.
///
class IniLetterDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    ///
    /// \brief IniLetterDelegate
    /// Конструктор делегата
    /// \param isDirectoryRole
    /// Код роли модели, отвечающей за выдачу признака "является ли индекс - папкой"
    /// \param settings
    /// Интерфейс класса параметров, который содержит(должен) параметры цветов/шрифтов иконок папок/файлов
    /// \param parent
    ///
    IniLetterDelegate(int isDirectoryRole, const QSharedPointer<IDisplaySettings> settings, QObject* parent = nullptr);
    ~IniLetterDelegate() = default;
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;

private:
    const int isDirRole_;
    QSharedPointer<IDisplaySettings> _settings;
};

#endif // INITIALLETTERDELEGATE_H
