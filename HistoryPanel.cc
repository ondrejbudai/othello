#include "HistoryPanel.hh"
#include "ui_HistoryPanel.h"
#include <QLayout>
#include <QScrollArea>

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

}

void HistoryPanel::AddHistoryItem(){


}


HistoryPanel::~HistoryPanel()
{
    delete ui;
}
