/**
 * @file
 * @brief Widget ukazující informace o aktuálně hrané hře.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#include "InfoPanel.hh"

namespace othello {
    InfoPanel::InfoPanel(QWidget* parent) : QFrame(parent) {

        //iniciaizujeme UI
        ui_.setupUi(this);
    }

    void InfoPanel::WriteScore(std::pair<unsigned, unsigned> score) {
        QString sb = QString::number(score.first);
        ui_.BlackScoreLabel->setText(sb);
        QString sw = QString::number(score.second);
        ui_.WhiteScoreLabel->setText(sw);
    }
    // v pravem sloupci, zobrazi obrazovku s vyberem hracu


    void InfoPanel::SetNames(const std::pair<std::string, std::string>& names) {
        QString black{names.first.c_str()};
        QString white{names.second.c_str()};

        black.prepend("<span style=\" font-size:14pt;\">").append("<\\span>");
        white.prepend("<span style=\" font-size:14pt;\">").append("<\\span>");
        ui_.BlackName->setText(black);
        ui_.WhiteName->setText(white);
    }

    void InfoPanel::ChangeIcon(bool to){
      if (to){
          ui_.PlayPause->setText("||");
      }
      else{
        ui_.PlayPause->setText("P");
      }
    }

    //zvyraznenie kto prave hra - je to najtrivilanejsie riesenie, caka sa ze sa prerobi
    //+ ak sa nezmeni hrac nejake oknieko aby bolo jasne ze sa nezmenil hrac!
    void InfoPanel::HighlightPlayer(Color c){

        if (c == Color::BLACK){
            ui_.BlackName->setStyleSheet("QLabel { background-color : red}");
            ui_.WhiteName->setStyleSheet("QLabel { background-color : transparent}");
        } else {
            ui_.WhiteName->setStyleSheet("QLabel { background-color : red}");
            ui_.BlackName->setStyleSheet("QLabel { background-color : transparent}");


        }
    }
}
