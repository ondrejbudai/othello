#include "StartPanel.hh"
#include "ui_StartPanel.h"

namespace othello {
    StartPanel::StartPanel(QWidget* parent) : QFrame(parent), ui(new Ui::StartPanel) {

        //iniciaizujeme UI
        ui->setupUi(this);
    }
}

