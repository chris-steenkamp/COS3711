#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QTableView>
#include <QVBoxLayout>

#include "albumlistviewer.h"
#include "albumlistmodel.h"

AlbumListViewer::AlbumListViewer(QWidget *parent)
    : QWidget(parent),
      m_Composer(new QLineEdit(this)),
      m_AlbumName(new QLineEdit(this)),
      m_Value(new QDoubleSpinBox(this)),
      m_Rating(new QSpinBox(this)),
      m_AddRecord(new QPushButton("&Add", this)),
      m_AlbumModel(new AlbumListModel(this))
{
    m_Rating->setRange(0, 100);
    m_Value->setRange(0, 9999);
    m_Value->setDecimals(2);
    setWindowTitle("View Album List");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QGridLayout *grid= new QGridLayout;

    grid->addWidget(new QLabel(tr("Composer")), 0, 0);
    grid->addWidget(m_Composer, 1, 0);
    grid->addWidget(new QLabel(tr("Album Name")), 0, 1);
    grid->addWidget(m_AlbumName, 1, 1);
    grid->addWidget(new QLabel(tr("Replacement Cost (R)")), 0, 2);
    grid->addWidget(m_Value, 1, 2);
    grid->addWidget(new QLabel(tr("Rating")), 0, 3);
    grid->addWidget(m_Rating, 1, 3);
    grid->addWidget(m_AddRecord, 1, 4, 1, 2);

    mainLayout->addLayout(grid);

    QTableView *tableView = new QTableView(this);
    tableView->setModel(m_AlbumModel);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->resizeColumnsToContents();
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->verticalHeader()->hide();
    tableView->setTabKeyNavigation(false);

    mainLayout->addWidget(tableView);

    setLayout(mainLayout);

    connect(m_AddRecord, SIGNAL(clicked(bool)), this, SLOT(handleAddRecordClicked()));

    //Add some test data
    AlbumListModel *model = qobject_cast<AlbumListModel*>(m_AlbumModel);
    if (model) {
        model->addAlbum("Black Sabbath", "Paranoid", 69.95f, 98);
        model->addAlbum("Abba", "The Essential Collection", 178.0, 70);
        model->addAlbum("The Shins", "Wincing the Night Away", 120.5f, 85);
    }

    m_Composer->setFocus();
}

void AlbumListViewer::handleAddRecordClicked()
{
    //Ensure the model being used is an AlbumListModel
    AlbumListModel *model = qobject_cast<AlbumListModel*>(m_AlbumModel);
    if (model) {
        model->addAlbum(m_Composer->text(), m_AlbumName->text(), static_cast<float>(m_Value->value()), m_Rating->value());
        m_AlbumName->clear();
        m_Composer->clear();
        m_Value->clear();
        m_Rating->clear();
        m_Composer->setFocus();
    }
}
