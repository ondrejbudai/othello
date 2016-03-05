#ifndef HISTORYPANEL_HH
#define HISTORYPANEL_HH

#include <QWidget>
#include <QVBoxLayout>
#include <QLayout>
#include <QScrollArea>
#include <QListWidgetItem>
#include "HistoryItem.hh"

namespace Ui {
class HistoryPanel;
}

class HistoryPanel : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryPanel(QWidget *parent = 0);
    ~HistoryPanel();
    void AddHistoryItem();

private:
    Ui::HistoryPanel *ui;
    QVBoxLayout *lay;

public slots:
    void HistoryItemSelected(QListWidgetItem* item);

};

#endif // HISTORYPANEL_HH
