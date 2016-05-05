#include "HistoryPanel.hh"
#include "ui_HistoryPanel.h"
#include <iostream>

namespace othello{
    HistoryPanel::HistoryPanel(QWidget *parent) :
            QWidget(parent)
    {
        ui.setupUi(this);
        connect(ui.TheList, SIGNAL(itemClicked(QListWidgetItem * )),
                this, SLOT(HistoryItemSelected(QListWidgetItem*)));


    }

    void HistoryPanel::HistoryItemSelected(QListWidgetItem* item){
        QWidget* selected_ = ui.TheList->itemWidget(item);
    //    HistoryItemGui *selected = (HistoryItemGui *) selected_;
        //TODO po kliknuti zobrazi vo velkom okne?
        //std::cout<<selected->getText()<<std::endl;

    }


    // void HistoryPanel::AddHistory(std::vector<HistoryItem> H)const{
    //     for (unsigned i = 0; i < H.size(); i++){
    //         HistoryItemGui *hit = new HistoryItemGui();
    //         hit->setColor(H[i].currentPlayer);
    //         hit->setMove(H[i].currentMove);
    //         hit->setBoard(H[i].board);
    //
    //
    //         QListWidgetItem *item = new QListWidgetItem;
    //         item->setSizeHint(QSize(238,169));
    //         ui.TheList->addItem(item);
    //         ui.TheList->setItemWidget(item, hit);
    //     }
    // }
    //

    HistoryPanel::~HistoryPanel()
    {
    }
}
