/****************************************************************************
 *  progressindicator.cpp
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

#include "progressindicator.h"
#include <QPainter>

ProgressIndicatorBase::ProgressIndicatorBase(QDeclarativeItem *parent) :
	QDeclarativeItem(parent),
	m_angle(0),
	m_color(Qt::black),
	m_leafCount(12),
	m_delta(30),
	m_minimumOpacity(0.3)
{
	setFlag(QGraphicsItem::ItemHasNoContents, false);
}

void ProgressIndicatorBase::paint(QPainter *p, const QStyleOptionGraphicsItem *i, QWidget *w)
{
	p->save();

	int width = qMin(this->width(), this->height());

	p->setRenderHint(QPainter::Antialiasing);

	int outerRadius = (width-1)*0.5;
	int innerRadius = (width-1)*0.5*0.38;

	int capsuleHeight = outerRadius - innerRadius;
	int capsuleWidth  = (width > 32 ) ? capsuleHeight *.23 : capsuleHeight *.35;
	int capsuleRadius = capsuleWidth/2;

	for (int i = 0; i < m_leafCount; i++) {
		QColor color = m_color;
		color.setAlphaF(qMax(m_minimumOpacity, qreal((int(i * m_delta) + m_angle) % 360) / 360));
		p->setPen(Qt::NoPen);
		p->setBrush(color);
		p->save();
		p->translate(boundingRect().center());
		p->rotate(i*m_delta);
		p->drawRoundedRect(-capsuleWidth*0.5, -(innerRadius+capsuleHeight), capsuleWidth, capsuleHeight, capsuleRadius, capsuleRadius);
		p->restore();
	}

	p->restore();
}

QColor ProgressIndicatorBase::color() const
{
	return m_color;
}

void ProgressIndicatorBase::setColor(const QColor &color)
{
	if (m_color == color)
		return;
	m_color = color;
	emit colorChanged();
	update();
}

int ProgressIndicatorBase::leafCount() const
{
	return m_leafCount;
}

void ProgressIndicatorBase::setLeafCount(int count)
{
	if (m_leafCount == count)
		return;
	m_leafCount = count;
	m_delta = 360 / m_leafCount;
	emit leafCountChanged();
	update();
}

int ProgressIndicatorBase::angle() const
{
	return m_angle;
}

void ProgressIndicatorBase::setAngle(int angle)
{
	if (m_angle == angle)
		return;
	m_angle = angle;
	update();
}
