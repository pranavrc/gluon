/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Shantanu Tushar Jha <jhahoneyk@gmail.com>
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

#include "highscoresmodel.h"
#include <core/gluonobject.h>
#include <core/gdlhandler.h>
#include <core/gluon_global.h>

#include <QDebug>
#include <QDir>
#include <QTextStream>

using namespace GluonCore;
using namespace GluonPlayer;

static const char serviceURI[] = "gamingfreedom.org";

HighScoresModel::HighScoresModel (QObject* parent)
        : QAbstractTableModel (parent), rootNode (0)
{
    loadData();
}

HighScoresModel::~HighScoresModel()
{
    saveData();
}

QVariant HighScoresModel::data (const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (index.column()) {
        case NameColumn:
            return rootNode->child (index.row())->name();
            break;
        case HighScoreColumn:
            return rootNode->child (index.row())->property("HighScore");
            break;
        case LevelColumn:
            return rootNode->child (index.row())->property("Level");
            break;
        }
    }
    return QVariant();
}

int HighScoresModel::columnCount (const QModelIndex& parent) const
{
    Q_UNUSED (parent);
    return 3;
}

int HighScoresModel::rowCount (const QModelIndex& parent) const
{
    if (rootNode) {
        return rootNode->children().count();
    }
}

QVariant HighScoresModel::headerData (int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case NameColumn:
            return QString("Name");
            break;
        case HighScoreColumn:
            return QString("High Score");
            break;
        case LevelColumn:
            return QString("Level");
            break;
        }
    }

    return QVariant();
}

void HighScoresModel::loadData()
{
    QDir gluonDir = QDir::home();
    gluonDir.mkdir(".gluon/" + QString(serviceURI));
    gluonDir.cd(".gluon/" + QString(serviceURI));
    QString filename = gluonDir.absoluteFilePath("highscores.gdl");

    QFile dataFile(filename);
    if (!dataFile.open(QIODevice::ReadOnly))
        qDebug() << "Cannot open the high scores file";

    QTextStream highScoresReader(&dataFile);
    QString fileContents = highScoresReader.readAll();
    dataFile.close();

    if (fileContents.isEmpty())
        qDebug() << "Something is wrong with the high scores file";
    
    QList<GluonObject*> highScores = GluonCore::GDLHandler::instance()->parseGDL(fileContents, 0);
    rootNode = highScores.at(0);
}

void HighScoresModel::saveData()
{
    QDir gluonDir = QDir::home();
    gluonDir.mkpath (".gluon/" + QString(serviceURI));
    gluonDir.cd(".gluon/" + QString(serviceURI));
    QString filename = gluonDir.absoluteFilePath("highscores.gdl");

    QFile dataFile(filename);
    if (!dataFile.open(QIODevice::WriteOnly))
        qDebug() << "Cannot open the high scores file";

    QList<const GluonObject*> highScores;
    highScores.append(rootNode);
    QTextStream dataWriter(&dataFile);
    dataWriter << GluonCore::GDLHandler::instance()->serializeGDL(highScores);
    dataFile.close();
}

#include "highscoresmodel.moc"