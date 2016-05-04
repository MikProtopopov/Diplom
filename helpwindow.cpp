// Copyright 2016, Protopopov Mikhail G. <mikprotopopov@yandex.ru>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "helpwindow.h"
#include "ui_helpwindow.h"

#include <QPushButton>
#include <QTextStream>
#include <QTextEdit>


HelpWindow::HelpWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpWindow)
{
    ui->setupUi(this);
//    ui->textBrowser->setSource(QUrl("docs/help.html"));
//    ui->textBrowser->setHtml("<h1>Hello</h1>");


    QFile f("docs/help.html");
    if (!f.open(QIODevice::ReadOnly)) return;

    QTextStream ts(&f);
    QString s = ts.readAll();
    f.close();

    ui->textBrowser->setHtml(s);
}

HelpWindow::~HelpWindow()
{
    delete ui;
}
