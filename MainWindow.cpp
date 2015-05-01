/* MainWindow.cpp
Copyright (c) 2015 by Michael Zahniser

Endless Sky is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later version.

Endless Sky is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.  See the GNU General Public License for more details.
*/

#include "MainWindow.h"

#include "DetailView.h"
#include "GalaxyView.h"
#include "Map.h"
#include "SystemView.h"

#include <QHBoxLayout>
#include <QSizePolicy>
#include <QTabWidget>

#include <string>

using namespace std;



MainWindow::MainWindow(Map &map, QWidget *parent)
    : QMainWindow(parent), map(map)
{
    QHBoxLayout *layout = new QHBoxLayout;
    QWidget *box = new QWidget(this);
    box->setLayout(layout);
    setCentralWidget(box);

    DetailView *detailView = new DetailView(map, box);
    detailView->setMinimumWidth(300);
    layout->addWidget(detailView);

    QTabWidget *tabs = new QTabWidget(box);
    QSizePolicy policy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tabs->setSizePolicy(policy);
    layout->addWidget(tabs);

    SystemView *systemView = new SystemView(detailView, tabs, tabs);
    auto it = map.Systems().find("Sol");
    if(it != map.Systems().end())
        systemView->Select(&it->second);

    GalaxyView *galaxyView = new GalaxyView(map, systemView, tabs, tabs);

    tabs->addTab(galaxyView, "Galaxy");
    tabs->addTab(systemView, "System");
}

MainWindow::~MainWindow()
{
}
