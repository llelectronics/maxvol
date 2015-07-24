#ifndef VOLHELPER_HPP
#define VOLHELPER_HPP

#include <QObject>
#include <QProcess>
#include <QVariant>
#include <QSettings>
#include <QString>
#include <QDir>
#include <QStandardPaths>
#include <QCoreApplication>


class volHelper : public QObject
{   Q_OBJECT

public:
    QString config_dir;
    QString volMax;
    bool autostart;

public slots:
    void setMaxVol(QVariant maxVol)
    {
        QProcess *setVolProcess = new QProcess();
        setVolProcess->start("pactl set-sink-volume sink.primary " + maxVol.toString() + "%");
        volMax = maxVol.toString();
        saveConfig();
    }
    void setAutostart(QVariant restore)
    {
        autostart = restore.toBool();
        saveConfig();
    }
    void loadConfig()
    {
        config_dir = QDir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation))
                    .filePath(QCoreApplication::applicationName());
        QSettings settings(config_dir+"/settings.ini",QSettings::IniFormat);

        //qDebug() << "Config dir: " + config_dir;
        settings.beginGroup("Global");
        QString savedVol = settings.value("Volume", "").toString();
        bool isAuto = settings.value("Autostart", "").toBool();
        if (isAuto && !savedVol.isEmpty()){
            setMaxVol(savedVol);
        }
        settings.endGroup();
    }
    void saveConfig()
    {
        config_dir = QDir(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation))
                    .filePath(QCoreApplication::applicationName());
        QSettings settings(config_dir+"/settings.ini",QSettings::IniFormat);

        settings.beginGroup("Global");
        settings.setValue("Volume",volMax);
        settings.setValue("Autostart", autostart);
        settings.endGroup();
    }
};



#endif // VOLHELPER_HPP
