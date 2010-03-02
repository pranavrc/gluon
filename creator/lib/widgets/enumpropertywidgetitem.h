/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef GLUONCREATOR_ENUMPROPERTYWIDGETITEM_H
#define GLUONCREATOR_ENUMPROPERTYWIDGETITEM_H

#include "propertywidgetitem.h"

namespace GluonCreator
{
class EnumPWIPrivate;
    class EnumPropertyWidgetItem : public PropertyWidgetItem
    {
        Q_OBJECT
        public:
            EnumPropertyWidgetItem(const QString &typeName, QWidget* parent = 0, Qt::WindowFlags f = 0);
            ~EnumPropertyWidgetItem();

            virtual PropertyWidgetItem* instantiate();
            virtual QList< QString > supportedDataTypes() const;

        public slots:
            virtual void setEditObject(QObject* editThis);
            virtual void setEditValue(const QVariant& value);
            virtual void indexChanged(int newIndex);
            
        private:
            EnumPWIPrivate * d;
    };
}

#endif // GLUONCREATOR_ENUMPROPERTYWIDGETITEM_H