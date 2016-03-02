#include "ui_InfoPanel.h"
#include "InfoPanel.hh"

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


    void InfoPanel::setNames(std::array<QString, 2> names) {
        ui->BlackName->setText(names[0]);
        ui->WhiteName->setText(names[1]);
    }
}
