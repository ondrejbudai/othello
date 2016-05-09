/**
 * @file
 * @brief Widget na zobrazování herní grafiky.
 * @author Ondřej Budai <xbudai00@stud.fit.vutbr.cz>
 * @author Matej Marušák <xmarus06@stud.fit.vutbr.cz>
 */

#ifndef GRAPHICS_SCENE_HH
#define GRAPHICS_SCENE_HH

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QResizeEvent>
#include <QPixmap>
#include "../logic/MainGame.hh"

namespace othello {

    /**
     * @brief Velikost herní desky.
     */
    constexpr unsigned GAME_SIZE = 200;

    /**
     * @brief Pohled na hrací desku. Veškeré příchozí údalosti jsou přeposílány přímo herní desce.
     */
    class GraphicsView : public QGraphicsView {
    Q_OBJECT
    public:
        /**
         * @brief Konstruktor pohledu.
         * @param scene Scéna, která se bude v pohledu zobrazovat.
         */
        GraphicsView(QGraphicsScene* scene);

        /**
         * @brief Událost změny velikosti pohledu
         */
        virtual void resizeEvent(QResizeEvent*) override;

        /**
         * @brief Událost změny polohy kurzoru
         * @param mouse_event Informace o vykonaném pohybu.
         */
        virtual void mouseMoveEvent(QMouseEvent* mouse_event) override;

        /**
         * @brief Událost vstoupení kurzoru nad pohled
         */
        virtual void enterEvent(QEvent*) override;

        /**
         * @brief Událost vystoupení kurzoru z pohledu
         */
        virtual void leaveEvent(QEvent*) override;

    signals:
        /**
         * @brief Signál emitovaný po změně polohy kurzoru.
         * @param coords Souřadnice aktuální polohy.
         */
        void MouseMoveSignal(QPointF coords);
        /**
         * @brief Signál emitovaný po vstoupení kurzory nad pohled.
         */
        void EnterSignal();

        /**
         * Signál emitovaný po vystoupení kurzoru z pohledu.
         */
        void LeaveSignal();
    };

    /**
     * @brief Grafika herní desky - zde dochází k vykreslování.
     */
    class BoardGraphics : public QGraphicsScene {
    Q_OBJECT
    private:
        /**
         * @brief Sprite černého kamene
         */
        QPixmap black_disc_;

        /**
         * @brief Sprite černého kamene, průhledný
         */
        QPixmap black_disc_shadow_;

        /**
         * @brief Sprite bílého kamene
         */
        QPixmap white_disc_;

        /**
         * @brief Sprite bílého kamene, průhledný
         */
        QPixmap white_disc_shadow_;

        /**
         * @brief Sprite neobsazeného herního pole
         */
        QPixmap blank_;

        /**
         * @brief Sprite mozne herního pole
         */
        QPixmap possible_;

        /**
         * @brief Velikost herní desky (kolik kamenů je v herní sloupci)
         */
        unsigned size_;

        /**
         * @brief Vykreslovaná hra
         */
        const MainGame& game_;

        /**
         * @brief Zobrazovanie_nápovedy
         */
        int show_help;

        /**
         * @brief Seznam kamenů, které se změní, pokud hráč provede zamýšlený tah
         */
        std::vector<Coords> current_changes_;

        /**
         * @brief Indikátor, zda je kurzor nad deskou
         */
        bool mouse_over_ = false;


        /**
         * @brief Matice spritů herních polí a kamenů na desce
         */
        std::vector<std::vector<QGraphicsPixmapItem*>> graphics_matrix_;

        /**
         * @brief Vrací velikost grafiky jednoho pole v závislosti na velikost celé desky a počtu kamenů
         * @return Velikost grafiky jednoho pole
         */
        double GetPieceSize() const;
    public:

      /**
       * @brief Zmena stavu zobrazovania nápovedy
       * @param state Nový stav pre zobrazenie nápovedy
       */
        void Set_show_help(int state){show_help = state;}

        /**
         * @brief Konstruktor grafiky herní desky
         * @param game Vykreslovaná hra
         */
        BoardGraphics(const MainGame& game);

        /**
         * @brief Překreslí herní desku dle aktuálního stavu hry.
         */
        void Repaint();

        /**
         * @brief Událost uvolnění tlačítka myši
         * @param mouseEvent Popis události
         */
        virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);

    signals:

        /**
         * @brief Signál vyslaný po kliknutí tlačítka myši nad deskou
         * @param x X souřadnice kamene, na který bylo kliknuto
         * @param y Y souřadnice kamene, na který bylo kliknuto
         */
        void ClickSignal(unsigned x, unsigned y);

    public slots:

        /**
         * @brief Slot, který přijímá události při pohybu kurzoru.
         * @param coords Souřadnice pohybu myši
         */
        void MouseMoveSlot(QPointF coords);

        /**
         * @brief Slot, který přijímá událost při vstoupení kurzoru nad scénu.
         */
        void EnterSlot();

        /**
         * @brief Slot, který přijímá událost při vystoupení kurzoru ze scény.
         */
        void LeaveSlot();

    };
}
#endif
