#ifndef HISTORYITEM_HH
#define HISTORYITEM_HH

#include <QWidget>

namespace Ui {
class HistoryItem;
}

class HistoryItem : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryItem(QWidget *parent = 0);
    ~HistoryItem();
    void setText(int i);

private:
    Ui::HistoryItem *ui;
};

#endif // HISTORYITEM_HH
