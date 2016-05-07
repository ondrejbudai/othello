/**
 * @file
 * @brief Widget na vybírání hráčů.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#include "PlayerSelection.hh"

namespace othello {

    PlayerSelection::PlayerSelection(QWidget *parent) :
            QFrame(parent)
    {
        ui_.setupUi(this);

        connect(ui_.name1, SIGNAL(textChanged(const QString &)), ui_.player1L, SLOT(setText(const QString &)));
        connect(ui_.name2, SIGNAL(textChanged(const QString &)), ui_.player2L, SLOT(setText(const QString &)));


    }

    QString PlayerSelection::GetBoardSize(){
        return (ui_.BoardSize->currentText());
    }


    std::pair<QString, QString> PlayerSelection::GetNames() {
        return {ui_.name1->text(), ui_.name2->text()};
    }

    std::pair<QString, QString> PlayerSelection::GetTypes() {
        return {ui_.selectPlayer1->currentText(), ui_.selectPlayer2->currentText()};
    }
}
