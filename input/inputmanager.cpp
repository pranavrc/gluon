/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Kim Jung Nissen <jungnissen@gmail.com>
 * Copyright (C) 2010 Laszlo Papp <djszapi@archlinux.us>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */
#include "inputmanager.h"

#include "inputmanagerprivate.h"
#include "gluondevices.h"

#ifdef Q_WS_X11
#include "detectlinux.h"
#endif

#ifdef Q_WS_MAC
#include "detectmac.h"
#endif

#ifdef Q_WS_WIN
#include "detectwin.h"
#endif

#include <QKeyEvent>
#include <QtCore/QCoreApplication>
#include <QtGui/QMessageBox>
#include <QtCore/QDebug>

using namespace GluonInput;

GLUON_DEFINE_SINGLETON(InputManager)

InputManager::InputManager( QObject* parent )
    : d( new InputManagerPrivate )
    , m_filteredObj(0)
{
    init();
}

InputManager::~InputManager()
{
}

void InputManager::init()
{
    QObject* parent = QCoreApplication::instance();
    if( !parent )
    {
        qDebug() << "No QCoreApplication instance found, the InputManager instance may be leaked when leaving";
    }

#ifdef Q_WS_X11
    d->m_detect = new DetectLinux( parent );
#endif

#ifdef Q_WS_MAC
    d->m_detect = new DetectMac( parent );
#endif

#ifdef Q_WS_WIN
    d->m_detect = new DetectWin( parent );
#endif
    if( d->m_detect )
    {
        if( !d->m_detect->isReadable() )
        {
            setInputManagementType(QT_INPUT_HIGHLEVEL);
            if (filteredObject())
                installEventFiltered(filteredObject());
            // else
                // qDebug() << "Null filtered object pointer - no install";

            InputDevice* keyboard = new Keyboard( 0 );
            d->m_detect->addKeyboard( static_cast<Keyboard*>( keyboard ) );
            InputDevice* mouse = new Mouse( 0 );
            d->m_detect->addMouse( static_cast<Mouse*>( mouse ) );
        }
        else
        {
#ifdef Q_WS_X11
            setInputManagementType(LINUX_INPUT_LOWLEVEL);
#elif defined(Q_WS_MAC)
            setInputManagementType(MAC_INPUT_LOWLEVEL);
#elif defined(Q_WS_WIN)
            setInputManagementType(WIN_INPUT_LOWLEVEL);
#endif
            if (filteredObject())
                removeEventFiltered(filteredObject());
            // else
                // qDebug() << "Null filtered object pointer - no remove";
            d->m_detect->detectDevices();
        }
    }
    else
    {
        qDebug() << "Instance not created, fail!";
    }
}

void InputManager::detectDevices()
{
    d->m_detect->detectDevices();
}

void InputManager::setAllEnabled( bool enable )
{
    d->m_detect->setAllEnabled( enable );
}

unsigned int InputManager::deviceCount()
{
    return inputList().size();
}

unsigned int InputManager::keyboardCount()
{
    return d->m_detect->keyboardList().size();
}

unsigned int InputManager::mouseCount()
{
    return d->m_detect->mouseList().size();
}

unsigned int InputManager::joystickCount()
{
    return d->m_detect->joystickList().size();
}

unsigned int InputManager::touchCount()
{
    return d->m_detect->touchList().size();
}

unsigned int InputManager::unknownDeviceCount()
{
    return d->m_detect->unknownDeviceList().size();
}

QList<Keyboard*> InputManager::keyboardList()
{
    return d->m_detect->keyboardList();
}

QList<Mouse*> InputManager::mouseList()
{
    return d->m_detect->mouseList();
}

QList<Joystick*> InputManager::joystickList()
{
    return d->m_detect->joystickList();
}

QList<Touch*> InputManager::touchList()
{
    return d->m_detect->touchList();
}

QList<InputDevice*> InputManager::unknownDeviceList()
{
    return d->m_detect->unknownDeviceList();
}

InputList InputManager::inputList()
{
    return d->m_detect->inputList();
}

Keyboard* InputManager::keyboard( int id )
{
    if( !d->m_detect->keyboardList().isEmpty() )
    {
        return d->m_detect->keyboardList().at( id );
    }
    return 0;
}

Mouse* InputManager::mouse( int id )
{
    if( !d->m_detect->mouseList().isEmpty() )
    {
        return d->m_detect->mouseList().at( id );
    }
    return 0;
}

Joystick* InputManager::joystick( int id )
{
    if( !d->m_detect->joystickList().isEmpty() )
    {
        return d->m_detect->joystickList().at( id );
    }
    return 0;
}

Touch* InputManager::touch( int id )
{
    if( !d->m_detect->touchList().isEmpty() )
    {
        return d->m_detect->touchList().at( id );
    }
    return 0;
}

InputDevice* InputManager::input( int id )
{
    if( !d->m_detect->inputList().isEmpty() )
    {
        return d->m_detect->inputList().at( id );
    }
    return 0;
}

bool InputManager::eventFilter(QObject* object, QEvent* event)
{
    if (object != m_filteredObj)
        return false;

    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        keyboard(0)->setButtonState(keyEvent->key(), 1);
		emit keyPressed(keyEvent->key());
        return true;
    }

    if (event->type() == QEvent::KeyRelease)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        keyboard(0)->setButtonState(keyEvent->key(), 0);
		emit keyReleased(keyEvent->key());
        return true;
    }

    if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        mouse(0)->setPosition( mouseEvent->pos( ) );
        return true;
    }

    if (event->type() == QEvent::Wheel)
    {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent *>(event);
        mouse(0)->setHWheelPosition( wheelEvent->x( ) );
        mouse(0)->setHWheelPosition( wheelEvent->y( ) );
        return true;
    }

    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        switch (mouseEvent->button()) {
        case Qt::LeftButton:
            return true;
        case Qt::RightButton:
            return true;
        case Qt::MiddleButton:
            return true;
        case Qt::XButton1:
            return true;
        case Qt::XButton2:
            return true;
        default:
            return false;
        }
    }

	if (event->type() == QEvent::Gesture)
	{
		QGestureEvent *gestureEvent = static_cast<QGestureEvent *>(event);
        return true;
	}

	if (event->type() == QEvent::GestureOverride)
	{
		QGestureEvent *gestureEvent = static_cast<QGestureEvent *>(event);
        return true;
	}

    return false;
}

void InputManager::installEventFiltered(QObject *filteredObj)
{
    filteredObj->installEventFilter(this);
}

void InputManager::removeEventFiltered(QObject *filteredObj)
{
    filteredObj->removeEventFilter(this);
}

QObject* InputManager::filteredObject()
{
    return m_filteredObj;
}

void InputManager::setFilteredObject(QObject *filteredObj)
{
    if( filteredObj && inputManagementType() == QT_INPUT_HIGHLEVEL )
    {
        if( m_filteredObj )
            removeEventFiltered(m_filteredObj);
        installEventFiltered(filteredObj);
    }

    m_filteredObj = filteredObj;
}

InputManager::InputManagementType InputManager::inputManagementType() const
{
    return m_inputManagementType;
}

void InputManager::setInputManagementType( InputManager::InputManagementType inputManagementType )
{
    m_inputManagementType = inputManagementType;
}

#include "inputmanager.moc"
