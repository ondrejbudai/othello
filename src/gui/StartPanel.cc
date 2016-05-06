/**
 * @file
 * @brief Panel na zahájení nové hry.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#include "StartPanel.hh"

namespace othello {
    StartPanel::StartPanel(QWidget* parent) : QFrame(parent), ui(new Ui::StartPanel) {

        //iniciaizujeme UI
        ui->setupUi(this);
    }
}
