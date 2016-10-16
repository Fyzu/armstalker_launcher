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

#include <src/launcher/base/presenters/LauncherPresenter.h>

#include "DashboardView.h"

DashboardView::DashboardView() : BaseView("DashboardView"), ui(new Ui::DashboardView) {

    Logger::debug(TAG, "DashboardView");

    ui->setupUi(this);

    connect(ui->gameSettingsButton, &QPushButton::clicked, [&]() {
        emit viewChange(LauncherPresenter::GAME_SETTINGS);
    });
    connect(ui->settingsButton, &QPushButton::clicked, [&]() {

    });
    connect(ui->statsButton, &QPushButton::clicked, [&]() {

    });
    connect(ui->serversButton, &QPushButton::clicked, [&]() {
        //emit viewChange(LauncherPresenter::);
    });
    connect(ui->updatesButton, &QPushButton::clicked, [&]() {
        //emit viewChange(LauncherPresenter::);
    });
    connect(ui->vkButton, &QPushButton::clicked, [&]() {
        QDesktopServices::openUrl(QUrl("https://vk.com/armstalker_online"));

    });
    connect(ui->forumButton, &QPushButton::clicked, [&]() {
        QDesktopServices::openUrl(QUrl("http://armstalker.ru/forum/"));
    });
}

DashboardView::~DashboardView() {

    Logger::debug(TAG, "~DashboardView");

    delete ui;
}

void DashboardView::onResume() {

    Logger::debug(TAG, "onResume");

}

void DashboardView::onStop() {

}
