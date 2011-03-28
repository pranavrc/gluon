/******************************************************************************
 * This file is part of the Gluon Development Platform
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

#include "gameitemsmodel.h"

#include "player/lib/atticamanager.h"

#include <core/gluon_global.h>
#include <engine/gameproject.h>

#include <attica/content.h>

#include <QtCore/QHash>
#include <QtCore/QByteArray>
#include <QtCore/QDebug>

using namespace GluonPlayer;

GameItemsModel::GameItemsModel( QObject* parent )
    : QAbstractListModel( parent )
{
    QDir m_dir;
    m_dir.cd( GluonCore::Global::dataDirectory() + "/gluon/games" );
    QStringList gameDirNameList = m_dir.entryList( QStringList() << QString("*" + GluonEngine::projectSuffix), QDir::Dirs | QDir::NoDotAndDotDot );
    foreach( const QString& gameDirName, gameDirNameList)
    {
        QDir gameDir = m_dir;
        gameDir.cd( gameDirName );
        QStringList gluonProjectFiles = gameDir.entryList( QStringList( GluonEngine::projectFilename ) );
        if( !gluonProjectFiles.isEmpty() )
        {
            QString projectFileName = gameDir.absoluteFilePath( gluonProjectFiles.at( 0 ) );
            GluonEngine::GameProject project;
            project.loadFromFile( projectFileName );
            GameViewItem* gameViewItem = new GameViewItem(project.name(), project.description(), gameDir.path(), projectFileName,
                                      GameViewItem::Installed, project.property("id").toString());
            m_gameViewItems.append(gameViewItem);
        }
    }

    QHash<int, QByteArray> roles;
    roles[GameNameRole] = "gameName";
    roles[GameDescriptionRole] = "gameDescription";
    roles[ProjectFileNameRole] = "projectFileName";
    roles[ProjectDirNameRole] = "projectDirName";
    roles[ScreenshotUrlsRole] = "screenshotUrls";
    roles[IDRole] = "id";
    roles[StatusRole] = "status";
    setRoleNames(roles);

    fetchGamesList();
}

QVariant GameItemsModel::data( const QModelIndex& index, int role ) const
{
    if (index.row() < 0 || index.row() > m_gameViewItems.count())
        return QVariant();

    switch (role) {
    case Qt::UserRole:
        break;
    case GameNameRole:
        return m_gameViewItems.at( index.row() )->gameName();
    case GameDescriptionRole:
        return m_gameViewItems.at( index.row() )->gameDescription();
    case ProjectDirNameRole:
        return m_gameViewItems.at( index.row() )->projectDirName();
    case Qt::DisplayRole:
    case ProjectFileNameRole:
        return m_gameViewItems.at( index.row() )->projectFileName();
    case ScreenshotUrlsRole:
        return m_gameViewItems.at( index.row() )->screenshotUrls();
    case IDRole:
        return m_gameViewItems.at( index.row() )->id();
    case StatusRole:
        return m_gameViewItems.at (index.row() )->status();
    default:
        break;
    }

    return QVariant();
}

int GameItemsModel::rowCount( const QModelIndex& /* parent */ ) const
{
    return m_gameViewItems.count();
}

int GameItemsModel::columnCount( const QModelIndex& /* parent */ ) const
{
    return 1;
}

QVariant GameItemsModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if( section == 0 )
    {
        return QString( "Game" );
    }

    return QAbstractItemModel::headerData( section, orientation, role );
}

void GameItemsModel::fetchGamesList()
{
    if( AtticaManager::instance()->isProviderValid() )
    {
        providersUpdated();
    }
    else
    {
        connect( AtticaManager::instance(), SIGNAL( gotProvider() ), SLOT( providersUpdated() ) );
    }
}

void GameItemsModel::providersUpdated()
{
    if( AtticaManager::instance()->isProviderValid() )
    {
        QStringList gluonGamesCategories;
        gluonGamesCategories << "4400" << "4410" << "4420" << "4430" << "4440";
        Attica::Category::List categories;

        foreach (QString gluonCategory, gluonGamesCategories) {
            Attica::Category category;
            category.setId(gluonCategory);
            categories.append(category);
        }

        Attica::ListJob<Attica::Content> *job =
            AtticaManager::instance()->provider().searchContents(categories);
        connect( job, SIGNAL( finished( Attica::BaseJob* ) ), SLOT( processFetchedGamesList( Attica::BaseJob* ) ) );
        job->start();
    }
    else
    {
        qDebug() << "No providers found.";
    }
}

void GameItemsModel::processFetchedGamesList(Attica::BaseJob* job)
{
    qDebug() << "Game List Successfully Fetched from the server!";

    Attica::ListJob<Attica::Content> *contentJob = static_cast<Attica::ListJob<Attica::Content> *>( job );
    if( contentJob->metadata().error() == Attica::Metadata::NoError )
    {
        for( int i = 0; i < contentJob->itemList().count(); ++i )
        {
            Attica::Content c( contentJob->itemList().at(i));
            GameViewItem* gameViewItem = new GameViewItem(c.name(), c.description(), "", "",
                                      GameViewItem::Downloadable, c.id());
            m_gameViewItems.append(gameViewItem);
            reset();
        }
}
    else
    {
        qDebug() << "Could not fetch information";
    }
}

#include "gameitemsmodel.moc"
