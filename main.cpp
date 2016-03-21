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

#include "diplom.h"
#include "startwindow.h"
#include "rastrmanipulation.h"
#include <QApplication>
#include <QSizePolicy>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Diplom diplom;
    StartWindow sWindow;

    QObject::connect(&sWindow, SIGNAL(newParametersSet(int xInt, int yInt)),
                     &diplom, SLOT(acceptParameters(int xInt, int yInt)));

    diplom.show();

    return a.exec();
}
