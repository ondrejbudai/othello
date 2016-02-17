#ifndef PLAYERSELECTION_H
#define PLAYERSELECTION_H

#include <QWidget>
#include <QFrame>
#include <QString>
#include <vector>
#include <string>

namespace Ui {
class PlayerSelection;
}

class PlayerSelection : public QFrame
{
    Q_OBJECT

public:
    explicit PlayerSelection(QWidget *parent = 0);
    ~PlayerSelection();

    std::vector<QString> getNames();
    std::vector<QString> getTypes();
    QString getBoardSize();
signals:
    void on_ButtonStartGame_clicked();
private:
    Ui::PlayerSelection *ui;
};

#endif // PLAYERSELECTION_H
