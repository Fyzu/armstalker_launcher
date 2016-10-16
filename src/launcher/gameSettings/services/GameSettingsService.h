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
#include <QtCore/QDir>
#include <QStandardPaths>
#include <windows.h>
#include <tchar.h>
#include <QtCore/QTextCodec>

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

    QString documentsPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

    GameSettingsService(const GameSettingsService &) = delete;

    GameSettingsService &operator=(const GameSettingsService &) = delete;

public:

    GameSettingsModel get() {
        GameSettingsModel settingsModel = GameSettingsModel();
        settingsModel.setAddParam(settings->value("addParam", "").toString());
        settingsModel.setBattlEye(settings->value("battleEye", false).toBool());
        settingsModel.setCpuCount(settings->value("cpuCount", "").toString());
        settingsModel.setEnableHT(settings->value("enableHT", false).toBool());
        settingsModel.setExThreads(settings->value("exThreads", "").toString());
        settingsModel.setMalloc(settings->value("malloc", "").toString());
        settingsModel.setMaxMem(settings->value("maxMem", "").toString());
        settingsModel.setMaxVRAM(settings->value("maxVRAM", "").toString());
        settingsModel.setName(settings->value("name", "").toString());
        settingsModel.setNoCB(settings->value("noCB", false).toBool());
        settingsModel.setNoFilePatching(settings->value("noFilePatching", false).toBool());
        settingsModel.setNoLogs(settings->value("noLogs", "").toBool());
        settingsModel.setNoPause(settings->value("noPause", false).toBool());
        settingsModel.setNosplash(settings->value("nosplash", false).toBool());
        settingsModel.setPriorityLaunch(settings->value("priorityLaunch", 3).toInt());
        settingsModel.setShowScriptErrors(settings->value("showScriptErrors", false).toBool());
        settingsModel.setSkipIntro(settings->value("skipIntro", false).toBool());
        settingsModel.setWindow(settings->value("window", false).toBool());
        settingsModel.setWinxp(settings->value("winxp", false).toBool());
        settingsModel.setWorldEmpty(settings->value("worldEmpty", false).toBool());
        settingsModel.setGamePath(settings->value("gamePath", "").toString());

        return settingsModel;
    }

    void save(const GameSettingsModel &settingsModel) {
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
        settings->setValue("gamePath", settingsModel.getGamePath());
        settings->sync();
    }

    QStringList getUserProfiles() {
        QStringList names = QDir(documentsPath + "/Arma 3 - Other Profiles").entryList(QDir::Dirs);
        for (int j = 0; j < names.size(); j++) {
            if (names.at(j) == "." || names.at(j) == "..") {
                names.removeAt(j);
                j--;
            }
        }

        return names;
    }

    QStringList getMallocs() {
        QString gamePath = settings->value("gamePath", "").toString().replace("arma3.exe", "");
        QStringList mallocs = QDir(gamePath.append("Dll")).entryList(QDir::Files);
        for (int j = 0; j < mallocs.size(); j++) {
            if (mallocs[j].contains(".dll")) {
                mallocs[j].remove(".dll");
            } else {
                mallocs.removeAt(j--);
            }
        }

        return mallocs;
    }

    void saveGamePath(QString gamePath) {
        settings->setValue("gamePath", gamePath);
        settings->sync();
    }

    QString getGameVersion() {

        QString gameExePath = settings->value("gamePath", "").toString();

        // Получаем версию установленной игры
        if (!gameExePath.isEmpty()) {
            LPCWSTR lpszFilePath = (LPCWSTR) gameExePath.utf16();
            DWORD dwDummy;

            // Получаем размер версии файла
            DWORD dwFVISize = GetFileVersionInfoSizeW(lpszFilePath, &dwDummy);
            if (dwFVISize == 0) {
                Logger::warning(TAG, "getGameVersion") << "dwFVISize = 0";
                return "";
            }
            // Создаем байтовый массив с этим размером
            BYTE *lpVersionInfo = new BYTE[dwFVISize];

            // Получаем информацию о версии файла
            if (!GetFileVersionInfoW(lpszFilePath, 0, dwFVISize, lpVersionInfo)) {
                delete[] lpVersionInfo;
                Logger::warning(TAG, "getGameVersion") << "file version info";
                return "";
            }

            // Получаем собственно версию
            UINT uLen;
            VS_FIXEDFILEINFO *lpFfi;
            VerQueryValue(lpVersionInfo, TEXT("\\"), (LPVOID *) &lpFfi, &uLen);
            DWORD dwFileVersionMS = lpFfi->dwFileVersionMS;
            DWORD dwFileVersionLS = lpFfi->dwFileVersionLS;
            delete[] lpVersionInfo;

            // Получаем числа версий в ячейках
            DWORD dwLeftMost = HIWORD(dwFileVersionMS);
            DWORD dwSecondLeft = LOWORD(dwFileVersionMS);
            DWORD dwSecondRight = HIWORD(dwFileVersionLS);
            DWORD dwRightMost = LOWORD(dwFileVersionLS);

            // Преобразуем в строку
            return QString::number(dwLeftMost) + '.' + QString::number(dwSecondLeft) + '.' +
                   QString::number(dwSecondRight) + '.' + QString::number(dwRightMost);
        } else {
            Logger::warning(TAG, "getGameVersion") << "game path empty";
            return "";
        }
    }

    QString getModVersion() {

        QString version;
        QString fileName = settings->value("gamePath", "").toString()
                .remove("arma3.exe")
                .append("@WARZONE/mod.cpp");

        QFile file(fileName);
        // Открываем файл и получаем информацию
        if (file.open(QFile::ReadOnly | QFile::Text)) {
            QTextCodec *defaultTextCodec = QTextCodec::codecForName("CP1251");
            QTextDecoder *decoder = new QTextDecoder(defaultTextCodec);
            QString str = decoder->toUnicode(file.readAll());
            int index = str.indexOf(QString("version = "));
            if (index > -1) {
                for (index = index + 11; str[index] != '"' && index < 100; index++)
                    version.append(str[index]);
                file.close();
            }
        }

        return version;
    }

    QStringList buildLaunchParams(const GameSettingsModel &settingsModel) {

        Logger::warning(TAG, "buildLaunchParams");

        QStringList launchParams;

        if (!settingsModel.getName().isEmpty()) {
            launchParams.append("-name=" + settingsModel.getName());
        }
        if (!settingsModel.getMalloc().isEmpty()) {
            launchParams.append("-malloc=" + settingsModel.getMalloc());
        }
        if (settingsModel.isShowScriptErrors()) {
            launchParams.append("-showScriptErrors");
        }
        if (settingsModel.isNoPause()) {
            launchParams.append("-noPause");
        }
        if (settingsModel.isNoFilePatching()) {
            launchParams.append("-filePathcing");
        }
        if (settingsModel.isWindow()) {
            launchParams.append("-window");
        }
        if (!settingsModel.getMaxMem().isEmpty()) {
            launchParams.append("-maxMem=" + QString::number(settingsModel.getMaxMem().toInt() - 1));
        }
        if (!settingsModel.getMaxVRAM().isEmpty()) {
            launchParams.append("-maxVRAM=" + QString::number(settingsModel.getMaxVRAM().toInt() - 1));
        }
        if (!settingsModel.getCpuCount().isEmpty()) {
            launchParams.append("-cpuCount=" + settingsModel.getCpuCount());
        }
        if (!settingsModel.getExThreads().isEmpty()) {
            launchParams.append("-exThreads=" + settingsModel.getExThreads());
        }
        if (settingsModel.isEnableHT()) {
            launchParams.append("-enableHT");
        }
        if (settingsModel.isWinxp()) {
            launchParams.append("-winxp");
        }
        if (settingsModel.isNoCB()) {
            launchParams.append("-noCB");
        }
        if (settingsModel.isNosplash()) {
            launchParams.append("-nosplash");
        }
        if (settingsModel.isSkipIntro()) {
            launchParams.append("-skipIntro");
        }
        if (settingsModel.isWorldEmpty()) {
            launchParams.append("-world=empty");
        }
        if (settingsModel.isNoLogs()) {
            launchParams.append("-noLogs");
        }

        // Сделать добавление
        launchParams.append("-mod=@WARZONE;");
        launchParams.append("-mod=@task_force_radio;");

        /*launchParams.append("-connect=" + ui->serverIP->text());
        launchParams.append("-port=" + ui->serverPort->text());*/

        if (!settingsModel.getAddParam().isEmpty()) {
            QStringList addParams = settingsModel.getAddParam().split(' ');
            for (QString addParam : addParams) {
                if (!addParam.isEmpty() && addParam.startsWith('-')) {
                    launchParams.append(addParam);
                }
            }
        }

        return launchParams;
    }
};

#endif //ARMSTALKER_GAME_SETTINGS_SERVICE_H
