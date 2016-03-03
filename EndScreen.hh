#ifndef OTHELLO_ENDSCREEN_HH
#define OTHELLO_ENDSCREEN_HH

#include <QWidget>
#include <QFrame>
#include "ui_EndScreen.h"

namespace othello {
    class EndScreen : public QFrame {
    Q_OBJECT

    private:
        Ui::EndScreen* ui;

    public:
        explicit EndScreen(QWidget* parent = 0);

        void SetNames(const std::pair<std::string, std::string>& names);

        void SetScores(const std::pair<unsigned, unsigned>& scores);
    };
}


#endif
