#include "circularprogresswidget.h"
#include <QTimerEvent>

void TextProgressWidget::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer.timerId()) {
       if(progress.count() > numprogress)
           progress.clear();
       else
           progress.append('.');
       QString caption = title + progress;
       pLabel->setText(caption);

    } else
    {
        QWidget::timerEvent(event);
    }
}

