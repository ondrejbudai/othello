#include "EndScreen.hh"

namespace othello {
    const char* pre = "<span style=\" font-size:14pt;\">";
    const char* post = "<\\span>";

    EndScreen::EndScreen(QWidget* parent) : QFrame(parent), ui(new Ui::EndScreen) {

        //iniciaizujeme UI
        ui->setupUi(this);
    }

    void EndScreen::SetNames(const std::pair<std::string, std::string>& names) {

        QString black{names.first.c_str()};
        QString white{names.second.c_str()};

        black.prepend(pre).append(post);
        white.prepend(pre).append(post);
        ui->BlackName->setText(black);
        ui->WhiteName->setText(white);
    }

    void EndScreen::SetScores(const std::pair<unsigned, unsigned>& scores) {
        QString black, white;
        black.setNum(scores.first).prepend(pre).append(post);
        white.setNum(scores.second).prepend(pre).append(post);

        ui->BlackScore->setText(black);
        ui->WhiteScore->setText(white);

        if (scores.first > scores.second) {
            ui->BlackWinner->setText("<span style=\" font-size:14pt; font-weight:600;\">Winner<\\span>");
            ui->WhiteWinner->setText("<span style=\" font-size:14pt; font-weight:600;\">Looser<\\span>");
        } else if (scores.first < scores.second) {
            ui->BlackWinner->setText("<span style=\" font-size:14pt; font-weight:600;\">Looser<\\span>");
            ui->WhiteWinner->setText("<span style=\" font-size:14pt; font-weight:600;\">Winner<\\span>");
        } else {
            ui->BlackWinner->setText("<span style=\" font-size:14pt; font-weight:600;\">Draw!<\\span>");
            ui->WhiteWinner->setText("<span style=\" font-size:14pt; font-weight:600;\">Draw!<\\span>");
        }
    }
}

