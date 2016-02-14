#ifndef PLAYERSELECTION_H
#define PLAYERSELECTION_H

#include <QWidget>

namespace Ui {
class PlayerSelection;
}

class PlayerSelection : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerSelection(QWidget *parent = 0);
    ~PlayerSelection();

//signals:
//    void on_ButtonStartGame_clicked();

private:
    Ui::PlayerSelection *ui;
};

#endif // PLAYERSELECTION_H
