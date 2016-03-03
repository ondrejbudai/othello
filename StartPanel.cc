#include "StartPanel.hh"

namespace othello {
    StartPanel::StartPanel(QWidget* parent) : QFrame(parent), ui(new Ui::StartPanel) {

        //iniciaizujeme UI
        ui->setupUi(this);
    }
}

