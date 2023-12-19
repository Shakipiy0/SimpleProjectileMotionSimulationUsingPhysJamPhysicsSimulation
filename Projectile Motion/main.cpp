/*** Physics Simulation using the Qt Framework
*created by Julio Morgado
***/

#include "engine.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    engine w;
    w.show();
    w.setWindowTitle("Jonathan's Projectile Motion Simulator");
    return a.exec();
}
