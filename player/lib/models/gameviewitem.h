/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2011 Laszlo Papp <djszapi@archlinux.us>
 * Copyright (C) 2011 Shantanu Tushar <jhahoneyk@gmail.com>
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

#ifndef GLUONPLAYER_GAMEVIEWITEM_H
#define GLUONPLAYER_GAMEVIEWITEM_H

#include "gluon_player_export.h"

#include <QtCore/QStringList>

namespace GluonPlayer
{
    /**
     *\brief Model which contains a list of the installed games
     *
     * This model can be used to obtain a list of all the installed games
     * Use the different roles of the model to obtain required properties.
     *
     */

    class GLUON_PLAYER_EXPORT GameViewItem
    {
        public:
            enum Status {
                Downloadable,
                Installed,
                Upgradable
            };

            explicit GameViewItem ( const QString& gameName, const QString& description,
                                    const QString& projectDirName, const QString& projectFileName,
                                    const Status &status, const QString &id);
            virtual ~GameViewItem() {}

            QString gameName() const;
            QString gameDescription() const;
            QString projectDirName() const;
            QString projectFileName() const;
            QStringList screenshotUrls() const;
            Status status() const;
            QString id() const;

        private:
            QString m_gameName;
            QString m_gameDescription;
            QString m_projectDirName;
            QString m_projectFileName;
            QStringList m_screenshotUrls;
            Status m_status;
            QString m_id;
    };
}

#endif // GLUONPLAYER_GAMEITEMSMODEL_H
