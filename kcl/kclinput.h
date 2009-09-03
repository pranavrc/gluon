#ifndef KCLINPUT_H
#define KCLINPUT_H

#include <QThread>
#include <QMap>
#include <QPair>
#include <QPoint>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <linux/input.h>
#include <KDebug>
#include "kclcode.h"


enum DEVICE {KCL_KEYBOARD,KCL_MOUSE,KCL_JOYSTICK,KCL_TABLET,KCL_TOUCHPAD,KCL_UNKNOWN};

class KCLInput;
class KCLThread;
class KCLInputEvent;

class AbsVal
{
public:
    AbsVal(int v=0,int m=0, int M=0, int f=0, int F=0)
    {
        value = v;
        min =m;
        max = M;
        flat = f;
        fuzz = F;
    }
    int value;
    int min;
    int max;
    int flat;
    int fuzz;
};
/**
 * @class KCLInputEvent gluon/kcl/kclinput.h <Gluon/KCL/KCLInput>
 *
 * @short Provides a input events
 *
 * This class provide an event like QEvent ( but it's not a QEvent child) which contain all information of an input status
 *
 * @author sacha schutz <istdasklar@gmail.com>
 */

class KCLInputEvent
{
public:
    KCLInputEvent(unsigned long tvSec_,unsigned long tvUsec_,unsigned short type_, unsigned short code_, unsigned short value_);
    KCLInputEvent(struct input_event ev);
    unsigned long tvSec(){return m_inputEvent.time.tv_sec;}
    unsigned long tvUsec(){return m_inputEvent.time.tv_usec;}
    /**
    * For example, if you press a button, it will return EV_KEY.
    *If you move your mouse, it will return EV_REL. If you move your joystick it will return EV_ABS.
    * Please look in evdev type for more information
    * @return the type of the input status .
    */
    unsigned short type(){return m_inputEvent.type;}
    /**
    * For example the code of Mouse button left is : LeftBtn. Look on this page to see the code list.
    * @return  the code of the input status.
    */
    unsigned short code(){return m_inputEvent.code;}

    /**
    * For example the value after press a button is 1.
    * If you move an axis, the value will return the axis value.
    * @return the value of the input status.
    */
    unsigned int value(){return m_inputEvent.value;}

    /**
    * convert KCLInputEvent into a standard C input_event
    * @return an input_event
    */
    struct input_event inputEvent(){return m_inputEvent;}
private:
    struct input_event m_inputEvent;
};

//---------------------------------------------------------------------------------------------
/**
 * @class KCLThread gluon/kcl/kclinput.h <Gluon/KCL/KCLInput>
 *
 * @short Provides a QThread witch listen the input status.
 * @author sacha schutz <istdasklar@gmail.com>
 */

class KCLThread : public QThread
{
    Q_OBJECT
public:
    KCLThread(const QString& name, QObject *parent=0);
    ~KCLThread(){close(m_fd);}
    virtual void run();
signals:
    /**
    * emit a KCLInput. This signal is emited when somthing happen on a device.
    */
    void emitInputEvent(KCLInputEvent * event);
protected:
    bool openDevice(const QString &device);
    void closeDevice(){close(m_fd);}
private:
    int m_fd;
};
//---------------------------------------------------------------------------------------------

/**
 * @class KCLInput gluon/kcl/kclinput.h <Gluon/KCL/KCLInput>
 *
 * @short provide an object that represent an input.
 * This is the class mother of all device you want to use. It return you all information about the device, for example the name.
 * And it return the status of the device, it means the type, code, and value.
 * @author sacha schutz <istdasklar@gmail.com>

 * @section creating Creating a KCLInput
 * The easiest way to create usable KCLInput is to set it by the evdev file name.
 * @code
 * KCLInput * myInput  = new KCLInput("/dev/input/event2");
 * kDebug()<<myInput->name();
 * @endcode
 */

class KCLInput : public QObject
{
    Q_OBJECT
public:

    KCLInput(const QString& device,QObject * parent=0);
    ~KCLInput(){inputListener->exit();}
    /**
    * @return the id of vendor
    */
    unsigned int vendor(){return m_device_info.vendor;}
    /**
    * @return the id of product
    */
    unsigned int product(){return m_device_info.product;}
    /**
    * @return the version driver of the device
    */
    unsigned int version(){return m_device_info.version;}
    /**
    * @return the bus of the device
    */
    unsigned int bustype(){return m_device_info.bustype;}

    QString device(){return m_device;}
    /**
    * @return the name of the device
    */
    QString name(){return m_deviceName;}
    /**
    * @return the device Type. KCL_KEYBOARD,KCL_MOUSE,KCL_JOYSTICK,KCL_TABLET,KCL_TOUCHPAD,KCL_UNKNOWN;
    * @see DEVICE
    */
    DEVICE deviceType(){return m_deviceType;}
    /**
    * @return true if the button with code is pressed. Otherwise it return false
    * @code
    * KCLInput * myInput = new KCLInput("/dev/input/event3");
    * if ( myInput->button(LeftBtn)) kDebug()<<"clicked";
    * @endcode
    * @see KCLInputEvent
    */
    bool button(int code){return m_buttons.contains(code);}
    /**
    * @return true if a button is pressed.
    * @code
    * KCLInput * myInput = new KCLInput("/dev/input/event3");
    * if ( myInput->anyPress()) kDebug()<<"you have press on something...";
    * @endcode
    * @see KCLInputEvent
    */
    bool anyPress(){if (m_buttons.size()>0) return true; else return false;}

    /**
    * @return true if a motion is done by a motion input.( mouse , joystick ...)
    * @code
    * KCLInput * myInput = new KCLInput("/dev/input/event3");
    * if ( myInput->anyMove()) kDebug()<<"you have move something...";
    * @endcode
    * @see KCLInputEvent
    */
    bool anyMove(){if ( m_move) {m_move=false;return true;} return false; }
    /**
    * @return the axis position. This is a relativ value. For example the mouse return a relativ position.
    * @see KCLInputEvent
    */

    int axisPosition(int code){
        if(m_axisPositions.contains(code))
            return m_axisPositions[code] ;
        else return 0;
    }
    /**
    * @return the axis Absolute value. This is an absolue value. For example the Joystick return an absolu position.
    * @see KCLInputEvent
    */
    int axisAbsolu(int code){
        if(m_axisAbsolus.contains(code))
            return m_axisAbsolus[code] ;
        else return 0;
    }
    /**
    * @return a list of capability button input. For example the mouse will return a list with LeftBtn,RightBtn ....
    * @see KCLInputEvent
    */
    QList<int> buttonCapabilities(){return m_buttonCapabilities;}
      /**
    * @return the axis capability..This is usefull to know the capability of a joystick .
    * @see KCLInputEvent
    */
    AbsVal axisCapability(int axisCode){return m_axisCapabilities[axisCode];}
    bool error(){return m_error;}
        /**
    * this function can be reimplemented to customize the event Loop.
     * @code
    * void MyInput::inputEventFilter(KCLInputEvent * event)
    *{
    * switch ( event->type())
    *{
    *case EV_KEY : //do something....
    *}
    *}
    * if ( myInput->anyMove()) kDebug()<<"you have move something...";
    * @endcode
    * @see KCLInputEvent
    */
    virtual void inputEventFilter(KCLInputEvent * event);

public slots:
    void slotInputEvent(KCLInputEvent * event);

protected :
        void readInformation();

private:
KCLThread * inputListener;
struct input_id m_device_info;
struct input_event m_currentEvent;
QString m_device;
QString m_deviceName;
DEVICE m_deviceType;

QList<int> m_buttons;
QMap<int,int> m_axisPositions;
QMap<int,int> m_axisAbsolus;
QList<int> m_buttonCapabilities;
QMap<int, AbsVal> m_axisCapabilities;
bool m_move;
bool m_error;

};

//---------------------------------------------------------------------------------------------






#endif // KCLINPUT_H
