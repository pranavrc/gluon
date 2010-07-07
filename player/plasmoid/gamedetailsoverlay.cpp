/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (C) 2010 Shantanu Tushar <jhahoneyk@gmail.com>
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

#include "gamedetailsoverlay.h"
#include "views/highscoresview.h"
#include "views/achievementsview.h"
#include "views/commentsview.h"

#include <QGraphicsLinearLayout>

#include <Plasma/TabBar>
#include <Plasma/IconWidget>
#include <KIcon>

GameDetailsOverlay::GameDetailsOverlay(QGraphicsItem* parent, Qt::WindowFlags wFlags)
    : Overlay(parent, wFlags)
{
    m_tabBar = new Plasma::TabBar(this);

    m_backButton = new Plasma::IconWidget(KIcon("go-previous-view"), i18n("Back"), this);
    m_backButton->setOrientation(Qt::Horizontal);
    m_backButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(m_backButton, SIGNAL(activated()), SIGNAL(back()));

    m_highScoresView = new HighScoresView(this);
    m_achievementsView = new AchievementsView(this);
    m_commentsView = new CommentsView(this);

    m_tabBar->addTab(KIcon("games-highscores"), i18n("High Scores"), m_highScoresView);
    m_tabBar->addTab(KIcon("games-endturn"), i18n("Achievements"), m_achievementsView);
    m_tabBar->addTab(KIcon ("text-plain"), i18n("Comments"), m_commentsView);

    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Vertical);
    layout->addItem(m_backButton);
    layout->addItem(m_tabBar);
    setLayout(layout);
}