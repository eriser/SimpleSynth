#ifndef AUDIOSETUPWINDOW_H
#define AUDIOSETUPWINDOW_H

#include "RtAudio.h"
#include <QWidget>

class AudioSetupWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AudioSetupWindow(QWidget *parent = 0);

signals:

public slots:

private:

    QVBoxLayout* aswLayout;
    RtAudio
};

#endif // AUDIOSETUPWINDOW_H
