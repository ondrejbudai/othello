#ifndef OTHELLO_INFOPANEL_HH
#define OTHELLO_INFOPANEL_HH

#include <QWidget>
#include <QFrame>
#include <string>

namespace Ui {
    class InfoPanel;
}
namespace othello {
    class InfoPanel : public QFrame {
    Q_OBJECT


    public:
        Ui::InfoPanel* ui;

        explicit InfoPanel(QWidget* parent = 0);

        void WriteScore(std::pair<unsigned, unsigned> score);

        void setNames(std::array<std::string, 2> names);
    signals:
        void on_ButtonSaveGame_clicked();
        
    };
}

#endif //OTHELLO_INFOPANEL_HH
