#ifndef OTHELLO_STARTPANEL_HH
#define OTHELLO_STARTPANEL_HH

#include <QWidget>
#include <QFrame>

namespace Ui {
    class StartPanel;
}

namespace othello {
    class StartPanel : public QFrame {
    Q_OBJECT


    public:
        Ui::StartPanel* ui;

        explicit StartPanel(QWidget* parent = 0);

    signals:
        void on_ButtonLoadGame_clicked();

        void on_ButtonNewGame_clicked();
    };
}


#endif
