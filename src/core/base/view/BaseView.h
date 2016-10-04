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

#ifndef ARMSTALKER_LAUNCHER_BASE_VIEW_H
#define ARMSTALKER_LAUNCHER_BASE_VIEW_H

#include "src/core/base/core/BaseCore.h"
#include <QObject>

class BaseView : public BaseCore {

public:
    BaseView(const char *className) : BaseCore(className) {
        QObject *viewObject = dynamic_cast<QObject*>(this);
        QObject::connect(viewObject, SIGNAL(resume()), viewObject, SLOT(onResume()));
    }

    virtual void resume() = 0;
    virtual void stop() = 0;

protected:
    virtual void onResume() = 0;
    virtual void onStop() = 0;

    void init() {
    }

};

#endif //ARMSTALKER_LAUNCHER_BASE_VIEW_H
