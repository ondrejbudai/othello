#include "InfoPanel.hh"
#include <iostream>

namespace othello {
    InfoPanel::InfoPanel(QWidget* parent) : QFrame(parent), ui(new Ui::InfoPanel) {

        //iniciaizujeme UI
        ui->setupUi(this);

    }

    void InfoPanel::WriteScore(std::pair<unsigned, unsigned> score) {
        QString sb = QString::number(score.first);
        ui->BlackScoreLabel->setText(sb);
        QString sw = QString::number(score.second);
        ui->WhiteScoreLabel->setText(sw);
    }
    // v pravem sloupci, zobrazi obrazovku s vyberem hracu


    void InfoPanel::SetNames(const std::pair<std::string, std::string>& names) {
        QString black{names.first.c_str()};
        QString white{names.second.c_str()};

        black.prepend("<span style=\" font-size:14pt;\">").append("<\\span>");
        white.prepend("<span style=\" font-size:14pt;\">").append("<\\span>");
        ui->BlackName->setText(black);
        ui->WhiteName->setText(white);
    }
}
