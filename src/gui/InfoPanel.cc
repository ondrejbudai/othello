#include "InfoPanel.hh"
#include <iostream>

namespace othello {
    InfoPanel::InfoPanel(QWidget* parent) : QFrame(parent) {

        //iniciaizujeme UI
        ui.setupUi(this);

    }

    void InfoPanel::WriteScore(std::pair<unsigned, unsigned> score) {
        QString sb = QString::number(score.first);
        ui.BlackScoreLabel->setText(sb);
        QString sw = QString::number(score.second);
        ui.WhiteScoreLabel->setText(sw);
    }
    // v pravem sloupci, zobrazi obrazovku s vyberem hracu


    void InfoPanel::SetNames(const std::pair<std::string, std::string>& names) {
        QString black{names.first.c_str()};
        QString white{names.second.c_str()};

        black.prepend("<span style=\" font-size:14pt;\">").append("<\\span>");
        white.prepend("<span style=\" font-size:14pt;\">").append("<\\span>");
        ui.BlackName->setText(black);
        ui.WhiteName->setText(white);
    }
    
    //zvyraznenie kto prave hra - je to najtrivilanejsie riesenie, caka sa ze sa prerobi
    //+ ak sa nezmeni hrac nejake oknieko aby bolo jasne ze sa nezmenil hrac!
    void InfoPanel::HighlightPlayer(Color c){

        if (c == Color::BLACK){
            ui.BlackName->setStyleSheet("QLabel { background-color : red}");
            ui.WhiteName->setStyleSheet("QLabel { background-color : transparent}");
        } else {
            ui.WhiteName->setStyleSheet("QLabel { background-color : red}");
            ui.BlackName->setStyleSheet("QLabel { background-color : transparent}");


        }    
    }
}
