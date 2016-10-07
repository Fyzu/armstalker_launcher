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

#include <src/core/base/logger/Logger.h>
#include "GameSettingsView.h"

GameSettingsView::GameSettingsView() : BaseView("GameSettingsView"), ui(new Ui::GameSettingsView()),
                                       gameSettingsService(GameSettingsService::getInstance()) {

    Logger::debug(TAG, "GameSettingsView");

    ui->setupUi(this);

    //TODO: Добавить хранение путей к арме и аддонам армы
}

GameSettingsView::~GameSettingsView() {

}

void GameSettingsView::onResume() {

    Logger::debug(TAG, "onResume");

    //TODO: Получение списка профайлов

    //TODO: Получение списка malloc'ов

    GameSettingsModel gameSettingsModel = gameSettingsService->get();

    ui->battleEye->setChecked(gameSettingsModel.isBattlEye());
    ui->enableHT->setChecked(gameSettingsModel.isEnableHT());
    ui->window->setChecked(gameSettingsModel.isWindow());
    ui->worldEmpty->setChecked(gameSettingsModel.isWorldEmpty());
    ui->winxp->setChecked(gameSettingsModel.isWinxp());
    ui->noLogs->setChecked(gameSettingsModel.isNoLogs());
    ui->skipIntro->setChecked(gameSettingsModel.isSkipIntro());
    ui->showScriptErrors->setChecked(gameSettingsModel.isShowScriptErrors());
    ui->nosplash->setChecked(gameSettingsModel.isNosplash());
    ui->noPause->setChecked(gameSettingsModel.isNoPause());
    ui->noCB->setChecked(gameSettingsModel.isNoCB());
    ui->noFilePatching->setChecked(gameSettingsModel.isNoFilePatching());

    //TODO: добавить проверку на пустую строку, с результатом выбора чекбокса
    ui->name->setCurrentText(gameSettingsModel.getName());
    ui->maxVRAM->setCurrentText(gameSettingsModel.getMaxVRAM());
    ui->maxMem->setCurrentText(gameSettingsModel.getMaxMem());
    ui->cpuCount->setCurrentText(gameSettingsModel.getCpuCount());
    ui->exThreads->setCurrentText(gameSettingsModel.getExThreads());
    ui->malloc->setCurrentText(gameSettingsModel.getMalloc());

    ui->addParameters->setText(gameSettingsModel.getAddParam());
}

void GameSettingsView::onStop() {

}
