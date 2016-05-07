/**
 * @file
 * @brief Widget ukazující informace na konci hry.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#include "EndScreen.hh"

namespace othello {
    const char* pre = "<span style=\" font-size:14pt;\">";
    const char* post = "<\\span>";

    EndScreen::EndScreen(QWidget* parent) : QFrame(parent) {

        //iniciaizujeme UI
        ui_.setupUi(this);
    }

    void EndScreen::SetNames(const std::pair<std::string, std::string>& names) {

        QString black{names.first.c_str()};
        QString white{names.second.c_str()};

        black.prepend(pre).append(post);
        white.prepend(pre).append(post);
        ui_.BlackName->setText(black);
        ui_.WhiteName->setText(white);
    }

    void EndScreen::SetScores(const std::pair<unsigned, unsigned>& scores) {
        QString black, white;
        black.setNum(scores.first).prepend(pre).append(post);
        white.setNum(scores.second).prepend(pre).append(post);

        ui_.BlackScore->setText(black);
        ui_.WhiteScore->setText(white);

        if (scores.first > scores.second) {
            ui_.BlackWinner->setText("<span style=\" font-size:14pt; font-weight:600;\">Winner<\\span>");
            ui_.WhiteWinner->setText("<span style=\" font-size:14pt; font-weight:600;\">Looser<\\span>");
        } else if (scores.first < scores.second) {
            ui_.BlackWinner->setText("<span style=\" font-size:14pt; font-weight:600;\">Looser<\\span>");
            ui_.WhiteWinner->setText("<span style=\" font-size:14pt; font-weight:600;\">Winner<\\span>");
        } else {
            ui_.BlackWinner->setText("<span style=\" font-size:14pt; font-weight:600;\">Draw!<\\span>");
            ui_.WhiteWinner->setText("<span style=\" font-size:14pt; font-weight:600;\">Draw!<\\span>");
        }
    }
}
