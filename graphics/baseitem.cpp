/*
 * This file is part of the Gluon library.
 * Copyright 2008 Sacha Schutz <istdasklar@free.fr>
 * Copyright 2008 Olivier Gueudelot <gueudelotolive@gmail.com>
 * Copyright 2008 Charles Huet <packadal@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "baseitem.h"
#include <algorithm>
namespace GluonGraphics
{
BaseItem::BaseItem(QObject *parent)
    : QObject(parent)
{
    m_angle = 0;
    m_position=QPointF(0,0);
    m_translate=QPointF(0,0);
    m_scale = QPointF(1,1);
    m_rotateCenter = QPointF(0,0);
    m_shear = QPointF(0,0);
    m_center=QPointF(0,0);
    m_polygon = QPolygonF();
    m_dim = QSizeF();
    m_radius = 1;
    m_zindex = 0;
    initShearMatrix(m_shear);
}

BaseItem::~BaseItem()
{
}

void  BaseItem::updateTransform()
{
    m_matrix.setIdentity();

    m_matrix.translate(Eigen::Vector3f(m_position.x() , m_position.y(), 0));

    m_matrix.scale(Eigen::Vector3f(m_scale.x() , m_scale.y(), 0));
    m_matrix.translate(Eigen::Vector3f(m_translate.x() , m_translate.y(), 0));

    m_matrix.translate(Eigen::Vector3f(m_rotateCenter.x(), m_rotateCenter.y(), 0));
    m_matrix.rotate(Eigen::AngleAxisf(m_angle, AXIS_Z));
    m_matrix.translate(Eigen::Vector3f(-m_rotateCenter.x() , -m_rotateCenter.y(), 0));



    //    m_shearMatrix(0,1) = m_shear.x();
    //    m_shearMatrix(1,0) = m_shear.y();
    //    m_matrix =   m_matrix* m_shearMatrix ;
}

void BaseItem::resetTransform()
{
    m_matrix.setIdentity();
    m_angle  = 0;
    m_scale  = QPointF(1,1);
    m_shear  = QPointF(0,0);
    m_position = QPointF(0,0);
}

void BaseItem::computeGeometry()
{
    //Compute the center
    m_center = QPointF(0,0);
    foreach(const Vertex &p, m_vertexList) {
        m_center += QPointF(p.x(), p.y());
    }
    m_center /= (float)vertexCount();

    //Compute the Polygon
    m_polygon = QPolygonF();
    foreach(const Vertex &p, m_vertexList) {
        m_polygon<<QPointF(p.x(), p.y());
    }

    //Compute width and height
    m_dim.setWidth( m_polygon.boundingRect().width());
    m_dim.setHeight(m_polygon.boundingRect().height());

    //Compute the radius of bounding Circle
    const double cx = m_center.x();
    const double px = m_vertexList[0].x();
    const double cy = m_center.y();
    const double py = m_vertexList[0].y();

    m_radius = sqrt((cx - px) * (cx - px) + (cy - py) * (cy - py));
}

//=======================================================

QPointF BaseItem::transform(const QPointF &p) const
{
    Eigen::Vector3f vect = m_matrix * Eigen::Vector3f(p.x(), p.y(), 0);
    return QPointF(vect.x(), vect.y());
}

//=========================================================

QPolygonF BaseItem::transform(const QPolygonF &p) const
{
    QPolygonF poly;
    foreach(const QPointF &point, p) {
        poly<<transform(point);
    }
    return poly;
}

//=========================================================

QRectF BaseItem::transform(const QRectF &r) const
{
    Eigen::Vector3f a = m_matrix * Eigen::Vector3f(r.x(), r.y(), 0);
    Eigen::Vector3f b = m_matrix * Eigen::Vector3f(r.width(), r.height(), 0);

    return QRectF(a.x(), a.y(), b.x(), b.y());
}

//=========================================================

void BaseItem::createBox(const QSizeF &dim)
{
    clear();
    addVertex(Vertex(-dim.width()/2, -dim.width()/2, Qt::white, QPointF(0 , 0 )));
    addVertex(Vertex( dim.width()/2, -dim.width()/2, Qt::white, QPointF(1 , 0)));
    addVertex(Vertex( dim.width()/2,  dim.width()/2, Qt::white, QPointF(1 , 1)));
    addVertex(Vertex(-dim.width()/2,  dim.width()/2, Qt::white, QPointF(0 , 1)));
    computeGeometry();
}

void BaseItem::createPolygon(const QPolygonF &poly)
{
    clear();
    foreach(const QPointF &p, poly) {
        addVertex(Vertex(p.x(), p.y() , Qt::white, QPointF(p.x(), p.y())));
    }
    computeGeometry();
}

void BaseItem::createLine(const QLineF &line)
{
    clear();
    addVertex(Vertex(line.x1(), line.y1(), Qt::white));
    addVertex(Vertex(line.x2(), line.y2(), Qt::white));
    computeGeometry();
}

void BaseItem::initShearMatrix(const QPointF &s)
{
    m_shearMatrix(0,0) = 1;
    m_shearMatrix(0,1) = s.x();
    m_shearMatrix(0,2) = 0;
    m_shearMatrix(0,3) = 0;

    m_shearMatrix(1,0) = s.y();
    m_shearMatrix(1,1) = 1;
    m_shearMatrix(1,2) = 0;
    m_shearMatrix(1,3) = 0;

    m_shearMatrix(2,0) = 0;
    m_shearMatrix(2,1) = 0;
    m_shearMatrix(2,2) = 1;
    m_shearMatrix(2,3) = 0;

    m_shearMatrix(3,0) = 0;
    m_shearMatrix(3,1) = 0;
    m_shearMatrix(3,2) = 0;
    m_shearMatrix(3,3) = 1;
}
}//namespace
#include "baseitem.moc"
