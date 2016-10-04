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

#ifndef ARMSTALKER_GAME_SETTINGS_MODEL_H
#define ARMSTALKER_GAME_SETTINGS_MODEL_H

#include <QtCore/QString>
#include <QDataStream>

class GameSettingsModel {

private:
    QString addParam;
    QString name;
    bool window;
    bool noPause;
    bool showScriptErrors;
    bool noFilePatching;
    bool battlEye;
    int priorityLaunch;
    QString maxMem;
    QString maxVRAM;
    QString cpuCount;
    QString exThreads;
    QString malloc;
    bool enableHT;
    bool winxp;
    bool noCB;
    bool nosplash;
    bool skipIntro;
    bool worldEmpty;
    bool noLogs;

public:

    GameSettingsModel() {}

    GameSettingsModel(const QString &addParam, const QString &name, bool window, bool noPause, bool showScriptErrors,
                      bool noFilePatching, bool battlEye, int priorityLaunch, const QString &maxMem,
                      const QString &maxVRAM, const QString &cpuCount, const QString &exThreads, const QString &malloc,
                      bool enableHT, bool winxp, bool noCB, bool nosplash, bool skipIntro, bool worldEmpty, bool noLogs)
            : addParam(addParam), name(name), window(window), noPause(noPause), showScriptErrors(showScriptErrors),
              noFilePatching(noFilePatching), battlEye(battlEye), priorityLaunch(priorityLaunch), maxMem(maxMem),
              maxVRAM(maxVRAM), cpuCount(cpuCount), exThreads(exThreads), malloc(malloc), enableHT(enableHT),
              winxp(winxp), noCB(noCB), nosplash(nosplash), skipIntro(skipIntro), worldEmpty(worldEmpty),
              noLogs(noLogs) {}

    bool operator==(const GameSettingsModel &rhs) const {
        return addParam == rhs.addParam &&
               name == rhs.name &&
               window == rhs.window &&
               noPause == rhs.noPause &&
               showScriptErrors == rhs.showScriptErrors &&
               noFilePatching == rhs.noFilePatching &&
               battlEye == rhs.battlEye &&
               priorityLaunch == rhs.priorityLaunch &&
               maxMem == rhs.maxMem &&
               maxVRAM == rhs.maxVRAM &&
               cpuCount == rhs.cpuCount &&
               exThreads == rhs.exThreads &&
               malloc == rhs.malloc &&
               enableHT == rhs.enableHT &&
               winxp == rhs.winxp &&
               noCB == rhs.noCB &&
               nosplash == rhs.nosplash &&
               skipIntro == rhs.skipIntro &&
               worldEmpty == rhs.worldEmpty &&
               noLogs == rhs.noLogs;
    }

    bool operator!=(const GameSettingsModel &rhs) const {
        return !(rhs == *this);
    }

    friend QDataStream &operator<<(QDataStream &out, const GameSettingsModel &model) {
        out << model.addParam << model.name << model.window << model.noPause << model.showScriptErrors
            << model.noFilePatching << model.battlEye << model.priorityLaunch << model.maxMem << model.maxVRAM
            << model.cpuCount << model.exThreads << model.malloc << model.enableHT << model.winxp << model.noCB
            << model.nosplash << model.skipIntro << model.worldEmpty << model.noLogs;
        return out;
    }

    friend QDataStream &operator>>(QDataStream &in, GameSettingsModel &model) {
        in >> model.addParam >> model.name >> model.window >> model.noPause >> model.showScriptErrors
           >> model.noFilePatching >> model.battlEye >> model.priorityLaunch >> model.maxMem >> model.maxVRAM
           >> model.cpuCount >> model.exThreads >> model.malloc >> model.enableHT >> model.winxp >> model.noCB
           >> model.nosplash >> model.skipIntro >> model.worldEmpty >> model.noLogs;
        return in;
    }

    const QString &getAddParam() const {
        return addParam;
    }

    void setAddParam(const QString &addParam) {
        GameSettingsModel::addParam = addParam;
    }

    const QString &getName() const {
        return name;
    }

    void setName(const QString &name) {
        GameSettingsModel::name = name;
    }

    bool isWindow() const {
        return window;
    }

    void setWindow(bool window) {
        GameSettingsModel::window = window;
    }

    bool isNoPause() const {
        return noPause;
    }

    void setNoPause(bool noPause) {
        GameSettingsModel::noPause = noPause;
    }

    bool isShowScriptErrors() const {
        return showScriptErrors;
    }

    void setShowScriptErrors(bool showScriptErrors) {
        GameSettingsModel::showScriptErrors = showScriptErrors;
    }

    bool isNoFilePatching() const {
        return noFilePatching;
    }

    void setNoFilePatching(bool noFilePatching) {
        GameSettingsModel::noFilePatching = noFilePatching;
    }

    bool isBattlEye() const {
        return battlEye;
    }

    void setBattlEye(bool battlEye) {
        GameSettingsModel::battlEye = battlEye;
    }

    int getPriorityLaunch() const {
        return priorityLaunch;
    }

    void setPriorityLaunch(int priorityLaunch) {
        GameSettingsModel::priorityLaunch = priorityLaunch;
    }

    const QString &getMaxMem() const {
        return maxMem;
    }

    void setMaxMem(const QString &maxMem) {
        GameSettingsModel::maxMem = maxMem;
    }

    const QString &getMaxVRAM() const {
        return maxVRAM;
    }

    void setMaxVRAM(const QString &maxVRAM) {
        GameSettingsModel::maxVRAM = maxVRAM;
    }

    const QString &getCpuCount() const {
        return cpuCount;
    }

    void setCpuCount(const QString &cpuCount) {
        GameSettingsModel::cpuCount = cpuCount;
    }

    const QString &getExThreads() const {
        return exThreads;
    }

    void setExThreads(const QString &exThreads) {
        GameSettingsModel::exThreads = exThreads;
    }

    const QString &getMalloc() const {
        return malloc;
    }

    void setMalloc(const QString &malloc) {
        GameSettingsModel::malloc = malloc;
    }

    bool isEnableHT() const {
        return enableHT;
    }

    void setEnableHT(bool enableHT) {
        GameSettingsModel::enableHT = enableHT;
    }

    bool isWinxp() const {
        return winxp;
    }

    void setWinxp(bool winxp) {
        GameSettingsModel::winxp = winxp;
    }

    bool isNoCB() const {
        return noCB;
    }

    void setNoCB(bool noCB) {
        GameSettingsModel::noCB = noCB;
    }

    bool isNosplash() const {
        return nosplash;
    }

    void setNosplash(bool nosplash) {
        GameSettingsModel::nosplash = nosplash;
    }

    bool isSkipIntro() const {
        return skipIntro;
    }

    void setSkipIntro(bool skipIntro) {
        GameSettingsModel::skipIntro = skipIntro;
    }

    bool isWorldEmpty() const {
        return worldEmpty;
    }

    void setWorldEmpty(bool worldEmpty) {
        GameSettingsModel::worldEmpty = worldEmpty;
    }

    bool isNoLogs() const {
        return noLogs;
    }

    void setNoLogs(bool noLogs) {
        GameSettingsModel::noLogs = noLogs;
    }
};

#endif //ARMSTALKER_GAME_SETTINGS_MODEL_H
