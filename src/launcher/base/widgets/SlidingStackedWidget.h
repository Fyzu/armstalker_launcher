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

#ifndef SLIDING_STACKED_WIDGET_H
#define SLIDING_STACKED_WIDGET_H

#include <QStackedWidget>
#include <QEasingCurve>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

class SlidingStackedWidget : public QStackedWidget {

    Q_OBJECT

public:
    enum Direction {
        LEFT_TO_RIGHT,
        RIGHT_TO_LEFT,
        TOP_TO_BOTTOM,
        BOTTOM_TO_TOP,
        AUTOMATIC
    };

    SlidingStackedWidget(QWidget *parent = 0);

    ~SlidingStackedWidget();

    void setAnimationSpeed(int animationSpeed);

    void setAnimationType(QEasingCurve::Type animationType);

    void setIsVertical(bool isVertical);

protected:
    void showWidget(QWidget *widget, enum Direction direction = AUTOMATIC);

private:
    int animationSpeed;
    enum QEasingCurve::Type animationType;
    bool isVertical;
    int nextIndex;
    QPoint pointNow;
    bool isActive;

public slots:

    void showWidget(int index);

signals:

    void animationFinished();

protected slots:

    void animationFinish();
};

#endif // SLIDING_STACKED_WIDGET_H