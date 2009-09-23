#ifndef KCLCUSTOMINPUT_H
#define KCLCUSTOMINPUT_H

#include "kcldetect.h"
#include "kclinput.h"

#include <QObject>
#include <QList>
#include <QMap>

class KCLCustomInput : public QObject
{
    Q_OBJECT
public:
    KCLCustomInput(QObject * parent=0);
    void addButton(QString name, KCLInput* input, int keyCode);
    void addButton(QString name);
    void remButton(QString name);
    void addAbsAxis(QString name, KCLInput * input, int axis);
    void addRelAxis(QString name,KCLInput* input, int axis);
    void remAbsAxis(QString name);
    void remRelAxis(QString name);

    bool button(const QString& name);
    int relAxisValue(const QString &name);
    int absAxisValue(const QString &name);
signals:
    void buttonPressed(QString name);
    void buttonReleased(QString name);
    void absAxisChanged(QString name,int value);
    void relAxisChanged(QString name,int value);

protected slots:
     void inputEvent(KCLInputEvent * event);


private:
    QMap <QString,QPair<KCLInput*,int> > m_buttons;
    QMap <QString,QPair<KCLInput*,int> > m_absAxis;
    QMap <QString,QPair<KCLInput*,int> > m_relAxis;


};




#endif // KCLCUSTOMINPUT_H