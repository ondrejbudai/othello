#ifndef HISTORYPANEL_HH
#define HISTORYPANEL_HH

#include <QWidget>
#include <QVBoxLayout>
#include <QLayout>
#include <QScrollArea>
#include <QListWidgetItem>
#include "HistoryItemGui.hh"
#include "MainGame.hh"
#include "ui_HistoryPanel.h"

namespace othello{

    //namespace Ui {
    //class HistoryPanel;
    //}

    class HistoryPanel : public QWidget
    {
        Q_OBJECT

    public:
        explicit HistoryPanel(QWidget *parent = 0);
        ~HistoryPanel();
        
        void AddHistory(std::vector<HistoryItem> H)const;
    
    signals:

        // todo: opravit preklep
        void on_ButtonCancle_clicked();


    private:
        Ui::HistoryPanel ui;
        QVBoxLayout *lay;

    public slots:
        void HistoryItemSelected(QListWidgetItem* item);

    };

}
#endif // HISTORYPANEL_HH
