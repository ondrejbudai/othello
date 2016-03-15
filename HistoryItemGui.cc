#include "HistoryItemGui.hh"
#include "ui_HistoryItemGui.h"
#include <string>
#include "BoardGraphics.hh"

namespace othello{

    HistoryItemGui::HistoryItemGui(QWidget *parent) :
            QWidget(parent)
    {
        ui.setupUi(this);
    }

    HistoryItemGui::~HistoryItemGui()
    {
    }

    void HistoryItemGui::setColor(Color C){
        ui.color->setText(QString::fromStdString(C == Color::BLACK ? "black" : "white"));
    }


    void HistoryItemGui::setMove(std::pair<unsigned, unsigned> M){
        ui.x->setText(QString::number(M.first));
        ui.y->setText(QString::number(M.second));
    }
    
    void HistoryItemGui::setBoard(std::vector<std::vector<Field>> &B){
        BoardGraphics* scene;
        scene = new BoardGraphics(B);
        GraphicsView *view = new GraphicsView(scene);
        ui.BoardLayout->addWidget(view);
    
    }
}
