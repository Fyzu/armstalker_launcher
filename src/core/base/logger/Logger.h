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

#ifndef ARMSTALKER_LOGGER_H
#define ARMSTALKER_LOGGER_H

#include <QMessageLogger>
#include <QDebug>



class Logger {

public:

    static void init() {
        qSetMessagePattern(
            "[%{time dd.MM.yyyy h:mm:ss}]"
            "%{file}::%{function}/"
            "%{if-debug}D%{endif}%{if-info}I%{endif}%{if-warning}W%{endif}%{if-critical}C%{endif}%{if-fatal}F%{endif}"
            ": %{message}"
        );
    }

    static QDebug debug(const char * file = 0, const char * function = 0) {
        return QMessageLogger(file, 0, function).debug();
    }
    static QDebug info(const char * file = 0, const char * function = 0) {
        return QMessageLogger(file, 0, function).info();
    }

    static QDebug warning(const char * file = 0, const char * function = 0) {
        return QMessageLogger(file, 0, function).warning();
    }

    static QDebug critical(const char * file = 0, const char * function = 0) {
        return QMessageLogger(file, 0, function).critical();
    }

    static void fatal(const char * file, const char * function, const char * message = 0) {
        QMessageLogger(file, 0, function).fatal(message);
    }
};


#endif //ARMSTALKER_LOGGER_H
