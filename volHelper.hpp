#ifndef VOLHELPER_HPP
#define VOLHELPER_HPP

#include <QObject>
#include <QProcess>
#include <QVariant>


class volHelper : public QObject
{   Q_OBJECT
public slots:
    void setMaxVol(QVariant maxVol)
    {
        QProcess *setVolProcess = new QProcess();
        setVolProcess->start("pactl set-sink-volume sink.primary " + maxVol.toString() + "%");
    }
};



#endif // VOLHELPER_HPP
