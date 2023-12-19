    /*** Physics Simulation using the Qt Framework
    *created by Julio Morgado
    ***/

#include "engine.h"
#include "ui_engine.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QtMath>
#include <QMessageBox>

    engine::engine(QWidget *parent)
        : QDialog(parent)
        , ui(new Ui::engine)
    {
        ui->setupUi(this);
        simulationSpeed = 0.1;
        scene = new QGraphicsScene(this);
        QRect bg(0,0,1498, 848);
        scene->setSceneRect(bg);
        ui->graphicsView->setScene(scene);
        ui->graphicsView->setRenderHint(QPainter::Antialiasing);

        timer = new QTimer();
        connect(timer, SIGNAL(timeout()), scene ,SLOT(advance()));
        connect(timer, SIGNAL(timeout()), this ,SLOT(refreshBg()));
        timer->start(50);
    }

    void engine::spawnProjectile()
    {
        // Spawn a single particle (projectile) at the bottom left corner
        qreal startX = 0;
        qreal startY = scene->height();
        qreal diameter = 20;  // You can adjust this value based on your preferences

        Particle *projectile = new Particle(startX, startY, diameter, diameter, "Ball");
        particles << projectile;
        scene->addItem(particles.last());
    }

    engine::~engine()
    {
        delete ui;
    }

    void engine::spawn(int num)
    {
        for(int i = 0; i < num; i++){
            qreal d=40;
            qreal x = 0;
            qreal y = scene->height() - d;
            Particle * obj = new Particle(x,y,d,d);
            particles << obj;
            scene->addItem(particles.last());
        }
    }

    void engine::refreshBg()
    {
        scene->setBackgroundBrush(QBrush(QColor(135,206,250)));
    }


    void engine::updateSimulation()
    {
        // Advance the scene and particles
        scene->advance();

        // Adjust particle velocities based on simulation speed
        for (Particle *particle : particles)
        {
            particle->v->mult(simulationSpeed, "xy");
            particle->a->mult(simulationSpeed, "xy");
        }

        // Optionally, perform additional updates or checks

        // Refresh the background or perform any other necessary actions
        refreshBg();
    }


void engine::on_pushButton_clicked()
{
        // Get the user input for velocity and angle
        qreal initialVelocity = ui->initialvelocity->value();
        qreal launchAngle = ui->launchangle->value();

        // Calculate the initial velocity components based on angle
        qreal initialVelocityX = initialVelocity * qCos(qDegreesToRadians(launchAngle));
        qreal initialVelocityY = initialVelocity * qSin(qDegreesToRadians(launchAngle));

        qreal maxheight = qPow(initialVelocityY,2)/(2*9.81) ;
        qreal time = initialVelocityY/9.81;

        ui->textBrowser->setText(QString::number(maxheight));
        ui->textBrowser_2->setText(QString::number(time));


        // Spawn a projectile with the calculated initial velocity components
        spawnProjectile();
        particles.last()->v->setX(initialVelocityX);
        particles.last()->v->setY(-initialVelocityY);  // Negative sign for Y due to Qt's coordinate system
}


void engine::on_pushButton_2_clicked()
{
        ui->launchangle->clear();
        ui->initialvelocity->clear();
        ui->textBrowser->clear();
        ui->textBrowser_2->clear();
        scene->clear();
}


void engine::on_pushButton_3_clicked()
{
        QMessageBox msgBOX;
        msgBOX.setWindowTitle("Algorithm");
        msgBOX.setTextFormat(Qt::RichText);
        QString Text1 = tr("<strong> This is Jonathan's Simple Projectile Motion Simulation </strong> \n");
        QString Text2 = tr("<br/>  This is a modification from the <strong> PhysJam Physics simulation </strong> from GitHub\n");
        QString Text3 = tr("<br/> This programme is used to simulate the parabolic trajectory of the ball during its motion \n");
        QString Text4 = tr("<br/> It also computes the highest height that the ball can reach and the time it took to reach that height \n");
        QString Text5 = tr("<br/> <strong> engine.h </strong> : contains the variables and functions required to make the simulation and compile functions from particle.h and vector.h \n");
        QString Text6 = tr("<br/> <strong> particle.h </strong> : contains variable and function that designs the physical attributes of the particle or in this case 'ball' \n");
        QString Text7 = tr("<br/> <strong> vector.h </strong> : contains the variable and function that will contribute to the movement of the particle \n");
        QString Text8 = tr("<br/> <strong> .cpp </strong> : contains the instruction for variables or new functions for each respective headers \n");
        msgBOX.setText(Text1 + Text2 + Text3 + Text4 + Text5 + Text6 + Text7 + Text8);
        msgBOX.exec();
}

