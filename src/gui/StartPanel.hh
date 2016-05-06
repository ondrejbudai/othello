/**
 * @file
 * @brief Panel na zahájení nové hry.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

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
