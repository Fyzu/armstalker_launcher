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

#ifndef ARMSTALKER_LAUNCHER_LAUNCHER_PRESENTER_H
#define ARMSTALKER_LAUNCHER_LAUNCHER_PRESENTER_H

#include <QApplication>
#include <QTextStream>
#include <QFile>

#include "src/core/base/logger/Logger.h"
#include "src/core/base/presenter/BasePresenter.h"
#include "src/launcher/base/views/LauncherView.h"
#include "src/launcher/dashboard/views/DashboardView.h"
#include "src/launcher/gameSettings/views/GameSettingsView.h"

class LauncherView;

class LauncherPresenter : public BasePresenter {

Q_OBJECT

public:
    enum ViewType {
        DASHBOARD,
        GAME_SETTINGS
    };

    LauncherPresenter(LauncherView *launcherView);

    ~LauncherPresenter();

private:
    LauncherView *launcherView;
    DashboardView *dashBoardView = nullptr;
    GameSettingsView *gameSettingsView = nullptr;

private slots:

    void updateStyle();

    void onViewChange(int index);

};

#endif //ARMSTALKER_LAUNCHER_LAUNCHER_PRESENTER_H
