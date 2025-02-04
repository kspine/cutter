#ifndef VISUALNAVBAR_H
#define VISUALNAVBAR_H

#include <QToolBar>
#include <QGraphicsScene>

#include "core/Cutter.h"

#include <rz_core.h>

#include <memory>

class MainWindow;
class QGraphicsView;

class VisualNavbar : public QToolBar
{
    Q_OBJECT

    struct XToAddress
    {
        double x_start;
        double x_end;
        RVA address_from;
        RVA address_to;
    };

public:
    explicit VisualNavbar(MainWindow *main, QWidget *parent = nullptr);

public slots:
    void paintEvent(QPaintEvent *event) override;
    void updateGraphicsScene();

private slots:
    void fetchAndPaintData();
    void fetchStats();
    void drawSeekCursor();
    void drawPCCursor();
    void drawCursor(RVA addr, QColor color, QGraphicsRectItem *&graphicsItem);
    void on_seekChanged(RVA addr);

private:
    QGraphicsView *graphicsView;
    QGraphicsScene *graphicsScene;
    QGraphicsRectItem *seekGraphicsItem;
    QGraphicsRectItem *PCGraphicsItem;
    MainWindow *main;

    std::unique_ptr<RzCoreAnalysisStats, decltype(&rz_core_analysis_stats_free)> stats;
    unsigned int statsWidth = 0;
    unsigned int previousWidth = 0;

    QList<XToAddress> xToAddress;
    bool blockTooltip;

    RVA localXToAddress(double x);
    double addressToLocalX(RVA address);
    QList<QString> sectionsForAddress(RVA address);
    QString toolTipForAddress(RVA address);

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // VISUALNAVBAR_H
