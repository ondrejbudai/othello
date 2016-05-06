/**
 * @file
 * @brief Widget na vybírání hráčů.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#ifndef PLAYERSELECTION_H
#define PLAYERSELECTION_H

#include <QFrame>
#include "ui_PlayerSelection.h"

namespace othello {

    class PlayerSelection : public QFrame
    {
        Q_OBJECT

    public:
        explicit PlayerSelection(QWidget *parent = 0);
        ~PlayerSelection();

        std::array<QString, 2> getNames();

        std::array<QString, 2> getTypes();
        QString getBoardSize();
    signals:
        void on_ButtonStartGame_clicked();
    private:
        Ui::PlayerSelection *ui;
    };

}

#endif // PLAYERSELECTION_H
