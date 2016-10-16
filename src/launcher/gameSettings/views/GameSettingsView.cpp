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
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include "GameSettingsView.h"

GameSettingsView::GameSettingsView() : BaseView("GameSettingsView"), ui(new Ui::GameSettingsView()),
                                       gameSettingsService(GameSettingsService::getInstance()) {

    Logger::debug(TAG, "GameSettingsView");

    ui->setupUi(this);

    connect(ui->pathBrowse, SIGNAL(clicked()), this, SLOT(onGamePathBrowse()));

    //TODO: Добавить хранение путей к кастомным аддонам армы

    //TODO: Добавить настройки лаунчера

    //TODO: Добавить оптимизацию настроек армы
}

GameSettingsView::~GameSettingsView() {

}

void GameSettingsView::onResume() {

    Logger::debug(TAG, "onResume");

    ui->name->addItems(gameSettingsService->getUserProfiles());
    ui->malloc->addItems(gameSettingsService->getMallocs());

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
    ui->priorityLaunch->setCurrentIndex(gameSettingsModel.getPriorityLaunch());

    if (!gameSettingsModel.getName().isEmpty()) {
        ui->check_name->setChecked(true);
        ui->name->setCurrentText(gameSettingsModel.getName());
    } else {
        ui->check_name->setChecked(false);
    }
    if (!gameSettingsModel.getMaxVRAM().isEmpty()) {
        ui->check_maxVRAM->setChecked(true);
        ui->maxVRAM->setCurrentText(gameSettingsModel.getMaxVRAM());
    } else {
        ui->check_maxVRAM->setChecked(false);
    }
    if (!gameSettingsModel.getMaxMem().isEmpty()) {
        ui->check_maxMem->setChecked(true);
        ui->maxMem->setCurrentText(gameSettingsModel.getMaxMem());
    } else {
        ui->check_maxMem->setChecked(false);
    }
    if (!gameSettingsModel.getCpuCount().isEmpty()) {
        ui->check_cpuCount->setChecked(true);
        ui->cpuCount->setCurrentText(gameSettingsModel.getCpuCount());
    } else {
        ui->check_cpuCount->setChecked(false);
    }
    if (!gameSettingsModel.getExThreads().isEmpty()) {
        ui->check_exThreads->setChecked(true);
        ui->exThreads->setCurrentText(gameSettingsModel.getExThreads());
    } else {
        ui->check_exThreads->setChecked(false);
    }
    if (!gameSettingsModel.getMalloc().isEmpty()) {
        ui->check_malloc->setChecked(true);
        ui->malloc->setCurrentText(gameSettingsModel.getMalloc());
    } else {
        ui->check_malloc->setChecked(false);
    }

    ui->addParameters->setText(gameSettingsModel.getAddParam());

    ui->gamePath->setText(gameSettingsModel.getGamePath());


    ui->launchParameters->setText(gameSettingsService->buildLaunchParams(gameSettingsModel).join('\n'));
}

void GameSettingsView::onStop() {

    Logger::debug(TAG, "onStop");

    saveSettings();

    ui->name->clear();
    ui->malloc->clear();
}

void GameSettingsView::saveSettings() {

    GameSettingsModel gameSettingsModel;
    gameSettingsModel.setWinxp(ui->winxp->isChecked());
    gameSettingsModel.setBattlEye(ui->battleEye->isChecked());
    gameSettingsModel.setEnableHT(ui->enableHT->isChecked());
    gameSettingsModel.setWindow(ui->window->isChecked());
    gameSettingsModel.setWorldEmpty(ui->worldEmpty->isChecked());
    gameSettingsModel.setNoLogs(ui->noLogs->isChecked());
    gameSettingsModel.setSkipIntro(ui->skipIntro->isChecked());
    gameSettingsModel.setShowScriptErrors(ui->showScriptErrors->isChecked());
    gameSettingsModel.setNosplash(ui->nosplash->isChecked());
    gameSettingsModel.setNoPause(ui->noPause->isChecked());
    gameSettingsModel.setNoCB(ui->noCB->isChecked());
    gameSettingsModel.setNoFilePatching(ui->noFilePatching->isChecked());
    gameSettingsModel.setPriorityLaunch(ui->priorityLaunch->currentIndex());
    gameSettingsModel.setGamePath(ui->gamePath->text());
    gameSettingsModel.setAddParam(ui->addParameters->text());

    if (ui->check_cpuCount->isChecked()) {
        gameSettingsModel.setCpuCount(ui->cpuCount->currentText());
    }
    if (ui->check_exThreads->isChecked()) {
        gameSettingsModel.setExThreads(ui->exThreads->currentText());
    }
    if (ui->check_malloc->isChecked()) {
        gameSettingsModel.setMalloc(ui->malloc->currentText());
    }
    if (ui->check_maxMem->isChecked()) {
        gameSettingsModel.setMaxMem(ui->maxMem->currentText());
    }
    if (ui->check_maxVRAM->isChecked()) {
        gameSettingsModel.setMaxVRAM(ui->maxVRAM->currentText());
    }
    if (ui->check_name->isChecked()) {
        gameSettingsModel.setName(ui->name->currentText());
    }

    gameSettingsService->save(gameSettingsModel);
}

void GameSettingsView::onGamePathBrowse() {

    QString gamePath = QFileDialog::getOpenFileName(
            this, QString(tr("Открыть исполняемый файл ArmA 3")), QString(), QString(tr("arma3.exe;;"))
    );

    if (gamePath.endsWith(QString("arma3.exe"))) {

        gameSettingsService->saveGamePath(gamePath);
        ui->gamePath->setText(gamePath);

        QString currentMalloc = ui->malloc->currentText();
        ui->malloc->clear();
        ui->malloc->addItems(gameSettingsService->getMallocs());
        ui->malloc->setCurrentText(currentMalloc);

    } else {
        QMessageBox::warning(this, tr("Ошибка!"), tr("Указан неверный путь к исполняемому файлу arma3.exe"));
    }
}
