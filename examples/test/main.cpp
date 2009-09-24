/*
 * This file is part of the KGLEngine2D project.
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KDebug>
#include <iostream>



#include <gluon/kcl/kcldetect.h>
#include <gluon/kcl/kclcustominput.h>
#include <gluon/kcl/widgets/kclcustominputdialog.h>
#include <gluon/kcl/kclbutton.h>
#include <gluon/kal/widgets/kalplayerwidget.h>
#include <gluon/kal/kalmusic.h>
#include <gluon/kcl/widgets/kclinputwidget.h>
#include <gluon/kcl/widgets/kclpressbutton.h>
#include <gluon/gluonmainwindow.h>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QToolBar>
#include <KAction>
#include <KIcon>
#include <QTextEdit>
#include <QSpinBox>
using namespace std;


int main(int argc, char *argv[])
{
    KAboutData aboutData("main", 0,
                         ki18n("gluon"), "1.0",
                         ki18n("gluon"),
                         KAboutData::License_GPL,
                         ki18n("Copyright (c) 2009 Developer"));
    KCmdLineArgs::init(argc, argv, &aboutData);

    KApplication app;


//
    KCLCustomInput * input = new KCLCustomInput;
    input->addButton("FIRE",KCLDetect::joystick(),BTN_TRIGGER);
    input->addAbsAxis("AXE X",KCLDetect::joystick(),ABS_X);
    input->addAbsAxis("AXE Y",KCLDetect::joystick(),ABS_Y);
    input->addButton("KILL",KCLDetect::mouse(),BTN_LEFT);

    KCLCustomInputDialog * dialog = new KCLCustomInputDialog;
    dialog->addCustomInput(input);

    dialog->exec();



app.exec();


}
