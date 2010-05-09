/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) <year> <author> <email@example.com>
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

#ifndef GLUONPLAYER_VIEWITEM_H
#define GLUONPLAYER_VIEWITEM_H

#include <QGraphicsWidget>
#include <QModelIndex>

class QGraphicsSceneMouseEvent;
class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;

namespace GluonPlayer
{
    class ViewItem : public QGraphicsWidget
    {
    Q_OBJECT

    public:
        ViewItem(QGraphicsItem* parent = 0, Qt::WindowFlags wFlags = 0);
        
        virtual void setModelIndex(const QModelIndex &index);
        QModelIndex modelIndex() const;

    protected:
        QModelIndex m_index;

        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

    signals:
        void activated(QModelIndex);
    };

}

#endif // GLUONPLAYER_VIEWITEM_H
