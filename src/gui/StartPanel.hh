#ifndef OTHELLO_STARTPANEL_HH
#define OTHELLO_STARTPANEL_HH

#include <QWidget>
#include <QFrame>
#include "ui_StartPanel.h"

namespace othello {
    class StartPanel : public QFrame {
    Q_OBJECT

    private:
        Ui::StartPanel* ui;

    public:
        explicit StartPanel(QWidget* parent = 0);

    signals:
        void on_ButtonLoadGame_clicked();

        void on_ButtonNewGame_clicked();
    };
}


#endif
