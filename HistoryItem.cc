#include "HistoryItem.hh"
#include "ui_HistoryItem.h"

HistoryItem::HistoryItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryItem)
{
    ui->setupUi(this);
}

HistoryItem::~HistoryItem()
{
    delete ui;
}
    void HistoryItem::setText(int i){
        ui->label->setText(QString::number(i));
    }
