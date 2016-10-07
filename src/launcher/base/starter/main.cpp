/***************************************************************************
 * This file is part of ArmSTALKER.
 *
 * ArmSTALKER is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ArmSTALKER is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ArmSTALKER. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include <QApplication>

#include "src/core/base/logger/Logger.h"
#include "src/launcher/base/views/LauncherView.h"

#define STARTER "Starter"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    Logger::init();

    Logger::info(STARTER, "main") << "system locale -" << QLocale::system().name();

    LauncherView launcherView;
    launcherView.show();

    int execCode = a.exec();

    Logger::info(STARTER, "main") << "application finish with code -" << execCode;

    return execCode;
}