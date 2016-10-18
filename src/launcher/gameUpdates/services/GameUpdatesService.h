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

#ifndef ARMSTALKER_GAME_UPDATES_SERVICE_H
#define ARMSTALKER_GAME_UPDATES_SERVICE_H

#include <QObject>
#include <c++/memory>
#include <src/core/base/core/BaseCore.h>

class GameUpdatesService : public BaseCore, public QObject {

    Q_OBJECT

public:
    GameUpdatesService() : BaseCore("GameSettingsService"), QObject() {

    }

    ~GameUpdatesService() {

    }

    static GameUpdatesService *getInstance() {
        static std::shared_ptr<GameUpdatesService> _instance = std::make_shared<GameUpdatesService>();
        return _instance.get();
    }

private:
    static std::shared_ptr<GameUpdatesService> _instance;

    GameUpdatesService(const GameUpdatesService &) = delete;

    GameUpdatesService &operator=(const GameUpdatesService &) = delete;
public:


};

#endif //ARMSTALKER_GAME_UPDATES_SERVICE_H
