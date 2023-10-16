#ifndef CIRCULARPROGRESSWIDGET_H
#define CIRCULARPROGRESSWIDGET_H
#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QBoxLayout>
#include <QBasicTimer>

class TextProgressWidget : public QWidget {
     Q_OBJECT
     QLabel *pLabel;
     QString title;
     QString progress;
     int numprogress;
     QBasicTimer timer;
protected:
     void timerEvent(QTimerEvent *event) override;

public:
 explicit TextProgressWidget(QLabel *pProgreesWidget, const QString& caption, int interval = 200, QWidget * p = 0,int numProgressSymbols = 5 ) : QWidget(p) {
        setMinimumSize(400, 40);
        title = caption;
        numprogress = numProgressSymbols;
        timer.start(interval, this);

        pLabel = pProgreesWidget;
/*
        pLabel = new QLabel(this);
        pLabel->setText(title);

        QHBoxLayout * l = new QHBoxLayout(this);
        l->addWidget(pLabel);
        setLayout(l);
*/
      }

     ~TextProgressWidget()
     {
         timer.stop();
     }
};


class CircularProgressWidget : public QWidget {
    Q_OBJECT
    qreal p; // progress 0.0 to 1.0
  public:

    CircularProgressWidget(QWidget * p = 0) : QWidget(p), p(0) {
      setMinimumSize(54, 54);
    }

    void upd(qreal pp) {
      if (p == pp) return;
      p = pp;
      update();
    }

  void paintEvent(QPaintEvent *) {
    qreal pd = p * 360;
    qreal rd = 360 - pd;
    QPainter p(this);
//    p.fillRect(rect(), Qt::white);
/*    p.translate(4, 4);
*/

/*    QTransform transform;
    transform.rotate(45.0);
    p.setWorldTransform(transform);
*/
    p.setRenderHint(QPainter::Antialiasing);
    QPainterPath path, path2;
    path.moveTo(25, 0);
    path.arcTo(QRectF(0, 0, 50, 50), 90, 270.0);//-pd);
    QPen pen, pen2;
    pen.setCapStyle(Qt::FlatCap);
    pen.setColor(QColor("#30b7e0"));
    pen.setWidth(2);
    p.strokePath(path, pen);

//    transform.rotate(0.0);
//    p.setWorldTransform(transform);
    //p.translate(4, 4);

    //p.translate(-4, -4);
  /*  path2.moveTo(25, 0);
    pen2.setWidth(2);
    pen2.setColor(QColor("#d7d7d7"));
    pen2.setCapStyle(Qt::FlatCap);
    pen2.setDashPattern(QVector<qreal>{0.5, 1.105});
    path2.arcTo(QRectF(0, 0, 50, 50), 90, rd);
    pen2.setDashOffset(2.2);
    p.strokePath(path2, pen2);*/
  }
};


#endif // CIRCULARPROGRESSWIDGET_H
