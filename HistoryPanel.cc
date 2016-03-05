#include "HistoryPanel.hh"
#include "ui_HistoryPanel.h"
#include <iostream>

HistoryPanel::HistoryPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryPanel)
{
    ui->setupUi(this);
    
    for (int i = 0; i < 10; ++i){
        HistoryItem *hit = new HistoryItem();
        hit->setText(i);
        QListWidgetItem *item = new QListWidgetItem;    
        item->setSizeHint(QSize(238,169));
        ui->TheList->addItem(item);
        ui->TheList->setItemWidget(item, hit);
    }


    connect(ui->TheList, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(HistoryItemSelected(QListWidgetItem*)));


}

void HistoryPanel::HistoryItemSelected(QListWidgetItem* item){
    QWidget *selected_  = ui->TheList->itemWidget(item);
    HistoryItem *selected = (HistoryItem *) selected_;
    
    std::cout<<selected->getText()<<std::endl;

}


void HistoryPanel::AddHistoryItem(){


}


HistoryPanel::~HistoryPanel()
{
    delete ui;
}
