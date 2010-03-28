/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright (C) 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright (C) 2008 Charles Huet <packadal@gmail.com>
 * Copyright (C) year  name of author
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

#include <QDebug>
#include <iostream>

#include <gluon/audio/sound.h>
#include <gluon/audio/engine.h>

int main(int argc, char *argv[])
{
    GluonAudio::Engine::instance();

    GluonAudio::Sound *left = new GluonAudio::Sound("/usr/share/sounds/alsa/Front_Left.wav");
    GluonAudio::Sound *right = new GluonAudio::Sound("/usr/share/sounds/alsa/Front_Right.wav");
    GluonAudio::Sound *center = new GluonAudio::Sound("/usr/share/sounds/alsa/Front_Center.wav");

    left->setPosition(-1, 0, 0);
    right->setPosition(1, 0, 0);

    qDebug() << "Playing left. Press enter to continue.";
    left->play();
    std::cin.get();

    qDebug() << "Playing right. Press enter to continue.";
    right->play();
    std::cin.get();

    qDebug() << "Playing center. Press enter to continue.";
    center->play();
    std::cin.get();

    delete left;
    delete right;
    delete center;

    GluonAudio::Engine::close();
}
