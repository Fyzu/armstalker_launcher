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

#ifndef VIEW_MANAGER_H
#define VIEW_MANAGER_H

#include <QObject>
#include <QStackedWidget>
#include <QEasingCurve>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

class ViewManager : protected QStackedWidget, public BaseCore {

    Q_OBJECT

public:
    enum Direction {
        LEFT_TO_RIGHT,
        RIGHT_TO_LEFT,
        TOP_TO_BOTTOM,
        BOTTOM_TO_TOP,
        AUTOMATIC
    };

    ViewManager(QWidget *parent = 0);

    ~ViewManager();

    void setAnimationSpeed(int animationSpeed);

    void setAnimationType(QEasingCurve::Type animationType);

    void setIsVertical(bool isVertical);

    void showView(BaseView *view, enum Direction direction = AUTOMATIC);

    BaseView *getView(int index);

    BaseView *currentView();

    void addView(BaseView *view);

private:
    int animationSpeed = 500;
    enum QEasingCurve::Type animationType = QEasingCurve::OutBack;
    bool isVertical = false;

    BaseView *nextView;
    bool isActive = false;

public slots:

    void showView(int index);

signals:

    void changeViewFinished(int currentView);

protected slots:

    void animationFinish();
};

#endif // VIEW_MANAGER_H