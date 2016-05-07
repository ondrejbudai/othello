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

        connect(ui_.name1, &QLineEdit::textChanged, ui_.player1L, &QLabel::setText);
        connect(ui_.name2, &QLineEdit::textChanged, ui_.player2L, &QLabel::setText);


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
