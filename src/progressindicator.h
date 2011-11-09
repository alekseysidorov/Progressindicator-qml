/****************************************************************************
 *  progressindicator.h
 *
 *  Copyright (c) 2011 by Sidorov Aleksey <sauron@citadelspb.com>
 *
 ***************************************************************************
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
*****************************************************************************/

#ifndef PROGRESSINDICATOR_H
#define PROGRESSINDICATOR_H
#include <QDeclarativeItem>

class ProgressIndicatorBase : public QDeclarativeItem
{
	Q_OBJECT

	Q_PROPERTY(int angle READ angle WRITE setAngle)
	Q_PROPERTY(int leafCount READ leafCount WRITE setLeafCount NOTIFY leafCountChanged)
public:
	ProgressIndicatorBase(QDeclarativeItem *parent = 0);
	virtual void paint(QPainter *p, const QStyleOptionGraphicsItem *i, QWidget *w);
	QColor color() const;
	void setColor(const QColor &color);
	int leafCount() const;
	void setLeafCount(int count);
	int angle() const;
	void setAngle(int angle);
signals:
	void colorChanged();
	void leafCountChanged();
private:
	int m_angle;
	QColor m_color;
	int m_leafCount;
	qreal m_delta;
	qreal m_minimumOpacity;
};

#endif // PROGRESSINDICATOR_H
