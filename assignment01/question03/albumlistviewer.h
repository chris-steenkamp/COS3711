#ifndef ALBUMLISTVIEWER_H
#define ALBUMLISTVIEWER_H

#include <QWidget>

class QDoubleSpinBox;
class QLineEdit;
class QPushButton;
class QSpinBox;
class QAbstractTableModel;

class AlbumListViewer : public QWidget
{
    Q_OBJECT
public:
    explicit AlbumListViewer(QWidget *parent = 0);

signals:

public slots:
    void handleAddRecordClicked();
private:
    QLineEdit *m_Composer;
    QLineEdit *m_AlbumName;
    QDoubleSpinBox *m_Value;
    QSpinBox *m_Rating;
    QPushButton *m_AddRecord;
    QAbstractTableModel *m_AlbumModel;
};

#endif // ALBUMLISTVIEWER_H
