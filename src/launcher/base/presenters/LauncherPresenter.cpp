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

#include "LauncherPresenter.h"

LauncherPresenter::LauncherPresenter(LauncherView *launcherView)
        : launcherView(launcherView), BasePresenter("LauncherPresenter") {

    Logger::debug(TAG, "LauncherPresenter");

    connect(launcherView, SIGNAL(viewChange(int)), this, SLOT(onViewChange(int)));

    updateStyle();
    onViewChange(DASHBOARD);
}

LauncherPresenter::~LauncherPresenter() {

    Logger::debug(TAG, "~LauncherPresenter");

    delete dashBoardView;
    delete gameSettingsView;
}

void LauncherPresenter::updateStyle() {

    Logger::debug(TAG, "updateStyle");

    QFile f(STYLE_PATH);
    if (f.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
        f.close();
    } else {
        Logger::fatal(TAG, "updateStyle");
    }
}

void LauncherPresenter::onViewChange(int viewTypeIndex) {

    Logger::debug(TAG, "onViewChange") << "viewIndex -" << viewTypeIndex;

    switch (viewTypeIndex) {
        case DASHBOARD:
            if (dashBoardView == nullptr) {
                dashBoardView = new DashboardView();
                launcherView->addView(dashBoardView);

                connect(dashBoardView, SIGNAL(viewChange(int)), this, SLOT(onViewChange(int)));
            }
            launcherView->showView(dashBoardView);
            break;
        case GAME_SETTINGS:
            if (gameSettingsView == nullptr) {
                gameSettingsView = new GameSettingsView();
                launcherView->addView(gameSettingsView);
            }
            launcherView->showView(gameSettingsView);
            break;
        case GAME_UPDATES:
            if (gameUpdatesView == nullptr) {
                gameUpdatesView = new GameUpdatesView();
                launcherView->addView(gameUpdatesView);
            }
            launcherView->showView(gameUpdatesView);
            break;
        default:
            return;
    }
}
