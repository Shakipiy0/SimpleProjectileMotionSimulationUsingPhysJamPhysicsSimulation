#ifndef ENGINE_H
#define ENGINE_H

#include <QDialog>
#include <QGraphicsScene>
#include <QTimer>
#include "particle.h"
#include <QList>
#include <QLineEdit>


QT_BEGIN_NAMESPACE
namespace Ui { class engine; }
QT_END_NAMESPACE

class engine : public QDialog
{
    Q_OBJECT

public:
    engine(QWidget *parent = nullptr);
    ~engine();
private:
    Ui::engine * ui;
    QGraphicsScene *scene;
    QTimer * timer;
    QList <Particle*> particles;
    QLineEdit *velocityInput;
    QLineEdit *angleInput;
    qreal simulationSpeed;

protected:
    void spawn(int num);

protected slots:
    void spawnProjectile();
    void refreshBg();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void updateSimulation();
    void on_pushButton_3_clicked();
};
#endif // ENGINE_H
