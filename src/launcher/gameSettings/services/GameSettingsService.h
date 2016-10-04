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

#ifndef ARMSTALKER_GAME_SETTINGS_SERVICE_H
#define ARMSTALKER_GAME_SETTINGS_SERVICE_H

#include <memory>
#include <src/launcher/gameSettings/models/GameSettingsModel.h>
#include <QtCore/QSettings>
#include <src/core/base/core/BaseCore.h>

#define SETTINGS_FILENAME "config.ini"

class GameSettingsService : public BaseCore {

public:
    GameSettingsService() : BaseCore("GameSettingsService") {
        settings = new QSettings(SETTINGS_FILENAME, QSettings::IniFormat);
        settings->beginGroup(TAG);
    }

    ~GameSettingsService() {
        delete settings;
    }

    static GameSettingsService *getInstance() {
        static std::shared_ptr<GameSettingsService> _instance = std::make_shared<GameSettingsService>();
        return _instance.get();
    }

private:
    static std::shared_ptr<GameSettingsService> _instance;

    QSettings *settings;

    GameSettingsService(const GameSettingsService &) = delete;

    GameSettingsService &operator=(const GameSettingsService &) = delete;

public:

    GameSettingsModel get() {
        GameSettingsModel settingsModel = GameSettingsModel();
        settingsModel.setAddParam(settings->value("addParam", "").toString());
        settingsModel.setBattlEye(settings->value("battleEye", "").toBool());
        settingsModel.setCpuCount(settings->value("cpuCount", "").toString());
        settingsModel.setEnableHT(settings->value("enableHT", "").toBool());
        settingsModel.setExThreads(settings->value("exThreads", "").toString());
        settingsModel.setMalloc(settings->value("malloc", "").toString());
        settingsModel.setMaxMem(settings->value("maxMem", "").toString());
        settingsModel.setMaxVRAM(settings->value("maxVRAM", "").toString());
        settingsModel.setName(settings->value("name", "").toString());
        settingsModel.setNoCB(settings->value("noCB", "").toBool());
        settingsModel.setNoFilePatching(settings->value("noFilePatching", "").toBool());
        settingsModel.setNoLogs(settings->value("noLogs", "").toBool());
        settingsModel.setNoPause(settings->value("noPause", "").toBool());
        settingsModel.setNosplash(settings->value("nosplash", "").toBool());
        settingsModel.setPriorityLaunch(settings->value("priorityLaunch", "").toInt());
        settingsModel.setShowScriptErrors(settings->value("showScriptErrors", "").toBool());
        settingsModel.setSkipIntro(settings->value("skipIntro", "").toBool());
        settingsModel.setWindow(settings->value("window", "").toBool());
        settingsModel.setWinxp(settings->value("winxp", "").toBool());
        settingsModel.setWorldEmpty(settings->value("worldEmpty", "").toBool());

        return settingsModel;
    }

    void save(const GameSettingsModel & settingsModel) {
        settings->setValue("addParam", settingsModel.getAddParam());
        settings->setValue("cpuCount", settingsModel.getCpuCount());
        settings->setValue("exThreads", settingsModel.getExThreads());
        settings->setValue("malloc", settingsModel.getMalloc());
        settings->setValue("maxMem", settingsModel.getMaxMem());
        settings->setValue("maxVRAM", settingsModel.getMaxVRAM());
        settings->setValue("name", settingsModel.getName());
        settings->setValue("priorityLaunch", settingsModel.getPriorityLaunch());
        settings->setValue("battleEye", settingsModel.isBattlEye());
        settings->setValue("enableHT", settingsModel.isEnableHT());
        settings->setValue("noCB", settingsModel.isNoCB());
        settings->setValue("noFilePatching", settingsModel.isNoFilePatching());
        settings->setValue("noLogs", settingsModel.isNoLogs());
        settings->setValue("noPause", settingsModel.isNoPause());
        settings->setValue("nosplash", settingsModel.isNosplash());
        settings->setValue("showScriptErrors", settingsModel.isShowScriptErrors());
        settings->setValue("skipIntro", settingsModel.isSkipIntro());
        settings->setValue("window", settingsModel.isWindow());
        settings->setValue("winxp", settingsModel.isWinxp());
        settings->setValue("worldEmpty", settingsModel.isWorldEmpty());
        settings->sync();
    }

};

#endif //ARMSTALKER_GAME_SETTINGS_SERVICE_H
